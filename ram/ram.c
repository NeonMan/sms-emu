#define WITHOUT_LIB
#include "ram.h"
#include "../z80/z80_externs.h"
#include <stdint.h>

#define RAM_SIZE (1024 * 8)
#define RAM_BASE_ADDRESS 0xC000

uint8_t ram_image[RAM_SIZE];

void ram_tick(){
    //If mreq is up or address out of range, return.
    if (z80_n_mreq) return;
    if (z80_address < RAM_BASE_ADDRESS) return;
    else{
        const size_t image_addr = (z80_address - RAM_BASE_ADDRESS) % RAM_SIZE;
        //Is a write or a read?
        if (z80_n_rd == 0){
            //Read
            z80_data = ram_image[image_addr];
        }
        else if (z80_n_wr == 0){
            //Write
            ram_image[image_addr] = z80_data;
        }
    }
}