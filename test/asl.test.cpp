#include <gtest/gtest.h>
#include "test.common.hpp"

extern "C" {
    #include "core/cpu.h"
    #include "core/memory.h"
    #include "instruction.h"
}

TEST(CpuInstructions, AslAcc) {
    setup_testbed();

    mem_write(0x8000, asl_acc.opcode);

    CPU->A = 0x80;

    fde();

    ASSERT_EQ(CPU->A, 0x00);
    ASSERT_EQ(CPU->PS.flags.C, 1);
    ASSERT_EQ(CPU->PS.flags.N, 0);
    ASSERT_EQ(CPU->PS.flags.Z, 1);

    destroy_testbed();
}

TEST(CpuInstructions, AslZp) {
    setup_testbed();

    mem_write(0x8000, asl_zp.opcode);
    mem_write(0x8001, 0x6e);

    mem_write(0x6e, 0x40);
    
    fde();

    ASSERT_EQ(mem_read(0x6e), 0x80);
    ASSERT_EQ(CPU->PS.flags.C, 0);
    ASSERT_EQ(CPU->PS.flags.N, 1);
    ASSERT_EQ(CPU->PS.flags.Z, 0);;

    destroy_testbed();
}
