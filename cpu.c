
#include <stdlib.h>
#include <stdio.h>

#include "cpu.h"
#include "ops.h"

#include "inst_names.h"

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
void cpu_run() {

    cpu_dump(0);

    while(1) {

        // fetch op code and increase PC by 1
        uint8_t *inst = &MEMORY[(*CPU->PC)++]; 
        if (*inst > 255) {
            printf("invalid op code: %d\n", *inst);
            break;
        }
        
        OPC *func = (OPC*)&OP_CODES[*inst * 3 + 2]; // call op func
        (*func)(); 
        
        (*CPU->PC) += (OP_CODES[*inst * 3] - 1); // increase PC by op size - 1
        CPU->cycles += OP_CODES[*inst * 3 + 1]; // add min  cycle count 

        // exit on NOP
        if (*inst == 0) {
            break;
        }

        cpu_dump(*inst);
        usleep(1000000);

    }
    
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

    if (!(*r & 128))           (*CPU->F) |= 128; // set SIGN flag
    if (*r == 0)               (*CPU->F) |=  64; // set ZERO flag
    if (!(*r & 15 && *r & 31)) (*CPU->F) |=  16; // set AUXILLARY CARRY flag
    if (ParityTable256[*r])    (*CPU->F) |=   4; // set PARITY flag
    
}

inline void cpu_flag_szap_dec(uint16_t *r) {

    (*CPU->F) = 0; // clear flags

    if (!(*r & 128))           (*CPU->F) |= 128; // set SIGN flag
    if (*r == 0)               (*CPU->F) |=  64; // set ZERO flag
    if (!(*r & 7 && *r & 15))  (*CPU->F) |=  16; // set AUXILLARY CARRY flag
    if (ParityTable256[*r])    (*CPU->F) |=   4; // set PARITY flag

}


/* Debug -------------------------------------------------------------------- */
void cpu_dump(uint8_t inst) {

    uint8_t flags = *CPU->F;

    printf("\n  (F) %c %c %c %c %c %c %c %c\n", 
                (flags & 128) ? 'S' : '-',
                (flags &  64) ? 'Z' : '-',
                (flags &  32) ? '0' : ' ',
                (flags &  16) ? 'A' : '-',
                (flags &   8) ? '0' : ' ',
                (flags &   4) ? 'P' : '-',
                (flags &   2) ? '1' : ' ',
                (flags &   1) ? 'C' : '-' );

    printf("  (A)   %03d (PSW) %05d  (OP)  %-5s(%02x)\n", *CPU->A, *CPU->PSW, INST_NAMES[inst], inst);
    printf("  (B)   %03d   (C)   %03d  (BC)  %05d\n", *CPU->B, *CPU->C, *CPU->BC);
    printf("  (D)   %03d   (E)   %03d  (DE)  %05d\n", *CPU->D, *CPU->E, *CPU->DE);
    printf("  (H)   %03d   (L)   %03d  (HL)  %05d\n", *CPU->H, *CPU->L, *CPU->HL);
    printf(" (SP) %05d  (PC) %05d\n", *CPU->SP, *CPU->PC);
    printf("(CYC) %17lu\n", CPU->cycles);

//    fputs("\x1b[2J", stdout);
//
}

