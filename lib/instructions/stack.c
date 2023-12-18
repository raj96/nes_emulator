#include <instruction.h>
#include <core/cpu.h>
#include <core/memory.h>

void __base_pha() {
    push(CPU->A);
}

const instruction pha_imp = {
    .mnemonic = "pha",
    .opcode = 0x48,
    .total_bytes = 1,
    .addr_mode = &__addr_mode_imp,
    .operation = &__base_pha,
};

void __base_php() {
    push(CPU->PS.reg | 0x10);
}

const instruction php_imp = {
    .mnemonic = "php",
    .opcode = 0x08,
    .total_bytes = 1,
    .addr_mode = &__addr_mode_imp,
    .operation = &__base_php,
};

void __base_pla() {
    CPU->A = pop();

    CPU->__cycles++;
    CPU->PS.flags.Z = CPU->A == 0x00;
    CPU->PS.flags.N = CPU->A >> 7;
}

const instruction pla_imp = {
    .mnemonic = "pla",
    .opcode = 0x68,
    .total_bytes = 1,
    .addr_mode = &__addr_mode_imp,
    .operation = &__base_pla,
};

void __base_plp() {
    CPU->PS.reg = (pop() & 0xEF) | 0x20;

    CPU->__cycles++;
}

const instruction plp_imp = {
    .mnemonic = "plp",
    .opcode = 0x28,
    .total_bytes = 1,
    .addr_mode = &__addr_mode_imp,
    .operation = &__base_plp,
};

void register_stack_instruction_set() {
    register_instruction(pha_imp);
    register_instruction(php_imp);
    register_instruction(pla_imp);
    register_instruction(plp_imp);
}