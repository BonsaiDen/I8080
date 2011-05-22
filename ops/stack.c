// Stack Instructions ---------------------------------------------------------
// ----------------------------------------------------------------------------
#include "../cpu/8080.h"


// Push REG onto the Stack
#define PUSH(NAME, REG1, REG2) static void PUSH_##NAME() { \
    mmu_write((*CPU->SP) - 1, *CPU->REG1); \
    mmu_write((*CPU->SP) - 2, *CPU->REG2); \
    *CPU->SP -= 2; \
}
PUSH(B, B, C); PUSH(D, D, E); PUSH(H, H, L); PUSH(PSW, A, F);

// Pop Stack into REG
#define POP(NAME, REG1, REG2) static void POP_##NAME() { \
    *CPU->REG1 = mmu_read((*CPU->SP) + 1); \
    *CPU->REG2 = mmu_read(*CPU->SP); \
    *CPU->SP += 2; \
}
POP(B, B, C); POP(D, D, E); POP(H, H, L); POP(PSW, A, F);


// Exchange HL and DE
static void XCHG() {
    uint16_t i = *CPU->HL;
    *CPU->HL = *CPU->DE;
    *CPU->DE = i;
}


// Exchange Top of Stack with HL
// Swap H with (SP +1) / L with (SP)
static void XTHL() {
    uint8_t h = *CPU->H;
    uint8_t l = *CPU->L;

    *CPU->H = mmu_read((*CPU->SP) + 1);
    *CPU->L = mmu_read((*CPU->SP));
    
    mmu_write(*CPU->SP + 1, h);
    mmu_write(*CPU->SP, l);
}

