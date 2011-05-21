
#ifndef CPU_8080_H
#define CPU_8080_H

#include <stdint.h>

/* Structs ------------------------------------------------------------------ */
typedef struct CPU {

    uint8_t reg[12];

    uint8_t *A;
    uint8_t *F;
    uint16_t *PSW;

    uint8_t *B;
    uint8_t *C;
    uint16_t *BC;

    uint8_t *D;
    uint8_t *E;
    uint16_t *DE;

    uint8_t *H;
    uint8_t *L;
    uint16_t *HL;

    uint16_t *SP;
    uint16_t *PC;

    unsigned long cycles;

} CPU;


/* Constructor -------------------------------------------------------------- */
CPU *cpu() {

    CPU *cpu = calloc(1, sizeof(CPU));

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

#endif

