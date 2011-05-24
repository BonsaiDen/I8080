// Intel 8080 Emulator --------------------------------------------------------
// ----------------------------------------------------------------------------
#include "Cpu.h"
#include "flags.c"
#include "table.c"

#include <stdlib.h>

// Definitions
static unsigned long cpu_exec(Intel8080 *cpu, unsigned long cycles);
static void cpu_reset(Intel8080 *cpu);
static void cpu_destroy(Intel8080 **cpu);


// Constructor ----------------------------------------------------------------
// ----------------------------------------------------------------------------
Intel8080 *cpu_create(uint8_t (*read_mem)(uint16_t addr),
                      void (*write_mem)(uint16_t addr, uint8_t val),
                      uint16_t *stack_top) {
                        
    Intel8080 *cpu = calloc(1, sizeof(Intel8080));

    cpu->A = (uint8_t*)&cpu->reg[1]; cpu->F = (uint8_t*)&cpu->reg[0];
    cpu->B = (uint8_t*)&cpu->reg[3]; cpu->C = (uint8_t*)&cpu->reg[2];
    cpu->D = (uint8_t*)&cpu->reg[5]; cpu->E = (uint8_t*)&cpu->reg[4];
    cpu->H = (uint8_t*)&cpu->reg[7]; cpu->L = (uint8_t*)&cpu->reg[6];

    cpu->PSW = (uint16_t*)&cpu->reg[0];
    cpu->BC = (uint16_t*)&cpu->reg[2];
    cpu->DE = (uint16_t*)&cpu->reg[4];
    cpu->HL = (uint16_t*)&cpu->reg[6];

    cpu->SP = (uint16_t*)&cpu->reg[8]; 
    cpu->PC = (uint16_t*)&cpu->reg[10];

    // Pointer to the top of stack
    cpu->stack_top = stack_top;

    // Map methods
    cpu->exec = &cpu_exec;
    cpu->reset = &cpu_reset;
    cpu->destroy = &cpu_destroy;

    // Memory access
    cpu->read_mem = read_mem;
    cpu->write_mem = write_mem;

    // Inital Reset
    cpu->reset(cpu);

    return cpu;

}


// Exectute a given number of cycles ------------------------------------------
// ----------------------------------------------------------------------------
static unsigned long cpu_exec(Intel8080 *cpu, unsigned long cycles) {

    unsigned long old_cycle_count = cpu->cycle_count;
    uint8_t inst = 0;
    while(cpu->cycle_count - old_cycle_count < cycles) {

        // Fetch instruction and increase PC
        inst = cpu->read_mem((*cpu->PC)++);

        // Call op code function
        op_code_table(cpu, inst);
        
    }
    
    cpu->instruction = inst;
    return cpu->cycle_count - old_cycle_count;

}


// Reset the CPU --------------------------------------------------------------
// ----------------------------------------------------------------------------
static void cpu_reset(Intel8080 *cpu) {

    // Registers
    *cpu->PSW = 0;
    *cpu->BC = 0;
    *cpu->DE = 0;
    *cpu->HL = 0;

    *cpu->SP = *cpu->stack_top;
    *cpu->PC = 0;

    // State info
    cpu->instruction = 0;
    cpu->cycle_count = 0;
    cpu->ime = 0;

    // Pins
    cpu->halt = 0;
    
}


// Destructor -----------------------------------------------------------------
// ----------------------------------------------------------------------------
static void cpu_destroy(Intel8080 **cpu) {
    free(*cpu);
    *cpu = NULL;
}

