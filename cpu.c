
#include <stdlib.h>
#include <stdio.h>

#include "cpu.h"
#include "ops.h"

extern CPU_8080 *CPU;
extern uint8_t *MEMORY;


/* Create ------------------------------------------------------------------- */
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

    cpu->cycles = 0;

    return cpu;

}


/* Main --------------------------------------------------------------------- */
inline uint8_t *cpu_next() {
    return &MEMORY[*CPU->PC];
}

void cpu_step() {

    // fetch op code
    uint8_t *inst = cpu_next();
    (*CPU->PC)++; // increase PC
    
    OPC *func = (OPC*)&OP_CODES[*inst * 3 + 2]; // call op func
    (*func)(); 
    
    *CPU->PC += (OP_CODES[*inst * 3] - 1); // increase PC by op size - 1
    *CPU->PC &= 0xffff;

    CPU->cycles += OP_CODES[*inst * 3 + 1]; // add min  cycle count 
    
}


/* Flags -------------------------------------------------------------------- */
static const unsigned int ParityTable256[256] = {
#   define P2(n) n, n^1, n^1, n
#   define P4(n) P2(n), P2(n^1), P2(n^1), P2(n)
#   define P6(n) P4(n), P4(n^1), P4(n^1), P4(n)
    P6(0), P6(1), P6(1), P6(0)
};

inline cpu_flag_szap_inc(uint16_t *r) {
    
    (*CPU->F) = 0; // clear flags

    if ((*r & 128))            (*CPU->F) |= 128; // set SIGN flag
    if (*r == 0)               (*CPU->F) |=  64; // set ZERO flag
    if (!(*r & 15 && *r & 31)) (*CPU->F) |=  16; // set AUXILLARY CARRY flag
    if (ParityTable256[*r])    (*CPU->F) |=   4; // set PARITY flag
    
}

inline void cpu_flag_szap_dec(uint16_t *r) {

    (*CPU->F) = 0; // clear flags

    if (!(*r & 128))           (*CPU->F) |= 128; // set SIGN flag
    if (*r == 0)               (*CPU->F) |=  64; // set ZERO flag
    if (ParityTable256[*r])    (*CPU->F) |=   4; // set PARITY flag

}

