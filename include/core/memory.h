#include <stdint.h>

#ifndef __memory
#define __memory
// 64K of RAM
#define MEM_SIZE 64 * 1024

#define MEM_ZP_ADDR_START 0x0000
#define MEM_ZP_ADDR_END 0x00ff

// Stack is NOT relocatable
#define STACK_ADDR(x) (0x0100 | x)
#define MEM_STACK_BEGIN 0x00
#define MEM_STACK_END 0xff

#define MEM_NMI_HANDLER_L 0xfffa
#define MEM_NMI_HANDLER_H 0xfffb

#define MEM_PWR_ON_RST_L 0xfffc
#define MEM_PWR_ON_RST_H 0xfffd

#define MEM_INTR_HANDLER_L 0xfffe
#define MEM_INTR_HANDLER_H 0xffff

extern uint8_t *RAM;

// Initialize RAM
void init_memory();
void mem_write(uint16_t address, uint8_t data);
uint8_t mem_read(uint16_t address);
void deinit_memory();

void push(uint8_t data);
uint8_t pop();

#endif