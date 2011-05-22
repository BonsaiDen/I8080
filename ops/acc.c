// Other Accumulator Instructions ---------------------------------------------
// ----------------------------------------------------------------------------
#include "../cpu/8080.h"


// Load BYTE (WORD) into A
static void LDA(CPU_8080 *cpu) {
    uint16_t addr = mmu_read(*cpu->PC) | (mmu_read((*cpu->PC) + 1) << 8);
    *cpu->A = mmu_read(addr);
}

// Read BYTE (BC) into A
static void LDAX_B(CPU_8080 *cpu) {
    *cpu->A = mmu_read(*cpu->BC);
}

// Read BYTE (DE) into A
static void LDAX_D(CPU_8080 *cpu) {
    *cpu->A = mmu_read(*cpu->DE);
}


// Store A to (WORD)
static void STA(CPU_8080 *cpu) {
    uint16_t addr = mmu_read(*cpu->PC) | (mmu_read((*cpu->PC) + 1) << 8);
    mmu_write(addr, *cpu->A);
}

// Store A to (BC)
static void STAX_B(CPU_8080 *cpu) {
    mmu_write(*cpu->BC, *cpu->A);
}

// Store A to (DE)
static void STAX_D(CPU_8080 *cpu) {
    mmu_write(*cpu->DE, *cpu->A);
}

