#include <cartridge.h>
#include <core/cpu.h>
#include <core/memory.h>
#include <log.h>
#include <mapper.h>
#include <stdio.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        LOGF("Usage: %s <nes file>", argv[0]);
    }

    char *nes_file_name = argv[1];

    _cartridge c = load_cartridge(nes_file_name);
    // printf("Mapper: %d\n", c.mapper);
    // printf("PrgRomSize: %d\n", c.prg_rom_size);
    // printf("ChrRomSize: %d\n", c.chr_rom_size);

    init_memory();
    init_cpu();

    load_cartridge_via_mapper(c, mapper_000);

    // LOGI("%x %x", RAM[MEM_PWR_ON_RST_H], RAM[MEM_PWR_ON_RST_L]);

    reset();

    // print_cpu_state();

    while (1) {
        fde();
        // print_cpu_state();
    }

    destroy_cartridge(c);
    return 0;
}