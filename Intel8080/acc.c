// Other Accumulator Instructions ---------------------------------------------
// ----------------------------------------------------------------------------
#include "Cpu.h"
#include "flags.h"


// Load BYTE (WORD) into A
static void OP_LDA(Intel8080 *cpu) {
    uint16_t addr = cpu->read_mem(*cpu->PC) | (cpu->read_mem((*cpu->PC) + 1) << 8);
    *cpu->A = cpu->read_mem(addr);
}

// Read BYTE (BC) into A
static void OP_LDAX_B(Intel8080 *cpu) {
    *cpu->A = cpu->read_mem(*cpu->BC);
}

// Read BYTE (DE) into A
static void OP_LDAX_D(Intel8080 *cpu) {
    *cpu->A = cpu->read_mem(*cpu->DE);
}


// Store A to (WORD)
static void OP_STA(Intel8080 *cpu) {
    uint16_t addr = cpu->read_mem(*cpu->PC) | (cpu->read_mem((*cpu->PC) + 1) << 8);
    cpu->write_mem(addr, *cpu->A);
}

// Store A to (BC)
static void OP_STAX_B(Intel8080 *cpu) {
    cpu->write_mem(*cpu->BC, *cpu->A);
}

// Store A to (DE)
static void OP_STAX_D(Intel8080 *cpu) {
    cpu->write_mem(*cpu->DE, *cpu->A);
}

