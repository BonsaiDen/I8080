// Stack Instructions ---------------------------------------------------------
// ----------------------------------------------------------------------------
#include "Cpu.h"
#include "flags.h"


// Push REG onto the Stack
#define PUSH(NAME, REG1, REG2) static void OP_PUSH_##NAME(Intel8080 *cpu) { \
    cpu->write_mem((*cpu->SP) - 1, *cpu->REG1); \
    cpu->write_mem((*cpu->SP) - 2, *cpu->REG2); \
    *cpu->SP -= 2; \
}
PUSH(B, B, C) PUSH(D, D, E) PUSH(H, H, L) PUSH(PSW, A, F)

// Pop Stack into REG
#define POP(NAME, REG1, REG2) static void OP_POP_##NAME(Intel8080 *cpu) { \
    *cpu->REG1 = cpu->read_mem((*cpu->SP) + 1); \
    *cpu->REG2 = cpu->read_mem(*cpu->SP); \
    *cpu->SP += 2; \
}
POP(B, B, C) POP(D, D, E) POP(H, H, L) POP(PSW, A, F)


// Exchange HL and DE
static void OP_XCHG(Intel8080 *cpu) {
    uint16_t i = *cpu->HL;
    *cpu->HL = *cpu->DE;
    *cpu->DE = i;
}


// Exchange Top of Stack with HL
// Swap H with (SP +1) / L with (SP)
static void OP_XTHL(Intel8080 *cpu) {
    uint8_t h = *cpu->H;
    uint8_t l = *cpu->L;

    *cpu->H = cpu->read_mem((*cpu->SP) + 1);
    *cpu->L = cpu->read_mem((*cpu->SP));
    
    cpu->write_mem(*cpu->SP + 1, h);
    cpu->write_mem(*cpu->SP, l);
}

