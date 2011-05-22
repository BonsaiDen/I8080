// gcc -ggdb -o main cpu.c mmu.c main.c -fomit-frame-pointer -lcurses -DDEBUG_MEM && ./main


#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <curses.h>

uint8_t PAGE;
uint8_t *MEMORY;

struct CPU_8080 *CPU;
WINDOW *cpu_win;
WINDOW *mem_win;

#include "cpu.h"
#include "mmu.h"
#include "ops/codes.h"
#include "ops/names.h"


static void run();

int main(int argc, const char *argv[]) {

    // Setup
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    cpu_win = newwin(LINES, COLS / 2, 0, 0);
    mem_win = newwin(LINES, COLS / 2 - 1, 0, COLS / 2 + 1);
    scrollok(mem_win, TRUE);

    // Init memory
    MEMORY = calloc(65536, sizeof(uint8_t));
    uint8_t TEST[65536] = {

        LHLD, 64, 0,
        INR_L,
        SHLD, 64, 0,
        LXI_H, 0, 0,
        LHLD, 64, 0,
        HLT,

    };

    TEST[64] = 42;
    TEST[100] = 128;

    memcpy(MEMORY, TEST, sizeof(TEST));
    
    // Start CPU
    CPU = cpu_create();
    run();

    // cleanup
    free(mem_win);
    free(cpu_win);
    free(MEMORY);
    free(CPU);
    endwin();

    return 0;

}

static void run() {

    *CPU->SP = 65535;

    int ch = 0;
    int paused = 0;
    while(1) {
            
        uint8_t inst = *cpu_next();
        if (!paused) {
            wprintw(mem_win, "%-5s(%02x)\n", OP_CODE_NAMES[inst], inst);
            cpu_step();
            
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
            
        }

        wrefresh(cpu_win);
        wrefresh(mem_win);

        usleep(1000000);
    
    }
    
}

