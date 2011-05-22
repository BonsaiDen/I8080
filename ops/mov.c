// Transfer Instructions ------------------------------------------------------
// ----------------------------------------------------------------------------
#include "../cpu/8080.h"


// Move FROM to TO
#define MOV(TO, FROM) static void MOV_##TO##_##FROM(CPU_8080 *cpu) { \
    *cpu->TO = *cpu->FROM; \
}

// Move BYTE (HL) to TO
#define MOV_M_R(TO) static void MOV_##TO##_M(CPU_8080 *cpu) { \
    *cpu->TO = mmu_read(*cpu->HL); \
}

MOV(A, A); MOV(A, B); MOV(A, C); MOV(A, D); MOV(A, E); MOV(A, H); MOV(A, L); 
MOV_M_R(A);

MOV(B, A); MOV(B, B); MOV(B, C); MOV(B, D); MOV(B, E); MOV(B, H); MOV(B, L); 
MOV_M_R(B);

MOV(C, A); MOV(C, B); MOV(C, C); MOV(C, D); MOV(C, E); MOV(C, H); MOV(C, L); 
MOV_M_R(C);

MOV(D, A); MOV(D, B); MOV(D, C); MOV(D, D); MOV(D, E); MOV(D, H); MOV(D, L); 
MOV_M_R(D);

MOV(E, A); MOV(E, B); MOV(E, C); MOV(E, D); MOV(E, E); MOV(E, H); MOV(E, L); 
MOV_M_R(E);

MOV(H, A); MOV(H, B); MOV(H, C); MOV(H, D); MOV(H, E); MOV(H, H); MOV(H, L); 
MOV_M_R(H);

MOV(L, A); MOV(L, B); MOV(L, C); MOV(L, D); MOV(L, E); MOV(L, H); MOV(L, L); 
MOV_M_R(L);

// Write FROM to (HL)
#define MOV_M(FROM) static void MOV_M_##FROM(CPU_8080 *cpu) { \
    mmu_write(*cpu->HL, *cpu->FROM); \
}
MOV_M(A); MOV_M(B); MOV_M(C); MOV_M(D); MOV_M(E); MOV_M(H); MOV_M(L);


// Move next BYTE to TO
#define MVI(TO) static void MVI_##TO(CPU_8080 *cpu) { \
    *cpu->TO = mmu_read(*cpu->PC); \
}
MVI(A); MVI(B); MVI(C); MVI(D); MVI(E); MVI(H); MVI(L);

// Move next BYTE to (HL)
static void MVI_M(CPU_8080 *cpu) {
    mmu_write(*cpu->HL, mmu_read(*cpu->PC));
}


// 16 BIT ---------------------------------------------------------------------
// ----------------------------------------------------------------------------

// Load (WORD) to HL
static void LHLD(CPU_8080 *cpu) {
    uint16_t addr = mmu_read(*cpu->PC) | (mmu_read((*cpu->PC) + 1) << 8);
    *cpu->HL = mmu_read(addr) | (mmu_read(addr + 1) << 8);
}

// Store HL to (WORD)
static void SHLD(CPU_8080 *cpu) {
    uint16_t addr = mmu_read(*cpu->PC) | (mmu_read((*cpu->PC) + 1) << 8);
    mmu_write(addr, (*cpu->HL) & 0xff);
    mmu_write(addr + 1, (*cpu->HL) >> 8);
}

// Move HL to SP
static void SPHL(CPU_8080 *cpu) {
    *cpu->SP = *cpu->HL;
}

// Load next WORD into REG
#define LXI(NAME, REG) static void LXI_##NAME(CPU_8080 *cpu) { \
    *cpu->REG = mmu_read(*cpu->PC) | (mmu_read((*cpu->PC) + 1) << 8); \
}
LXI(B, BC); LXI(D, DE); LXI(H, HL); LXI(SP, SP);

