// Math Instructions ----------------------------------------------------------
// ----------------------------------------------------------------------------
#include "../cpu/8080.h"


// Compare A with REG
#define CMP(REG) static void CMP_##REG(CPU_8080 *cpu) { \
    int16_t i = *cpu->A - *cpu->REG; \
    *cpu->A = i & 0xff; \
    cpu_flag_szp(cpu, cpu->A); \
    *cpu->F |= i < 0; \
}

CMP(B); CMP(C); CMP(D); CMP(E); CMP(H); CMP(L); CMP(A);

// Compare A with (HL)
static void CMP_M(CPU_8080 *cpu) { \
    int16_t i = *cpu->A - mmu_read(*cpu->HL);
    *cpu->A = i & 0xff;
    cpu_flag_szp(cpu, cpu->A);
    *cpu->F |= i < 0;
}

// Compare A with next BYTE
static void CPI(CPU_8080 *cpu) {
    int16_t i = *cpu->A - mmu_read(*cpu->PC);
    *cpu->A = i & 0xff;
    cpu_flag_szp(cpu, cpu->A);
    *cpu->F |= i < 0;
}


// 8 BIT ----------------------------------------------------------------------
// ----------------------------------------------------------------------------


// Add (REG) to A
#define ADD(REG) static void ADD_##REG(CPU_8080 *cpu) { \
    uint16_t i = *cpu->A + *cpu->REG; \
    *cpu->A = i & 0xff; \
    cpu_flag_szap(cpu, cpu->A); \
    *cpu->F |= i > 0xff; \
}
ADD(B); ADD(C); ADD(D); ADD(E); ADD(H); ADD(L); ADD(A);

// Add contents of (HL) to A
static void ADD_M(CPU_8080 *cpu) { \
    uint16_t i = *cpu->A + mmu_read(*cpu->HL);
    *cpu->A = i & 0xff; // mask to 255
    cpu_flag_szap(cpu, cpu->A); // check flags
    *cpu->F |= i > 0xff; // set carry flag
}

// Add next BYTE to A
static void ADI(CPU_8080 *cpu) {
    uint16_t i = *cpu->A + mmu_read(*cpu->PC);
    *cpu->A = i & 0xff;
    cpu_flag_szap(cpu, cpu->A);
    *cpu->F |= i > 0xff;
}


// Add (REG + carry) to A
#define ADC(REG) static void ADC_##REG(CPU_8080 *cpu) { \
    uint16_t i = (*cpu->A + *cpu->REG) + (*cpu->F & 1); \
    *cpu->A = i & 0xff; \
    cpu_flag_szap(cpu, cpu->A); \
    *cpu->F |= i > 0xff; \
}
ADC(B); ADC(C); ADC(D); ADC(E); ADC(H); ADC(L); ADC(A);

// Add (contents of (HL) + carry) to A
static void ADC_M(CPU_8080 *cpu) {
    uint16_t i = (*cpu->A + mmu_read(*cpu->HL)) + (*cpu->F & 1);
    *cpu->A = i & 0xff; // mask to 255
    cpu_flag_szap(cpu, cpu->A); // check flags
    *cpu->F |= i > 0xff; // set carry flag
}

// Add next (BYTE + carry) to A
static void ACI(CPU_8080 *cpu) {
    uint16_t i = *cpu->A + mmu_read(*cpu->PC) + (*cpu->F & 1);
    *cpu->A = i & 0xff;
    cpu_flag_szap(cpu, cpu->A);
    *cpu->F |= i > 0xff;
}


// Subtract (REG) from A
#define SUB(REG) static void SUB_##REG(CPU_8080 *cpu) { \
    int16_t i = *cpu->A - *cpu->REG; \
    *cpu->A = i & 0xff; \
    cpu_flag_szp(cpu, cpu->A); \
    *cpu->F |= i < 0; \
}
SUB(B); SUB(C); SUB(D); SUB(E); SUB(H); SUB(L); SUB(A);

// Subtract contents of (HL) from A
static void SUB_M(CPU_8080 *cpu) { \
    int16_t i = *cpu->A - mmu_read(*cpu->HL);
    *cpu->A = i & 0xff; // mask to 255
    cpu_flag_szp(cpu, cpu->A); // check flags
    *cpu->F |= i < 0; // set carry flag
}

// Subtract next BYTE from A
static void SUI(CPU_8080 *cpu) {
    uint16_t i = *cpu->A - mmu_read(*cpu->PC);
    *cpu->A = i & 0xff;
    cpu_flag_szap(cpu, cpu->A);
    *cpu->F |= i < 0xff;
}


// Subtract (REG + carry) from A
#define SBB(REG) static void SBB_##REG(CPU_8080 *cpu) { \
    int16_t i = (*cpu->A - *cpu->REG) - (*cpu->F & 1); \
    *cpu->A = i & 0xff; \
    cpu_flag_szp(cpu, cpu->A); \
    *cpu->F |= i < 0; \
}
SBB(B); SBB(C); SBB(D); SBB(E); SBB(H); SBB(L); SBB(A);

// Subtract (contents of (HL) + carry) from A
static void SBB_M(CPU_8080 *cpu) {
    int16_t i = (*cpu->A - mmu_read(*cpu->HL)) - (*cpu->F & 1);
    *cpu->A = i & 0xff; // mask to 255
    cpu_flag_szp(cpu, cpu->A); // check flags
    *cpu->F |= i < 0; // set carry flag
}

// Subtract next (BYTE + carry) from A
static void SBI(CPU_8080 *cpu) {
    uint16_t i = (*cpu->A - mmu_read(*cpu->PC)) - (*cpu->F & 1);
    *cpu->A = i & 0xff;
    cpu_flag_szap(cpu, cpu->A);
    *cpu->F |= i < 0xff;
}


// 16 BIT ---------------------------------------------------------------------
// ----------------------------------------------------------------------------

// Add BC to HL
static void DAD_B(CPU_8080 *cpu) {
    uint32_t i = *cpu->HL + *cpu->BC;
    *cpu->F = i > 0xffff; // Carry is bit 1, so this clears and sets correctly
    *cpu->HL = (i & 0xffff);
}

// Add DE to HL
static void DAD_D(CPU_8080 *cpu) {
    uint32_t i = *cpu->HL + *cpu->DE;
    *cpu->F = i > 0xffff;
    *cpu->HL = (i & 0xffff);
}

// Add HL to HL
static void DAD_H(CPU_8080 *cpu) {
    uint32_t i = *cpu->HL + *cpu->HL;
    *cpu->F = i > 0xffff;
    *cpu->HL = (i & 0xffff);
}

// Add SP to HL
static void DAD_SP(CPU_8080 *cpu) {
    uint32_t i = *cpu->HL + *cpu->SP;
    *cpu->F = i > 0xffff;
    *cpu->HL = (i & 0xffff);
}

