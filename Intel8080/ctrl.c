// Basic Instructions ---------------------------------------------------------
// ----------------------------------------------------------------------------
#include "cpu.h"
#include "flags.h"


// Move HL to PC
static void PCHL(Intel8080 *cpu) {
    *cpu->PC = *cpu->HL;
}

// Jump helper
static inline void jmp(Intel8080 *cpu) {

    // PC is + 1 already,
    // so 2 will be added after this instruction
    // since the instruction has 3 bytes (inst/word)
    // therefore we need to substract here
    *cpu->PC = (cpu->read_mem(*cpu->PC) | (cpu->read_mem((*cpu->PC) + 1) << 8)) - 2; 

}

// Call helper
static inline void call(Intel8080 *cpu) {

    // Push PC onto stack
    cpu->write_mem((*cpu->SP) - 1, (*cpu->PC + 2) >> 8); // high byte
    cpu->write_mem((*cpu->SP) - 2, (*cpu->PC + 2) & 0xff); // low byte
    *cpu->SP -= 2;
    jmp(cpu);

}

// Return helper
static inline void ret(Intel8080 *cpu) {
    *cpu->PC = cpu->read_mem((*cpu->SP)) | (cpu->read_mem((*cpu->SP) + 1) << 8);
    *cpu->SP += 2;
}

// Control Macro
#define CONTROL(PREFIX, DIRECT, METHOD, CYCLES) \
    static void DIRECT(Intel8080 *cpu) {\
        METHOD(cpu);\
    }\
    static void PREFIX##NZ(Intel8080 *cpu) {\
        if (!(*cpu->F & 64)) {\
            METHOD(cpu); cpu->cycle_count += CYCLES;\
        }\
    }\
    static void PREFIX##Z(Intel8080 *cpu) {\
        if (*cpu->F & 64) {\
            METHOD(cpu); cpu->cycle_count += CYCLES;\
        }\
    }\
    static void PREFIX##NC(Intel8080 *cpu) {\
        if (!(*cpu->F & 1)) {\
            METHOD(cpu); cpu->cycle_count += CYCLES;\
        }\
    }\
    static void PREFIX##C(Intel8080 *cpu) {\
        if (*cpu->F & 1) {\
            METHOD(cpu); cpu->cycle_count += CYCLES;\
        }\
    }\
    static void PREFIX##PO(Intel8080 *cpu) {\
        if (!(*cpu->F & 4)) {\
            METHOD(cpu); cpu->cycle_count += CYCLES;\
        }\
    }\
    static void PREFIX##PE(Intel8080 *cpu) {\
        if (*cpu->F & 4) {\
            METHOD(cpu); cpu->cycle_count += CYCLES;\
        }\
    }\
    static void PREFIX##P(Intel8080 *cpu) {\
        if (!(*cpu->F & 128)) {\
            METHOD(cpu); cpu->cycle_count += CYCLES;\
        }\
    }\
    static void PREFIX##M(Intel8080 *cpu) {\
        if (*cpu->F & 128) {\
            METHOD(cpu); cpu->cycle_count += CYCLES;\
        }\
    }\

// Define a ton of stuff...
CONTROL(C, CALL, call, 6)
CONTROL(R, RET, ret, 6)
CONTROL(J, JMP, jmp, 0)


// Restart, jump to a fixed address where special stuff may reside
#define RST(ID) static void RST_##ID(Intel8080 *cpu) { \
    cpu->write_mem((*cpu->SP) - 1, (*cpu->PC) >> 8); \
    cpu->write_mem((*cpu->SP) - 2, (*cpu->PC) & 0xff); \
    *cpu->SP -= 2; \
    *cpu->PC = 8 * ID; \
}

RST(0) RST(1) RST(2) RST(3) RST(4) RST(5) RST(6) RST(7)

