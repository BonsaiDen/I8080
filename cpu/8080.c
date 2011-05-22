
#include <stdlib.h>

#include "8080.h"
#include "../ops/data.h"

void cpu_init() {
    
    CPU = calloc(1, sizeof(CPU_8080));

    CPU->A = (uint8_t*)&CPU->reg[1]; CPU->F = (uint8_t*)&CPU->reg[0];
    CPU->B = (uint8_t*)&CPU->reg[3]; CPU->C = (uint8_t*)&CPU->reg[2];
    CPU->D = (uint8_t*)&CPU->reg[5]; CPU->E = (uint8_t*)&CPU->reg[4];
    CPU->H = (uint8_t*)&CPU->reg[7]; CPU->L = (uint8_t*)&CPU->reg[6];

    CPU->PSW = (uint16_t*)&CPU->reg[0];
    CPU->BC = (uint16_t*)&CPU->reg[2];
    CPU->DE = (uint16_t*)&CPU->reg[4];
    CPU->HL = (uint16_t*)&CPU->reg[6];

    CPU->SP = (uint16_t*)&CPU->reg[8]; 
    CPU->PC = (uint16_t*)&CPU->reg[10];

    cpu_reset();

}

void cpu_fetch() {

    // Act to low reset pin. Reset halted state.
    if (!CPU->reset) {
        CPU->halt = 0;
        *CPU->PC = 0;
    }

    // fetch instruction and increase PC
    CPU->instruction = mmu_read((*CPU->PC)++);

    // set halted state
    if (CPU->instruction == 0x76) {
        CPU->halt = 1;
    }
    
}

void cpu_exec() {
    
    // call op code function
    uint8_t inst = CPU->instruction;
    (*(OP_CODE_POINTER*)&OP_CODE_DATA[inst * 3 + 2])(); 
    
    // increase PC by op size - 1, this is done to reduce amount of code inside
    // instructions
    *CPU->PC += (OP_CODE_DATA[inst * 3] - 1);
    *CPU->PC &= 0xffff; // mask PC

    // add min cycle count, extra cycles are added inside the op code functions
    CPU->cycles += OP_CODE_DATA[inst * 3 + 1];
    
}

void cpu_reset() {

    // Registers
    *CPU->PSW = 0;
    *CPU->BC = 0;
    *CPU->DE = 0;
    *CPU->HL = 0;

    *CPU->SP = 65535;
    *CPU->PC = 0;

    // state info
    CPU->instruction = 0;
    CPU->cycles = 0;
    CPU->ime = 0;

    // Pins
    CPU->halt = 0;
    CPU->reset = 1;
    
}

void cpu_destroy() {
    free(CPU);
}


/* Flags -------------------------------------------------------------------- */
static const unsigned int ParityTable256[256] = {
#   define P2(n) n, n^1, n^1, n
#   define P4(n) P2(n), P2(n^1), P2(n^1), P2(n)
#   define P6(n) P4(n), P4(n^1), P4(n^1), P4(n)
    P6(0), P6(1), P6(1), P6(0)
};

inline void cpu_flag_szap(uint8_t *r) {
    
    (*CPU->F) = 0; // clear flags

    // TODO double check these
    if (*r & 128)              (*CPU->F) |= 128; // set SIGN flag
    if (*r == 0)               (*CPU->F) |=  64; // set ZERO flag
    if (!(*r & 15 && *r & 31)) (*CPU->F) |=  16; // set AUXILLARY CARRY flag
    if (ParityTable256[*r])    (*CPU->F) |=   4; // set PARITY flag
    
}

inline void cpu_flag_szp(uint8_t *r) {

    (*CPU->F) = 0; // clear flags

    if (*r & 128)              (*CPU->F) |= 128; // set SIGN flag
    if (*r == 0)               (*CPU->F) |=  64; // set ZERO flag
    if (ParityTable256[*r])    (*CPU->F) |=   4; // set PARITY flag

}

