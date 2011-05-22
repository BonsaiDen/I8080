// Stack Instructions ---------------------------------------------------------
// ----------------------------------------------------------------------------
#include "../cpu/8080.h"


// Push REG onto the Stack
#define PUSH(NAME, REG1, REG2) static void PUSH_##NAME(CPU_8080 *cpu) { \
    mmu_write((*cpu->SP) - 1, *cpu->REG1); \
    mmu_write((*cpu->SP) - 2, *cpu->REG2); \
    *cpu->SP -= 2; \
}
PUSH(B, B, C); PUSH(D, D, E); PUSH(H, H, L); PUSH(PSW, A, F);

// Pop Stack into REG
#define POP(NAME, REG1, REG2) static void POP_##NAME(CPU_8080 *cpu) { \
    *cpu->REG1 = mmu_read((*cpu->SP) + 1); \
    *cpu->REG2 = mmu_read(*cpu->SP); \
    *cpu->SP += 2; \
}
POP(B, B, C); POP(D, D, E); POP(H, H, L); POP(PSW, A, F);


// Exchange HL and DE
static void XCHG(CPU_8080 *cpu) {
    uint16_t i = *cpu->HL;
    *cpu->HL = *cpu->DE;
    *cpu->DE = i;
}


// Exchange Top of Stack with HL
// Swap H with (SP +1) / L with (SP)
static void XTHL(CPU_8080 *cpu) {
    uint8_t h = *cpu->H;
    uint8_t l = *cpu->L;

    *cpu->H = mmu_read((*cpu->SP) + 1);
    *cpu->L = mmu_read((*cpu->SP));
    
    mmu_write(*cpu->SP + 1, h);
    mmu_write(*cpu->SP, l);
}

