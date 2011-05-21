
#include "cpu.h"

extern uint8_t *MEMORY;
extern CPU_8080 *CPU;


// Transfer Instructions ------------------------------------------------------
// ----------------------------------------------------------------------------


// Load into A ----------------------------------------------------------------
static void LDA() {
    *CPU->A = read8(read16(*CPU->PC)); // load from mem
}

static void LDAX_B() {
    *CPU->A = *CPU->BC;
}

static void LDAX_D() {
    *CPU->A = *CPU->DE;
}


// Store into A ---------------------------------------------------------------
static void STA() {
    write8(read16(*CPU->PC), CPU->A); // store to mem
}

static void STAX_B() {
    *CPU->BC = *CPU->A;
}

static void STAX_D() {
    *CPU->DE = *CPU->A;
}

// Move register 8 ------------------------------------------------------------
#define MOV(TO, FROM) static void MOV_##TO##_##FROM() { \
    *CPU->TO = *(CPU->FROM); \
}

// todo check for overflow?
#define MOV_M(TO) static void MOV_##TO##_M() { \
    *CPU->TO = *(CPU->HL); \
}

#define MOV_HL(FROM) static void MOV_M_##FROM() { \
    *CPU->HL = *(CPU->FROM); \
}

MOV(A, A); MOV(A, B); MOV(A, C); MOV(A, D); MOV(A, E); MOV(A, H); MOV(A, L); MOV_M(A);

MOV(B, A); MOV(B, B); MOV(B, C); MOV(B, D); MOV(B, E); MOV(B, H); MOV(B, L); MOV_M(B);
MOV(C, A); MOV(C, B); MOV(C, C); MOV(C, D); MOV(C, E); MOV(C, H); MOV(C, L); MOV_M(C);
MOV(D, A); MOV(D, B); MOV(D, C); MOV(D, D); MOV(D, E); MOV(D, H); MOV(D, L); MOV_M(D);
MOV(E, A); MOV(E, B); MOV(E, C); MOV(E, D); MOV(E, E); MOV(E, H); MOV(E, L); MOV_M(E);

MOV(H, A); MOV(H, B); MOV(H, C); MOV(H, D); MOV(H, E); MOV(H, H); MOV(H, L); MOV_M(H);
MOV(L, A); MOV(L, B); MOV(L, C); MOV(L, D); MOV(L, E); MOV(L, H); MOV(L, L); MOV_M(L);

MOV_HL(A); MOV_HL(B); MOV_HL(C); MOV_HL(D); MOV_HL(E); MOV_HL(H); MOV_HL(L);


// Move immediate 8 REG -------------------------------------------------------
#define MVI(TO) static void MVI_##TO() { \
    *CPU->TO = read8(*CPU->PC); \
}

MVI(A); MVI(B); MVI(C); MVI(D);
MVI(E); MVI(H); MVI(L);

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

static void INR_M() {
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

