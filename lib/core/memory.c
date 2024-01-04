#include <stddef.h>
#include <stdlib.h>

#include "core/memory.h"
#include "core/cpu.h"
#include "core/ppu.h"

#include <log.h>

uint8_t *RAM = NULL;

void init_memory()
{
	if(!RAM) {
		RAM = (uint8_t *)malloc(sizeof(uint8_t) * MEM_SIZE);
	}

	int index = 0;
	for (; index < MEM_SIZE; index++)
	{
		RAM[index] = 0;
	}
}

void mem_write(uint16_t address, uint8_t data)
{
	if(address <= CPU_MEM_RANGE_END) {
		RAM[address & CPU_MEM_MIRROR_END] = data;
	} 
	else if(address >= PPU_ADDR_BEGIN && address <= PPU_ADDR_END) {
		RAM[address & PPU_MIRROR_ADDR_END] = data;
		ppu_write(address & PPU_MIRROR_ADDR_END, data);
	}
	 else {
		RAM[address] = data;
	}
}

uint8_t mem_read(uint16_t address) {
	if(address <= CPU_MEM_RANGE_END) {
		return RAM[address & CPU_MEM_MIRROR_END];
	} else if(address >= PPU_ADDR_BEGIN && address <= PPU_ADDR_END) {
		return ppu_read(address & PPU_MIRROR_ADDR_END);
	} else {
		return RAM[address];
	}
}

void deinit_memory() {
	// free(RAM);
}

void push(uint8_t data) {
	// printf("Pushing %X to %X\n", data, STACK_ADDR(CPU->SP));
	mem_write(STACK_ADDR(CPU->SP), data);
	CPU->SP--;
	CPU->__cycles++;
}

uint8_t pop() {
	CPU->__cycles++;
	CPU->SP++;
	// printf("Popped %X from %X\n", RAM[STACK_ADDR(CPU->SP)], STACK_ADDR(CPU->SP));
	return mem_read(STACK_ADDR(CPU->SP));
}
