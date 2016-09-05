/**
 * @file  sms.h
 * @brief Miscellaneous SMS attributes and functions.
 */

#ifndef __SMS_H
#define __SMS_H

#include <stdint.h>

/* --- Hardware attributes --- */
#define SMS_RAM_BASE_ADDRESS   0xc000
#define SMS_RAM_MIRROR_ADDRESS 0xe000
#define SMS_RAM_SIZE           0x2000

/* --- Port address declarations --- */
#define SMS_ENABLE_PORT      0x3E
#define SMS_FM_PORT          0xF2
#define SMS_IO_CONTROL_PORT  0x3F
#define SMS_IO_AB_PORT       0xDC
#define SMS_IO_B_MISC_PORT   0xDD
#define SMS_PSG_PORT         0x7F
#define SMS_VDP_DATA_PORT    0xBE
#define SMS_VDP_CONTROL_PORT 0xBF
#define SMS_VDP_V_PORT       0x7E
#define SMS_VDP_H_PORT       0x7F

/* --- Return values --- */
#define SMS_REGION_JAPAN  1
#define SMS_REGION_EXPORT 0

uint8_t sms_region();

#endif
