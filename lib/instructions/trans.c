#include <instruction.h>
#include <core/cpu.h>
#include <core/memory.h>

void __base_transfer(uint8_t *dest, uint8_t data) {
    *dest = data;
    
    CPU->PS.flags.Z = data == 0x00;
    CPU->PS.flags.N = data >> 7;
    CPU->__cycles++;
}

void __base_tax() {
    __base_transfer(&CPU->X, CPU->A);
}

const instruction tax_imp = {
    .mnemonic = "tax",
    .opcode = 0xaa,
    .total_bytes = 1,
    .addr_mode = &__addr_mode_imp,
    .operation = &__base_tax,
};

void __base_tay() {
    __base_transfer(&CPU->Y, CPU->A);
}

const instruction tay_imp = {
    .mnemonic = "tay",
    .opcode = 0xa8,
    .total_bytes = 1,
    .addr_mode = &__addr_mode_imp,
    .operation = &__base_tay,
};

void __base_tsx() {
    __base_transfer(&CPU->X, CPU->SP);
}

const instruction tsx_imp = {
    .mnemonic = "tsx",
    .opcode = 0xba,
    .total_bytes = 1,
    .addr_mode = &__addr_mode_imp,
    .operation = &__base_tsx,
};

void __base_txa() {
    __base_transfer(&CPU->A, CPU->X);
}

const instruction txa_imp = {
    .mnemonic = "txa",
    .opcode = 0x8a,
    .total_bytes = 1,
    .addr_mode = &__addr_mode_imp,
    .operation = &__base_txa,
};

void __base_txs() {
    CPU->SP = CPU->X;
    // __base_transfer(&CPU->SP, CPU->X);
}

const instruction txs_imp = {
    .mnemonic = "txs",
    .opcode = 0x9a,
    .total_bytes = 1,
    .addr_mode = &__addr_mode_imp,
    .operation = &__base_txs,
};

void __base_tya() {
    __base_transfer(&CPU->A, CPU->Y);
}

const instruction tya_imp = {
    .mnemonic = "tya",
    .opcode = 0x98,
    .total_bytes = 1,
    .addr_mode = &__addr_mode_imp,
    .operation = &__base_tya,
};

void register_trans_instruction_set() {
    register_instruction(tax_imp);
    register_instruction(tay_imp);
    register_instruction(tsx_imp);
    register_instruction(txa_imp);
    register_instruction(txs_imp);
    register_instruction(tya_imp);
}