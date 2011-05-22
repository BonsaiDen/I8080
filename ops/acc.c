// Other Accumulator Instructions ---------------------------------------------
// ----------------------------------------------------------------------------
#include "../cpu.h"
extern CPU_8080 *CPU;


// Load BYTE (WORD) into A
static void LDA() {
    *CPU->A = read8(read16(*CPU->PC));
}

// Read BYTE (BC) into A
static void LDAX_B() {
    *CPU->A = read8(*CPU->BC);
}

// Read BYTE (DE) into A
static void LDAX_D() {
    *CPU->A = read(*CPU->DE);
}


// Store A to (WORD)
static void STA() {
    write8(read16(*CPU->PC), CPU->A);
}

// Store A to (BC)
static void STAX_B() {
    write8(*CPU->BC, CPU->A);
}

// Store A to (DE)
static void STAX_D() {
    write8(*CPU->DE, CPU->A);
}

