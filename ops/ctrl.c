// Basic Instructions ---------------------------------------------------------
// ----------------------------------------------------------------------------
#include "../cpu.h"
extern CPU_8080 *CPU;

// Move HL to PC
static void PCHL() {
    *CPU->PC = *CPU->HL;
}

// Jump helper
static inline void jmp() {
    // PC is + 1 already,
    // so 2 will be added after this instruction
    // since the instruction has 3 bytes (inst/word)
    // therefore we need to substract here
    *CPU->PC = read16(*CPU->PC) - 2; 
}

// Call helper
static inline void call() {

    // Push PC onto stack
    write8((*CPU->SP) - 1, (*CPU->PC) >> 8); // high byte
    write8((*CPU->SP) - 2, (*CPU->PC) & 0xff); // low byte
    *CPU->SP -= 2;

    // Adjust cycle count to account for the memory operations
    CPU->cycles += 6;

    jmp();

}

// Return helper
static inline void ret() {

    *CPU->PC = read8((*CPU->SP)) | (read8((*CPU->SP) + 1) << 8);
    *CPU->SP += 2;

    // Adjust cycle count to account for the memory operations
    CPU->cycles += 6;

}

// Control Macro
#define CONTROL(PREFIX, DIRECT, METHOD) \
    static void ##DIRECT() {\
        METHOD();\
    }\
    static void ##PREFIX##NZ() {\
        if (!(*CPU->F & 64)) METHOD();\
    }\
    static void ##PREFIX##Z() {\
        if (*CPU->F & 64) METHOD();\
    }\
    static void ##PREFIX##NC() {\
        if (!(*CPU->F & 1)) METHOD();\
    }\
    static void ##PREFIX##C() {\
        if (*CPU->F & 1) METHOD();\
    }\
    static void ##PREFIX##PO() {\
        if (!(*CPU->F & 4)) METHOD();\
    }\
    static void ##PREFIX##PE() {\
        if (*CPU->F & 4) METHOD();\
    }\
    static void ##PREFIX##P() {\
        if (!(*CPU->F & 128)) METHOD();\
    }\
    static void ##PREFIX##M() {\
        if (*CPU->F & 128) METHOD();\
    }\

// Define a ton of stuff...
CONTROL(C, CALL, call);
CONTROL(R, RET, ret);
CONTROL(J, JMP, jmp);


// Reset, jump to a fixed address where special stuff may reside
#define RST(ID) static void RST_##ID() { \
    write8((*CPU->SP) - 1, (*CPU->PC) >> 8); \
    write8((*CPU->SP) - 2, (*CPU->PC) & 0xff); \
    *CPU->SP -= 2; \
    *CPU->PC = 8 * ID; \
}

RST(0); RST(1); RST(2); RST(3); RST(4); RST(5); RST(6); RST(7);

