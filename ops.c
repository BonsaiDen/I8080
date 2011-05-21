
#include <stdio.h>
#include "cpu.h"

extern uint8_t *MEMORY;
extern CPU_8080 *CPU;

/* Others ------------------------------------------------------------------- */
static void NOP() { }

static void HLT() { 
    (*CPU->PC)--;
}


// Special Accumulator and Flags Instructions ---------------------------------
// ----------------------------------------------------------------------------

static void DAA() {
    (*CPU->F) = 0; // reset flags
}

static void CMA() {
    *CPU->A = ~*CPU->A; // not A
}

static void STC() {
    (*CPU->F) |= 1; // set carry
}

static void CMC() {
    (*CPU->F) ^= 1; // not carry TODO is this correct?
}


// Rotate Operations ----------------------------------------------------------
// ----------------------------------------------------------------------------

static void RLC() {
    // reg C left, check carry...
}

static void RRC() {
    // reg C right
}

static void RAL() {
    // reg A left
}

static void RAR() {
    // reg A right
}

