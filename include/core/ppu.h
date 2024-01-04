#include <stdint.h>

#ifndef __ppu
#define __ppu

#define PATTERN_TABLE_SIZE 0x1000
#define PATTERN_TABLE_1 0x0000
#define PATTERN_TABLE_2 0x1000

#define NAMETABLE_SIZE 0x0400
#define NAMETABLE_0 0x2000
#define NAMETABLE_1 0x2400
#define NAMETABLE_2 0x2800
#define NAMETABLE_3 0x2c00

#define PALETTE_START 0x3f00
#define PALETTE_END 0x3f1f
#define PALETTE_MIRROR_END 0x3fff

typedef union {
    uint8_t reg;
    struct {
        uint8_t NN : 2;
        uint8_t I : 1;
        uint8_t S : 1;
        uint8_t B : 1;
        uint8_t H : 1;
        uint8_t P : 1;
        uint8_t V : 1;
    } flags;
} ppuctrl_t;

typedef union {
    uint8_t reg;
    struct {
        uint8_t Grey : 1;
        uint8_t m : 1;
        uint8_t M : 1;
        uint8_t b : 1;
        uint8_t s : 1;
        uint8_t R : 1;
        uint8_t G : 1;
        uint8_t B : 1;
    } flags;
} ppumask_t;

typedef union {
    uint8_t reg;
    struct {
        uint8_t unused : 5;
        uint8_t O : 1;
        uint8_t S : 1;
        uint8_t V : 1;
    } flags;
} ppustatus_t;

typedef struct _ppu {
    ppuctrl_t PPUCTRL;
    ppumask_t PPUMASK;
    uint8_t OAMADDR;
    uint8_t OAMDATA;
    uint8_t PPUSCROLL;
    uint8_t PPUADDR;
    uint8_t PPUDATA;
    uint8_t OAMDMA;

    uint8_t vram[PALETTE_MIRROR_END + 1];
    uint8_t oam[256];
} ppu_t;

extern ppu_t *PPU;

void init_ppu();
void ppu_write(uint16_t address, uint8_t data);
uint8_t ppu_read(uint16_t address);

void ppu_oamdma_transfer();

#endif