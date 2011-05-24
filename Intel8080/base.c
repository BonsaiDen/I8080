// Basic Instructions ---------------------------------------------------------
// ----------------------------------------------------------------------------
#include "Cpu.h"
#include "flags.h"

// Mo Operation
static void OP_NOP(Intel8080 *cpu) { 
    *cpu->PC = *cpu->PC;
}

// Halt
static void OP_HLT(Intel8080 *cpu) { 
    cpu->halt = 1;
    (*cpu->PC)--;
}

// Reset Flags
static void OP_DAA(Intel8080 *cpu) {
    (*cpu->F) = 0; // reset flags
}

// Not A
static void OP_CMA(Intel8080 *cpu) {
    *cpu->A = ~*cpu->A;
}

// Set carry
static void OP_STC(Intel8080 *cpu) {
    (*cpu->F) |= 1; // set carry
}

// Not carry
// TODO is this correct?
static void OP_CMC(Intel8080 *cpu) {
    (*cpu->F) ^= 1;
}

// Input / Output
static void OP_IN(Intel8080 *cpu) {
    // TODO read from stream
}

static void OP_OUT(Intel8080 *cpu) {
    // TODO write to stream
}

// Enable / Disable Interupts
static void OP_EI(Intel8080 *cpu) {
    cpu->ime = 1;
}

static void OP_DI(Intel8080 *cpu) {
    cpu->ime = 0;
}

