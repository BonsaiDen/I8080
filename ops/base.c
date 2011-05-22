// Basic Instructions ---------------------------------------------------------
// ----------------------------------------------------------------------------
#include "../cpu/8080.h"


// Mo Operation
static void NOP(CPU_8080 *cpu) { }

// Halt
static void HLT(CPU_8080 *cpu) { 
    (*cpu->PC)--;
}

// Reset Flags
static void DAA(CPU_8080 *cpu) {
    (*cpu->F) = 0; // reset flags
}

// Not A
static void CMA(CPU_8080 *cpu) {
    *cpu->A = ~*cpu->A;
}

// Set carry
static void STC(CPU_8080 *cpu) {
    (*cpu->F) |= 1; // set carry
}

// Not carry
// TODO is this correct?
static void CMC(CPU_8080 *cpu) {
    (*cpu->F) ^= 1;
}

// Input / Output
static void IN(CPU_8080 *cpu) {
    // TODO read from stream
}

static void OUT(CPU_8080 *cpu) {
    // TODO write to stream
}

// Enable / Disable Interupts
static void EI(CPU_8080 *cpu) {
    cpu->ime = 1;
}

static void DI(CPU_8080 *cpu) {
    cpu->ime = 0;
}

