#include <mapper.h>
#include <core/memory.h>
#include <log.h>
#include <string.h>


void load_cartridge_via_mapper(_cartridge cartridge, _mapper mapper) {
    if(cartridge.prg_rom_size == 16384) {
        mapper.prg_rom_mode = Mapper0Nrom128;
    } else {
        mapper.prg_rom_mode = Mapper0Nrom256;
    }

    // LOGI("Mapper mode: %s", mapper.prg_rom_mode == Mapper0Nrom128 ? "NROM-128" : "NROM-256");
    memcpy(RAM + mapper.rom_addr_start, cartridge.prg_rom, 16384);
    if(mapper.prg_rom_mode == Mapper0Nrom128) {
        memcpy(RAM + mapper.rom_addr_start + 16384, cartridge.prg_rom, 16384);
    } else if (mapper.prg_rom_mode == Mapper0Nrom256) {
        memcpy(RAM + mapper.rom_addr_start + 16384, cartridge.prg_rom + 16384, 16384);
    }
    
    mem_write(MEM_PWR_ON_RST_L, mapper.rom_addr_start & 0xff);
    mem_write(MEM_PWR_ON_RST_H, (mapper.rom_addr_start >> 8));
}