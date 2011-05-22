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
    
    // Start CPU
    cpu_init();
    *CPU->SP = 65535;
    emulate();

    free(MEMORY);
    cpu_destroy();

    return 0;

}


static unsigned long now() {
    struct timeb tp;
    ftime(&tp);
    return tp.millitm + tp.time * 1000;
}


static void emulate() {

    unsigned int clock_speed = 2,
                 cycles_per_second = 0,
                 second_time = 0,
                 time_taken = 10;

    unsigned long last_time = now();

    for(;;) {

        unsigned long start_time = now();
        unsigned long cycle_end = CPU->cycle_count + clock_speed * 10000;
        while(CPU->cycle_count < cycle_end) {
            cpu_fetch();
            cycles_per_second += cpu_exec();
        }

        // Speed control
        usleep(10000 - time_taken * 20); // sleep ~10 ms - some other stuff

        time_taken = now() - start_time;
        second_time += time_taken;

        // Log Mhz every second
        if (second_time >= 1000) {

            double cur_clock_speed = (double)cycles_per_second / 1000000;
            printf("Clocking at %.2f Mhz\n", cur_clock_speed);

            cycles_per_second = 0;
            second_time -= 1000;

        }

    }

}

//            if (counter <= 0) {
//                printf("Hello World!\n");
//                counter += vblank_interrupt;
//            }


//
//    unsigned int CPU_HZ = 2000000;
//    unsigned int SCREEN_HZ = 50;
//    unsigned int VBLANK = CPU_HZ / SCREEN_HZ;
//    unsigned int SCANLINES = 256;
//    unsigned int SCREEN_LINES = 212;
//    unsigned int vblank_interrupt = (SCANLINES - SCREEN_LINES) * VBLANK / SCANLINES;
//    unsigned int CYCLE_DURATION = 1000000 / CPU_HZ;
//
//    printf("%d\n", vblank_interrupt);
//
//    int counter = vblank_interrupt;
//
//
