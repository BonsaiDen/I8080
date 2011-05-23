// Basic Instructions ---------------------------------------------------------
// ----------------------------------------------------------------------------
#include "cpu.h"
#include "flags.h"

// Mo Operation
static void NOP(Intel8080 *cpu) { 
    *cpu->PC = *cpu->PC;
}

// Halt
static void HLT(Intel8080 *cpu) { 
    (*cpu->PC)--;
}

// Reset Flags
static void DAA(Intel8080 *cpu) {
    (*cpu->F) = 0; // reset flags
}

// Not A
static void CMA(Intel8080 *cpu) {
    *cpu->A = ~*cpu->A;
}

// Set carry
static void STC(Intel8080 *cpu) {
    (*cpu->F) |= 1; // set carry
}

// Not carry
// TODO is this correct?
static void CMC(Intel8080 *cpu) {
    (*cpu->F) ^= 1;
}

// Input / Output
static void IN(Intel8080 *cpu) {
    // TODO read from stream
}

static void OUT(Intel8080 *cpu) {
    // TODO write to stream
}

// Enable / Disable Interupts
static void EI(Intel8080 *cpu) {
    cpu->ime = 1;
}

static void DI(Intel8080 *cpu) {
    cpu->ime = 0;
}

