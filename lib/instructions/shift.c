#include "core/cpu.h"
#include "core/memory.h"
#include "instruction.h"

uint8_t __base_asl_op(uint8_t value) {
    CPU->PS.flags.C = value >> 7;
    CPU->__dl = value << 1;

    CPU->PS.flags.Z = CPU->__dl == 0x00;
    CPU->PS.flags.N = CPU->__dl >> 7;

    CPU->__cycles++;

    return CPU->__dl;
}

void __asl_acc_op() {
    CPU->A = __base_asl_op(CPU->A);
}

void __asl_mem_op() {
    mem_write(CPU->__al, __base_asl_op(CPU->__dl));
}

const instruction asl_acc = {
    .mnemonic = "asl",
    .opcode = 0x0a,
    .total_bytes = 1,
    .addr_mode = &__addr_mode_acc,
    .operation = &__asl_acc_op};

const instruction asl_zp = {
    .mnemonic = "asl",
    .opcode = 0x06,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zp,
    .operation = &__asl_mem_op};

const instruction asl_zpx = {
    .mnemonic = "asl",
    .opcode = 0x16,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zpx,
    .operation = &__asl_mem_op};

const instruction asl_abs = {
    .mnemonic = "asl",
    .opcode = 0x0e,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abs,
    .operation = &__asl_mem_op};

const instruction asl_abx = {
    .mnemonic = "asl",
    .opcode = 0x1e,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abx,
    .operation = &__asl_mem_op};

uint8_t __base_lsr_op(uint8_t data) {
    CPU->PS.flags.C = data & 0x01;

    CPU->__dl = data >> 1;

    CPU->__cycles++;
    CPU->PS.flags.Z = CPU->__dl == 0x00;
    CPU->PS.flags.N = CPU->__dl >> 7;

    return CPU->__dl;
}

void __lsr_acc_op() {
    CPU->A = __base_lsr_op(CPU->A);
}

void __lsr_mem_op() {
    mem_write(CPU->__al, __base_lsr_op(CPU->__dl));
}

const instruction lsr_acc = {
    .mnemonic = "lsr",
    .opcode = 0x4a,
    .total_bytes = 1,
    .addr_mode = &__addr_mode_acc,
    .operation = &__lsr_acc_op,
};

const instruction lsr_zp = {
    .mnemonic = "lsr",
    .opcode = 0x46,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zp,
    .operation = &__lsr_mem_op,
};

const instruction lsr_zpx = {
    .mnemonic = "lsr",
    .opcode = 0x56,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zpx,
    .operation = &__lsr_mem_op,
};

const instruction lsr_abs = {
    .mnemonic = "lsr",
    .opcode = 0x4e,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abs,
    .operation = &__lsr_mem_op,
};

const instruction lsr_abx = {
    .mnemonic = "lsr",
    .opcode = 0x5e,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abx,
    .operation = &__lsr_mem_op,
};

uint8_t __base_rol_op(uint8_t data) {
    CPU->__dl = (data << 1)  | CPU->PS.flags.C;

    CPU->PS.flags.C = data >> 7;

    CPU->PS.flags.Z = CPU->__dl == 0x00;
    CPU->PS.flags.N = CPU->__dl >> 7;

    return CPU->__dl;
}

void __rol_acc_op() {
    CPU->A = __base_rol_op(CPU->A);
}

void __rol_mem_op() {
    mem_write(CPU->__al, __base_rol_op(CPU->__dl));
}

const instruction rol_acc = {
    .mnemonic = "rol",
    .opcode = 0x2a,
    .total_bytes = 1,
    .addr_mode = &__addr_mode_acc,
    .operation = &__rol_acc_op,
};

const instruction rol_zp = {
    .mnemonic = "rol",
    .opcode = 0x26,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zp,
    .operation = &__rol_mem_op,
};

const instruction rol_zpx = {
    .mnemonic = "rol",
    .opcode = 0x36,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zpx,
    .operation = &__rol_mem_op,
};

const instruction rol_abs = {
    .mnemonic = "rol",
    .opcode = 0x2e,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abs,
    .operation = &__rol_mem_op,
};

const instruction rol_abx = {
    .mnemonic = "rol",
    .opcode = 0x3e,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abx,
    .operation = &__rol_mem_op,
};

uint8_t __base_ror_op(uint8_t data) {
    CPU->PS.flags.N = CPU->PS.flags.C;
    CPU->__dl = (data >> 1)  | (CPU->PS.flags.C << 7);

    CPU->PS.flags.C = data & 0x01;

    CPU->PS.flags.Z = CPU->__dl == 0x00;

    return CPU->__dl;
}

void __ror_acc_op() {
    CPU->A = __base_ror_op(CPU->A);
}

void __ror_mem_op() {
    mem_write(CPU->__al, __base_ror_op(CPU->__dl));
}

const instruction ror_acc = {
    .mnemonic = "ror",
    .opcode = 0x6a,
    .total_bytes = 1,
    .addr_mode = &__addr_mode_acc,
    .operation = &__ror_acc_op,
};

const instruction ror_zp = {
    .mnemonic = "ror",
    .opcode = 0x66,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zp,
    .operation = &__ror_mem_op,
};

const instruction ror_zpx = {
    .mnemonic = "ror",
    .opcode = 0x76,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zpx,
    .operation = &__ror_mem_op,
};

const instruction ror_abs = {
    .mnemonic = "ror",
    .opcode = 0x6e,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abs,
    .operation = &__ror_mem_op,
};

const instruction ror_abx = {
    .mnemonic = "ror",
    .opcode = 0x7e,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abx,
    .operation = &__ror_mem_op,
};

void register_shift_instruction_set() {
    register_instruction(asl_acc);
    register_instruction(asl_zp);
    register_instruction(asl_zpx);
    register_instruction(asl_abs);
    register_instruction(asl_abx);

    register_instruction(lsr_acc);
    register_instruction(lsr_zp);
    register_instruction(lsr_zpx);
    register_instruction(lsr_abs);
    register_instruction(lsr_abx);

    register_instruction(rol_acc);
    register_instruction(rol_zp);
    register_instruction(rol_zpx);
    register_instruction(rol_abs);
    register_instruction(rol_abx);

    register_instruction(ror_acc);
    register_instruction(ror_zp);
    register_instruction(ror_zpx);
    register_instruction(ror_abs);
    register_instruction(ror_abx);
}