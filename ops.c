
#include <stdio.h>
#include "cpu.h"

extern uint8_t *MEMORY;
extern CPU_8080 *CPU;

/* Others ------------------------------------------------------------------- */
static void NOP() { }

static void HLT() { 
    (*CPU->PC)--;
}

static void DAA(uint8_t *mem) {
    
}

static void STC(uint8_t *mem) {
    
}

static void CMC(uint8_t *mem) {
    
}
static void CMA(uint8_t *mem) {
    
}

static void RLC(uint8_t *mem) {
    // reg C left, check carry...
}

static void RRC(uint8_t *mem) {
    // reg C right
}

static void RAL(uint8_t *mem) {
    // reg A left
}

static void RAR(uint8_t *mem) {
    // reg A right
}

