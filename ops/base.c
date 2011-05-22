// Basic Instructions ---------------------------------------------------------
// ----------------------------------------------------------------------------
#include "../cpu.h"
extern CPU_8080 *CPU;


// Mo Operation
static void NOP() { }

// Halt
static void HLT() { 
    (*CPU->PC)--;
}

// Reset Flags
static void DAA() {
    (*CPU->F) = 0; // reset flags
}

// Not A
static void CMA() {
    *CPU->A = ~*CPU->A;
}

// Set carry
static void STC() {
    (*CPU->F) |= 1; // set carry
}

// Not carry
// TODO is this correct?
static void CMC() {
    (*CPU->F) ^= 1;
}

// Input / Output
static void IN() {
}

static void OUT() {
}

// Enable / Disable Interupts
static void EI() {
}

static void DI() {
}

