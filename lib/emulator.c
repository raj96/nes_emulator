#include "emulator.h"

#include "cartridge.h"
#include "core/cpu.h"
#include "core/ppu.h"
#include "core/memory.h"
#include "log.h"
#include "mapper.h"

void emulator_run(char *nes_file_location) {
    const struct timespec nes_clock_delay = {
        .tv_nsec = 1,
    };

    cartridge_t c = load_cartridge(nes_file_location);
    // printf("Mapper: %d\n", c.mapper);
    // printf("PrgRomSize: %d\n", c.prg_rom_size);
    // printf("ChrRomSize: %d\n", c.chr_rom_size);

    init_memory();
    init_cpu();
    init_ppu();

    load_cartridge_via_mapper(c, mapper_000);

    // LOGI("%x %x", RAM[MEM_PWR_ON_RST_H], RAM[MEM_PWR_ON_RST_L]);

    reset();

    // print_cpu_state();

    while (1) {
        fde();
        nanosleep(&nes_clock_delay, NULL);
    }

    destroy_cartridge(c);
}