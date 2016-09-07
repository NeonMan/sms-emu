#include "bios-menu.h"
#include <sms/console.h>
#include <sms/sms.h>
#include <crc/crc16-ccitt.h>

uint8_t rom_buffer [ROM_BUFFER_SIZE];
uint8_t code_buffer[ROM_CODE_BUFFER_SIZE];
 
/**
 * @brief Signature mark for RAM loadable code.
 * Bootloader code searches for this signature at the end of the RAM-loaded
 * function. Any code beyond this point is not guaranteed to be available.
 */
#define RAM_CODE_SIGNATURE \
  __asm \
      jr LABEL \
      .ascii "YAP!" \
    LABEL: \
  __endasm;
  
/** Makes a jump to the chainload code.
 *
 *  This function takes the same parameters as boot_jump and exists only
 *  to receive the stack parameters for boot_jump and immediatly jump to
 *  its memory copy .
 *
 *  @param address reset verctor address, 0x0000 for regular ROMS
 *  @param io      value of the media selector register.
 */
static void bootcode_call(uint16_t address, uint8_t io){
  (void) address; /*                                   */
  (void) io;      /* <-- Remove 'unused param' warning */
  __asm__("JP _code_buffer");
}

/** Bootloader jump code.
 *
 *  This function is copied into memory then executed from there. It must give
 *  the IO chip its final config like disable the BIOS, enable ROM madia 
 *  (cartridge, card, expansion, none) and jump to the new program entry point
 *  (Usually 0x0000 for ROMs).
 *
 *  Warning!
 *  Since this code is copied to ram, the resulting assembler must be
 *  relocatable and not dependant on ROM contents beyond BIOS deactivation, so
 *  function calls are forbidden and any kind of (non-local) variable access is
 *  discouraged.
 *
 *  @param address Address to jump to load the program, usually 0x0000.
 *  @param io      Value of the media selector register.
 */
static void boot_jump(uint16_t address, uint8_t io){
  (void) address; /* <-- Remove unused param warning */
  
  /*Set the media enable chip register*/
  sms_enable_port = io;
  
  /* Jump to the selected address
   * Parameters are passed on the Stack:
   * SP --> Return addres (Low byte)
   * +1                   (High byte)
   * +2     arg: address (Low byte)
   * +3                  (High byte)
   * +4     arg: io
   *
   * Moving SP to point to address_L then returning should jump to the selected
   * ROM entry point
   */
  __asm__("POP HL"); /* <-- Jump address pointed by SP */
  __asm__("RET");    /* <-- Jump to ROM entry point */
  
  RAM_CODE_SIGNATURE; /* <-- Mark this function for RAM execution.*/
}

/** Copy bootcode to RAM then execute it. */
void rom_boot(uint8_t rom_media){
    uint16_t i;
    /*Copy boot code to RAM*/
    for(i=0; i<ROM_CODE_BUFFER_SIZE; i++){
        code_buffer[i] = ((uint8_t*)boot_jump)[i];
    }
    
    /*Call bootcode*/
    if(rom_media != ROM_RAM)    {
        bootcode_call(0x0000, rom_media);
    }
    else{
        bootcode_call((uint16_t)rom_buffer, ROM_BIOS);
    }
}

/** ROM read routine.
 *
 *  This function will copy a 1K block of data from the selected media. This
 *  function is intended to be run from RAM since the BIOS ROM wont be
 *  available during this operation.
 */
void _media_read(uint16_t block_index, uint8_t media){
    uint8_t  old_media;
    uint8_t  bank;
    uint16_t address;
    uint16_t i;
    
    old_media = media;
    
    /*Enable external media*/
    sms_enable_port = media;
    
    /*Calculate bank and address, avoid strange operations like modulus     */
    /*since this code shall run from RAM without any function calls.        */
    /*Make sure this function's size is below ROM_CODE_BUFFER_SIZE, check   */
    /*the .map file and fix the function or buffer sizeaccordingly.         */
    /*Undefined behaviour you say? Yeah, fuck you too ;3                    */
    /*  ------ as of this writting (2016-09-06) size is 164B         ------ */
    
    /*Calculating bank index:                                               */
    /*ROM is divided into 16K banks   0100 0000 0000 0000                   */
    /*Each 'read' slot is 1K          0000 0100 0000 0000                   */
    /*So, for each 16 slots (0001 0000), we increment bank index by one, up */
    /*to bank 255. So the bank index is block_index>>4 truncated to 8bits   */
    bank = (uint8_t)(block_index >> 4);
    
    /*Calculate offset within the bank*/
    /*The lower 4 bits of the block index tell us which of the 16 1K lines  */
    /*from the selected bank we shall copy.*/
    address = block_index & 0b00001111;
    /*Multiply by 1024 (1K) using shifting */
    address = address << 10;
    
    /*Set SEGA mapper SLOT2 to the selected bank*/
    *sms_mapper_slot2 = bank;
    
    /*copy 1K of data from it*/
    for(i = 0; i<1024; i++){
        rom_buffer[i] = (((uint8_t*)SMS_SLOT2_BASE_ADDRESS) + address)[i];
    }
    
    /*Restore mapper bank to the default value (2)*/
    *sms_mapper_slot2 = 2;
    
    /*Re-enable BIOS*/
    sms_enable_port = ROM_BIOS;
}

void media_read(uint16_t block_index, uint8_t media){
    /*Copy media_read code to RAM*/
    uint16_t i;
    for(i=0; i<ROM_CODE_BUFFER_SIZE; i++){
        code_buffer[i] = ((uint8_t*)_media_read)[i];
    }
    bootcode_call(block_index, media);
}

/*Extract SEGA header info*/
static const char tmr_sega[8+1] = "TMR SEGA";
static sega_header_t tmp_sega_header;
sega_header_t* get_sega_header(uint8_t rom_media){
    
    uint8_t i;
    /*Read ROM header*/
    /*It is located at the (1K) line number 31*/
    media_read(31, rom_media);
    
    /*Copy TMR SEGA (8B)*/
    for(i=0;i<8;i++){
        tmp_sega_header.tmr_sega[i] = rom_buffer[SEGA_HEADER_OFFSET + i];
    }
    
    /*Copy checksum (2B)*/
    tmp_sega_header.checksum = 
            rom_buffer[SH_CHECKSUM_OFFSET] +
            (((uint16_t)rom_buffer[SH_CHECKSUM_OFFSET + 1]) << 8)
            ;
    
    /*Copy product code (3B, 20bit)*/
    tmp_sega_header.code[0] = rom_buffer[SH_PRODUCT_CODE_OFFSET];
    tmp_sega_header.code[1] = rom_buffer[SH_PRODUCT_CODE_OFFSET + 1];
    tmp_sega_header.code[2] = rom_buffer[SH_PRODUCT_CODE_OFFSET + 2] & 0xF0;
    
    /*Version*/
    tmp_sega_header.version = (rom_buffer[SH_VERSION_OFFSET] >> 4) & 0x0F;
    
    /*Region*/
    tmp_sega_header.region = (rom_buffer[SH_REGION_OFFSET] >> 4) & 0x0F;
    
    /*Rom size*/
    tmp_sega_header.size_type = (rom_buffer[SH_SIZE_OFFSET]) & 0x0F;
    
    return &tmp_sega_header;
}

/*Extract SDSC header*/
#define SDSC_HEADER_OFFSET 0x3e0
static const char sdsc[4+1] = "SDSC";
static sdsc_header_t tmp_sdsc_header;
sdsc_header_t* get_sdsc_header(uint8_t rom_media){
    uint8_t* rp_p;
    uint8_t i;
    media_read(31, rom_media);
    rp_p = (uint8_t*) &tmp_sdsc_header;
    for(i=0; i<16; i++){
        rp_p[i] = rom_buffer[SDSC_HEADER_OFFSET + i];
    }
    return &tmp_sdsc_header;
}

/*Calculate SEGA checksum*/
uint16_t rom_checksum(uint8_t rom_media){
    sega_header_t* header;
    uint16_t rv;
    uint16_t line_index;
    uint16_t i;
    rv = 0;
    
    /*Read header*/
    header = get_sega_header(rom_media);
    
    /*Calculate lower region sum*/
    {
        /*First 7 1K 'lines' are summed up*/
        {
            for(line_index = 0; line_index < 7; line_index++){
                media_read(line_index, rom_media);
                for(i=0; i<1024; i++){
                    rv = rv + rom_buffer[i];
                }
            }
        }
        
        /*If ROM is 8K sum all 7 bytes except the last 16B and return*/
        if(header->size_type == SH_SIZE_8K){
            media_read(7, rom_media);
            for(i=0; i<(1024 - 16); i++){
                rv = rv + rom_buffer[i];
            }
            /*Return the sum*/
            return rv;
        }
        /*Otherwise sum all lines and continue until line 14 (15K)*/
        else{
            for(line_index = 7; line_index < 15; line_index++){
                media_read(line_index, rom_media);
                for(i=0; i<1024; i++){
                    rv = rv + rom_buffer[i];
                }
            }
        }
        
        /*If ROM is 16K sum line 15 bytes except the last 16B and return*/
        if(header->size_type == SH_SIZE_16K){
            media_read(15, rom_media);
            for(i=0; i<(1024 - 16); i++){
                rv = rv + rom_buffer[i];
            }
            return rv;
        }
        /*Otherwise sum all lines from 15 to 30 (31K)*/
        else{
            for(line_index = 15; line_index < 31; line_index++){
                media_read(line_index, rom_media);
                for(i=0; i<1024; i++){
                    rv = rv + rom_buffer[i];
                }
            }
        }
        
        /*If ROM is 32K (or more) sum line 31 bytes except the last 16B and return */
        media_read(31, rom_media);
        for(i=0; i<(1024 - 16); i++){
            rv = rv + rom_buffer[i];
        }
        /*If it is exactly 32K, return*/
        if(header->size_type == SH_SIZE_32K){
            return rv;
        }
        
        /*Special case. 48K ROMs*/
        if(header->size_type == SH_SIZE_48K){
            /*If ROM is 48K sum from line 31 to 46 (47K)*/
            for(line_index = 31; line_index < 47; line_index++){
                media_read(line_index, rom_media);
                for(i=0; i<1024; i++){
                    rv = rv + rom_buffer[i];
                }
            }
            /*Add the line 47 except its last 16B*/
            media_read(47, rom_media);
            for(i=0; i<(1024 - 16); i++){
                rv = rv + rom_buffer[i];
            }
            /*And return*/
            return rv;
        }
    }
    
    /*Upper region checksum*/
    {
        /*We need to sum a number of lines past the 0x7FFF mark (32K, line 31)*/
        /*In essence, rom size in KB minus 32 yields the number of additional */
        /*lines that will have to be summed.*/
        uint16_t upper_line_count;
        switch(header->size_type){
            case SH_SIZE_64K:
            upper_line_count = 64 - 32;
            break;
            case SH_SIZE_128K:
            upper_line_count = 128 - 32;
            break;
            case SH_SIZE_256K:
            upper_line_count = 256 - 32;
            break;
            case SH_SIZE_512K:
            upper_line_count = 512 - 32;
            break;
            case SH_SIZE_1M:
            upper_line_count = 1024 - 32;
            break;
            default:
            upper_line_count = 0;
        }
        for(line_index = 31; line_index < (upper_line_count + 32); line_index ++){
            media_read(line_index, rom_media);
            for(i=0; i<1024; i++){
                rv = rv + rom_buffer[i];
            }
        }
    }
    /*Return the result*/
    return rv;
}

/*Returns the checksum of the currently stored rom_buffer.*/
static uint16_t line_sum(){
    uint16_t rv;
    rv = crc16_ccitt_init();
    rv = crc16_ccitt_update(rv, rom_buffer, 1024);
    rv = crc16_ccitt_finalize(rv);
    return rv;
}

/*Detect the _REAL_ rom size*/
#define ROM_SIZE_TEST_DEPTH 4 /*<-- How many mirror locations shall we test for each test.*/
#define ROM_SIZE_UNK  (0   )
#define ROM_SIZE_1K   (1<<0)
#define ROM_SIZE_2K   (1<<1)
#define ROM_SIZE_4K   (1<<2)
#define ROM_SIZE_8K   (1<<3)
#define ROM_SIZE_16K  (1<<4)
#define ROM_SIZE_32K  (1<<5)
#define ROM_SIZE_64K  (1<<6)
#define ROM_SIZE_128K (1<<7)
#define ROM_SIZE_256K (1<<8)
#define ROM_SIZE_512K (1<<9)
#define ROM_SIZE_1M   (1<<10)
#define ROM_SIZE_2M   (1<<11)
#define ROM_SIZE_4M   (1<<12)
#define ROM_SIZE_8M   (1<<13) /*<-- Max size with SEGA mapper */
#define ROM_SIZE_RES1 (1<<14)
#define ROM_SIZE_RES2 (1<<15)
static uint16_t rom_size(uint8_t rom_media){
    /* To detect the REAL rom size we must check for data mirrors.
     * for a 4K ROM the data will be mirrored every 4K bytes
     */
    
    /*Current size rom being tested.           */
    /*Shifting left this value will give us the*/
    /*next 'common' rom increment.             */
    uint16_t size_increment = ROM_SIZE_1K;
    
    /*Test common sizes. 1K*(2^n)*/
    {
        for( ; size_increment <= ROM_SIZE_8M; size_increment = size_increment << 1){
            uint16_t sum;
            uint16_t current_line;
            uint8_t  hits;
            uint8_t  test_depth;
            media_read(0, rom_media); /*<-- Read the first 1K line */
            sum = line_sum();         /*<-- Store its checksum     */
            current_line = size_increment;
            hits = 1;                 /*<-- How many mirror 'hits' we got, inc ourselves.*/
            test_depth = 1;
            /*Find mirrors*/
            while ((current_line < ROM_SIZE_8M) && (test_depth < ROM_SIZE_TEST_DEPTH)){
                media_read(current_line, rom_media);
                if(line_sum() == sum){
                    hits++;
                }
                current_line = current_line + size_increment;
                test_depth++;
            }
            
            /*Test wether we found the correct size*/
            {
                uint8_t max_hits;
                /*The maximum ammount of hits is the minor of: */
                /*  - ROM_SIZE_TEST_DEPTH                      */
                /*  - ROM_SIZE_8M / size_increment             */
                max_hits = (ROM_SIZE_TEST_DEPTH < (ROM_SIZE_8M / size_increment)) ?
                    ROM_SIZE_TEST_DEPTH :
                    (ROM_SIZE_8M / size_increment)
                    ;
                /*If we get a full hit strike, we (most likely) found the ROM size*/
                if(max_hits == hits){
                    break;
                }
            }
        }
    }
    
    /*Test for uncommon sizes.*/
    {
        /*ToDo*/
    }
    
    return size_increment;
}

/*Dump information*/
void rom_info(uint8_t rom_media){
    uint8_t i;
    uint8_t is_sega;
    uint8_t is_sdsc;
    sega_header_t* header;
    sdsc_header_t* s_header;
    
    con_gotoxy(0, 4);
    
    /*Read ROM header*/
    header = get_sega_header(rom_media);
    
    /*Check for TMR SEGA*/
    is_sega = 1;
    for(i = 0; i<8; i++){
        if(header->tmr_sega[i] != tmr_sega[i]){
            is_sega = 0;
        }
    }
    
    /*Show SEGA header info*/
    con_put(" SEGA header: ");
    if(is_sega){
        con_put("Yes\n"); /*Dump header info*/
        
        /*Checksum*/
        {
            uint16_t checksum;
            con_put("   Checksum: ");
            con_put(" ****");
            /*Calculate sum*/
            checksum = rom_checksum(rom_media);
            con_relxy(-5,0);
            if(checksum == header->checksum){
                con_puth(checksum>>8);
                con_puth(checksum   );
                con_put(" OK");
            }
            else{
                con_puth(checksum>>8);
                con_puth(checksum   );
                con_put(" ERROR!\n");
                con_put("   Expected: ");
                con_puth(header->checksum>>8);
                con_puth(header->checksum   );
            }
            con_put("\n");
        }
        
        /*Product code*/
        {
            con_put("       Code: ");
            con_puth(header->code[0]);
            con_puth(header->code[1]);
            con_puth(header->code[2]);
            con_put("\n");
        }
        
        /*Version*/
        {
            con_put("    Version: ");
            con_puth(header->version);
            con_put("\n");
        }
        
        /*Region*/
        {
            con_put("     Region: ");
            switch(header->region){
                case 3:
                con_put("Japan"); break;
                case 4:
                con_put("Export"); break;
                case 5:
                con_put("Japan (GG)"); break;
                case 6:
                con_put("Export (GG)"); break;
                case 7:
                con_put("Intl. (GG)"); break;
                default:
                con_put("Unknown ");
                con_puth(header->region);
                break;
            }
            con_put("\n");
        }
        
        /*ROM size*/
        {
            con_put("       Size: ");
            switch(header->size_type){
                case 0x00:
                con_put("256KB"); break;
                case 0x01:
                con_put("512KB"); break;
                case 0x02:
                con_put("1MB (!)"); break;
                case 0x0A:
                con_put("8K"); break;
                case 0x0B:
                con_put("16K"); break;
                case 0x0C:
                con_put("32K"); break;
                case 0x0D:
                con_put("48K (!)"); break;
                case 0x0E:
                con_put("64K"); break;
                case 0x0F:
                con_put("128K"); break;
                default:
                con_put("Unknown ");
                con_puth(header->size_type);
                break;
            }
            con_put("\n");
        }
        
    }
    else{
        con_put("No\n");
    }
    con_put("\n");
    
    /*Check for SDSC*/
    {
        s_header = get_sdsc_header(rom_media);
        is_sdsc = 1;
        for(i = 0; i<4; i++){
            if(s_header->sdsc[i] != sdsc[i]){
                is_sdsc = 0;
            }
        }
    }

    
    /*Show SDSC header info*/
    con_put(" SDSC header: ");
    if(is_sdsc){
        con_put("Yes\n");
        
        /*Version*/
        {
            con_put("   Version: ");
            con_puth(s_header->version_h);
            con_putc('.');
            con_puth(s_header->version_l);
            con_put("\n");
        }
        
        /*Date*/
        {
            con_put("      Date: ");
            con_puth(s_header->date_day); con_putc('/');
            con_puth(s_header->date_month); con_putc('/');
            con_puth(s_header->date_year[1]);
            con_puth(s_header->date_year[0]);
            con_put("\n");
        }
        
        /*Author*/
        con_put("    Author: ToDo\n");
        /*Name*/
        con_put("      Name: ");
        /*
        if((s_header->name != (void*)0xFFFF) && (s_header->name != (void*)0x0000)){
            con_put("\n ");
            con_put((char*)(s_header->name));
            con_put("\n");
        }
        else{
            con_put("      Name: *None*\n");
        }
        */
        con_put("ToDo\n");
        /*Description*/
        con_put("      Desc: ToDo\n");
        
    }
    else{
        con_put("No\n");
    }
    con_put("\n");
    
    /*Calculate real ROM size*/
    con_put("   Real size: ***");
    {
        uint16_t r_size;
        r_size = rom_size(rom_media);
        con_relxy(-3,0);
        switch(r_size){
            case ROM_SIZE_1K:
            con_put("1K "); break;
            case ROM_SIZE_2K:
            con_put("2K "); break;
            case ROM_SIZE_4K:
            con_put("4K "); break;
            case ROM_SIZE_8K:
            con_put("8K "); break;
            case ROM_SIZE_16K:
            con_put("16K"); break;
            case ROM_SIZE_32K:
            con_put("32K"); break;
            case ROM_SIZE_64K:
            con_put("64K"); break;
            case ROM_SIZE_128K:
            con_put("128K"); break;
            case ROM_SIZE_256K:
            con_put("256K"); break;
            case ROM_SIZE_512K:
            con_put("512K"); break;
            case ROM_SIZE_1M:
            con_put("1M "); break;
            case ROM_SIZE_2M:
            con_put("2M "); break;
            case ROM_SIZE_4M:
            con_put("4M "); break;
            case ROM_SIZE_8M:
            con_put("8M "); break;
            default:
            con_put("Unknown"); break;
        }
        con_putc('\n');
    }
}

uint8_t* rom_get_buffer(){
    return rom_buffer;
}