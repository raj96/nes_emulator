#include <stdint.h>

#ifndef __cartridge
#define __cartridge

typedef enum {
    MirroringHorizontal,
    MirroringVertical,
    MirroringFourScreenVram
} Mirroring;

typedef struct {
    uint8_t *prg_rom;
    int prg_rom_size;
    uint8_t *chr_rom;
    int chr_rom_size;
    uint8_t mapper;

    Mirroring mirror_mode;
} cartridge_t;

cartridge_t load_cartridge(char *nes_file_loc);
void destroy_cartridge(cartridge_t cartridge);
#endif