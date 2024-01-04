#include "core/ppu.h"

#include <stdlib.h>
#include <string.h>

#include "core/cpu.h"
#include "core/memory.h"

ppu_t *PPU = NULL;

void init_ppu() {
    PPU = (ppu_t *)malloc(sizeof(ppu_t));
}

void ppu_oamdma_transfer() {
    memcpy(PPU->oam, RAM + ((PPU->OAMDMA << 8) | 0x00), 256);
}

void ppu_write(uint16_t address, uint8_t data) {
    switch (address) {
        case PPU_CTRL:
            PPU->PPUCTRL.reg = data;
            break;
        case PPU_MASK:
            PPU->PPUMASK.reg = data;
            break;
        case PPU_STATUS:
            // Read only
            break;
        case PPU_OAMADDR:
            PPU->OAMADDR = data;
            break;
        case PPU_OAMDATA:
            PPU->OAMDATA = data;
            PPU->OAMADDR++;
            break;
        case PPU_SCROLL:
            // First X scroll then Y scroll
            PPU->PPUSCROLL = data;
            break;
        case PPU_ADDR:
            // First the upper byte
            PPU->PPUADDR = data;
            break;
        case PPU_DATA:
            PPU->PPUDATA = data;
            break;
        case PPU_OAMDMA:
            PPU->OAMDMA = data;
            ppu_oamdma_transfer();
            break;
    }
}

uint8_t ppu_read(uint16_t address) {
    switch (address) {
        case PPU_CTRL:
            break;
        case PPU_MASK:
            break;
        case PPU_STATUS:
            break;
        case PPU_OAMADDR:
            break;
        case PPU_OAMDATA:
            break;
        case PPU_SCROLL:
            break;
        case PPU_ADDR:
            break;
        case PPU_DATA:
            break;
        case PPU_OAMDMA:
            break;
    }

    return 0;
}