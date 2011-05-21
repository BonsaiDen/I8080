
#include <stdlib.h>
#include <stdio.h>
#include "cpu.h"

/* Op Codes ----------------------------------------------------------------- */
static void NOP(CPU *c, uint8_t *mem) { }


/* Move --------------------------------------------------------------------- */
#define MVI_8(REG) static void MVI_##REG(CPU *c, uint8_t *mem) { \
    *c->REG = *mem; \
}

MVI_8(A);
MVI_8(B);
MVI_8(C);
MVI_8(D);
MVI_8(E);
MVI_8(H);
MVI_8(L);

static void MVI_M(CPU *c, uint8_t *mem) {
    *c->HL = *mem;
}


/* Load --------------------------------------------------------------------- */
#define LXI(REG, RE) static void LXI_##REG(CPU *c, uint8_t *mem) { \
    *c->RE = read16(mem); \
}

LXI(B, BC);
LXI(D, DE);
LXI(H, HL);
LXI(SP, SP);

static void LDAX_B(CPU *c, uint8_t *mem) {
    *c->A = *c->BC;
}

static void LDAX_D(CPU *c, uint8_t *mem) {
    *c->A = *c->DE;
}


// Memory
static void LHLD(CPU *c, uint8_t *mem) {

    // use c->mem here bcause *mem is offseted with the PC
    uint16_t p = read16(mem);
    *c->HL = read16(&c->mem[p]);

}


/* Store -------------------------------------------------------------------- */
static void STAX_B(CPU *c, uint8_t *mem) {
    *c->BC = *c->A;
}

static void STAX_D(CPU *c, uint8_t *mem) {
    *c->DE = *c->A;
}


// Memory
static void SHLD(CPU *c, uint8_t *mem) {
    
    // use c->mem here bcause *mem is offseted with the PC
    uint16_t p = read16(mem);
    write16(&c->mem[p], c->HL);

}

// just here to make gcc compile
static void DAA(CPU *c, uint8_t *mem) {
    
}

static void STA(CPU *c, uint8_t *mem) {
    
}

static void STC(CPU *c, uint8_t *mem) {
    
}

static void LDA(CPU *c, uint8_t *mem) {
    
}

static void CMC(CPU *c, uint8_t *mem) {
    
}
static void CMA(CPU *c, uint8_t *mem) {
    
}


/* Increment ---------------------------------------------------------------- */
#define INX_16(REG, RE) static void INX_##REG(CPU *c, uint8_t *mem) { \
    (*c->RE)++; \
}

INX_16(B, BC);
INX_16(D, DE);
INX_16(H, HL);
INX_16(SP, SP);

// 8 bit
#define INR_8(REG) static void INR_##REG(CPU *c, uint8_t *mem) { \
    (*c->REG)++; \
    check_szap_inc(c, (uint16_t*)c->REG); \
}

INR_8(A);
INR_8(B);
INR_8(C);
INR_8(D);
INR_8(E);
INR_8(H);
INR_8(L);

// 16 bit
static void INR_M(CPU *c, uint8_t *mem) {
    (*c->HL)++;
    check_szap_inc(c, c->HL);
}


/* Decrement ---------------------------------------------------------------- */
#define DCX_16(REG, RE) static void DCX_##REG(CPU *c, uint8_t *mem) { \
    (*c->RE)--; \
}

DCX_16(B, BC);
DCX_16(D, DE);
DCX_16(H, HL);
DCX_16(SP, SP);

// 8 bit
#define DCR_8(REG) static void DCR_##REG(CPU *c, uint8_t *mem) { \
    (*c->REG)--; \
    check_szap_dec(c, (uint16_t*)c->REG); \
}

DCR_8(A);
DCR_8(B);
DCR_8(C);
DCR_8(D);
DCR_8(E);
DCR_8(H);
DCR_8(L);


// 16 bit
#define DCR_16(REG, RE) static void DCR_##REG(CPU *c, uint8_t *mem) { \
    (*c->RE)--; \
    check_szap_dec(c, c->RE); \
}

DCR_16(M, HL);


/* Rotate ------------------------------------------------------------------- */
static void RLC(CPU *c, uint8_t *mem) {
    // reg C left, check carry...
}

static void RRC(CPU *c, uint8_t *mem) {
    // reg C right
}

static void RAL(CPU *c, uint8_t *mem) {
    // reg A left
}

static void RAR(CPU *c, uint8_t *mem) {
    // reg A right
}


/* Double Add --------------------------------------------------------------- */
static void DAD_B(CPU *c, uint8_t *mem) {
    uint32_t i = *c->HL + *c->BC;
    *c->F = i > 0xffff;
    *c->HL = (i & 0xffff);
}

static void DAD_D(CPU *c, uint8_t *mem) {
    uint32_t i = *c->HL + *c->DE;
    *c->F = i > 0xffff;
    *c->HL = (i & 0xffff);
}

static void DAD_H(CPU *c, uint8_t *mem) {
    uint32_t i = *c->HL + *c->HL;
    *c->F = i > 0xffff;
    *c->HL = (i & 0xffff);
}

static void DAD_SP(CPU *c, uint8_t *mem) {
    uint32_t i = *c->HL + *c->SP;
    *c->F = i > 0xffff;
    *c->HL = (i & 0xffff);
}

