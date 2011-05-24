// Intel 8080 OP Code Table ----------------------------------------------------
// -----------------------------------------------------------------------------
#include "Codes.h"

#include "base.c"
#include "acc.c"
#include "bit.c"
#include "math.c"
#include "mov.c"
#include "reg.c"
#include "stack.c"
#include "ctrl.c"


// Wrapper for instructions
#define INST(SIZE, CYCLES, OP) case OP:  \
    OP_##OP(cpu); \
    size = SIZE; \
    cycles = CYCLES; \
    break; \

// Handle remaps
#define REMAP(SIZE, CYCLES, OP, OOP) case OP:  \
    OP_##OOP(cpu); \
    size = SIZE; \
    cycles = CYCLES; \
    break; \


// Here be dragons...
// Switch statement is really the fastest thing
void op_code_table(Intel8080 *cpu, uint8_t inst) {
    
    uint8_t size = 1, cycles = 0;
    switch(inst) {

        INST(1,   4, NOP)
        INST(3,  10, LXI_B)
        INST(1,   7, STAX_B)
        INST(1,   5, INX_B)

        INST(1,   5, INR_B)
        INST(1,   5, DCR_B)
        INST(2,   7, MVI_B)
        INST(1,   4, RLC)

        // x8 - xF
        REMAP(1,   4, NOP_8, NOP)
        INST(1,  10, DAD_B)
        INST(1,   7, LDAX_B)
        INST(1,   5, DCX_B)
        
        INST(1,   5, INR_C)
        INST(1,   5, DCR_C)
        INST(2,   7, MVI_C)
        INST(1,   4, RRC)

        // 10 - 17
        REMAP(1,   4, NOP_10, NOP)
        INST(3,  10, LXI_D)
        INST(1,   7, STAX_D)
        INST(1,   5, INX_D)

        INST(1,   5, INR_D)
        INST(1,   5, DCR_D)
        INST(2,   7, MVI_D)
        INST(1,   4, RAL)

        // 18 - 1F
        REMAP(1,   4, NOP_18, NOP)
        INST(1,  10, DAD_D)
        INST(1,   7, LDAX_D)
        INST(1,   5, DCX_D)
                     
        INST(1,   5, INR_E)
        INST(1,   5, DCR_E)
        INST(2,   7, MVI_E)
        INST(1,   4, RAR)

        // 20 - 27
        REMAP(1,   4, NOP_20, NOP)
        INST(3,  10, LXI_H)
        INST(3,  16, SHLD)
        INST(1,   5, INX_H)
             
        INST(1,   5, INR_H)
        INST(1,   5, DCR_H)
        INST(2,   7, MVI_H)
        INST(1,   4, DAA)

        // 28 - 2f
        REMAP(1,   4, NOP_28, NOP)
        INST(1,  10, DAD_H)
        INST(3,  16, LHLD)
        INST(1,   5, DCX_H)

        INST(1,   5, INR_L)
        INST(1,   5, DCR_L)
        INST(2,   7, MVI_L)
        INST(1,   4, CMA)

        // 30 - 37
        REMAP(1,   4, NOP_30, NOP)
        INST(3,  10, LXI_SP)
        INST(3,  13, STA)
        INST(1,   5, INX_SP)

        INST(1,  10, INR_M)
        INST(1,  10, DCR_M)
        INST(2,  10, MVI_M)
        INST(1,   4, STC)

        // 38 - 3f
        REMAP(1,   4, NOP_38, NOP)
        INST(1,  10, DAD_SP)
        INST(3,  13, LDA)
        INST(1,   5, DCX_SP)

        INST(1,   5, INR_A)
        INST(1,   5, DCR_A)
        INST(2,   7, MVI_A)
        INST(1,   4, CMC)
        
        // 40 - 47
        INST(1,   5, MOV_B_B)
        INST(1,   5, MOV_B_C)
        INST(1,   5, MOV_B_D)
        INST(1,   5, MOV_B_E)

        INST(1,   5, MOV_B_H)
        INST(1,   5, MOV_B_L)
        INST(1,   7, MOV_B_M)
        INST(1,   5, MOV_B_A)

        // 48 - 4f
        INST(1,   5, MOV_C_B)
        INST(1,   5, MOV_C_C)
        INST(1,   5, MOV_C_D)
        INST(1,   5, MOV_C_E)

        INST(1,   5, MOV_C_H)
        INST(1,   5, MOV_C_L)
        INST(1,   7, MOV_C_M)
        INST(1,   5, MOV_C_A)

        // 50 - 57
        INST(1,   5, MOV_D_B)
        INST(1,   5, MOV_D_C)
        INST(1,   5, MOV_D_D)
        INST(1,   5, MOV_D_E)

        INST(1,   5, MOV_D_H)
        INST(1,   5, MOV_D_L)
        INST(1,   7, MOV_D_M)
        INST(1,   5, MOV_D_A)

        // 58 - 5f
        INST(1,   5, MOV_E_B)
        INST(1,   5, MOV_E_C)
        INST(1,   5, MOV_E_D)
        INST(1,   5, MOV_E_E)

        INST(1,   5, MOV_E_H)
        INST(1,   5, MOV_E_L)
        INST(1,   7, MOV_E_M)
        INST(1,   5, MOV_E_A)
        
        // 60 - 67
        INST(1,   5, MOV_H_B)
        INST(1,   5, MOV_H_C)
        INST(1,   5, MOV_H_D)
        INST(1,   5, MOV_H_E)

        INST(1,   5, MOV_H_H)
        INST(1,   5, MOV_H_L)
        INST(1,   7, MOV_H_M)
        INST(1,   5, MOV_H_A)

        // 68 - 6f
        INST(1,   5, MOV_L_B)
        INST(1,   5, MOV_L_C)
        INST(1,   5, MOV_L_D)
        INST(1,   5, MOV_L_E)

        INST(1,   5, MOV_L_H)
        INST(1,   5, MOV_L_L)
        INST(1,   7, MOV_L_M)
        INST(1,   5, MOV_L_A)

        // 70 - 77
        INST(1,   7, MOV_M_B)
        INST(1,   7, MOV_M_C)
        INST(1,   7, MOV_M_D)
        INST(1,   7, MOV_M_E)

        INST(1,   7, MOV_M_H)
        INST(1,   7, MOV_M_L)
        INST(1,   7, HLT)
        INST(1,   7, MOV_M_A)

        // 78 - 7f
        INST(1,   5, MOV_A_B)
        INST(1,   5, MOV_A_C)
        INST(1,   5, MOV_A_D)
        INST(1,   5, MOV_A_E)

        INST(1,   5, MOV_A_H)
        INST(1,   5, MOV_A_L)
        INST(1,   7, MOV_A_M)
        INST(1,   5, MOV_A_A)

        // 80 - 87
        INST(1,   4, ADD_B)
        INST(1,   4, ADD_C)
        INST(1,   4, ADD_D)
        INST(1,   4, ADD_E)

        INST(1,   4, ADD_H)
        INST(1,   4, ADD_L)
        INST(1,   7, ADD_M)
        INST(1,   4, ADD_A)

        // 88 - 8f
        INST(1,   4, ADC_B)
        INST(1,   4, ADC_C)
        INST(1,   4, ADC_D)
        INST(1,   4, ADC_E)

        INST(1,   4, ADC_H)
        INST(1,   4, ADC_L)
        INST(1,   7, ADC_M)
        INST(1,   4, ADC_A)

        // 90 - 97
        INST(1,   4, SUB_B)
        INST(1,   4, SUB_C)
        INST(1,   4, SUB_D)
        INST(1,   4, SUB_E)

        INST(1,   4, SUB_H)
        INST(1,   4, SUB_L)
        INST(1,   7, SUB_M)
        INST(1,   4, SUB_A)
        
        // 98 - 9f
        INST(1,   4, SBB_B)
        INST(1,   4, SBB_C)
        INST(1,   4, SBB_D)
        INST(1,   4, SBB_E)

        INST(1,   4, SBB_H)
        INST(1,   4, SBB_L)
        INST(1,   7, SBB_M)
        INST(1,   4, SBB_A)

        // A0 - A7
        INST(1,   4, ANA_B)
        INST(1,   4, ANA_C)
        INST(1,   4, ANA_D)
        INST(1,   4, ANA_E)

        INST(1,   4, ANA_H)
        INST(1,   4, ANA_L)
        INST(1,   7, ANA_M)
        INST(1,   4, ANA_A)
        
        // A8 - Af
        INST(1,   4, XRA_B)
        INST(1,   4, XRA_C)
        INST(1,   4, XRA_D)
        INST(1,   4, XRA_E)

        INST(1,   4, XRA_H)
        INST(1,   4, XRA_L)
        INST(1,   7, XRA_M)
        INST(1,   4, XRA_A)

        // B0 - B7
        INST(1,   4, ORA_B)
        INST(1,   4, ORA_C)
        INST(1,   4, ORA_D)
        INST(1,   4, ORA_E)

        INST(1,   4, ORA_H)
        INST(1,   4, ORA_L)
        INST(1,   7, ORA_M)
        INST(1,   4, ORA_A)
        
        // B8 - Bf
        INST(1,   4, CMP_B)
        INST(1,   4, CMP_C)
        INST(1,   4, CMP_D)
        INST(1,   4, CMP_E)

        INST(1,   4, CMP_H)
        INST(1,   4, CMP_L)
        INST(1,   7, CMP_M)
        INST(1,   4, CMP_A)

        // C0 - C7
        INST(1,   5, RNZ)
        INST(1,  10, POP_B)
        INST(3,  10, JNZ)
        INST(3,  10, JMP)

        INST(3,  11, CNZ)
        INST(1,  11, PUSH_B)
        INST(2,   7, ADI)
        INST(1,  11, RST_0)

        // C8 - Cf
        INST(1,   5, RZ)
        INST(1,  10, RET)
        INST(3,  10, JZ)
        REMAP(3,  10, JMP_CB, JMP)

        INST(3,  11, CZ)
        INST(3,  17, CALL)
        INST(2,   7, ACI)
        INST(1,  11, RST_1)

        // D0 - D7
        INST(1,   5, RNC)
        INST(1,  10, POP_D)
        INST(3,  10, JNC)
        INST(2,  10, OUT)

        INST(3,  11, CNC)
        INST(1,  11, PUSH_D)
        INST(2,   7, SUI)
        INST(1,  11, RST_2)

        // D8 - Df
        INST(1,   5, RC)
        REMAP(1,  10, RET_D9, RET)
        INST(3,  10, JC)
        INST(2,  10, IN)

        INST(3,  11, CC)
        REMAP(3,  17, CALL_DD, CALL)
        INST(2,   7, SBI)
        INST(1,  11, RST_3)

        // E0 - E7
        INST(1,   5, RPO)
        INST(1,  10, POP_H)
        INST(3,  10, JPO)
        INST(1,  18, XTHL)

        INST(3,  11, CPO)
        INST(1,  11, PUSH_H)
        INST(2,   7, ANI)
        INST(1,  11, RST_4)

        // E8 - Ef
        INST(1,   5, RPE)
        INST(1,   5, PCHL)
        INST(3,  10, JPE)
        INST(1,   5, XCHG)

        INST(3,  11, CPE)
        REMAP(3,  17, CALL_ED, CALL)
        INST(2,   7, XRI)
        INST(1,  11, RST_5)

        // F0 - F7
        INST(1,   5, RP)
        INST(1,  10, POP_PSW)
        INST(3,  10, JP)
        INST(1,   4, DI)

        INST(3,  11, CP)
        INST(1,  11, PUSH_PSW)
        INST(2,   7, ORI)
        INST(1,  11, RST_6)

        // F8 - Ff
        INST(1,   5, RM)
        INST(1,   5, SPHL)
        INST(3,  10, JM)
        INST(1,   4, EI)

        INST(3,  11, CM)
        REMAP(3,  17, CALL_FD, CALL)
        INST(2,   7, CPI)
        INST(1,  11, RST_7)
        
        default:
            break;
    }

    // Increase PC by op size - 1
    // This is done to reduce amount of code inside instructions
    *cpu->PC += size - 1;

    // Add min cycle count
    // Extra cycles are added inside the specific functions (see ctrl.c)
    cpu->cycle_count += cycles;

}

