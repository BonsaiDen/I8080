// Basic Instructions ---------------------------------------------------------
// ----------------------------------------------------------------------------
#include "../cpu/8080.h"


// Move HL to PC
static void PCHL(CPU_8080 *cpu) {
    *cpu->PC = *cpu->HL;
}

// Jump helper
static inline void jmp(CPU_8080 *cpu) {

    // PC is + 1 already,
    // so 2 will be added after this instruction
    // since the instruction has 3 bytes (inst/word)
    // therefore we need to substract here
    *cpu->PC = (mmu_read(*cpu->PC) | (mmu_read((*cpu->PC) + 1) << 8)) - 2; 

}

// Call helper
static inline void call(CPU_8080 *cpu) {

    // Push PC onto stack
    mmu_write((*cpu->SP) - 1, (*cpu->PC + 2) >> 8); // high byte
    mmu_write((*cpu->SP) - 2, (*cpu->PC + 2) & 0xff); // low byte
    *cpu->SP -= 2;
    jmp(cpu);

}

// Return helper
static inline void ret(CPU_8080 *cpu) {
    *cpu->PC = mmu_read((*cpu->SP)) | (mmu_read((*cpu->SP) + 1) << 8);
    *cpu->SP += 2;
}

// Control Macro
#define CONTROL(PREFIX, DIRECT, METHOD, CYCLES) \
    static void DIRECT(CPU_8080 *cpu) {\
        METHOD(cpu);\
    }\
    static void PREFIX##NZ(CPU_8080 *cpu) {\
        if (!(*cpu->F & 64)) {\
            METHOD(cpu); cpu->cycle_count += CYCLES;\
        }\
    }\
    static void PREFIX##Z(CPU_8080 *cpu) {\
        if (*cpu->F & 64) {\
            METHOD(cpu); cpu->cycle_count += CYCLES;\
        }\
    }\
    static void PREFIX##NC(CPU_8080 *cpu) {\
        if (!(*cpu->F & 1)) {\
            METHOD(cpu); cpu->cycle_count += CYCLES;\
        }\
    }\
    static void PREFIX##C(CPU_8080 *cpu) {\
        if (*cpu->F & 1) {\
            METHOD(cpu); cpu->cycle_count += CYCLES;\
        }\
    }\
    static void PREFIX##PO(CPU_8080 *cpu) {\
        if (!(*cpu->F & 4)) {\
            METHOD(cpu); cpu->cycle_count += CYCLES;\
        }\
    }\
    static void PREFIX##PE(CPU_8080 *cpu) {\
        if (*cpu->F & 4) {\
            METHOD(cpu); cpu->cycle_count += CYCLES;\
        }\
    }\
    static void PREFIX##P(CPU_8080 *cpu) {\
        if (!(*cpu->F & 128)) {\
            METHOD(cpu); cpu->cycle_count += CYCLES;\
        }\
    }\
    static void PREFIX##M(CPU_8080 *cpu) {\
        if (*cpu->F & 128) {\
            METHOD(cpu); cpu->cycle_count += CYCLES;\
        }\
    }\

// Define a ton of stuff...
CONTROL(C, CALL, call, 6);
CONTROL(R, RET, ret, 6);
CONTROL(J, JMP, jmp, 0);


// Restart, jump to a fixed address where special stuff may reside
#define RST(ID) static void RST_##ID(CPU_8080 *cpu) { \
    mmu_write((*cpu->SP) - 1, (*cpu->PC) >> 8); \
    mmu_write((*cpu->SP) - 2, (*cpu->PC) & 0xff); \
    *cpu->SP -= 2; \
    *cpu->PC = 8 * ID; \
}

RST(0); RST(1); RST(2); RST(3); RST(4); RST(5); RST(6); RST(7);

