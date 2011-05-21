
#include "cpu.h"

extern uint8_t *MEMORY;
extern CPU_8080 *CPU;


// Transfer Instructions ------------------------------------------------------
// ----------------------------------------------------------------------------


// Read 16 REG ----------------------------------------------------------------
#define LXI(REG, RE) static void LXI_##REG() { \
    *CPU->RE = read16(*CPU->PC); \
}

LXI(B, BC);
LXI(D, DE);
LXI(H, HL);
LXI(SP, SP);


// Read / write HL ------------------------------------------------------------
static void LHLD() {
    *CPU->HL = read16(read16(*CPU->PC));
}

static void SHLD() {
    write16(read16(*CPU->PC), CPU->HL);
}


// Double ADD -----------------------------------------------------------------
static void DAD_B() {
    uint32_t i = *CPU->HL + *CPU->BC;
    *CPU->F = i > 0xffff;
    *CPU->HL = (i & 0xffff);
}

static void DAD_D() {
    uint32_t i = *CPU->HL + *CPU->DE;
    *CPU->F = i > 0xffff;
    *CPU->HL = (i & 0xffff);
}

static void DAD_H() {
    uint32_t i = *CPU->HL + *CPU->HL;
    *CPU->F = i > 0xffff;
    *CPU->HL = (i & 0xffff);
}

static void DAD_SP() {
    uint32_t i = *CPU->HL + *CPU->SP;
    *CPU->F = i > 0xffff;
    *CPU->HL = (i & 0xffff);
}


// Register Instructions ------------------------------------------------------
// ----------------------------------------------------------------------------


// Increment ------------------------------------------------------------------
#define INX(REG, RE) static void INX_##REG(uint8_t *mem) { \
    (*CPU->RE)++; \
}

INX(B, BC);
INX(D, DE);
INX(H, HL);
INX(SP, SP);


// Decrement ------------------------------------------------------------------
#define DCX(REG, RE) static void DCX_##REG(uint8_t *mem) { \
    (*CPU->RE)--; \
}

DCX(B, BC);
DCX(D, DE);
DCX(H, HL);
DCX(SP, SP);

