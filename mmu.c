
#include "mmu.h"
#include "cpu.h"

#include <stdio.h>

extern uint8_t *MEMORY;
extern uint8_t PAGE;
extern CPU_8080 *CPU;

inline uint8_t read8(uint16_t addr) {
    uint16_t val = MEMORY[addr];
    #ifdef DEBUG_MEM
        printf("MEM (read8) @ %d > %d\n", addr, val);
    #endif
    return val;
}

inline uint16_t read16(uint16_t addr) {
    uint16_t val = MEMORY[addr] << 8 | MEMORY[addr + 1];
    #ifdef DEBUG_MEM
        printf("MEM (read16) @ %d > %d\n", addr, val);
    #endif
    return val;
}

inline void write8(uint16_t addr, uint8_t *val) {
    #ifdef DEBUG_MEM
        printf("MEM (write8) @ %d > %d\n", addr, *val);
    #endif
    MEMORY[addr] = *val;
}

inline void write16(uint16_t addr, uint16_t *val) {
    #ifdef DEBUG_MEM
        printf("MEM (write16) @ %d > %d\n", addr, *val);
    #endif
    MEMORY[addr] = *val >> 8;
    MEMORY[addr + 1] = *val & 0xff;
}

