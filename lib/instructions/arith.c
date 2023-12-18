#include <instruction.h>
#include <core/cpu.h>

void __base_adc()
{
    uint16_t res = CPU->A + CPU->__dl + CPU->PS.flags.C;
    CPU->PS.flags.C = res >> 8;
    CPU->PS.flags.V = ((CPU->A ^ (uint8_t)res) & (CPU->__dl ^ (uint8_t)res)) >> 7;

    CPU->A = (uint8_t)res;

    CPU->PS.flags.N = CPU->A >> 7;
    CPU->PS.flags.Z = CPU->A == 0x00;
    CPU->__cycles++;
}

const instruction adc_imm = {
    .mnemonic = "adc",
    .opcode = 0x69,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_imm,
    .operation = &__base_adc,
};

const instruction adc_zp = {
    .mnemonic = "adc",
    .opcode = 0x65,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zp,
    .operation = &__base_adc,
};

const instruction adc_zpx = {
    .mnemonic = "adc",
    .opcode = 0x75,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zpx,
    .operation = &__base_adc,
};

const instruction adc_abs = {
    .mnemonic = "adc",
    .opcode = 0x6d,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abs,
    .operation = &__base_adc,
};

const instruction adc_abx = {
    .mnemonic = "adc",
    .opcode = 0x7d,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abx,
    .operation = &__base_adc,
};

const instruction adc_aby = {
    .mnemonic = "adc",
    .opcode = 0x79,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_aby,
    .operation = &__base_adc,
};

const instruction adc_idx = {
    .mnemonic = "adc",
    .opcode = 0x61,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_idx,
    .operation = &__base_adc,
};

const instruction adc_idy = {
    .mnemonic = "adc",
    .opcode = 0x71,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_idy,
    .operation = &__base_adc,
};

void __base_cmp() {
    CPU->__cycles++;
    // printf("CMP: comparing %02X and %02X\n", CPU->A, CPU->__dl);
    CPU->PS.flags.C = CPU->A >= CPU->__dl;
    CPU->PS.flags.Z = CPU->A == CPU->__dl;
    CPU->PS.flags.N = (CPU->A - CPU->__dl) >> 7;
}

const instruction cmp_imm = {
    .mnemonic = "cmp",
    .opcode = 0xc9,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_imm,
    .operation = &__base_cmp,
};

const instruction cmp_zp = {
    .mnemonic = "cmp",
    .opcode = 0xc5,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zp,
    .operation = &__base_cmp,
};

const instruction cmp_zpx = {
    .mnemonic = "cmp",
    .opcode = 0xd5,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zpx,
    .operation = &__base_cmp,
};

const instruction cmp_abs = {
    .mnemonic = "cmp",
    .opcode = 0xcd,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abs,
    .operation = &__base_cmp,
};

const instruction cmp_abx = {
    .mnemonic = "cmp",
    .opcode = 0xdd,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abx,
    .operation = &__base_cmp,
};

const instruction cmp_aby = {
    .mnemonic = "cmp",
    .opcode = 0xd9,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_aby,
    .operation = &__base_cmp,
};

const instruction cmp_idx = {
    .mnemonic = "cmp",
    .opcode = 0xc1,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_idx,
    .operation = &__base_cmp,
};

const instruction cmp_idy = {
    .mnemonic = "cmp",
    .opcode = 0xd1,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_idy,
    .operation = &__base_cmp,
};

void __base_cpx() {
    CPU->__cycles++;
    CPU->PS.flags.C = CPU->X >= CPU->__dl;
    CPU->PS.flags.Z = CPU->X == CPU->__dl;
    CPU->PS.flags.N = (CPU->X - CPU->__dl) >> 7;
}

const instruction cpx_imm = {
    .mnemonic = "cpx",
    .opcode = 0xe0,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_imm,
    .operation = &__base_cpx,
};

const instruction cpx_zp = {
    .mnemonic = "cpx",
    .opcode = 0xe4,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zp,
    .operation = &__base_cpx,
};

const instruction cpx_abs = {
    .mnemonic = "cpx",
    .opcode = 0xec,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abs,
    .operation = &__base_cpx,
};

void __base_cpy() {
    CPU->__cycles++;
    CPU->PS.flags.C = CPU->Y >= CPU->__dl;
    CPU->PS.flags.Z = CPU->Y == CPU->__dl;
    CPU->PS.flags.N = (CPU->Y - CPU->__dl) >> 7;
}

const instruction cpy_imm = {
    .mnemonic = "cpy",
    .opcode = 0xc0,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_imm,
    .operation = &__base_cpy,
};

const instruction cpy_zp = {
    .mnemonic = "cpy",
    .opcode = 0xc4,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zp,
    .operation = &__base_cpy,
};

const instruction cpy_abs = {
    .mnemonic = "cpy",
    .opcode = 0xcc,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abs,
    .operation = &__base_cpy,
};

void __base_sbc() {
    // uint16_t res = CPU->A - CPU->__dl - (!CPU->PS.flags.C);
    // printf("%u - %u - %u = %d\n", CPU->A, CPU->__dl, (!CPU->PS.flags.C), (uint8_t)res);
    // CPU->PS.flags.C = 1 - (res >> 8);
    // CPU->PS.flags.V = ((CPU->A ^ (uint8_t)res) & (CPU->__dl ^ (uint8_t)res)) >> 7;

    // CPU->A = (uint8_t)res;

    // CPU->PS.flags.N = CPU->A >> 7;
    // CPU->PS.flags.Z = CPU->A == 0x00;
    // CPU->__cycles++;
    CPU->__dl = 255 - CPU->__dl;
    __base_adc();
}

const instruction sbc_imm = {
    .mnemonic = "sbc",
    .opcode = 0xe9,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_imm,
    .operation = &__base_sbc,
};

const instruction sbc_zp = {
    .mnemonic = "sbc",
    .opcode = 0xe5,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zp,
    .operation = &__base_sbc,
};

const instruction sbc_zpx = {
    .mnemonic = "sbc",
    .opcode = 0xf5,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zpx,
    .operation = &__base_sbc,
};

const instruction sbc_abs = {
    .mnemonic = "sbc",
    .opcode = 0xed,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abs,
    .operation = &__base_sbc,
};

const instruction sbc_abx = {
    .mnemonic = "sbc",
    .opcode = 0xfd,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abx,
    .operation = &__base_sbc,
};

const instruction sbc_aby = {
    .mnemonic = "sbc",
    .opcode = 0xf9,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_aby,
    .operation = &__base_sbc,
};

const instruction sbc_idx = {
    .mnemonic = "sbc",
    .opcode = 0xe1,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_idx,
    .operation = &__base_sbc,
};

const instruction sbc_idy = {
    .mnemonic = "sbc",
    .opcode = 0xf1,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_idy,
    .operation = &__base_sbc,
};

void register_arith_instruction_set()
{
    register_instruction(adc_imm);
    register_instruction(adc_zp);
    register_instruction(adc_zpx);
    register_instruction(adc_abs);
    register_instruction(adc_abx);
    register_instruction(adc_aby);
    register_instruction(adc_idx);
    register_instruction(adc_idy);

    register_instruction(cmp_imm);
    register_instruction(cmp_zp);
    register_instruction(cmp_zpx);
    register_instruction(cmp_abs);
    register_instruction(cmp_abx);
    register_instruction(cmp_aby);
    register_instruction(cmp_idx);
    register_instruction(cmp_idy);

    register_instruction(cpx_imm);
    register_instruction(cpx_zp);
    register_instruction(cpx_abs);

    register_instruction(cpy_imm);
    register_instruction(cpy_zp);
    register_instruction(cpy_abs);

    register_instruction(sbc_imm);
    register_instruction(sbc_zp);
    register_instruction(sbc_zpx);
    register_instruction(sbc_abs);
    register_instruction(sbc_abx);
    register_instruction(sbc_aby);
    register_instruction(sbc_idx);
    register_instruction(sbc_idy);
}
