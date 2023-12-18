#include <instruction.h>
#include <core/cpu.h>
#include <core/memory.h>

void __base_dec() {
    CPU->__dl--;
    CPU->PS.flags.Z = CPU->__dl == 0x00;
    CPU->PS.flags.N = CPU->__dl >> 7;
    CPU->__cycles++;

    mem_write(CPU->__al, CPU->__dl);
}

const instruction dec_zp = {
    .mnemonic = "dec",
    .opcode = 0xc6,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zp,
    .operation = &__base_dec,
};

const instruction dec_zpx = {
    .mnemonic = "dec",
    .opcode = 0xd6,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zpx,
    .operation = &__base_dec,
};

const instruction dec_abs = {
    .mnemonic = "dec",
    .opcode = 0xce,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abs,
    .operation = &__base_dec,
};

const instruction dec_abx = {
    .mnemonic = "dec",
    .opcode = 0xde,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abx,
    .operation = &__base_dec,
};

void __base_dex() {
    CPU->X--;

    CPU->PS.flags.Z = CPU->X == 0x00;
    CPU->PS.flags.N = CPU->X >> 7;
    CPU->__cycles++;
}

const instruction dex_imp = {
    .mnemonic = "dex",
    .opcode = 0xca,
    .total_bytes = 1,
    .addr_mode = &__addr_mode_imp,
    .operation = &__base_dex,
};

void __base_dey() {
    CPU->Y--;

    CPU->PS.flags.Z = CPU->Y == 0x00;
    CPU->PS.flags.N = CPU->Y >> 7;
    CPU->__cycles++;
}

const instruction dey_imp = {
    .mnemonic = "dey",
    .opcode = 0x88,
    .total_bytes = 1,
    .addr_mode = &__addr_mode_imp,
    .operation = &__base_dey,
};

void __base_inc() {
    CPU->__dl++;
    CPU->PS.flags.Z = CPU->__dl == 0x00;
    CPU->PS.flags.N = CPU->__dl >> 7;
    CPU->__cycles++;

    mem_write(CPU->__al, CPU->__dl);
}

const instruction inc_zp = {
    .mnemonic = "inc",
    .opcode = 0xe6,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zp,
    .operation = &__base_inc,
};

const instruction inc_zpx = {
    .mnemonic = "inc",
    .opcode = 0xf6,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zpx,
    .operation = &__base_inc,
};

const instruction inc_abs = {
    .mnemonic = "inc",
    .opcode = 0xee,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abs,
    .operation = &__base_inc,
};

const instruction inc_abx = {
    .mnemonic = "inc",
    .opcode = 0xfe,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abx,
    .operation = &__base_inc,
};

void __base_inx() {
    CPU->X++;

    CPU->PS.flags.Z = CPU->X == 0x00;
    CPU->PS.flags.N = CPU->X >> 7;
    CPU->__cycles++;
}

const instruction inx_imp = {
    .mnemonic = "inx",
    .opcode = 0xe8,
    .total_bytes = 1,
    .addr_mode = &__addr_mode_imp,
    .operation = &__base_inx,
};

void __base_iny() {
    CPU->Y++;

    CPU->PS.flags.Z = CPU->Y == 0x00;
    CPU->PS.flags.N = CPU->Y >> 7;
    CPU->__cycles++;
}

const instruction iny_imp = {
    .mnemonic = "iny",
    .opcode = 0xc8,
    .total_bytes = 1,
    .addr_mode = &__addr_mode_imp,
    .operation = &__base_iny,
};

void register_inc_instruction_set() {
    register_instruction(dec_zp);
    register_instruction(dec_zpx);
    register_instruction(dec_abs);
    register_instruction(dec_abx);

    register_instruction(dex_imp);
    
    register_instruction(dey_imp);

    register_instruction(inc_zp);
    register_instruction(inc_zpx);
    register_instruction(inc_abs);
    register_instruction(inc_abx);

    register_instruction(inx_imp);

    register_instruction(iny_imp);
}