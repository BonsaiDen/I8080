
#include "mmu.h"

extern uint8_t *MEMORY;

#ifdef DEBUG_MEM
#include <curses.h>
extern WINDOW *mem_win;
#endif

inline uint8_t mmu_read(uint16_t addr) {
    uint16_t val = MEMORY[addr];
    #ifdef DEBUG_MEM
        wprintw(mem_win, "  [R 8] (%5d) %3d\n", addr, val);
    #endif
    return val;
}

inline void mmu_write(uint16_t addr, uint8_t val) {
    #ifdef DEBUG_MEM
        wprintw(mem_win, "  [W 8] (%5d) %3d\n", addr, val);
    #endif
    MEMORY[addr] = val;
}

