// gcc -ggdb -o main cpu.c mmu.c main.c -fomit-frame-pointer -lcurses -DDEBUG_MEM && ./main




#include "cpu/8080.h"
#include "mmu.h"
#include "ops/codes.h"
#include "ops/names.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#include <sys/timeb.h>

uint8_t *MEMORY;

static void emulate();

int main(int argc, const char *argv[]) {

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
    struct timeb tp;
    ftime(&tp);
    return tp.millitm + tp.time * 1000;
}


static void emulate() {
    
    CPU_8080 *cpu = cpu_create();
    *cpu->SP = 65535;
    // TODO add MMU reference and stuff

    unsigned int clock_speed = 2,
                 cycles_per_second = 0,
                 second_time = 0,
                 time_taken = 10;

    unsigned long last_time = now();

    for(;;) {

        unsigned long start_time = now();
        unsigned long cycle_end = cpu->cycle_count + clock_speed * 10000;
        while(cpu->cycle_count < cycle_end) {
            cpu->fetch(cpu);
            cycles_per_second += cpu->exec(cpu);
        }

        // Speed control
        usleep(10000 - time_taken * 20); // sleep ~10 ms - some other stuff

        time_taken = now() - start_time;
        second_time += time_taken;

        // Log Mhz every second
        if (second_time >= 1000) {

            uint8_t flags = *cpu->F;
            printf("\n  (F) %c %c %c %c %c %c %c %c\n", 
                        (flags & 128) ? 'S' : '-',
                        (flags &  64) ? 'Z' : '-',
                        (flags &  32) ? '0' : ' ',
                        (flags &  16) ? 'A' : '-',
                        (flags &   8) ? '0' : ' ',
                        (flags &   4) ? 'P' : '-',
                        (flags &   2) ? '1' : ' ',
                        (flags &   1) ? 'C' : '-' );

            printf("  (A)   %03d (PSW) %05d  (OP)  %-5s\n", *cpu->A, *cpu->PSW, OP_CODE_NAMES[cpu->instruction]);
            printf("  (B)   %03d   (C)   %03d  (BC)  %05d\n", *cpu->B, *cpu->C, *cpu->BC);
            printf("  (D)   %03d   (E)   %03d  (DE)  %05d\n", *cpu->D, *cpu->E, *cpu->DE);
            printf("  (H)   %03d   (L)   %03d  (HL)  %05d\n", *cpu->H, *cpu->L, *cpu->HL);
            printf(" (SP) %05d  (PC) %05d\n", *cpu->SP, *cpu->PC);
            printf("(CYC) %17lu\n", cpu->cycle_count);

            double cur_clock_speed = (double)cycles_per_second / 1000000;
            printf("Clocking at %.2f Mhz\n", cur_clock_speed);

            cycles_per_second = 0;
            second_time -= 1000;

        }

    }

    cpu->destroy(&cpu);

}

