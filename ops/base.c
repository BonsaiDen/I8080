// Basic Instructions ---------------------------------------------------------
// ----------------------------------------------------------------------------
#include "../cpu/8080.h"


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
    // TODO read from stream
}

static void OUT() {
    // TODO write to stream
}

// Enable / Disable Interupts
static void EI() {
    CPU->ime = 1;
}

static void DI() {
    CPU->ime = 0;
}

