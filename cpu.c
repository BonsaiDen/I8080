
#include <stdlib.h>
#include <stdio.h>

#include "cpu.h"

#include "helpers.c"
#include "map.c"

static void run(CPU *cpu);
static void dump(CPU *cpu);

CPU *cpu(uint8_t *mem) {
    
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
    cpu->mem = mem;
    cpu->run = &run;

    return cpu;

}

static void run(CPU *c) {

    while(1) {

        // fetch op code and increase PC by 1
        uint8_t *inst = &c->mem[(*c->PC)++]; 
        if (*inst > 255) {
            printf("invalid op code: %d\n", *inst);
            break;
        }

        printf("op: %d\n", *inst);
        
        // resolve op code function pointer...
        opCode *func = (opCode*)&OP_CODES[*inst * 3 + 2];
        (*func)(c, &c->mem[(*c->PC)]); 

        // increase PC by op size - 1
        (*c->PC) += (OP_CODES[*inst * 3] - 1); 

        // add min  cycle count
        c->cycles += OP_CODES[*inst * 3 + 1]; 

        // exit on NOP
        if (*inst == 0) {
            break;
        }

        dump(c);
        usleep(1000000);

    }
    
}


/* Debugging ---------------------------------------------------------------- */
static void dump(CPU *cpu) {

    uint8_t flags = *cpu->F;

    printf("  (F) %c %c %c %c %c %c %c %c\n\n", (flags & 128) ? 'S' : '-',
                           (flags &  64) ? 'Z' : '-',
                           (flags &  32) ? '0' : ' ',
                           (flags &  16) ? 'A' : '-',
                           (flags &   8) ? '0' : ' ',
                           (flags &   4) ? 'P' : '-',
                           (flags &   2) ? '1' : ' ',
                           (flags &   1) ? 'C' : '-' );

    printf("  (A)   %03d (PSW) %05d\n", *cpu->A, *cpu->PSW);
    printf("  (B)   %03d   (C)   %03d  (BC)  %05d\n", *cpu->B, *cpu->C, *cpu->BC);
    printf("  (D)   %03d   (E)   %03d  (DE)  %05d\n", *cpu->D, *cpu->E, *cpu->DE);
    printf("  (H)   %03d   (L)   %03d  (HL)  %05d\n", *cpu->H, *cpu->L, *cpu->HL);
    printf(" (SP) %05d  (PC) %05d\n", *cpu->SP, *cpu->PC);
    printf("(CYC) %17lu\n", cpu->cycles);

//    fputs("\x1b[2J", stdout);
}
