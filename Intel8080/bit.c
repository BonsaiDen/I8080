// Bitwise Instructions -------------------------------------------------------
// ----------------------------------------------------------------------------
#include "Cpu.h"
#include "flags.h"


// Rotate left ignoring F carry
static void RLC(Intel8080 *cpu) {
    uint8_t carry = (*cpu->A) & 128 ? 1 : 0; // check msb of A
    *cpu->A = ((*cpu->A) << 1) + carry;
    *cpu->F = ((*cpu->F) & ~1) | carry; // set new carry
}

// Rotate A left dropping MSB in favor fo F carry
static void RAL(Intel8080 *cpu) {
    uint8_t carry_in   = (*cpu->F) &   1 ? 1 : 0; // check carry flag
    uint8_t carry_out  = (*cpu->A) & 128 ? 1 : 0; // check msb of A

    *cpu->A = ((*cpu->A) << 1) + carry_in;
    *cpu->F = ((*cpu->F) & ~1) | carry_out; // set new carry
}

// Rotate A right ignoring F carry
static void RRC(Intel8080 *cpu) {
    uint8_t carry_in   = (*cpu->A) & 1 ? 128 : 0; // check for msb of A
    uint8_t carry_out  = (*cpu->A) & 1 ?   1 : 0; // check for lsb of A

    *cpu->A = ((*cpu->A) >> 1) + carry_in;
    *cpu->F = ((*cpu->F) & ~1) | carry_out; // set new carry
}

// Rotate A left dropping LSB in favor fo F carry
static void RAR(Intel8080 *cpu) {
    uint8_t carry_in   = (*cpu->F) & 1 ? 128 : 0; // check for carry flag
    uint8_t carry_out  = (*cpu->A) & 1 ?   1 : 0; // check for lsb of A

    *cpu->A = ((*cpu->A) >> 1) + carry_in;
    *cpu->F = ((*cpu->F) & ~1) | carry_out; // set new carry
}


// AND A with register REG
#define ANA(REG) static void ANA_##REG(Intel8080 *cpu) { \
    *cpu->A &= *cpu->REG; \
    cpu_flag_szp(cpu, cpu->A); \
}
ANA(B) ANA(C) ANA(D) ANA(E) ANA(H) ANA(L) ANA(A)

// AND A with contents of (HL)
static void ANA_M(Intel8080 *cpu) {
    *cpu->A &= cpu->read_mem(*cpu->HL); \
    cpu_flag_szp(cpu, cpu->A); \
}

// AND A with next BYTE
static void ANI(Intel8080 *cpu) {
    *cpu->A &= cpu->read_mem(*cpu->PC); \
    cpu_flag_szp(cpu, cpu->A); \
}


// XOR A with register REG
#define XRA(REG) static void XRA_##REG(Intel8080 *cpu) { \
    *cpu->A ^= *cpu->REG; \
    cpu_flag_szp(cpu, cpu->A); \
}
XRA(B) XRA(C) XRA(D) XRA(E) XRA(H) XRA(L) XRA(A)

// XOR A with contents of (HL)
static void XRA_M(Intel8080 *cpu) {
    *cpu->A ^= cpu->read_mem(*cpu->HL); \
    cpu_flag_szp(cpu, cpu->A); \
}

// XOR A with next BYTE
static void XRI(Intel8080 *cpu) {
    *cpu->A ^= cpu->read_mem(*cpu->PC); \
    cpu_flag_szp(cpu, cpu->A); \
}


// OR A with register REG
#define ORA(REG) static void ORA_##REG(Intel8080 *cpu) { \
    *cpu->A |= *cpu->REG; \
    cpu_flag_szp(cpu, cpu->A); \
}
ORA(B) ORA(C) ORA(D) ORA(E) ORA(H) ORA(L) ORA(A)

// OR A with contents of (HL)
static void ORA_M(Intel8080 *cpu) {
    *cpu->A |= cpu->read_mem(*cpu->HL); \
    cpu_flag_szp(cpu, cpu->A); \
}

// OR A with next BYTE
static void ORI(Intel8080 *cpu) {
    *cpu->A |= cpu->read_mem(*cpu->PC); \
    cpu_flag_szp(cpu, cpu->A); \
}

