#include <instruction.h>
#include <core/cpu.h>
#include <core/memory.h>

void __transfer_data(uint8_t *dest, uint8_t data) {
    *dest = data;
    CPU->PS.flags.Z = data == 0;
    CPU->PS.flags.N = data >> 7;
    
    CPU->__cycles++;
}

void __base_lda() {
    __transfer_data(&CPU->A, CPU->__dl);
}

const instruction lda_imm = {
    .mnemonic = "lda",
    .opcode = 0xa9,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_imm,
    .operation = &__base_lda,
};

const instruction lda_zp = {
    .mnemonic = "lda",
    .opcode = 0xa5,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zp,
    .operation = &__base_lda,
};

const instruction lda_zpx = {
    .mnemonic = "lda",
    .opcode = 0xb5,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zpx,
    .operation = &__base_lda,
};

const instruction lda_abs = {
    .mnemonic = "lda",
    .opcode = 0xad,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abs,
    .operation = &__base_lda,
};

const instruction lda_abx = {
    .mnemonic = "lda",
    .opcode = 0xbd,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abx,
    .operation = &__base_lda,
};

const instruction lda_aby = {
    .mnemonic = "lda",
    .opcode = 0xb9,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_aby,
    .operation = &__base_lda,
};

const instruction lda_idx = {
    .mnemonic = "lda",
    .opcode = 0xa1,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_idx,
    .operation = &__base_lda,
};

const instruction lda_idy = {
    .mnemonic = "lda",
    .opcode = 0xb1,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_idy,
    .operation = &__base_lda,
};

void __base_ldx() {
    __transfer_data(&CPU->X, CPU->__dl);
}

const instruction ldx_imm = {
    .mnemonic = "ldx",
    .opcode = 0xa2,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_imm,
    .operation = &__base_ldx,
};

const instruction ldx_zp = {
    .mnemonic = "ldx",
    .opcode = 0xa6,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zp,
    .operation = &__base_ldx,
};

const instruction ldx_zpy = {
    .mnemonic = "ldx",
    .opcode = 0xb6,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zpy,
    .operation = &__base_ldx,
};

const instruction ldx_abs = {
    .mnemonic = "ldx",
    .opcode = 0xae,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abs,
    .operation = &__base_ldx,
};

const instruction ldx_aby = {
    .mnemonic = "ldx",
    .opcode = 0xbe,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_aby,
    .operation = &__base_ldx,
};

void __base_ldy() {
    __transfer_data(&CPU->Y, CPU->__dl);
}

const instruction ldy_imm = {
    .mnemonic = "ldy",
    .opcode = 0xa0,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_imm,
    .operation = &__base_ldy,
};

const instruction ldy_zp = {
    .mnemonic = "ldy",
    .opcode = 0xa4,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zp,
    .operation = &__base_ldy,
};

const instruction ldy_zpx = {
    .mnemonic = "ldy",
    .opcode = 0xb4,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zpx,
    .operation = &__base_ldy,
};

const instruction ldy_abs = {
    .mnemonic = "ldy",
    .opcode = 0xac,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abs,
    .operation = &__base_ldy,
};

const instruction ldy_abx = {
    .mnemonic = "ldy",
    .opcode = 0xbc,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abx,
    .operation = &__base_ldy,
};

void __base_sta() {
    mem_write(CPU->__al, CPU->A);
    CPU->__cycles++;
}

const instruction sta_zp = {
    .mnemonic = "sta",
    .opcode = 0x85,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zp,
    .operation = &__base_sta,
};

const instruction sta_zpx = {
    .mnemonic = "sta",
    .opcode = 0x95,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zpx,
    .operation = &__base_sta,
};

const instruction sta_abs = {
    .mnemonic = "sta",
    .opcode = 0x8d,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abs,
    .operation = &__base_sta,
};

const instruction sta_abx = {
    .mnemonic = "sta",
    .opcode = 0x9d,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abx,
    .operation = &__base_sta,
};

const instruction sta_aby = {
    .mnemonic = "sta",
    .opcode = 0x99,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_aby,
    .operation = &__base_sta,
};

const instruction sta_idx = {
    .mnemonic = "sta",
    .opcode = 0x81,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_idx,
    .operation = &__base_sta,
};

const instruction sta_idy = {
    .mnemonic = "sta",
    .opcode = 0x91,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_idy,
    .operation = &__base_sta,
};

void __base_stx() {
    mem_write(CPU->__al, CPU->X);
    CPU->__cycles++;
}

const instruction stx_zp = {
    .mnemonic = "stx",
    .opcode = 0x86,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zp,
    .operation = &__base_stx,
};

const instruction stx_zpy = {
    .mnemonic = "stx",
    .opcode = 0x96,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zpy,
    .operation = &__base_stx,
};

const instruction stx_abs = {
    .mnemonic = "stx",
    .opcode = 0x8e,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abs,
    .operation = &__base_stx,
};

void __base_sty() {
    mem_write(CPU->__al, CPU->Y);
    CPU->__cycles++;
}

const instruction sty_zp = {
    .mnemonic = "sty",
    .opcode = 0x84,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zp,
    .operation = &__base_sty,
};

const instruction sty_zpx = {
    .mnemonic = "sty",
    .opcode = 0x94,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zpx,
    .operation = &__base_sty,
};

const instruction sty_abs = {
    .mnemonic = "sty",
    .opcode = 0x8c,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abs,
    .operation = &__base_sty,
};

void register_load_instruction_set() {
    register_instruction(lda_imm);
    register_instruction(lda_zp);
    register_instruction(lda_zpx);
    register_instruction(lda_abs);
    register_instruction(lda_abx);
    register_instruction(lda_aby);
    register_instruction(lda_idx);
    register_instruction(lda_idy);

    register_instruction(ldx_imm);
    register_instruction(ldx_zp);
    register_instruction(ldx_zpy);
    register_instruction(ldx_abs);
    register_instruction(ldx_aby);

    register_instruction(ldy_imm);
    register_instruction(ldy_zp);
    register_instruction(ldy_zpx);
    register_instruction(ldy_abs);
    register_instruction(ldy_abx);

    register_instruction(sta_zp);
    register_instruction(sta_zpx);
    register_instruction(sta_abs);
    register_instruction(sta_abx);
    register_instruction(sta_aby);
    register_instruction(sta_idx);
    register_instruction(sta_idy);

    register_instruction(stx_zp);
    register_instruction(stx_zpy);
    register_instruction(stx_abs);

    register_instruction(sty_zp);
    register_instruction(sty_zpx);
    register_instruction(sty_abs);
}