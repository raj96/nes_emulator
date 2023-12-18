extern "C" {
    #include "core/cpu.h"
    #include "core/memory.h"
}

#include "test.common.hpp"

void setup_testbed() {
    init_memory();

    mem_write(MEM_PWR_ON_RST_H, 0x80);
    mem_write(MEM_PWR_ON_RST_L, 0x00);

    init_cpu();
}

void destroy_testbed() {
    deinit_cpu();
    deinit_memory();
}