#include <instruction.h>
#include <core/cpu.h>

void __base_nop() {
    CPU->__cycles++;
}

const instruction nop_imp = {
    .mnemonic = "nop",
    .opcode = 0xea,
    .total_bytes = 1,
    .addr_mode = &__addr_mode_imp,
    .operation = &__base_nop,
};

void register_nop_instruction_set() {
    register_instruction(nop_imp);
}