// Stack Instructions ---------------------------------------------------------
// ----------------------------------------------------------------------------
#include "../cpu.h"
extern CPU_8080 *CPU;


// Push REG onto the Stack
#define PUSH(NAME, REG1, REG2) static void PUSH_##NAME() { \
    write8((*CPU->SP) - 1, CPU->REG1); \
    write8((*CPU->SP) - 2, CPU->REG2); \
    *CPU->SP -= 2; \
}
PUSH(B, B, C); PUSH(D, D, E); PUSH(H, H, L); PUSH(PSW, A, F);

// Pop Stack into REG
#define POP(NAME, REG1, REG2) static void POP_##NAME() { \
    *CPU->REG1 = read8((*CPU->SP) + 1); \
    *CPU->REG2 = read8(*CPU->SP); \
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

    *CPU->H = read8((*CPU->SP) + 1);
    *CPU->L = read8((*CPU->SP));
    
    write8(*CPU->SP + 1, &h);
    write8(*CPU->SP, &l);
}

