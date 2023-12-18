#include <gtest/gtest.h>
#include "test.common.hpp"

extern "C" {
    #include "core/cpu.h"
    #include "core/memory.h"
    #include "instruction.h"
}

TEST(CpuInstructions, AndImm) {
    setup_testbed();

    mem_write(0x8000, and_imm.opcode);
    mem_write(0x8001, 0x0f);

    CPU->A = 0xde;

    fde();

    ASSERT_EQ(CPU->A, 0xe);
    ASSERT_EQ(CPU->PS.flags.Z, 0);
    ASSERT_EQ(CPU->PS.flags.N, 0);

    destroy_testbed();
}