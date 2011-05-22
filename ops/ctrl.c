// Basic Instructions ---------------------------------------------------------
// ----------------------------------------------------------------------------
#include "../cpu/8080.h"


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
    *CPU->PC = (mmu_read(*CPU->PC) | (mmu_read((*CPU->PC) + 1) << 8)) - 2; 

}

// Call helper
static inline void call() {

    // Push PC onto stack
    mmu_write((*CPU->SP) - 1, (*CPU->PC + 2) >> 8); // high byte
    mmu_write((*CPU->SP) - 2, (*CPU->PC + 2) & 0xff); // low byte
    *CPU->SP -= 2;
    jmp();

}

// Return helper
static inline void ret() {
    *CPU->PC = mmu_read((*CPU->SP)) | (mmu_read((*CPU->SP) + 1) << 8);
    *CPU->SP += 2;
}

// Control Macro
#define CONTROL(PREFIX, DIRECT, METHOD, CYCLES) \
    static void DIRECT() {\
        METHOD();\
    }\
    static void PREFIX##NZ() {\
        if (!(*CPU->F & 64)) {\
            METHOD(); CPU->cycle_count += CYCLES;\
        }\
    }\
    static void PREFIX##Z() {\
        if (*CPU->F & 64) {\
            METHOD(); CPU->cycle_count += CYCLES;\
        }\
    }\
    static void PREFIX##NC() {\
        if (!(*CPU->F & 1)) {\
            METHOD(); CPU->cycle_count += CYCLES;\
        }\
    }\
    static void PREFIX##C() {\
        if (*CPU->F & 1) {\
            METHOD(); CPU->cycle_count += CYCLES;\
        }\
    }\
    static void PREFIX##PO() {\
        if (!(*CPU->F & 4)) {\
            METHOD(); CPU->cycle_count += CYCLES;\
        }\
    }\
    static void PREFIX##PE() {\
        if (*CPU->F & 4) {\
            METHOD(); CPU->cycle_count += CYCLES;\
        }\
    }\
    static void PREFIX##P() {\
        if (!(*CPU->F & 128)) {\
            METHOD(); CPU->cycle_count += CYCLES;\
        }\
    }\
    static void PREFIX##M() {\
        if (*CPU->F & 128) {\
            METHOD(); CPU->cycle_count += CYCLES;\
        }\
    }\

// Define a ton of stuff...
CONTROL(C, CALL, call, 6);
CONTROL(R, RET, ret, 6);
CONTROL(J, JMP, jmp, 0);


// Restart, jump to a fixed address where special stuff may reside
#define RST(ID) static void RST_##ID() { \
    mmu_write((*CPU->SP) - 1, (*CPU->PC) >> 8); \
    mmu_write((*CPU->SP) - 2, (*CPU->PC) & 0xff); \
    *CPU->SP -= 2; \
    *CPU->PC = 8 * ID; \
}

RST(0); RST(1); RST(2); RST(3); RST(4); RST(5); RST(6); RST(7);

