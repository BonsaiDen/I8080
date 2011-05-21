

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

typedef struct CPU {
    uint8_t A;

    uint8_t B;
    uint8_t C;

    uint8_t D;
    uint8_t E;

    uint8_t H;
    uint8_t L;

    uint16_t SP;
    uint16_t PC;

    uint16_t *BC;
    uint16_t *DE;
    uint16_t *HL;

} CPU;

enum CPU_INST {

    /* Unmapped */
    ERR = 0, 

    /* Others */
    NOP, HLT, XTHL, XCHG, DAA, CMA, CMC, STC, IN, OUT, 
    
    /* Intterupts */
    EI, DI,

    /* Load / Move */
    LXI, LDAX, MVI, LHLD, LDA,
    MOV, STAX, SHLD,

    /* Add */
    ADD, ADC, ADI, ACI, DAD,

    /* Subtract */
    SUB, SBB, SUI, SBI,
    
    /* And, Or, Xor */
    ANA, ANI,
    ORA, ORI,
    XRA, XRI,

    /* Inc / Dec */
    INX, INR,
    DCR, DCX, 

    /* Rotate */
    RRC, RAL, RAR, RLC,

    /* CALL */
    CNZ, CZ, CALL, CNC, CC, CPO, CPE, CP, CM,

    /* Returns */
    RNZ, RZ, RET, RNC, RC, RPO, RPE, RP, RM,

    /* Jumps */
    JNZ, JMP, JZ, JNC, JC, JPO, PCHL, JPE, JP, JM,

    /* Movel SP */
    SPML,

    /* Compare */
    CMP, CPI,

    /* Stack */
    POP, PUSH, 

    /* Reset */
    RST

};


uint8_t CPU_SET[256] = {
/*          0    1     2     3    4     5    6    7    8    9     A     B    C     D    E    F */
/* 0 */   NOP, LXI, STAX,  INX, INR,  DCR, MVI, RLC,   0, DAD, LDAX,  DCX, INR,  DCR, MVI, RRC,
/* 1 */     0, LXI, STAX,  INX, INR,  DCR, MVI, RAL,   0, DAD, LDAX,  DCX, INR,  DCR, MVI, RAR,
/* 2 */     0, LXI, SHLD,  INX, INR,  DCR, MVI, DAA,   0, DAD, LHLD,  DCX, INR,  DCR, MVI, CMA,
/* 3 */     0, LXI,    0,  INX, INR,  DCR, MVI, STC,   0, DAD,  LDA,  DCX, INR,  DCR, MVI, CMC,
/* 4 */     0,   0,    0,    0,   0,    0,   0,   0,   0,   0,    0,    0,   0,    0,   0,   0, 
/* 5 */     0,   0,    0,    0,   0,    0,   0,   0,   0,   0,    0,    0,   0,    0,   0,   0, 
/* 6 */     0,   0,    0,    0,   0,    0,   0,   0,   0,   0,    0,    0,   0,    0,   0,   0, 
/* 7 */   MOV, MOV,  MOV,  MOV, MOV,  MOV, HLT, MOV,   0,   0,    0,    0,   0,    0,   0,   0,                                                                                         
/* 8 */   ADD, ADD,  ADD,  ADD, ADD,  ADD, ADD, ADD, ADC, ADC,  ADC,  ADC, ADC,  ADC, ADC, ADC,  
/* 9 */   SUB, SUB,  SUB,  SUB, SUB,  SUB, SUB, SUB, SBB, SBB,  SBB,  SBB, SBB,  SBB, SBB, SBB,  
/* A */   ANA, ANA,  ANA,  ANA, ANA,  ANA, ANA, ANA, XRA, XRA,  XRA,  XRA, XRA,  XRA, XRA, XRA,  
/* B */   ORA, ORA,  ORA,  ORA, ORA,  ORA, ORA, ORA, CMP, CMP,  CMP,  CMP, CMP,  CMP, CMP, CMP,  
/* C */   RNZ, POP,  JNZ,  JMP, CNZ, PUSH, ADI, RST,  RZ, RET,   JZ,    0,  CZ, CALL, ACI, RST,                                                                                              
/* D */   RNC, POP,  JNC,  OUT, CNC, PUSH, SUI, RST,  RC,   0,   JC,   IN, CC,     0, SBI, RST,      
/* E */   RPO, POP,  JPO, XTHL, CPO, PUSH, ANI, RST, RPE, PCHL, JPE, XCHG, CPE,    0, XRI, RST,
/* F */    RP, POP,  JP,    DI,  CP, PUSH, ORI, RST,  RM, SPML,  JM,   EI,  CM,    0, CPI, RST

};


/* Constructor -------------------------------------------------------------- */
CPU *cpu() {

    CPU *cpu = calloc(sizeof(CPU), 1);

    cpu->BC = (uint16_t*)&cpu->B;
    cpu->DE = (uint16_t*)&cpu->D;
    cpu->HL = (uint16_t*)&cpu->H;
    
    return cpu;

}

static void dump(CPU *cpu) {

    printf("Registers:\n");
    printf("  A:   %2x    B:   %2x    D:   %2x     H:   %2x\n", cpu->A,   cpu->B,   cpu->D,   cpu->H);
    printf(" SP: %4x    C:   %2x    E:   %2x     L:   %2x\n", cpu->SP,  cpu->C,   cpu->E,   cpu->L);
    printf(" PC: %4x   BC: %4x   DE: %4x    HL: %4x\n", cpu->PC, *cpu->BC, *cpu->DE, *cpu->HL);

}

static void pop(CPU *cpu, uint8_t op, uint8_t reg) {
    
    
}

static void push(CPU *cpu, uint8_t op, uint8_t reg) {
    
    
}


static void run(CPU *cpu, uint8_t *code) {
    
    uint8_t op = 1;
    
    
    while(1) {
        op = code[cpu->SP++];

        switch(op) {
        case POP:
            pop(cpu, op, code[cpu->SP++]);
            break;

        case PUSH:
            push(cpu, op, code[cpu->SP++]);
            break;
        }

        
    }

}



int main(int argc, const char *argv[]) {
    
    CPU *main = cpu();
    main->B = 255;
    main->C = 255;

    dump(main);
    return 0;
}

