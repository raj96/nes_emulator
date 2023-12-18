#include "core/cpu.h"

#include <stdio.h>
#include <stdlib.h>

#include "core/memory.h"
#include "instruction.h"

#include <log.h>

cpu *CPU = NULL;

void init_cpu() {
    if (!CPU) {
        CPU = (cpu *)malloc(sizeof(cpu));
    }
    CPU->SP = (uint8_t)-3;
    CPU->A = 0x00;
    CPU->X = 0x00;
    CPU->Y = 0x00;
    CPU->PS.reg = 0x24;

    init_instructions();
}

void print_cpu_state() {
    printf("A:\t0x%x\t||\tPS:\t0x%x\n", CPU->A, CPU->PS.reg);
    printf("X:\t0x%x\t||\tY:\t0x%x\n", CPU->X, CPU->Y);
    printf("SP:\t0x%x\t||\tPC:\t0x%x\n", CPU->SP, CPU->PC);
    printf("dl:\t0x%x\t||\tal:\t0x%x\n\n", CPU->__dl, CPU->__al);
}

void deinit_cpu() {
    // deinit_instructions();
    // free(*CPU);
}

void __addr_mode_imp() {
    printf("\t\t");
    CPU->__cycles++;
    // CPU->PC++;
}

void __addr_mode_imm() {
    printf("%02X\t\t", RAM[CPU->PC]);
    CPU->__dl = mem_read(CPU->PC);
    CPU->__cycles++;
    CPU->PC++;
}

void __addr_mode_zp() {
    printf("%02X\t\t", RAM[CPU->PC]);
    CPU->__al = 0x00ff & mem_read(CPU->PC);
    CPU->__dl = mem_read(CPU->__al);
    CPU->__cycles++;
    CPU->PC++;
}

void __addr_mode_zpx() {
    printf("%02X\t\t", RAM[CPU->PC]);
    CPU->__al = 0x00ff & (mem_read(CPU->PC) + CPU->X);
    CPU->__dl = mem_read(CPU->__al);
    CPU->__cycles++;
    CPU->PC++;
}

void __addr_mode_zpy() {
    printf("%02X\t\t", RAM[CPU->PC]);
    CPU->__al = 0x00ff & (mem_read(CPU->PC) + CPU->Y);
    CPU->__dl = mem_read(CPU->__al);
    CPU->__cycles++;
    CPU->PC++;
}

void __addr_mode_abs() {
    printf("%02X %02X\t", RAM[CPU->PC], RAM[CPU->PC+1]);
    CPU->__al = mem_read(CPU->PC);
    CPU->__cycles++;
    CPU->PC++;

    CPU->__al |= (mem_read(CPU->PC) << 8);
    CPU->__cycles++;

    CPU->__dl = mem_read(CPU->__al);
    CPU->__cycles++;
    CPU->PC++;
}

void __addr_mode_abx() {
    printf("%02X %02X\t", RAM[CPU->PC], RAM[CPU->PC+1]);
    CPU->__al = mem_read(CPU->PC);
    CPU->__cycles++;
    CPU->PC++;

    CPU->__al += CPU->X;
    if (CPU->__al > 0x00ff) {
        CPU->__al &= 0x00ff;
        CPU->__al |= ((mem_read(CPU->PC) + 1) << 8);
        CPU->__cycles++;
    } else {
        CPU->__al |= (mem_read(CPU->PC) << 8);
    }
    CPU->__cycles++;

    CPU->__dl = mem_read(CPU->__al);
    CPU->__cycles++;
    CPU->PC++;
}

void __addr_mode_aby() {
    printf("%02X %02X\t", RAM[CPU->PC], RAM[CPU->PC+1]);
    CPU->__al = mem_read(CPU->PC);
    CPU->__cycles++;
    CPU->PC++;

    CPU->__al += CPU->Y;
    if (CPU->__al > 0x00ff) {
        CPU->__al &= 0x00ff;
        CPU->__al |= ((mem_read(CPU->PC) + 1) << 8);
        CPU->__cycles++;
    } else {
        CPU->__al |= (mem_read(CPU->PC) << 8);
    }
    CPU->__cycles++;

    CPU->__dl = mem_read(CPU->__al);
    CPU->__cycles++;
    CPU->PC++;
}

void __addr_mode_rel() {
    printf("%02X\t\t", RAM[CPU->PC]);
    CPU->__dl = mem_read(CPU->PC);

    CPU->__cycles++;
    CPU->PC++;
}

void __addr_mode_ind() {
    printf("%02X %02X\t", RAM[CPU->PC], RAM[CPU->PC + 1]);
    CPU->__al = mem_read(CPU->PC);
    CPU->__cycles++;
    CPU->PC++;

    CPU->__al |= (mem_read(CPU->PC) << 8);
    CPU->__cycles++;

    CPU->__dl = mem_read(CPU->__al);
    CPU->__cycles++;
    CPU->PC++;

    // Mimics the bug on original 6502
    CPU->__al = ((mem_read((CPU->__al & 0x00ff) == 0x00ff ? (CPU->__al >> 8) << 8 : CPU->__al+1)) << 8) | CPU->__dl;
    CPU->__cycles++;
    CPU->__dl = mem_read(CPU->__al);
    CPU->__cycles++;
}

void __addr_mode_idx() {
    printf("%02X\t\t", RAM[CPU->PC]);
    uint16_t temp_addr = 0x00ff & (mem_read(CPU->PC) + CPU->X);
    CPU->__cycles++;

    CPU->__al = mem_read(temp_addr);
    CPU->__cycles++;

    CPU->__al |= (mem_read(0x00ff & (temp_addr + 1)) << 8);
    CPU->__cycles++;

    CPU->__dl = mem_read(CPU->__al);
    CPU->__cycles++;
    CPU->PC++;
}

void __addr_mode_idy() {
    uint16_t temp_addr = mem_read(CPU->PC);
    printf("%02X\t\t", temp_addr);
    CPU->__cycles++;

    CPU->__al = mem_read(temp_addr);
    CPU->__cycles++;

    CPU->__al |= mem_read(0x00ff & (temp_addr + 1)) << 8;
    CPU->__al += CPU->Y;

    CPU->__dl = mem_read(CPU->__al);
    CPU->__cycles++;
    CPU->PC++;
}

void __addr_mode_acc() {
    printf("\t\t");
    CPU->__dl = CPU->A;
    CPU->__cycles++;
    // CPU->PC++;
}

void reset() {
    CPU->__lock = 0;
    CPU->PC = mem_read(MEM_PWR_ON_RST_L);
    CPU->PC |= mem_read(MEM_PWR_ON_RST_H) << 8;
    LOGI("PC: %04X\t\t", CPU->PC);
}

void fde() {
    if(CPU->__lock) return;
    // Fetch
    printf("%04X\t\t", CPU->PC);
    uint8_t opcode = mem_read(CPU->PC++);
    printf("%02X ", opcode);

    // Decode
    instruction i = fetch_instruction(opcode);
    // LOGI("Decoded to %s", i.mnemonic);

    // Execute
    if(i.addr_mode == NULL || i.operation == NULL) {
        LOGF("Opcode 0x%02X not available", opcode);
    }
    // LOGI("%s", i.mnemonic, CPU->PC);
    i.addr_mode();
    printf("%s\t", i.mnemonic);
    printf("A:%02X X:%02X Y:%02X P:%02X SP:%02X \tAL: %04X\n", CPU->A, CPU->X, CPU->Y, CPU->PS.reg, CPU->SP, CPU->__al);
    i.operation();
}
