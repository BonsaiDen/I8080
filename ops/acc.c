// Other Accumulator Instructions ---------------------------------------------
// ----------------------------------------------------------------------------
#include "../cpu.h"
extern CPU_8080 *CPU;


// Compare A with REG
#define CMP(REG) static void CMP_##REG() { \
    int16_t i = *CPU->A - *CPU->REG; \
    *CPU->A = i & 0xff; \
    cpu_flag_szp(CPU->A); \
    *CPU->F |= i < 0; \
}

CMP(B); CMP(C); CMP(D); CMP(E); CMP(H); CMP(L); CMP(A);

// Compare A with (HL)
static void CMP_M() { \
    int16_t i = *CPU->A - read8(*CPU->HL);
    *CPU->A = i & 0xff;
    cpu_flag_szp(CPU->A);
    *CPU->F |= i < 0;
}


// Load BYTE (WORD) into A
static void LDA() {
    *CPU->A = read8(read16(*CPU->PC));
}

// Read BYTE (BC) into A
static void LDAX_B() {
    *CPU->A = read8(*CPU->BC);
}

// Read BYTE (DE) into A
static void LDAX_D() {
    *CPU->A = read(*CPU->DE);
}


// Store A to (WORD)
static void STA() {
    write8(read16(*CPU->PC), CPU->A);
}

// Store A to (BC)
static void STAX_B() {
    write8(*CPU->BC, CPU->A);
}

// Store A to (DE)
static void STAX_D() {
    write8(*CPU->DE, CPU->A);
}

