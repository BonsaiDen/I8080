// gcc -ggdb -o main cpu.c mmu.c main.c -fomit-frame-pointer -lcurses -DDEBUG_MEM && ./main




#include "cpu/8080.h"
#include "mmu.h"
#include "ops/codes.h"
#include "ops/names.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <curses.h>
#include <unistd.h>

uint8_t *MEMORY;
WINDOW *cpu_win;
WINDOW *mem_win;


static void run();

int main(int argc, const char *argv[]) {

    // Setup
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    cpu_win = newwin(LINES, COLS / 2, 15, 0);
    mem_win = newwin(LINES, COLS / 2 - 1, 0, COLS / 2 + 1);
    scrollok(mem_win, TRUE);

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
    run();

    // cleanup
    free(mem_win);
    free(cpu_win);
    free(MEMORY);

    cpu_destroy();
    endwin();

    return 0;

}

static void run() {

    int ch = 0;
    int paused = 0, first = 1, count = 0;
    while(1) {
            
        if (!paused) {

            uint8_t inst = 0;
            if (!first) {

                cpu_fetch();
                inst = CPU->instruction;
//                wprintw(mem_win, "%-5s(%02x)\n", OP_CODE_NAMES[inst], inst);
                cpu_exec();
                
            }
            
            if (count > 2000) {
                 
                uint8_t flags = *CPU->F;
                wmove(cpu_win, 0, 0);
                wprintw(cpu_win, "\n  (F) %c %c %c %c %c %c %c %c\n", 
                            (flags & 128) ? 'S' : '-',
                            (flags &  64) ? 'Z' : '-',
                            (flags &  32) ? '0' : ' ',
                            (flags &  16) ? 'A' : '-',
                            (flags &   8) ? '0' : ' ',
                            (flags &   4) ? 'P' : '-',
                            (flags &   2) ? '1' : ' ',
                            (flags &   1) ? 'C' : '-' );

                wprintw(cpu_win, "  (A)   %03d (PSW) %05d  (OP)  %-5s\n", *CPU->A, *CPU->PSW, OP_CODE_NAMES[inst]);
                wprintw(cpu_win, "  (B)   %03d   (C)   %03d  (BC)  %05d\n", *CPU->B, *CPU->C, *CPU->BC);
                wprintw(cpu_win, "  (D)   %03d   (E)   %03d  (DE)  %05d\n", *CPU->D, *CPU->E, *CPU->DE);
                wprintw(cpu_win, "  (H)   %03d   (L)   %03d  (HL)  %05d\n", *CPU->H, *CPU->L, *CPU->HL);
                wprintw(cpu_win, " (SP) %05d  (PC) %05d\n", *CPU->SP, *CPU->PC);
                wprintw(cpu_win, "(CYC) %17lu\n", CPU->cycles);
                wrefresh(cpu_win);
                count = 0;
            }

        }

        count++;
//        wrefresh(mem_win);

//        usleep(1);
        first = 0;
    
    }
    
}

