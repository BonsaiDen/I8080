
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
#include "inst.h"
#include "inst_names.h"


static void run();

int main(int argc, const char *argv[]) {

    // Setup
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    cpu_win = newwin(LINES, COLS / 2, 0, 0);
    mem_win = newwin(LINES, COLS / 2 - 1, 0, COLS / 2 + 1);

    // Init memory
    MEMORY = calloc(65536, sizeof(uint8_t));
    uint8_t TEST[65536] = {


        STA,  255, 0,
        MVI_A,     0,
        LDA,  255, 0,
        LHLD, 100, 0,

        LXI_B, 42, 0,

        DAD_B,

        SHLD, 110, 0,

        LXI_H,  0, 0,

        LHLD, 110, 0,
        
        HLT

    };

    TEST[100] = 255;
    TEST[101] = 128;

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

    while(1) {
        
        uint8_t inst = *cpu_next();
        
        wprintw(mem_win, "%-5s(%02x)\n", INST_NAMES[inst], inst);

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

        wprintw(cpu_win, "  (A)   %03d (PSW) %05d  (OP)  %-5s(%02x)\n", *CPU->A, *CPU->PSW, INST_NAMES[inst], inst);
        wprintw(cpu_win, "  (B)   %03d   (C)   %03d  (BC)  %05d\n", *CPU->B, *CPU->C, *CPU->BC);
        wprintw(cpu_win, "  (D)   %03d   (E)   %03d  (DE)  %05d\n", *CPU->D, *CPU->E, *CPU->DE);
        wprintw(cpu_win, "  (H)   %03d   (L)   %03d  (HL)  %05d\n", *CPU->H, *CPU->L, *CPU->HL);
        wprintw(cpu_win, " (SP) %05d  (PC) %05d\n", *CPU->SP, *CPU->PC);
        wprintw(cpu_win, "(CYC) %17lu\n", CPU->cycles);
        
        wrefresh(cpu_win);
        wrefresh(mem_win);
    
    }
    
}

