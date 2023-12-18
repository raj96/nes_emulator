#include <instruction.h>
#include <core/cpu.h>

void __base_and() {
    CPU->A &= CPU->__dl;
    CPU->__cycles++;

    CPU->PS.flags.Z = CPU->A == 0x00;
    CPU->PS.flags.N = CPU->A >> 7;
}

const instruction and_imm = {
    .mnemonic = "and",
    .opcode = 0x29,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_imm,
    .operation = &__base_and
};

const instruction and_zp = {
    .mnemonic = "and",
    .opcode = 0x25,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zp,
    .operation = &__base_and
};

const instruction and_zpx = {
    .mnemonic = "and",
    .opcode = 0x35,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zpx,
    .operation = &__base_and
};

const instruction and_abs = {
    .mnemonic = "and",
    .opcode = 0x2d,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abs,
    .operation = &__base_and
};

const instruction and_abx = {
    .mnemonic = "and",
    .opcode = 0x3d,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abx,
    .operation = &__base_and
};

const instruction and_aby = {
    .mnemonic = "and",
    .opcode = 0x39,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_aby,
    .operation = &__base_and
};

const instruction and_idx = {
    .mnemonic = "and",
    .opcode = 0x21,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_idx,
    .operation = &__base_and
};

const instruction and_idy = {
    .mnemonic = "and",
    .opcode = 0x31,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_idy,
    .operation = &__base_and
};

void __base_bit() {
    uint8_t result = CPU->A & CPU->__dl;

    CPU->PS.flags.Z = result == 0x00;
    CPU->PS.flags.V = (CPU->__dl >> 6) & 0x01;
    CPU->PS.flags.N = CPU->__dl >> 7;
}

const instruction bit_zp = {
    .mnemonic = "bit",
    .opcode = 0x24,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zp,
    .operation = &__base_bit,
};

const instruction bit_abs = {
    .mnemonic = "bit",
    .opcode = 0x2c,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abs,
    .operation = &__base_bit,
};

void __base_eor() {
    CPU->A ^= CPU->__dl;

    CPU->__cycles++;
    CPU->PS.flags.Z = CPU->A == 0x00;
    CPU->PS.flags.N = CPU->A >> 7;
}

const instruction eor_imm = {
    .mnemonic = "eor",
    .opcode = 0x49,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_imm,
    .operation = &__base_eor,
};

const instruction eor_zp = {
    .mnemonic = "eor",
    .opcode = 0x45,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zp,
    .operation = &__base_eor,
};

const instruction eor_zpx = {
    .mnemonic = "eor",
    .opcode = 0x55,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zpx,
    .operation = &__base_eor,
};

const instruction eor_abs = {
    .mnemonic = "eor",
    .opcode = 0x4d,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abs,
    .operation = &__base_eor,
};

const instruction eor_abx = {
    .mnemonic = "eor",
    .opcode = 0x5d,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abx,
    .operation = &__base_eor,
};

const instruction eor_aby = {
    .mnemonic = "eor",
    .opcode = 0x59,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_aby,
    .operation = &__base_eor,
};

const instruction eor_idx = {
    .mnemonic = "eor",
    .opcode = 0x41,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_idx,
    .operation = &__base_eor,
};

const instruction eor_idy = {
    .mnemonic = "eor",
    .opcode = 0x51,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_idy,
    .operation = &__base_eor,
};

void __base_ora() {
    CPU->A |= CPU->__dl;

    CPU->__cycles++;
    CPU->PS.flags.Z = CPU->A == 0x00;
    CPU->PS.flags.N = CPU->A >> 7;
}

const instruction ora_imm = {
    .mnemonic = "ora",
    .opcode = 0x09,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_imm,
    .operation = &__base_ora,
};

const instruction ora_zp = {
    .mnemonic = "ora",
    .opcode = 0x05,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zp,
    .operation = &__base_ora,
};

const instruction ora_zpx = {
    .mnemonic = "ora",
    .opcode = 0x15,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zpx,
    .operation = &__base_ora,
};

const instruction ora_abs = {
    .mnemonic = "ora",
    .opcode = 0x0d,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abs,
    .operation = &__base_ora,
};

const instruction ora_abx = {
    .mnemonic = "ora",
    .opcode = 0x1d,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abx,
    .operation = &__base_ora,
};

const instruction ora_aby = {
    .mnemonic = "ora",
    .opcode = 0x19,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_aby,
    .operation = &__base_ora,
};

const instruction ora_idx = {
    .mnemonic = "ora",
    .opcode = 0x01,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_idx,
    .operation = &__base_ora,
};

const instruction ora_idy = {
    .mnemonic = "ora",
    .opcode = 0x11,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_idy,
    .operation = &__base_ora,
};

void register_logic_instruction_set() {
    register_instruction(and_imm);
    register_instruction(and_zp);
    register_instruction(and_zpx);
    register_instruction(and_abs);
    register_instruction(and_abx);
    register_instruction(and_aby);
    register_instruction(and_idx);
    register_instruction(and_idy);

    register_instruction(bit_zp);
    register_instruction(bit_abs);

    register_instruction(eor_imm);
    register_instruction(eor_zp);
    register_instruction(eor_zpx);
    register_instruction(eor_abs);
    register_instruction(eor_abx);
    register_instruction(eor_aby);
    register_instruction(eor_idx);
    register_instruction(eor_idy);

    register_instruction(ora_imm);
    register_instruction(ora_zp);
    register_instruction(ora_zpx);
    register_instruction(ora_abs);
    register_instruction(ora_abx);
    register_instruction(ora_aby);
    register_instruction(ora_idx);
    register_instruction(ora_idy);
}