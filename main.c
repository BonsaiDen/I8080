#include "Intel8080/Cpu.h"
#include "Intel8080/Codes.h"
#include "Intel8080/Names.h"


#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

uint8_t *MEMORY;

static uint8_t mmu_read(uint16_t addr) {
    uint16_t val = MEMORY[addr];
    #ifdef DEBUG_MEM
        wprintw(mem_win, "  [R 8] (%5d) %3d\n", addr, val);
    #endif
    return val;
}

static void mmu_write(uint16_t addr, uint8_t val) {
    #ifdef DEBUG_MEM
        wprintw(mem_win, "  [W 8] (%5d) %3d\n", addr, val);
    #endif
    MEMORY[addr] = val;
}


static void emulate();
static void dump(Intel8080 *cpu);

int main() {

    // Init memory
    MEMORY = calloc(65536, sizeof(uint8_t));
    uint8_t TEST[65536] = {
        
//        LHLD, 64, 0,
//        MVI_M, 17,
//        INR_M,
//        LHLD, 42, 0,
        CALL, 100, 0,
        JMP, 0, 0,
        HLT,
        NOP,

    };

    uint8_t LOOP[25] = {
        MVI_A, 128, // loop counter
        CPI, 0, // check if ourloop reached zero
        JZ, 111, 0, // in case it does, jump out
        DCR_A, // decrement A
        JMP, 102, 0, // jump back 
        INR_B,
        RET
    };

    memcpy(MEMORY, TEST, sizeof(TEST));
    memcpy(MEMORY + 100, LOOP, sizeof(LOOP));
    emulate();
    free(MEMORY);
    return 0;

}


static unsigned long now() {
    struct timeval t;
    gettimeofday(&t, NULL);
    return ((t.tv_sec) * 1000 + t.tv_usec / 1000.0) + 0.5;
}


static void emulate() {
    
    uint16_t top = 65535;
    Intel8080 *cpu = cpu_create(&mmu_read, &mmu_write, &top);

    unsigned int clock = 2;
    unsigned long last = now(), cycles = 0;
    int second = 0;

    // This loop tries to achieve a somewhat stable clock frequency
    for(;;) {

        unsigned long taken = now() - last;
        last = now();
        
        cycles += cpu->exec(cpu, clock * 1000 * taken);
        usleep(10000);

        second += taken;
        if (second >= 1000) {

            printf("Clocking at %.2f Mhz\n\n", (double)cycles / 1000000);
            dump(cpu);
            cycles = 0;
            second -= 1000;

        }

    }

    cpu->destroy(&cpu);

}

static void dump(Intel8080 *cpu) {

    uint8_t flags = *cpu->F;
    printf("  (F) %c %c %c %c %c\n", 
                (flags & 128) ? 'S' : '-', (flags &  64) ? 'Z' : '-',
                (flags &  16) ? 'A' : '-', (flags &   4) ? 'P' : '-',
                (flags &   1) ? 'C' : '-' );

    printf("  (A)   %03d (PSW) %05d  (OP)  %-5s\n", 
           *cpu->A, *cpu->PSW, INTEL_8080_OP_CODE_NAMES[cpu->instruction]);

    printf("  (B)   %03d   (C)   %03d  (BC)  %05d\n",
           *cpu->B, *cpu->C, *cpu->BC);

    printf("  (D)   %03d   (E)   %03d  (DE)  %05d\n",
           *cpu->D, *cpu->E, *cpu->DE);

    printf("  (H)   %03d   (L)   %03d  (HL)  %05d\n",
           *cpu->H, *cpu->L, *cpu->HL);

    printf(" (SP) %05d  (PC) %05d\n", *cpu->SP, *cpu->PC);
    printf("(CYC) %17lu\n\n", cpu->cycle_count);
//    fputs("\x1b[2J", stdout);

}

