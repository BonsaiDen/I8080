// Other Accumulator Instructions ---------------------------------------------
// ----------------------------------------------------------------------------
#include "../cpu/8080.h"


// Load BYTE (WORD) into A
static void LDA() {
    uint16_t addr = mmu_read(*CPU->PC) | (mmu_read((*CPU->PC) + 1) << 8);
    *CPU->A = mmu_read(addr);
}

// Read BYTE (BC) into A
static void LDAX_B() {
    *CPU->A = mmu_read(*CPU->BC);
}

// Read BYTE (DE) into A
static void LDAX_D() {
    *CPU->A = mmu_read(*CPU->DE);
}


// Store A to (WORD)
static void STA() {
    uint16_t addr = mmu_read(*CPU->PC) | (mmu_read((*CPU->PC) + 1) << 8);
    mmu_write(addr, *CPU->A);
}

// Store A to (BC)
static void STAX_B() {
    mmu_write(*CPU->BC, *CPU->A);
}

// Store A to (DE)
static void STAX_D() {
    mmu_write(*CPU->DE, *CPU->A);
}

