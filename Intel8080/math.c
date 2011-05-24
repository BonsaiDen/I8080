// Math Instructions ----------------------------------------------------------
// ----------------------------------------------------------------------------
#include "Cpu.h"
#include "flags.h"


// Compare A with REG
#define CMP(REG) static void OP_CMP_##REG(Intel8080 *cpu) { \
    int16_t i = *cpu->A - *cpu->REG; \
    *cpu->A = i & 0xff; \
    cpu_flag_szp(cpu, cpu->A); \
    *cpu->F |= i < 0; \
}

CMP(B) CMP(C) CMP(D) CMP(E) CMP(H) CMP(L) CMP(A)

// Compare A with (HL)
static void OP_CMP_M(Intel8080 *cpu) { \
    int16_t i = *cpu->A - cpu->read_mem(*cpu->HL);
    *cpu->A = i & 0xff;
    cpu_flag_szp(cpu, cpu->A);
    *cpu->F |= i < 0;
}

// Compare A with next BYTE
static void OP_CPI(Intel8080 *cpu) {
    int16_t i = *cpu->A - cpu->read_mem(*cpu->PC);
    *cpu->A = i & 0xff;
    cpu_flag_szp(cpu, cpu->A);
    *cpu->F |= i < 0;
}


// 8 BIT ----------------------------------------------------------------------
// ----------------------------------------------------------------------------


// Add (REG) to A
#define ADD(REG) static void OP_ADD_##REG(Intel8080 *cpu) { \
    uint16_t i = *cpu->A + *cpu->REG; \
    *cpu->A = i & 0xff; \
    cpu_flag_szap(cpu, cpu->A); \
    *cpu->F |= i > 0xff; \
}
ADD(B) ADD(C) ADD(D) ADD(E) ADD(H) ADD(L) ADD(A)

// Add contents of (HL) to A
static void OP_ADD_M(Intel8080 *cpu) { \
    uint16_t i = *cpu->A + cpu->read_mem(*cpu->HL);
    *cpu->A = i & 0xff; // mask to 255
    cpu_flag_szap(cpu, cpu->A); // check flags
    *cpu->F |= i > 0xff; // set carry flag
}

// Add next BYTE to A
static void OP_ADI(Intel8080 *cpu) {
    uint16_t i = *cpu->A + cpu->read_mem(*cpu->PC);
    *cpu->A = i & 0xff;
    cpu_flag_szap(cpu, cpu->A);
    *cpu->F |= i > 0xff;
}


// Add (REG + carry) to A
#define ADC(REG) static void OP_ADC_##REG(Intel8080 *cpu) { \
    uint16_t i = (*cpu->A + *cpu->REG) + (*cpu->F & 1); \
    *cpu->A = i & 0xff; \
    cpu_flag_szap(cpu, cpu->A); \
    *cpu->F |= i > 0xff; \
}
ADC(B) ADC(C) ADC(D) ADC(E) ADC(H) ADC(L) ADC(A)

// Add (contents of (HL) + carry) to A
static void OP_ADC_M(Intel8080 *cpu) {
    uint16_t i = (*cpu->A + cpu->read_mem(*cpu->HL)) + (*cpu->F & 1);
    *cpu->A = i & 0xff; // mask to 255
    cpu_flag_szap(cpu, cpu->A); // check flags
    *cpu->F |= i > 0xff; // set carry flag
}

// Add next (BYTE + carry) to A
static void OP_ACI(Intel8080 *cpu) {
    uint16_t i = *cpu->A + cpu->read_mem(*cpu->PC) + (*cpu->F & 1);
    *cpu->A = i & 0xff;
    cpu_flag_szap(cpu, cpu->A);
    *cpu->F |= i > 0xff;
}


// Subtract (REG) from A
#define SUB(REG) static void OP_SUB_##REG(Intel8080 *cpu) { \
    int16_t i = *cpu->A - *cpu->REG; \
    *cpu->A = i & 0xff; \
    cpu_flag_szp(cpu, cpu->A); \
    *cpu->F |= i < 0; \
}
SUB(B) SUB(C) SUB(D) SUB(E) SUB(H) SUB(L) SUB(A)

// Subtract contents of (HL) from A
static void OP_SUB_M(Intel8080 *cpu) { \
    int16_t i = *cpu->A - cpu->read_mem(*cpu->HL);
    *cpu->A = i & 0xff; // mask to 255
    cpu_flag_szp(cpu, cpu->A); // check flags
    *cpu->F |= i < 0; // set carry flag
}

// Subtract next BYTE from A
static void OP_SUI(Intel8080 *cpu) {
    uint16_t i = *cpu->A - cpu->read_mem(*cpu->PC);
    *cpu->A = i & 0xff;
    cpu_flag_szap(cpu, cpu->A);
    *cpu->F |= i < 0xff;
}


// Subtract (REG + carry) from A
#define SBB(REG) static void OP_SBB_##REG(Intel8080 *cpu) { \
    int16_t i = (*cpu->A - *cpu->REG) - (*cpu->F & 1); \
    *cpu->A = i & 0xff; \
    cpu_flag_szp(cpu, cpu->A); \
    *cpu->F |= i < 0; \
}
SBB(B) SBB(C) SBB(D) SBB(E) SBB(H) SBB(L) SBB(A)

// Subtract (contents of (HL) + carry) from A
static void OP_SBB_M(Intel8080 *cpu) {
    int16_t i = (*cpu->A - cpu->read_mem(*cpu->HL)) - (*cpu->F & 1);
    *cpu->A = i & 0xff; // mask to 255
    cpu_flag_szp(cpu, cpu->A); // check flags
    *cpu->F |= i < 0; // set carry flag
}

// Subtract next (BYTE + carry) from A
static void OP_SBI(Intel8080 *cpu) {
    uint16_t i = (*cpu->A - cpu->read_mem(*cpu->PC)) - (*cpu->F & 1);
    *cpu->A = i & 0xff;
    cpu_flag_szap(cpu, cpu->A);
    *cpu->F |= i < 0xff;
}


// 16 BIT ---------------------------------------------------------------------
// ----------------------------------------------------------------------------

// Add BC to HL
static void OP_DAD_B(Intel8080 *cpu) {
    uint32_t i = *cpu->HL + *cpu->BC;
    *cpu->F = i > 0xffff; // Carry is bit 1, so this clears and sets correctly
    *cpu->HL = (i & 0xffff);
}

// Add DE to HL
static void OP_DAD_D(Intel8080 *cpu) {
    uint32_t i = *cpu->HL + *cpu->DE;
    *cpu->F = i > 0xffff;
    *cpu->HL = (i & 0xffff);
}

// Add HL to HL
static void OP_DAD_H(Intel8080 *cpu) {
    uint32_t i = *cpu->HL + *cpu->HL;
    *cpu->F = i > 0xffff;
    *cpu->HL = (i & 0xffff);
}

// Add SP to HL
static void OP_DAD_SP(Intel8080 *cpu) {
    uint32_t i = *cpu->HL + *cpu->SP;
    *cpu->F = i > 0xffff;
    *cpu->HL = (i & 0xffff);
}

