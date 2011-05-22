// Bitwise Instructions -------------------------------------------------------
// ----------------------------------------------------------------------------
#include "../cpu.h"


// Rotate left ignoring F carry
static void RLC() {
    uint8_t carry = (*CPU->A) & 128 ? 1 : 0; // check msb of A
    *CPU->A = ((*CPU->A) << 1) + carry;
    *CPU->F = ((*CPU->F) & ~1) | carry; // set new carry
}

// Rotate A left dropping MSB in favor fo F carry
static void RAL() {
    uint8_t carry_in   = (*CPU->F) &   1 ? 1 : 0; // check carry flag
    uint8_t carry_out  = (*CPU->A) & 128 ? 1 : 0; // check msb of A

    *CPU->A = ((*CPU->A) << 1) + carry_in;
    *CPU->F = ((*CPU->F) & ~1) | carry_out; // set new carry
}

// Rotate A right ignoring F carry
static void RRC() {
    uint8_t carry_in   = (*CPU->A) & 1 ? 128 : 0; // check for msb of A
    uint8_t carry_out  = (*CPU->A) & 1 ?   1 : 0; // check for lsb of A

    *CPU->A = ((*CPU->A) >> 1) + carry_in;
    *CPU->F = ((*CPU->F) & ~1) | carry_out; // set new carry
}

// Rotate A left dropping LSB in favor fo F carry
static void RAR() {
    uint8_t carry_in   = (*CPU->F) & 1 ? 128 : 0; // check for carry flag
    uint8_t carry_out  = (*CPU->A) & 1 ?   1 : 0; // check for lsb of A

    *CPU->A = ((*CPU->A) >> 1) + carry_in;
    *CPU->F = ((*CPU->F) & ~1) | carry_out; // set new carry
}


// AND A with register REG
#define ANA(REG) static void ANA_##REG() { \
    *CPU->A &= *CPU->REG; \
    cpu_flag_szp(CPU->A); \
}
ANA(B); ANA(C); ANA(D); ANA(E); ANA(H); ANA(L); ANA(A);

// AND A with contents of (HL)
static void ANA_M() {
    *CPU->A &= read8(*CPU->HL); \
    cpu_flag_szp(CPU->A); \
}

// AND A with next BYTE
static void ANI() {
    *CPU->A &= read8(*CPU->PC); \
    cpu_flag_szp(CPU->A); \
}


// XOR A with register REG
#define XRA(REG) static void XRA_##REG() { \
    *CPU->A ^= *CPU->REG; \
    cpu_flag_szp(CPU->A); \
}
XRA(B); XRA(C); XRA(D); XRA(E); XRA(H); XRA(L); XRA(A);

// XOR A with contents of (HL)
static void XRA_M() {
    *CPU->A ^= read8(*CPU->HL); \
    cpu_flag_szp(CPU->A); \
}

// XOR A with next BYTE
static void XRI() {
    *CPU->A ^= read8(*CPU->PC); \
    cpu_flag_szp(CPU->A); \
}


// OR A with register REG
#define ORA(REG) static void ORA_##REG() { \
    *CPU->A |= *CPU->REG; \
    cpu_flag_szp(CPU->A); \
}
ORA(B); ORA(C); ORA(D); ORA(E); ORA(H); ORA(L); ORA(A);

// OR A with contents of (HL)
static void ORA_M() {
    *CPU->A |= read8(*CPU->HL); \
    cpu_flag_szp(CPU->A); \
}

// OR A with next BYTE
static void ORI() {
    *CPU->A |= read8(*CPU->PC); \
    cpu_flag_szp(CPU->A); \
}

