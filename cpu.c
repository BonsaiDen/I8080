
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "cpu.h"

#include "helpers.c"
#include "map.c"


static void dump(CPU *cpu);

int main(int argc, const char *argv[]) {
    
    CPU *core = cpu();

    uint8_t *mem = calloc(sizeof(uint8_t), 65536);
    (*core->HL) = 32768;
    (*core->BC) = 32768;
    mem[0] = 9;

    dump(core);
    
    while(1) {

        uint8_t *inst = &mem[(*core->PC)++]; // fetch op code and increase PC by 1
        printf("op: %d\n", *inst);
        
        // resolve op code function pointer...
        opCode *func = (opCode*)&OP_CODES[*inst * 3 + 2];
        (*func)(core, &mem[(*core->PC)]); 

        // increase PC by op size - 1
        (*core->PC) += (OP_CODES[*inst * 3] - 1); 

        // add min  cycle count
        core->cycles += OP_CODES[*inst * 3 + 1]; 

        if (*inst == 0) {
            break;
        }

        dump(core);
        usleep(1000000);

    }

    free(mem);
    free(core);
    return 0;
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

