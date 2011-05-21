
#include <stdio.h>
#include "cpu.h"

extern uint8_t *MEMORY;
extern CPU_8080 *CPU;

/* Others ------------------------------------------------------------------- */
static void NOP(uint8_t *mem) { };


/* Move --------------------------------------------------------------------- */
#define MVI_8(REG) static void MVI_##REG(uint8_t *mem) { \
    *CPU->REG = *mem; \
}

MVI_8(A); MVI_8(B); MVI_8(C); MVI_8(D);
MVI_8(E); MVI_8(H); MVI_8(L);

static void MVI_M(uint8_t *mem) {
    *CPU->HL = *mem;
}


/* Load --------------------------------------------------------------------- */
#define LXI(REG, RE) static void LXI_##REG(uint8_t *mem) { \
    *CPU->RE = read16(mem); \
}

LXI(B, BC);
LXI(D, DE);
LXI(H, HL);
LXI(SP, SP);

static void LDAX_B(uint8_t *mem) {
    *CPU->A = *CPU->BC;
}

static void LDAX_D(uint8_t *mem) {
    *CPU->A = *CPU->DE;
}


// Memory
static void LHLD(uint8_t *mem) {
    *CPU->HL = read16(read16(*mem));
}


/* Store -------------------------------------------------------------------- */
static void STAX_B(uint8_t *mem) {
    *CPU->BC = *CPU->A;
}

static void STAX_D(uint8_t *mem) {
    *CPU->DE = *CPU->A;
}


// Memory
static void SHLD(uint8_t *mem) {
    write16(read16(*mem), CPU->HL);
}

// just here to make gcc compile
static void DAA(uint8_t *mem) {
    
}

static void STA(uint8_t *mem) {
    
}

static void STC(uint8_t *mem) {
    
}

static void LDA(uint8_t *mem) {
    
}

static void CMC(uint8_t *mem) {
    
}
static void CMA(uint8_t *mem) {
    
}


/* Increment ---------------------------------------------------------------- */
#define INX_16(REG, RE) static void INX_##REG(uint8_t *mem) { \
    (*CPU->RE)++; \
}

INX_16(B, BC);
INX_16(D, DE);
INX_16(H, HL);
INX_16(SP, SP);

// 8 bit
#define INR_8(REG) static void INR_##REG(uint8_t *mem) { \
    (*CPU->REG)++; \
    cpu_flag_szap_inc((uint16_t*)CPU->REG); \
}

INR_8(A);
INR_8(B);
INR_8(C);
INR_8(D);
INR_8(E);
INR_8(H);
INR_8(L);

// 16 bit
static void INR_M(uint8_t *mem) {
    (*CPU->HL)++;
    cpu_flag_szap_inc(CPU->HL);
}


/* Decrement ---------------------------------------------------------------- */
#define DCX_16(REG, RE) static void DCX_##REG(uint8_t *mem) { \
    (*CPU->RE)--; \
}

DCX_16(B, BC);
DCX_16(D, DE);
DCX_16(H, HL);
DCX_16(SP, SP);

// 8 bit
#define DCR_8(REG) static void DCR_##REG(uint8_t *mem) { \
    (*CPU->REG)--; \
    cpu_flag_szap_dec((uint16_t*)CPU->REG); \
}

DCR_8(A);
DCR_8(B);
DCR_8(C);
DCR_8(D);
DCR_8(E);
DCR_8(H);
DCR_8(L);


// 16 bit
#define DCR_16(REG, RE) static void DCR_##REG(uint8_t *mem) { \
    (*CPU->RE)--; \
    cpu_flag_szap_dec(CPU->RE); \
}

DCR_16(M, HL);


/* Rotate ------------------------------------------------------------------- */
static void RLC(uint8_t *mem) {
    // reg C left, check carry...
}

static void RRC(uint8_t *mem) {
    // reg C right
}

static void RAL(uint8_t *mem) {
    // reg A left
}

static void RAR(uint8_t *mem) {
    // reg A right
}


/* Double Add --------------------------------------------------------------- */
static void DAD_B(uint8_t *mem) {
    uint32_t i = *CPU->HL + *CPU->BC;
    *CPU->F = i > 0xffff;
    *CPU->HL = (i & 0xffff);
}

static void DAD_D(uint8_t *mem) {
    uint32_t i = *CPU->HL + *CPU->DE;
    *CPU->F = i > 0xffff;
    *CPU->HL = (i & 0xffff);
}

static void DAD_H(uint8_t *mem) {
    uint32_t i = *CPU->HL + *CPU->HL;
    *CPU->F = i > 0xffff;
    *CPU->HL = (i & 0xffff);
}

static void DAD_SP(uint8_t *mem) {
    uint32_t i = *CPU->HL + *CPU->SP;
    *CPU->F = i > 0xffff;
    *CPU->HL = (i & 0xffff);
}

