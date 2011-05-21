
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

    // rotate left ignoring F carry
    uint8_t carry = (*CPU->A) & 128 ? 1 : 0; // check msb of A
    *CPU->A = ((*CPU->A) << 1) + carry;
    *CPU->F = ((*CPU->F) & ~1) | carry; // set new carry

}

static void RAL() {

    // rotate A left dropping MSB in favor fo F carry
    uint8_t carry_in   = (*CPU->F) &   1 ? 1 : 0; // check carry flag
    uint8_t carry_out  = (*CPU->A) & 128 ? 1 : 0; // check msb of A

    *CPU->A = ((*CPU->A) << 1) + carry_in;
    *CPU->F = ((*CPU->F) & ~1) | carry_out; // set new carry

}

static void RRC() {

    // rotate A right ignoring F carry
    uint8_t carry_in   = (*CPU->A) & 1 ? 128 : 0; // check for msb of A
    uint8_t carry_out  = (*CPU->A) & 1 ?   1 : 0; // check for lsb of A

    *CPU->A = ((*CPU->A) >> 1) + carry_in;
    *CPU->F = ((*CPU->F) & ~1) | carry_out; // set new carry

}

static void RAR() {

    // rotate A left dropping LSB in favor fo F carry
    uint8_t carry_in   = (*CPU->F) & 1 ? 128 : 0; // check for carry flag
    uint8_t carry_out  = (*CPU->A) & 1 ?   1 : 0; // check for lsb of A

    *CPU->A = ((*CPU->A) >> 1) + carry_in;
    *CPU->F = ((*CPU->F) & ~1) | carry_out; // set new carry

}

