#include <gtest/gtest.h>

extern "C"
{
#include "core/cpu.h"
#include "core/memory.h"
#include "instruction.h"
}

#include "test.common.hpp"

TEST(CpuInstructions, AdcImm)
{
    setup_testbed();

    mem_write(0x8000, adc_imm.opcode);
    mem_write(0x8001, 0x01);

    CPU->A = 0x05;

    fde();

    ASSERT_EQ(CPU->A, 0x06);
    ASSERT_EQ(CPU->PS.flags.C, 0);
    ASSERT_EQ(CPU->PS.flags.N, 0);
    ASSERT_EQ(CPU->PS.flags.Z, 0);

    destroy_testbed();
}

TEST(CpuInstructions, AdcAbs)
{
    setup_testbed();

    mem_write(0x8000, adc_abs.opcode);
    mem_write(0x8001, 0x50);
    mem_write(0x8002, 0x2f);

    mem_write(0x2f50, 0x0a);

    CPU->A = 0x06;

    fde();

    ASSERT_EQ(CPU->A, 0x10);
    ASSERT_EQ(CPU->PS.flags.C, 0);
    ASSERT_EQ(CPU->PS.flags.N, 0);
    ASSERT_EQ(CPU->PS.flags.Z, 0);

    destroy_testbed();
}

TEST(CpuInstructions, AdcZp)
{
    setup_testbed();

    mem_write(0x8000, adc_zp.opcode);
    mem_write(0x8001, 0x15);

    mem_write(0x15, 0xfe);

    CPU->A = 0x03;

    fde();

    ASSERT_EQ(CPU->A, 0x01);
    ASSERT_EQ(CPU->PS.flags.C, 1);
    ASSERT_EQ(CPU->PS.flags.N, 0);
    ASSERT_EQ(CPU->PS.flags.Z, 0);

    destroy_testbed();
}

TEST(CpuInstructions, AdcZpx)
{
    setup_testbed();

    mem_write(0x8000, adc_zpx.opcode);
    mem_write(0x8001, 0x16);

    CPU->X = 0x23;

    mem_write(0x16 + CPU->X, 0x80);

    CPU->A = 0x00;

    fde();

    ASSERT_EQ(CPU->A, 0x80);
    ASSERT_EQ(CPU->PS.flags.C, 0);
    ASSERT_EQ(CPU->PS.flags.N, 1);
    ASSERT_EQ(CPU->PS.flags.Z, 0);

    destroy_testbed();
}

TEST(CpuInstructions, AdcAbx)
{
    setup_testbed();

    mem_write(0x8000, adc_abx.opcode);
    mem_write(0x8001, 0x1f);
    mem_write(0x8002, 0x10);

    CPU->X = 0x1e;

    mem_write(0x103d, 0xff);

    CPU->A = 0x01;

    fde();

    ASSERT_EQ(CPU->A, 0x00);
    ASSERT_EQ(CPU->PS.flags.C, 1);
    ASSERT_EQ(CPU->PS.flags.N, 0);
    ASSERT_EQ(CPU->PS.flags.Z, 1);

    destroy_testbed();
}
