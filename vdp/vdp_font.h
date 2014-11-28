#ifndef __VDP_FONT_H
#define __VDP_FONT_H

/**
 * @file Mode0 font for the VDP.
 * 
 * Font converted from smspower.org SMS export fonts.
 */

#include <stdint.h>
uint8_t vdp_font[256*8] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x20,0x20,0x20,0x20,0x20,0x00,0x20,0x00,
0x50,0x50,0x50,0x00,0x00,0x00,0x00,0x00,
0x50,0x50,0xF8,0x50,0xF8,0x50,0x50,0x00,
0x20,0x78,0xA0,0x70,0x28,0xF0,0x20,0x00,
0xC8,0xC8,0x10,0x20,0x40,0x98,0x98,0x00,
0x40,0xA0,0xA0,0x40,0xA8,0x90,0x68,0x00,
0x20,0x20,0x40,0x00,0x00,0x00,0x00,0x00,
0x10,0x20,0x40,0x40,0x40,0x20,0x10,0x00,
0x40,0x20,0x10,0x10,0x10,0x20,0x40,0x00,
0x20,0xA8,0x70,0x20,0x70,0xA8,0x20,0x00,
0x00,0x20,0x20,0xF8,0x20,0x20,0x00,0x00,
0x00,0x00,0x00,0x00,0x30,0x10,0x20,0x00,
0x00,0x00,0x00,0x78,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x00,
0x00,0x08,0x10,0x20,0x40,0x80,0x00,0x00,

0x30,0x48,0x48,0x48,0x48,0x48,0x30,0x00,
0x20,0x60,0x20,0x20,0x20,0x20,0x70,0x00,
0x70,0x88,0x08,0x10,0x20,0x40,0xF8,0x00,
0x70,0x88,0x08,0x30,0x08,0x88,0x70,0x00,
0x30,0x50,0x90,0x90,0xF8,0x10,0x10,0x00,
0xF8,0x80,0xF0,0x08,0x08,0x88,0x70,0x00,
0x70,0x80,0x80,0xF0,0x88,0x88,0x70,0x00,
0xF8,0x88,0x08,0x10,0x20,0x20,0x20,0x00,
0x70,0x88,0x88,0x70,0x88,0x88,0x70,0x00,
0x70,0x88,0x88,0x78,0x08,0x10,0x60,0x00,
0x00,0x30,0x30,0x00,0x30,0x30,0x00,0x00,
0x00,0x30,0x30,0x00,0x30,0x10,0x20,0x00,
0x08,0x10,0x20,0x40,0x20,0x10,0x08,0x00,
0x00,0x00,0x78,0x00,0x78,0x00,0x00,0x00,
0x40,0x20,0x10,0x08,0x10,0x20,0x40,0x00,
0x70,0x88,0x88,0x10,0x20,0x00,0x20,0x00,

0x70,0x88,0x08,0x48,0xA8,0xA8,0x70,0x00,
0x20,0x50,0x88,0x88,0xF8,0x88,0x88,0x00,
0xF0,0x48,0x48,0x70,0x48,0x48,0xF0,0x00,
0x70,0x88,0x80,0x80,0x80,0x88,0x70,0x00,
0xF0,0x48,0x48,0x48,0x48,0x48,0xF0,0x00,
0xF8,0x80,0x80,0xF0,0x80,0x80,0xF8,0x00,
0xF8,0x80,0x80,0xF0,0x80,0x80,0x80,0x00,
0x70,0x88,0x80,0xB8,0x88,0x88,0x70,0x00,
0x88,0x88,0x88,0xF8,0x88,0x88,0x88,0x00,
0x70,0x20,0x20,0x20,0x20,0x20,0x70,0x00,
0x08,0x08,0x08,0x08,0x88,0x88,0x70,0x00,
0x88,0x90,0xA0,0xC0,0xA0,0x90,0x88,0x00,
0x80,0x80,0x80,0x80,0x80,0x80,0xF8,0x00,
0x88,0xD8,0xA8,0xA8,0x88,0x88,0x88,0x00,
0x88,0xC8,0xA8,0x98,0x88,0x88,0x88,0x00,
0xF8,0x88,0x88,0x88,0x88,0x88,0xF8,0x00,

0xF0,0x88,0x88,0xF0,0x80,0x80,0x80,0x00,
0x70,0x88,0x88,0x88,0xA8,0x90,0x68,0x00,
0xF0,0x88,0x88,0xF0,0xA0,0x90,0x88,0x00,
0x70,0x88,0x80,0x70,0x08,0x88,0x70,0x00,
0xF8,0x20,0x20,0x20,0x20,0x20,0x20,0x00,
0x88,0x88,0x88,0x88,0x88,0x88,0x70,0x00,
0x88,0x88,0x88,0x88,0x88,0x50,0x20,0x00,
0x88,0x88,0x88,0x88,0xA8,0xA8,0x50,0x00,
0x88,0x88,0x50,0x20,0x50,0x88,0x88,0x00,
0x88,0x88,0x50,0x20,0x20,0x20,0x20,0x00,
0xF8,0x08,0x10,0x20,0x40,0x80,0xF8,0x00,
0x38,0x20,0x20,0x20,0x20,0x20,0x38,0x00,
0x88,0x50,0x20,0x70,0x20,0x70,0x20,0x00,
0x70,0x10,0x10,0x10,0x10,0x10,0x70,0x00,
0x20,0x50,0x88,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x08,0xF0,0x50,0x50,0x90,0x00,

0x40,0x20,0x10,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x70,0x10,0x70,0x90,0x68,0x00,
0x80,0x80,0xB0,0xC8,0x88,0xC8,0xB0,0x00,
0x00,0x00,0x70,0x88,0x80,0x88,0x70,0x00,
0x08,0x08,0x68,0x98,0x88,0x98,0x68,0x00,
0x00,0x00,0x70,0x88,0xF8,0x80,0x70,0x00,
0x18,0x20,0x20,0xF8,0x20,0x20,0x20,0x00,
0x00,0x00,0x68,0x98,0x88,0x78,0x08,0x70,
0x80,0x80,0xB0,0xC8,0x88,0x88,0x88,0x00,
0x20,0x00,0x60,0x20,0x20,0x20,0x70,0x00,
0x10,0x00,0x30,0x10,0x10,0x10,0x90,0x60,
0x80,0x80,0x88,0x90,0xA0,0xD0,0x88,0x00,
0x60,0x20,0x20,0x20,0x20,0x20,0x70,0x00,
0x00,0x00,0xD0,0xA8,0xA8,0xA8,0xA8,0x00,
0x00,0x00,0xB0,0xC8,0x88,0x88,0x88,0x00,
0x00,0x00,0x70,0x88,0x88,0x88,0x70,0x00,

0x00,0x00,0x70,0x48,0x48,0x70,0x40,0x40,
0x00,0x00,0x38,0x48,0x48,0x38,0x08,0x08,
0x00,0x00,0xB0,0xC8,0x80,0x80,0x80,0x00,
0x00,0x00,0x78,0x80,0x70,0x08,0xF0,0x00,
0x20,0x20,0xF8,0x20,0x20,0x20,0x18,0x00,
0x00,0x00,0x88,0x88,0x88,0x98,0x68,0x00,
0x00,0x00,0x88,0x88,0x88,0x50,0x20,0x00,
0x00,0x00,0x88,0xA8,0xA8,0xA8,0x50,0x00,
0x00,0x00,0x88,0x50,0x20,0x50,0x88,0x00,
0x00,0x00,0x88,0x88,0x98,0x68,0x08,0x70,
0x00,0x00,0xF8,0x10,0x20,0x40,0xF8,0x00,
0x18,0x20,0x20,0x40,0x20,0x20,0x18,0x00,
0x20,0x20,0x20,0x00,0x20,0x20,0x20,0x00,
0xC0,0x20,0x20,0x10,0x20,0x20,0xC0,0x00,
0x00,0x00,0x40,0xA8,0x10,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x00,0x00,0x00,0xFC,0x00,0x00,0x00,0x00,
0x20,0x20,0x20,0xFC,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xFC,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0xE0,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x3C,0x20,0x20,0x20,0x20,
0x00,0x00,0x00,0x3C,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x3C,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xE0,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0xE0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x0C,0x10,0x20,0x20,0x20,
0x20,0x20,0x10,0x0C,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x80,0x40,0x20,0x20,0x20,
0x20,0x20,0x40,0x80,0x00,0x00,0x00,0x00,
0x20,0x70,0xA8,0x20,0x20,0x20,0x20,0x00,
0x00,0x20,0x40,0xF8,0x40,0x20,0x00,0x00,

0xA8,0x54,0xA8,0x54,0xA8,0x54,0xA8,0x54,
0x84,0x88,0x50,0x30,0x30,0x28,0x44,0x84,
0x20,0x20,0x20,0xFC,0x20,0x20,0x20,0x20,
0x04,0x08,0x10,0x10,0x20,0x20,0x40,0x80,
0x80,0x40,0x20,0x20,0x10,0x10,0x08,0x04,
0x04,0x0C,0x1C,0x1C,0x3C,0x3C,0x7C,0xFC,
0x80,0xC0,0xE0,0xE0,0xF0,0xF0,0xF8,0xFC,
0xFC,0x7C,0x3C,0x3C,0x1C,0x1C,0x0C,0x04,
0xFC,0xF8,0xF0,0xF0,0xE0,0xE0,0xC0,0x80,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFC,
0x00,0x00,0x00,0x00,0x00,0x00,0xFC,0xFC,
0x00,0x00,0x00,0x00,0xFC,0xFC,0xFC,0xFC,
0xFC,0xFC,0xFC,0xFC,0x00,0x00,0x00,0x00,
0xFC,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,
0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,

0x20,0x50,0x00,0x70,0x88,0xF8,0x88,0x00,
0x50,0x20,0x00,0x70,0x88,0xF8,0x88,0x00,
0x18,0x20,0x00,0x70,0x88,0xF8,0x88,0x00,
0xC0,0x20,0x00,0x70,0x88,0xF8,0x88,0x00,
0x00,0x50,0x00,0x70,0x88,0xF8,0x88,0x00,
0x20,0x50,0x20,0x70,0x88,0xF8,0x88,0x00,
0x48,0xB0,0x00,0x70,0x88,0xF8,0x88,0x00,
0x00,0x70,0x00,0x70,0x88,0xF8,0x88,0x00,
0x10,0x28,0xF0,0x80,0xF0,0x80,0xF0,0x00,
0x28,0x10,0xE0,0x80,0xF0,0x80,0xF0,0x00,
0x50,0x00,0xF0,0x80,0xF0,0x80,0xF0,0x00,
0x70,0x00,0xF0,0x80,0xF0,0x80,0xF0,0x00,
0x08,0x10,0xF0,0x80,0xF0,0x80,0xF0,0x00,
0x80,0x40,0xF0,0x80,0xF0,0x80,0xF0,0x00,
0x48,0xB0,0x00,0xC8,0xA8,0x98,0x88,0x00,
0x30,0x48,0x00,0xC8,0xA8,0x98,0x88,0x00,

0x28,0x10,0x00,0xE0,0x40,0x40,0xE0,0x00,
0x80,0x40,0x00,0x38,0x10,0x10,0x38,0x00,
0x08,0x10,0x00,0xE0,0x40,0x40,0xE0,0x00,
0x00,0x50,0x00,0x70,0x20,0x20,0x70,0x00,
0x10,0x28,0x00,0xE0,0x40,0x40,0xE0,0x00,
0x00,0x70,0x00,0x70,0x20,0x20,0x70,0x00,
0x20,0x50,0x00,0x70,0x88,0x88,0x70,0x00,
0x90,0x60,0x00,0x70,0x88,0x88,0x70,0x00,
0x70,0x88,0x88,0x88,0x70,0x20,0x40,0x00,
0x08,0x10,0x00,0x70,0x88,0x88,0x70,0x00,
0x80,0x40,0x00,0x70,0x88,0x88,0x70,0x00,
0x00,0x50,0x00,0x70,0x88,0x88,0x70,0x00,
0x48,0xB0,0x00,0x70,0x88,0x88,0x70,0x00,
0x10,0x28,0x00,0x88,0x88,0x88,0x70,0x00,
0x50,0x20,0x00,0x88,0x88,0x88,0x70,0x00,
0x10,0x20,0x00,0x88,0x88,0x88,0x70,0x00,

0x40,0x20,0x00,0x88,0x88,0x88,0x70,0x00,
0x00,0x50,0x00,0x88,0x88,0x88,0x70,0x00,
0x00,0x70,0x00,0x88,0x88,0x88,0x70,0x00,
0x00,0x68,0xB0,0x90,0xB0,0xE8,0x00,0x00,
0x00,0x70,0x48,0x70,0x48,0x48,0xB0,0x00,
0x60,0x90,0x90,0xF0,0x90,0x90,0x60,0x00,
0x00,0x08,0x18,0x28,0x48,0xC8,0x08,0x00,
0x00,0x48,0x48,0x48,0xB0,0x80,0x00,0x00,
0x00,0xF0,0x90,0x40,0x40,0x90,0xF0,0x00,
0x10,0x70,0x98,0xA8,0xC8,0x70,0x40,0x00,
0x00,0x00,0x70,0x88,0x88,0x50,0xD8,0x00,
0x70,0x88,0x80,0x88,0x70,0x20,0x40,0x00,
0x20,0x00,0x20,0x60,0x88,0x88,0x70,0x00,
0x20,0x00,0x20,0x20,0x20,0x20,0x20,0x00,
0x04,0x08,0x08,0x1C,0x10,0x20,0x20,0x00,
0x10,0x20,0x70,0x20,0x60,0xA0,0x78,0x00,

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,
0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,
0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,
0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,
0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,
0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,
0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,
0x00,0x00,0xFC,0xFC,0xFC,0x00,0x00,0x00,
0x20,0x50,0x20,0x50,0x20,0x50,0x20,0x50,
0x00,0x00,0xA8,0x54,0xA8,0x00,0x00,0x00,
0x1C,0x1C,0x1C,0x1C,0xE0,0xE0,0xE0,0xE0,
0x00,0x70,0x88,0x88,0x88,0x70,0x00,0x00,
0x00,0x70,0xF8,0xF8,0xF8,0x70,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x20,0x70,0xF8,0xF8,0xF8,0x20,0x70,0x00,
0x50,0xF8,0xF8,0xF8,0xF8,0x70,0x20,0x00,
0x20,0x20,0x70,0xF8,0x70,0x20,0x20,0x00,
0x70,0x70,0xA8,0xF8,0xA8,0x20,0x70,0x00,
0x78,0xFC,0xB4,0xB4,0xFC,0xCC,0x78,0x00,
0x00,0x20,0x70,0xA8,0xF8,0x50,0x00,0x00,
0x88,0xF8,0xA8,0x20,0xA8,0xF8,0x88,0x00,
0x00,0xDC,0x48,0x78,0x48,0xDC,0x00,0x00,
0x70,0x70,0x20,0xF8,0x20,0x20,0x50,0x00,
0x00,0x20,0x00,0xF8,0x00,0x20,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00

};
#endif