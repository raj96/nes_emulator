#include <core/cpu.h>
#include <instruction.h>
#include <log.h>

void __base_branch(int does_branch) {
    if ((CPU->PC & 0xff) + CPU->__dl > 0xff) {
        CPU->__cycles += 2;
    }

    if (does_branch) {
        CPU->PC += (int8_t)CPU->__dl;
        CPU->__cycles++;
    }
}

void __base_bcc() {
    __base_branch(CPU->PS.flags.C == 0);
}

const instruction bcc_rel = {
    .mnemonic = "bcc",
    .opcode = 0x90,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_rel,
    .operation = &__base_bcc,
};

void __base_bcs() {
    __base_branch(CPU->PS.flags.C == 1);
}

const instruction bcs_rel = {
    .mnemonic = "bcs",
    .opcode = 0xb0,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_rel,
    .operation = &__base_bcs,
};

void __base_beq() {
    __base_branch(CPU->PS.flags.Z == 1);
}

const instruction beq_rel = {
    .mnemonic = "beq",
    .opcode = 0xf0,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_rel,
    .operation = &__base_beq,
};

void __base_bmi() {
    __base_branch(CPU->PS.flags.N == 1);
}

const instruction bmi_rel = {
    .mnemonic = "bmi",
    .opcode = 0x30,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_rel,
    .operation = &__base_bmi,
};

void __base_bne() {
    __base_branch(CPU->PS.flags.Z == 0);
}

const instruction bne_rel = {
    .mnemonic = "bne",
    .opcode = 0xd0,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_rel,
    .operation = &__base_bne,
};

void __base_bpl() {
    __base_branch(CPU->PS.flags.N == 0);
}

const instruction bpl_rel = {
    .mnemonic = "bpl",
    .opcode = 0x10,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_rel,
    .operation = &__base_bpl,
};

void __base_bvc() {
    __base_branch(CPU->PS.flags.V == 0);
}

const instruction bvc_rel = {
    .mnemonic = "bvc",
    .opcode = 0x50,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_rel,
    .operation = &__base_bvc,
};

void __base_bvs() {
    __base_branch(CPU->PS.flags.V == 1);
}

const instruction bvs_rel = {
    .mnemonic = "bvs",
    .opcode = 0x70,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_rel,
    .operation = &__base_bvs,
};

void register_branch_instruction_set() {
    register_instruction(bcc_rel);
    register_instruction(bcs_rel);
    register_instruction(beq_rel);
    register_instruction(bmi_rel);
    register_instruction(bne_rel);
    register_instruction(bpl_rel);
    register_instruction(bvc_rel);
    register_instruction(bvs_rel);
}