#include <instruction.h>
#include <core/cpu.h>

void __base_clc() {
    CPU->PS.flags.C = 0;
    CPU->__cycles++;
}

const instruction clc_imp = {
    .mnemonic = "clc",
    .opcode = 0x18,
    .total_bytes = 1,
    .addr_mode = &__addr_mode_imp,
    .operation = &__base_clc,
};

void __base_cld() {
    CPU->PS.flags.D = 0;
    CPU->__cycles++;
}

const instruction cld_imp = {
    .mnemonic = "cld",
    .opcode = 0xd8,
    .total_bytes = 1,
    .addr_mode = &__addr_mode_imp,
    .operation = &__base_cld,
};

void __base_cli() {
    CPU->PS.flags.I = 0;
    CPU->__cycles++;
}

const instruction cli_imp = {
    .mnemonic = "cli",
    .opcode = 0x58,
    .total_bytes = 1,
    .addr_mode = &__addr_mode_imp,
    .operation = &__base_cli,
};

void __base_clv() {
    CPU->PS.flags.V = 0;
    CPU->__cycles++;
}

const instruction clv_imp = {
    .mnemonic = "clv",
    .opcode = 0xb8,
    .total_bytes = 1,
    .addr_mode = &__addr_mode_imp,
    .operation = &__base_clv,
};

void __base_sec() {
    CPU->PS.flags.C = 1;
    CPU->__cycles++;
}

const instruction sec_imp = {
    .mnemonic = "sec",
    .opcode = 0x38,
    .total_bytes = 1,
    .addr_mode = &__addr_mode_imp,
    .operation = &__base_sec,
};

void __base_sed() {
    CPU->PS.flags.D = 1;
    CPU->__cycles++;
}

const instruction sed_imp = {
    .mnemonic = "sed",
    .opcode = 0xf8,
    .total_bytes = 1,
    .addr_mode = &__addr_mode_imp,
    .operation = &__base_sed,
};

void __base_sei() {
    CPU->PS.flags.I = 1;
    CPU->__cycles++;
}

const instruction sei_imp = {
    .mnemonic = "sei",
    .opcode = 0x78,
    .total_bytes = 1,
    .addr_mode = &__addr_mode_imp,
    .operation = &__base_sei,
};

void register_flags_instruction_set() {
    register_instruction(clc_imp);
    register_instruction(cld_imp);
    register_instruction(cli_imp);
    register_instruction(clv_imp);
    register_instruction(sec_imp);
    register_instruction(sed_imp);
    register_instruction(sei_imp);
}