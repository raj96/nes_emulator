#include <core/ppu.h>
#include <core/memory.h>

void ppu_write(uint16_t address, uint8_t data) {
        RAM[address & PPU_MIRROR_ADDR_END] = data;
}

uint8_t ppu_read(uint16_t address) {
    return RAM[address & PPU_MIRROR_ADDR_END];
}