#include <instruction.h>
#include <log.h>
#include <stdlib.h>

instruction *INSTRUCTIONS = NULL;

void init_instructions() {
    if (!INSTRUCTIONS) {
        INSTRUCTIONS = (instruction *)malloc(sizeof(instruction) * 0x1FF);
        for(int i = 0; i < 0x1FF; i++) {
            INSTRUCTIONS[i] = (instruction){0};
        }

        register_illegal_instruction_set();
        register_load_instruction_set();
        register_trans_instruction_set();
        register_stack_instruction_set();
        register_shift_instruction_set();
        register_logic_instruction_set();
        register_arith_instruction_set();
        register_inc_instruction_set();
        register_ctrl_instruction_set();
        register_branch_instruction_set();
        register_flags_instruction_set();
        register_nop_instruction_set();
    }
}

void register_instruction(instruction i) {
    INSTRUCTIONS[i.opcode] = i;
}

instruction fetch_instruction(uint8_t opcode) {
    return INSTRUCTIONS[opcode];
}

void deinit_instructions() {
    free(INSTRUCTIONS);
}
