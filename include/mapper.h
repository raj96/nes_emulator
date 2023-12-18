#ifndef __mapper
#define __mapper

#include <stdint.h>
#include <cartridge.h>

typedef enum {
    Mapper0Unknown,
    Mapper0Nrom128,
    Mapper0Nrom256,
} Mapper0PrgRomMode;

typedef struct {
    uint16_t prg_ram_addr_start;
    uint16_t prg_ram_addr_end;
    uint16_t rom_addr_start;
    uint16_t rom_addr_end;
    Mapper0PrgRomMode prg_rom_mode;
} _mapper;

extern const _mapper 
    mapper_000;

void load_cartridge_via_mapper(_cartridge cartridge, _mapper mapper);

#endif