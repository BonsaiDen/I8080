
#include "cpu.h"

extern uint8_t *MEMORY;
extern CPU_8080 *CPU;


// Transfer Instructions ------------------------------------------------------
// ----------------------------------------------------------------------------


// Load into A ----------------------------------------------------------------
static void LDA() {
    // TODO impelement
}

static void LDAX_B() {
    *CPU->A = *CPU->BC;
}

static void LDAX_D() {
    *CPU->A = *CPU->DE;
}


// Store into A ---------------------------------------------------------------
static void STA(uint8_t *mem) {
    // TODO impelement
}

static void STAX_B(uint8_t *mem) {
    *CPU->BC = *CPU->A;
}

static void STAX_D(uint8_t *mem) {
    *CPU->DE = *CPU->A;
}


// Move 8 REG -----------------------------------------------------------------
#define MVI_8(REG) static void MVI_##REG() { \
    *CPU->REG = read8(*CPU->PC); \
}

MVI_8(A); MVI_8(B); MVI_8(C); MVI_8(D);
MVI_8(E); MVI_8(H); MVI_8(L);

static void MVI_M() {
    *CPU->HL = read8(*CPU->PC);
}


// Register Instructions ------------------------------------------------------
// ----------------------------------------------------------------------------

// Increment ------------------------------------------------------------------
#define INR(REG) static void INR_##REG() { \
    (*CPU->REG)++; \
    cpu_flag_szap_inc((uint16_t*)CPU->REG); \
}

INR(A);
INR(B);
INR(C);
INR(D);
INR(E);
INR(H);
INR(L);

static void INR_M(uint8_t *mem) {
    (*CPU->HL)++;
    cpu_flag_szap_inc(CPU->HL);
}


// Decrement ------------------------------------------------------------------
#define DCR(REG) static void DCR_##REG() { \
    (*CPU->REG)--; \
    cpu_flag_szap_dec((uint16_t*)CPU->REG); \
}

DCR(A);
DCR(B);
DCR(C);
DCR(D);
DCR(E);
DCR(H);
DCR(L);

static void DCR_M() {
    (*CPU->HL)--;
    cpu_flag_szap_dec(CPU->HL);
}

