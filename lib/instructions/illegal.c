#include <core/cpu.h>
#include <core/memory.h>
#include <instruction.h>
#include <log.h>

extern void __base_adc();
extern void __base_sbc();
extern void __base_nop();
extern void __rol_mem_op();
extern void __ror_mem_op();
extern void __asl_mem_op();
extern void __lsr_mem_op();
extern void __base_and();
extern void __base_ora();
extern void __base_eor();

void __base_aac() {
    CPU->A &= mem_read(CPU->PC);
    CPU->PS.flags.N = CPU->A >> 7;
    CPU->PS.flags.Z = CPU->A == 0x00;
    CPU->PS.flags.C = CPU->PS.flags.N;

    CPU->__cycles++;
}

const instruction aac_imm = {
    .mnemonic = "aac",
    .opcode = 0x0b,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_imm,
    .operation = &__base_aac,
};

const instruction aac_imm2 = {
    .mnemonic = "aac",
    .opcode = 0x2b,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_imm,
    .operation = &__base_aac,
};

void __base_aax() {
    CPU->__dl = CPU->X & CPU->A;
    CPU->PS.flags.N = CPU->__dl >> 7;
    CPU->PS.flags.Z = CPU->__dl == 0x00;
    mem_write(CPU->__al, CPU->__dl);
    CPU->__cycles++;
}

const instruction aax_zp = {
    .mnemonic = "aax",
    .opcode = 0x87,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zp,
    .operation = &__base_aax,
};

const instruction aax_zpy = {
    .mnemonic = "aax",
    .opcode = 0x97,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zpy,
    .operation = &__base_aax,
};

const instruction aax_idx = {
    .mnemonic = "aax",
    .opcode = 0x83,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_idx,
    .operation = &__base_aax,
};

const instruction aax_abs = {
    .mnemonic = "aax",
    .opcode = 0x8f,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abs,
    .operation = &__base_aax,
};

void __base_arr() {
    CPU->A &= CPU->__dl;
    CPU->A >>= 1;
    CPU->A |= CPU->PS.flags.C << 7;

    uint8_t bits6_5 = (CPU->A >> 4) & 0x03;
    switch (bits6_5) {
        case 0x00:
            CPU->PS.flags.C = 0;
            CPU->PS.flags.V = 0;
            break;
        case 0x01:
            CPU->PS.flags.C = 0;
            CPU->PS.flags.V = 1;
            break;
        case 0x02:
            CPU->PS.flags.C = 1;
            CPU->PS.flags.V = 1;
            break;
        case 0x03:
            CPU->PS.flags.C = 1;
            CPU->PS.flags.V = 0;
            break;
    }

    CPU->PS.flags.N = CPU->A >> 7;
    CPU->PS.flags.Z = CPU->A == 0x00;

    CPU->__cycles++;
}

const instruction arr_imm = {
    .mnemonic = "arr",
    .opcode = 0x6b,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_imm,
    .operation = &__base_arr,
};

void __base_asr() {
    CPU->A &= CPU->__dl;
    CPU->PS.flags.C = CPU->A & 0x01;
    CPU->A >>= 1;

    CPU->PS.flags.N = 0x00;
    CPU->PS.flags.Z = CPU->A == 0x00;
    CPU->__cycles++;
}

const instruction asr_imm = {
    .mnemonic = "asr",
    .opcode = 0x4b,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_imm,
    .operation = &__base_asr,
};

void __base_atx() {
    CPU->A &= CPU->__dl;
    CPU->X = CPU->A;

    CPU->PS.flags.N = CPU->A >> 7;
    CPU->PS.flags.Z = CPU->A == 0x00;
    CPU->__cycles++;
}

const instruction atx_imm = {
    .mnemonic = "atx",
    .opcode = 0xab,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_imm,
    .operation = &__base_atx,
};

void __base_axa() {
    CPU->__dl = (CPU->X & CPU->A) & 0x07;
    mem_write(CPU->__al, CPU->__dl);
    CPU->__cycles++;
}

const instruction axa_aby = {
    .mnemonic = "axa",
    .opcode = 0x9f,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_aby,
    .operation = &__base_axa,
};

const instruction axa_idy = {
    .mnemonic = "axa",
    .opcode = 0x93,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_idy,
    .operation = &__base_axa,
};

void __base_axs() {
    CPU->X &= CPU->A;
    uint16_t res = CPU->X - CPU->__dl;
    CPU->X = res;

    CPU->PS.flags.N = CPU->X >> 7;
    CPU->PS.flags.Z = CPU->X == 0x00;
    CPU->PS.flags.C = res >> 8;

    CPU->__cycles++;
}

const instruction axs_imm = {
    .mnemonic = "axs",
    .opcode = 0xcb,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_imm,
    .operation = &__base_axs,
};

void __base_dcp() {
    uint16_t res = CPU->__dl - 1;
    mem_write(CPU->__al, res);

    CPU->PS.flags.C = res >> 8;
    CPU->__cycles++;
}

const instruction dcp_zp = {
    .mnemonic = "dcp",
    .opcode = 0xc7,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zp,
    .operation = &__base_dcp,
};

const instruction dcp_zpx = {
    .mnemonic = "dcp",
    .opcode = 0xd7,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zpx,
    .operation = &__base_dcp,
};

const instruction dcp_abs = {
    .mnemonic = "dcp",
    .opcode = 0xcf,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abs,
    .operation = &__base_dcp,
};

const instruction dcp_abx = {
    .mnemonic = "dcp",
    .opcode = 0xdf,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abx,
    .operation = &__base_dcp,
};

const instruction dcp_aby = {
    .mnemonic = "dcp",
    .opcode = 0xdb,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_aby,
    .operation = &__base_dcp,
};

const instruction dcp_idx = {
    .mnemonic = "dcp",
    .opcode = 0xc3,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_idx,
    .operation = &__base_dcp,
};

const instruction dcp_idy = {
    .mnemonic = "dcp",
    .opcode = 0xd3,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_idy,
    .operation = &__base_dcp,
};

void __base_dop() {
    __base_nop();
    __base_nop();
}

const instruction dop_zp = {
    .mnemonic = "dop",
    .opcode = 0x04,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zp,
    .operation = &__base_dop,
};

const instruction dop_zpx = {
    .mnemonic = "dop",
    .opcode = 0x14,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zpx,
    .operation = &__base_dop,
};

const instruction dop_zpx2 = {
    .mnemonic = "dop",
    .opcode = 0x34,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zpx,
    .operation = &__base_dop,
};

const instruction dop_zp2 = {
    .mnemonic = "dop",
    .opcode = 0x44,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zp,
    .operation = &__base_dop,
};

const instruction dop_zpx3 = {
    .mnemonic = "dop",
    .opcode = 0x54,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zpx,
    .operation = &__base_dop,
};

const instruction dop_zp3 = {
    .mnemonic = "dop",
    .opcode = 0x64,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zp,
    .operation = &__base_dop,
};

const instruction dop_zpx4 = {
    .mnemonic = "dop",
    .opcode = 0x74,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zpx,
    .operation = &__base_dop,
};

const instruction dop_imm = {
    .mnemonic = "dop",
    .opcode = 0x80,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_imm,
    .operation = &__base_dop,
};

const instruction dop_imm2 = {
    .mnemonic = "dop",
    .opcode = 0x82,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_imm,
    .operation = &__base_dop,
};

const instruction dop_imm3 = {
    .mnemonic = "dop",
    .opcode = 0x89,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_imm,
    .operation = &__base_dop,
};

const instruction dop_imm4 = {
    .mnemonic = "dop",
    .opcode = 0xc2,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_imm,
    .operation = &__base_dop,
};

const instruction dop_zpx5 = {
    .mnemonic = "dop",
    .opcode = 0xd4,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zpx,
    .operation = &__base_dop,
};

const instruction dop_imm5 = {
    .mnemonic = "dop",
    .opcode = 0xe2,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_imm,
    .operation = &__base_dop,
};

const instruction dop_zpx6 = {
    .mnemonic = "dop",
    .opcode = 0xf4,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zpx,
    .operation = &__base_dop,
};

void __base_isc() {
    CPU->__al++;
    CPU->__dl = 255 - mem_read(CPU->__al);
    __base_adc();
}

const instruction isc_zp = {
    .mnemonic = "isc",
    .opcode = 0xe7,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zp,
    .operation = &__base_isc,
};

const instruction isc_zpx = {
    .mnemonic = "isc",
    .opcode = 0xf7,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zpx,
    .operation = &__base_isc,
};

const instruction isc_abs = {
    .mnemonic = "isc",
    .opcode = 0xef,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abs,
    .operation = &__base_isc,
};

const instruction isc_abx = {
    .mnemonic = "isc",
    .opcode = 0xff,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abx,
    .operation = &__base_isc,
};

const instruction isc_aby = {
    .mnemonic = "isc",
    .opcode = 0xfb,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_aby,
    .operation = &__base_isc,
};

const instruction isc_idx = {
    .mnemonic = "isc",
    .opcode = 0xe3,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_idx,
    .operation = &__base_isc,
};

const instruction isc_idy = {
    .mnemonic = "isc",
    .opcode = 0xf3,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_idy,
    .operation = &__base_isc,
};

void __base_kil() {
    CPU->__dl = 0xff;
    CPU->__lock = 1;
    CPU->__cycles++;
}

const instruction kil_imp = {
    .mnemonic = "kil",
    .opcode = 0x02,
    .total_bytes = 1,
    .addr_mode = &__addr_mode_imp,
    .operation = &__base_kil,
};

const instruction kil_imp2 = {
    .mnemonic = "kil",
    .opcode = 0x12,
    .total_bytes = 1,
    .addr_mode = &__addr_mode_imp,
    .operation = &__base_kil,
};

const instruction kil_imp3 = {
    .mnemonic = "kil",
    .opcode = 0x22,
    .total_bytes = 1,
    .addr_mode = &__addr_mode_imp,
    .operation = &__base_kil,
};

const instruction kil_imp4 = {
    .mnemonic = "kil",
    .opcode = 0x32,
    .total_bytes = 1,
    .addr_mode = &__addr_mode_imp,
    .operation = &__base_kil,
};

const instruction kil_imp5 = {
    .mnemonic = "kil",
    .opcode = 0x42,
    .total_bytes = 1,
    .addr_mode = &__addr_mode_imp,
    .operation = &__base_kil,
};

const instruction kil_imp6 = {
    .mnemonic = "kil",
    .opcode = 0x52,
    .total_bytes = 1,
    .addr_mode = &__addr_mode_imp,
    .operation = &__base_kil,
};

const instruction kil_imp7 = {
    .mnemonic = "kil",
    .opcode = 0x62,
    .total_bytes = 1,
    .addr_mode = &__addr_mode_imp,
    .operation = &__base_kil,
};

const instruction kil_imp8 = {
    .mnemonic = "kil",
    .opcode = 0x72,
    .total_bytes = 1,
    .addr_mode = &__addr_mode_imp,
    .operation = &__base_kil,
};

const instruction kil_imp9 = {
    .mnemonic = "kil",
    .opcode = 0x92,
    .total_bytes = 1,
    .addr_mode = &__addr_mode_imp,
    .operation = &__base_kil,
};

const instruction kil_imp10 = {
    .mnemonic = "kil",
    .opcode = 0xb2,
    .total_bytes = 1,
    .addr_mode = &__addr_mode_imp,
    .operation = &__base_kil,
};

const instruction kil_imp11 = {
    .mnemonic = "kil",
    .opcode = 0xd2,
    .total_bytes = 1,
    .addr_mode = &__addr_mode_imp,
    .operation = &__base_kil,
};

const instruction kil_imp12 = {
    .mnemonic = "kil",
    .opcode = 0xf2,
    .total_bytes = 1,
    .addr_mode = &__addr_mode_imp,
    .operation = &__base_kil,
};

void __base_lar() {
    CPU->A = CPU->__dl & pop();
    CPU->X = CPU->A;
    push(CPU->X);

    CPU->PS.flags.N = CPU->A >> 7;
    CPU->PS.flags.Z = CPU->A == 0x00;

    CPU->__cycles++;
}

const instruction lar_aby = {
    .mnemonic = "lar",
    .opcode = 0xbb,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_aby,
    .operation = &__base_lar,
};

void __base_lax() {
    CPU->A = CPU->__dl;
    CPU->X = CPU->__dl;

    CPU->PS.flags.N = CPU->A >> 7;
    CPU->PS.flags.Z = CPU->A == 0x00;

    CPU->__cycles++;
}

const instruction lax_zp = {
    .mnemonic = "lax",
    .opcode = 0xa7,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zp,
    .operation = &__base_lax,
};

const instruction lax_zpy = {
    .mnemonic = "lax",
    .opcode = 0xb7,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zpy,
    .operation = &__base_lax,
};

const instruction lax_abs = {
    .mnemonic = "lax",
    .opcode = 0xaf,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abs,
    .operation = &__base_lax,
};

const instruction lax_aby = {
    .mnemonic = "lax",
    .opcode = 0xbf,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_aby,
    .operation = &__base_lax,
};

const instruction lax_idx = {
    .mnemonic = "lax",
    .opcode = 0xa3,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_idx,
    .operation = &__base_lax,
};

const instruction lax_idy = {
    .mnemonic = "lax",
    .opcode = 0xb3,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_idy,
    .operation = &__base_lax,
};

const instruction nop_imp2 = {
    .mnemonic = "nop",
    .opcode = 0x1a,
    .total_bytes = 1,
    .addr_mode = &__addr_mode_imp,
    .operation = &__base_nop,
};

const instruction nop_imp3 = {
    .mnemonic = "nop",
    .opcode = 0x3a,
    .total_bytes = 1,
    .addr_mode = &__addr_mode_imp,
    .operation = &__base_nop,
};

const instruction nop_imp4 = {
    .mnemonic = "nop",
    .opcode = 0x5a,
    .total_bytes = 1,
    .addr_mode = &__addr_mode_imp,
    .operation = &__base_nop,
};

const instruction nop_imp5 = {
    .mnemonic = "nop",
    .opcode = 0x7a,
    .total_bytes = 1,
    .addr_mode = &__addr_mode_imp,
    .operation = &__base_nop,
};

const instruction nop_imp6 = {
    .mnemonic = "nop",
    .opcode = 0xda,
    .total_bytes = 1,
    .addr_mode = &__addr_mode_imp,
    .operation = &__base_nop,
};

const instruction nop_imp7 = {
    .mnemonic = "nop",
    .opcode = 0xfa,
    .total_bytes = 1,
    .addr_mode = &__addr_mode_imp,
    .operation = &__base_nop,
};

void __base_rla() {
    __rol_mem_op();
    __base_and();
}

const instruction rla_zp = {
    .mnemonic = "rla",
    .opcode = 0x27,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zp,
    .operation = &__base_rla,
};

const instruction rla_zpx = {
    .mnemonic = "rla",
    .opcode = 0x37,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zpx,
    .operation = &__base_rla,
};

const instruction rla_abs = {
    .mnemonic = "rla",
    .opcode = 0x2f,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abs,
    .operation = &__base_rla,
};

const instruction rla_abx = {
    .mnemonic = "rla",
    .opcode = 0x3f,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abx,
    .operation = &__base_rla,
};

const instruction rla_aby = {
    .mnemonic = "rla",
    .opcode = 0x3b,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_aby,
    .operation = &__base_rla,
};

const instruction rla_idx = {
    .mnemonic = "rla",
    .opcode = 0x23,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_idx,
    .operation = &__base_rla,
};

const instruction rla_idy = {
    .mnemonic = "rla",
    .opcode = 0x33,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_idy,
    .operation = &__base_rla,
};

void __base_rra() {
    __ror_mem_op();
    __base_adc();
}

const instruction rra_zp = {
    .mnemonic = "rra",
    .opcode = 0x67,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zp,
    .operation = &__base_rra,
};

const instruction rra_zpx = {
    .mnemonic = "rra",
    .opcode = 0x77,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zpx,
    .operation = &__base_rra,
};

const instruction rra_abs = {
    .mnemonic = "rra",
    .opcode = 0x6f,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abs,
    .operation = &__base_rra,
};

const instruction rra_abx = {
    .mnemonic = "rra",
    .opcode = 0x7f,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abx,
    .operation = &__base_rra,
};

const instruction rra_aby = {
    .mnemonic = "rra",
    .opcode = 0x7b,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_aby,
    .operation = &__base_rra,
};

const instruction rra_idx = {
    .mnemonic = "rra",
    .opcode = 0x63,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_idx,
    .operation = &__base_rra,
};

const instruction rra_idy = {
    .mnemonic = "rra",
    .opcode = 0x73,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_idy,
    .operation = &__base_rra,
};

const instruction sbc_imm2 = {
    .mnemonic = "sbc",
    .opcode = 0xeb,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_imm,
    .operation = &__base_sbc,
};

void __base_slo() {
    __asl_mem_op();
    __base_ora();
}

const instruction slo_zp = {
    .mnemonic = "slo",
    .opcode = 0x07,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zp,
    .operation = &__base_slo,
};

const instruction slo_zpx = {
    .mnemonic = "slo",
    .opcode = 0x17,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zpx,
    .operation = &__base_slo,
};

const instruction slo_abs = {
    .mnemonic = "slo",
    .opcode = 0x0f,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abs,
    .operation = &__base_slo,
};

const instruction slo_abx = {
    .mnemonic = "slo",
    .opcode = 0x1f,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abx,
    .operation = &__base_slo,
};

const instruction slo_aby = {
    .mnemonic = "slo",
    .opcode = 0x1b,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_aby,
    .operation = &__base_slo,
};

const instruction slo_idx = {
    .mnemonic = "slo",
    .opcode = 0x03,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_idx,
    .operation = &__base_slo,
};

const instruction slo_idy = {
    .mnemonic = "slo",
    .opcode = 0x13,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_idy,
    .operation = &__base_slo,
};

void __base_sre() {
    __lsr_mem_op();
    __base_eor();
}

const instruction sre_zp = {
    .mnemonic = "sre",
    .opcode = 0x47,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zp,
    .operation = &__base_sre,
};

const instruction sre_zpx = {
    .mnemonic = "sre",
    .opcode = 0x57,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_zpx,
    .operation = &__base_sre,
};

const instruction sre_abs = {
    .mnemonic = "sre",
    .opcode = 0x4f,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abs,
    .operation = &__base_sre,
};

const instruction sre_abx = {
    .mnemonic = "sre",
    .opcode = 0x5f,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abx,
    .operation = &__base_sre,
};

const instruction sre_aby = {
    .mnemonic = "sre",
    .opcode = 0x5b,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_aby,
    .operation = &__base_sre,
};

const instruction sre_idx = {
    .mnemonic = "sre",
    .opcode = 0x43,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_idx,
    .operation = &__base_sre,
};

const instruction sre_idy = {
    .mnemonic = "sre",
    .opcode = 0x53,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_idy,
    .operation = &__base_sre,
};

void __base_sxa() {
    mem_write(CPU->__al, CPU->X & ((CPU->__al >> 8) + 1));
    CPU->__cycles++;
}

const instruction sxa_aby = {
    .mnemonic = "sxa",
    .opcode = 0x9e,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_aby,
    .operation = &__base_sxa,
};

void __base_sya() {
    mem_write(CPU->__al, CPU->Y & ((CPU->__al >> 8) + 1));
    CPU->__cycles++;
}

const instruction sya_abx = {
    .mnemonic = "sya",
    .opcode = 0x9c,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abx,
    .operation = &__base_sya,
};

void __base_top() {
    __base_nop();
    __base_nop();
    __base_nop();
}

const instruction top_abs = {
    .mnemonic = "top",
    .opcode = 0x0c,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abs,
    .operation = &__base_top,
};

const instruction top_abx = {
    .mnemonic = "top",
    .opcode = 0x1c,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abx,
    .operation = &__base_top,
};

const instruction top_abx2 = {
    .mnemonic = "top",
    .opcode = 0x3c,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abx,
    .operation = &__base_top,
};

const instruction top_abx3 = {
    .mnemonic = "top",
    .opcode = 0x5c,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abx,
    .operation = &__base_top,
};

const instruction top_abx4 = {
    .mnemonic = "top",
    .opcode = 0x7c,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abx,
    .operation = &__base_top,
};

const instruction top_abx5 = {
    .mnemonic = "top",
    .opcode = 0xdc,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abx,
    .operation = &__base_top,
};

const instruction top_abx6 = {
    .mnemonic = "top",
    .opcode = 0xfc,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_abx,
    .operation = &__base_top,
};

void __base_xaa() {
    /*
        Definition taken from here https://www.masswerk.at/nowgobang/2021/6502-illegal-opcodes
        Operation: (A OR CONST) AND X AND ARG -> A
        Selecting CONST as 0xff for this implementation
    */
//    LOGW("Highly unstable XAA being used");
   CPU->A = CPU->X & CPU->__dl;
   CPU->__cycles++;
}

const instruction xaa_imm = {
    .mnemonic = "xaa",
    .opcode = 0x8b,
    .total_bytes = 2,
    .addr_mode = &__addr_mode_imm,
    .operation = &__base_xaa,
};

void __base_xas() {
    push(CPU->A & CPU->X);
    mem_write(CPU->__al, pop() & ((CPU->__al >> 8) + 1));

    CPU->__cycles++;
}

const instruction xas_aby = {
    .mnemonic = "xas",
    .opcode = 0x9b,
    .total_bytes = 3,
    .addr_mode = &__addr_mode_aby,
    .operation = &__base_xas,
};

void register_illegal_instruction_set() {
    register_instruction(aac_imm);
    register_instruction(aac_imm2);

    register_instruction(aax_zp);
    register_instruction(aax_zpy);
    register_instruction(aax_idx);
    register_instruction(aax_abs);

    register_instruction(arr_imm);

    register_instruction(asr_imm);

    register_instruction(atx_imm);

    register_instruction(axa_aby);
    register_instruction(axa_idy);

    register_instruction(axs_imm);

    register_instruction(dcp_zp);
    register_instruction(dcp_zpx);
    register_instruction(dcp_abs);
    register_instruction(dcp_abx);
    register_instruction(dcp_aby);
    register_instruction(dcp_idx);
    register_instruction(dcp_idy);

    register_instruction(dop_zp);
    register_instruction(dop_zpx);
    register_instruction(dop_zpx2);
    register_instruction(dop_zp2);
    register_instruction(dop_zpx3);
    register_instruction(dop_zp3);
    register_instruction(dop_zpx4);
    register_instruction(dop_imm);
    register_instruction(dop_imm2);
    register_instruction(dop_imm3);
    register_instruction(dop_imm4);
    register_instruction(dop_zpx5);
    register_instruction(dop_imm5);
    register_instruction(dop_zpx6);

    register_instruction(isc_zp);
    register_instruction(isc_zpx);
    register_instruction(isc_abs);
    register_instruction(isc_abx);
    register_instruction(isc_aby);
    register_instruction(isc_idx);
    register_instruction(isc_idy);

    register_instruction(kil_imp);
    register_instruction(kil_imp2);
    register_instruction(kil_imp3);
    register_instruction(kil_imp4);
    register_instruction(kil_imp5);
    register_instruction(kil_imp6);
    register_instruction(kil_imp7);
    register_instruction(kil_imp8);
    register_instruction(kil_imp9);
    register_instruction(kil_imp10);
    register_instruction(kil_imp11);
    register_instruction(kil_imp12);

    register_instruction(lar_aby);

    register_instruction(lax_zp);
    register_instruction(lax_zpy);
    register_instruction(lax_abs);
    register_instruction(lax_aby);
    register_instruction(lax_idx);
    register_instruction(lax_idy);

    register_instruction(nop_imp2);
    register_instruction(nop_imp3);
    register_instruction(nop_imp4);
    register_instruction(nop_imp5);
    register_instruction(nop_imp6);
    register_instruction(nop_imp7);

    register_instruction(rla_zp);
    register_instruction(rla_zpx);
    register_instruction(rla_abs);
    register_instruction(rla_abx);
    register_instruction(rla_aby);
    register_instruction(rla_idx);
    register_instruction(rla_idy);

    register_instruction(rra_zp);
    register_instruction(rra_zpx);
    register_instruction(rra_abs);
    register_instruction(rra_abx);
    register_instruction(rra_aby);
    register_instruction(rra_idx);
    register_instruction(rra_idy);

    register_instruction(sbc_imm2);

    register_instruction(slo_zp);
    register_instruction(slo_zpx);
    register_instruction(slo_abs);
    register_instruction(slo_abx);
    register_instruction(slo_aby);
    register_instruction(slo_idx);
    register_instruction(slo_idy);

    register_instruction(sre_zp);
    register_instruction(sre_zpx);
    register_instruction(sre_abs);
    register_instruction(sre_abx);
    register_instruction(sre_aby);
    register_instruction(sre_idx);
    register_instruction(sre_idy);

    register_instruction(sxa_aby);

    register_instruction(sya_abx);

    register_instruction(top_abs);
    register_instruction(top_abx);
    register_instruction(top_abx2);
    register_instruction(top_abx3);
    register_instruction(top_abx4);
    register_instruction(top_abx5);
    register_instruction(top_abx6);

    register_instruction(xaa_imm);

    register_instruction(xas_aby);
}