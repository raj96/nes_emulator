#include <stdint.h>

#ifndef __ppu
#define __ppu

#define PPU_CTRL 0x2000
#define PPU_MASK 0x2001
#define PPU_STATUS 0x2002
#define PPU_OAMADDR 0x2003
#define PPU_OAMDATA 0x2004
#define PPU_SCROLL 0x2005
#define PPU_ADDR 0x2006
#define PPU_DATA 0x2007
#define PPU_OAMDMA 0x4014

#define PPU_ADDR_BEGIN 0x2000
#define PPU_ADDR_END 0x3fff
#define PPU_MIRROR_ADDR_END 0x2007

void ppu_write(uint16_t address, uint8_t data);
uint8_t ppu_read(uint16_t address);

#endif