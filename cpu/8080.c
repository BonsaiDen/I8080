
#include <stdlib.h>

#include "8080.h"
#include "../ops/data.h"

static void cpu_fetch(CPU_8080 *cpu);
static uint8_t cpu_exec(CPU_8080 *cpu);
static void cpu_reset(CPU_8080 *cpu);
static void cpu_destroy(CPU_8080 **cpu);


CPU_8080 *cpu_create() {
    
    CPU_8080 *cpu = calloc(1, sizeof(CPU_8080));

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

    // Map methods
    cpu->fetch = &cpu_fetch;
    cpu->exec = &cpu_exec;
    cpu->reset = &cpu_reset;
    cpu->destroy = &cpu_destroy;

}

static void cpu_fetch(CPU_8080 *cpu) {

    // fetch instruction and increase PC
    cpu->instruction = mmu_read((*cpu->PC)++);

    // set halted state
    if (cpu->instruction == 0x76) {
        cpu->halt = 1;
    }
    
}

static uint8_t cpu_exec(CPU_8080 *cpu) {

    unsigned long cycle_count = cpu->cycle_count;
    
    // call op code function
    uint8_t inst = cpu->instruction;
    (*(OP_CODE_POINTER*)&OP_CODE_DATA[inst * 3 + 2])(cpu); 
    
    // increase PC by op size - 1, this is done to reduce amount of code inside
    // instructions
    *cpu->PC += (OP_CODE_DATA[inst * 3] - 1);
    *cpu->PC &= 0xffff; // mask PC

    // add min cycle count, extra cycles are added inside the op code functions
    cpu->cycle_count += OP_CODE_DATA[inst * 3 + 1];
    
    return cpu->cycle_count - cycle_count;

}

static void cpu_reset(CPU_8080 *cpu) {

    // Registers
    *cpu->PSW = 0;
    *cpu->BC = 0;
    *cpu->DE = 0;
    *cpu->HL = 0;

    *cpu->SP = 65535;
    *cpu->PC = 0;

    // state info
    cpu->instruction = 0;
    cpu->cycle_count = 0;
    cpu->ime = 0;

    // Pins
    cpu->halt = 0;
    
}

static void cpu_destroy(CPU_8080 **cpu) {
    free(*cpu);
    *cpu = NULL;
}


/* Flags -------------------------------------------------------------------- */
static const unsigned int ParityTable256[256] = {
#   define P2(n) n, n^1, n^1, n
#   define P4(n) P2(n), P2(n^1), P2(n^1), P2(n)
#   define P6(n) P4(n), P4(n^1), P4(n^1), P4(n)
    P6(0), P6(1), P6(1), P6(0)
};

inline void cpu_flag_szap(CPU_8080 *cpu, uint8_t *r) {
    
    (*cpu->F) = 0; // clear flags

    // TODO double check these
    if (*r & 128)              (*cpu->F) |= 128; // set SIGN flag
    if (*r == 0)               (*cpu->F) |=  64; // set ZERO flag
    if (!(*r & 15 && *r & 31)) (*cpu->F) |=  16; // set AUXILLARY CARRY flag
    if (ParityTable256[*r])    (*cpu->F) |=   4; // set PARITY flag
    
}

inline void cpu_flag_szp(CPU_8080 *cpu, uint8_t *r) {

    (*cpu->F) = 0; // clear flags

    if (*r & 128)              (*cpu->F) |= 128; // set SIGN flag
    if (*r == 0)               (*cpu->F) |=  64; // set ZERO flag
    if (ParityTable256[*r])    (*cpu->F) |=   4; // set PARITY flag

}

