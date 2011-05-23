// Other Register Instructions ------------------------------------------------
// ----------------------------------------------------------------------------
#include "cpu.h"
#include "flags.h"


// Increment REG
#define INR(REG) static void INR_##REG(Intel8080 *cpu) { \
    (*cpu->REG)++; \
    cpu_flag_szap(cpu, cpu->REG); \
}

INR(A) INR(B) INR(C) INR(D) INR(E) INR(H) INR(L)

// Increment contents of (HL)
static void INR_M(Intel8080 *cpu) {
    uint8_t i = cpu->read_mem(*cpu->HL) + 1;
    cpu->write_mem(*cpu->HL, i);
    cpu_flag_szap(cpu, &i);
}


// Decrement REG
#define DCR(REG) static void DCR_##REG(Intel8080 *cpu) { \
    (*cpu->REG)--; \
    cpu_flag_szp(cpu, cpu->REG); \
}
DCR(A) DCR(B) DCR(C) DCR(D) DCR(E) DCR(H) DCR(L)

// Decrement contents of (HL)
static void DCR_M(Intel8080 *cpu) {
    uint8_t i = cpu->read_mem(*cpu->HL) - 1;
    cpu->write_mem(*cpu->HL, i);
    cpu_flag_szap(cpu, &i);
}


// Increment register pair REG
#define INX(NAME, REG) static void INX_##NAME(Intel8080 *cpu) { \
    (*cpu->REG)++; \
}
INX(B, BC) INX(D, DE) INX(H, HL) INX(SP, SP)


// Decrement register pair REG
#define DCX(NAME, REG) static void DCX_##NAME(Intel8080 *cpu) { \
    (*cpu->REG)--; \
}
DCX(B, BC) DCX(D, DE) DCX(H, HL) DCX(SP, SP)

