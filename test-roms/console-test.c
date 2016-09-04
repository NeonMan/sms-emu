/**
 * @file  test-roms/vdp-test.c
 * @brief Sample VDP message.
 */

#include "sms/console.h"
#include "sms/intv-dummy.h" /*<-- Ignore interrupts*/
#include <stdint.h>

void main(){
    uint16_t i;
    con_init();
    
    con_put("Master System VDP Console test\n\n\n");
    
    /*Print the whole ASCII range*/
    con_put("       -Character  map-\n");
    for(i=0x20; i<0x80; i++){
        /*Every 16th char print a newline and a bunch of spaces*/
        if((i%16) == 0){
            con_put("\n       ");
        }
        con_putc(i & 0x7F);
    }
    
    /*Do nothing*/
    while(1){
        
    }
}