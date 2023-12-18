#include <instruction.h>
#include <core/cpu.h>
#include <core/memory.h>

void __base_brk() {
    CPU->__cycles++;
    push(CPU->PC >> 8);
    push(CPU->PC & 0xff);
    CPU->PS.flags.B = 1;
    push(CPU->PS.reg);

    CPU->PC = mem_read(MEM_INTR_HANDLER_L);
    CPU->__cycles++;
    CPU->PC |= (mem_read(MEM_INTR_HANDLER_H) << 8);
    CPU->__cycles++;
}

const instruction brk_imp = {
    .mnemonic = "brk",
    .opcode = 0x00,
    .total_bytes = 1,
    .addr_mode = &__addr_mode_imp,
    .operation = &__base_brk,
};

void __base_jmp() {
    CPU->PC = CPU->__al;
}

const instruction jmp_abs = {
    .mnemonic = "jmp",
    .opcode = 0x4c,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abs,
    .operation = &__base_jmp,
};

const instruction jmp_ind = {
    .mnemonic = "jmp",
    .opcode = 0x6c,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_ind,
    .operation = &__base_jmp,
};

void __base_jsr() {
    CPU->PC--;
    push(CPU->PC >> 8);
    push(CPU->PC & 0xff);

    CPU->PC = CPU->__al;
    CPU->__cycles++;
}

const instruction jsr_abs = {
    .mnemonic = "jsr",
    .opcode = 0x20,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abs,
    .operation = &__base_jsr,
};

void __base_rti() {
    CPU->PS.reg = (pop() & 0xEF) | 0x20;
    CPU->PC = pop();
    CPU->__cycles++;
    CPU->PC |= pop() << 8;
    CPU->__cycles++;
}

const instruction rti_imp = {
    .mnemonic = "rti",
    .opcode = 0x40,
    .total_bytes = 1,
    .addr_mode = &__addr_mode_imp,
    .operation = &__base_rti,
};

void __base_rts() {
    CPU->__cycles++;
    CPU->PC = pop();
    CPU->__cycles++;
    CPU->PC |= pop() << 8;
    CPU->PC++;
    // printf("RTS addr: %X\n", CPU->PC);
    CPU->__cycles++;
}

const instruction rts_imp = {
    .mnemonic = "rts",
    .opcode = 0x60,
    .total_bytes = 1,
    .addr_mode = &__addr_mode_imp,
    .operation = &__base_rts,
};

void register_ctrl_instruction_set() {
    register_instruction(brk_imp);

    register_instruction(jmp_abs);
    register_instruction(jmp_ind);

    register_instruction(jsr_abs);

    register_instruction(rti_imp);

    register_instruction(rts_imp);
}