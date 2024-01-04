#include <stdint.h>
#include <stddef.h>

#ifndef __cpu
#define __cpu

#define PPU_CTRL 0x2000
#define PPU_MASK 0x2001
#define PPU_STATUS 0x2002
#define PPU_OAMADDR 0x2003
#define PPU_OAMDATA 0x2004
#define PPU_SCROLL 0x2005
#define PPU_ADDR 0x2006
#define PPU_DATA 0x2007
#define PPU_OAMDMA 0x4014

#define PPU_ADDR_BEGIN 0x2000
#define PPU_ADDR_END 0x3fff
#define PPU_MIRROR_ADDR_END 0x2007

#define CPU_MEM_RANGE_BEGIN 0x0000
#define CPU_MEM_RANGE_END 0x1FFF
#define CPU_MEM_MIRROR_END 0x07FF

typedef union {
	uint8_t reg;
	struct {
		uint8_t C:1;	//Carry flag
		uint8_t Z:1;	//Zero flag
		uint8_t I:1;	//Interrupt Disable flag
		uint8_t D:1;	//Decimal mode flag
		uint8_t B:1;	//Break flag
		uint8_t U:1;	//Unused always 1
		uint8_t V:1;	//Overflow flag
		uint8_t N:1;	//Negative flag
	} flags;
} processor_status_t;

typedef struct _cpu
{
	// Program counter
	uint16_t PC;

	// Stack pointer
	uint8_t SP;

	// Registers
	uint8_t A;
	uint8_t X, Y;

	// Processor status register
	processor_status_t PS;

	// Track cycle number
	uint32_t __cycles;
	// Data latch
	uint8_t __dl;
	// Address latch
	uint16_t __al;
	// Processor lock, used by illegal opcode KIL
	uint8_t __lock;
} cpu_t;

extern cpu_t *CPU;

void init_cpu();
void print_cpu_state();
void deinit_cpu();

// Addressing modes
void __addr_mode_imm();
void __addr_mode_zp();
void __addr_mode_zpx();
void __addr_mode_zpy();
void __addr_mode_abs();
void __addr_mode_abx();
void __addr_mode_aby();
void __addr_mode_rel();
void __addr_mode_ind();
void __addr_mode_idx();
void __addr_mode_idy();
void __addr_mode_acc();
void __addr_mode_imp();

void fde();

void reset();

#endif
