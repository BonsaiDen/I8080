
#include "mmu.h"
#include "cpu.h"

#include <stdio.h>

extern uint8_t *MEMORY;
extern uint8_t PAGE;
extern CPU_8080 *CPU;

#ifdef DEBUG_MEM
#include <curses.h>
extern WINDOW *mem_win;
#endif

inline uint8_t read8(uint16_t addr) {
    if (addr < 0 || addr > 0xffff) {
        #ifdef DEBUG_MEM
            wprintw(mem_win, "  [R 8] (%5d) INVALID\n", addr);
        #endif
        return 0;
    }

    uint16_t val = MEMORY[addr];
    #ifdef DEBUG_MEM
        wprintw(mem_win, "  [R 8] (%5d) %3d\n", addr, val);
    #endif
    return val;
}

inline uint16_t read16(uint16_t addr) {
    uint16_t val = MEMORY[addr] | MEMORY[addr + 1] << 8;
    #ifdef DEBUG_MEM
        wprintw(mem_win, "  [R16] (%5d) %5d\n", addr, val);
    #endif
    return val;
}

inline void write8(uint16_t addr, uint8_t *val) {

    if (addr < 0 || addr > 0xffff) {
        #ifdef DEBUG_MEM
            wprintw(mem_win, "  [R 8] (%5d) INVALID\n", addr);
        #endif
        return;
    }

    #ifdef DEBUG_MEM
        wprintw(mem_win, "  [W 8] (%5d) %3d\n", addr, *val);
    #endif
    MEMORY[addr] = *val;
}

inline void write16(uint16_t addr, uint16_t *val) {
    #ifdef DEBUG_MEM
        wprintw(mem_win, "  [W16] (%5d) %5d\n", addr, *val);
    #endif
    MEMORY[addr] = *val & 0xff;
    MEMORY[addr + 1] = *val >> 8;
}

