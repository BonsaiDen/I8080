// Other Register Instructions ------------------------------------------------
// ----------------------------------------------------------------------------
#include "../cpu.h"
extern CPU_8080 *CPU;


// Increment REG
#define INR(REG) static void INR_##REG() { \
    (*CPU->REG)++; \
    cpu_flag_szap(CPU->REG); \
}

INR(A); INR(B); INR(C); INR(D); INR(E); INR(H); INR(L);

// Increment contents of (HL)
static void INR_M() {
    uint8_t i = read8(*CPU->HL) + 1;
    write8(*CPU->HL, &i);
    cpu_flag_szap(&i);
}


// Decrement REG
#define DCR(REG) static void DCR_##REG() { \
    (*CPU->REG)--; \
    cpu_flag_szp(CPU->REG); \
}
DCR(A); DCR(B); DCR(C); DCR(D); DCR(E); DCR(H); DCR(L);

// Decrement contents of (HL)
static void DCR_M() {
    uint8_t i = read8(*CPU->HL) - 1;
    write8(*CPU->HL, &i);
    cpu_flag_szap(&i);
}


// Increment register pair REG
#define INX(NAME, REG) static void INX_##NAME() { \
    (*CPU->REG)++; \
}
INX(B, BC); INX(D, DE); INX(H, HL); INX(SP, SP);


// Decrement register pair REG
#define DCX(NAME, REG) static void DCX_##NAME() { \
    (*CPU->REG)--; \
}
DCX(B, BC); DCX(D, DE); DCX(H, HL); DCX(SP, SP);

