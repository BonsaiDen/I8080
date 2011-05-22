// 8080 OP Code Data Table ----------------------------------------------------
// ----------------------------------------------------------------------------
#ifndef CPU_8080_OP_CODE_DATA_H
#define CPU_8080_OP_CODE_DATA_H

#include "base.c"
#include "acc.c"
#include "bit.c"
#include "math.c"
#include "mov.c"
#include "reg.c"

typedef void (*OP_CODE_POINTER)();

// Size in Bytes | Cycle Count | Function Address
unsigned int OP_CODE_DATA[768] = {

    // x0 - x7
    1,   4,  (unsigned int)& NOP,
    3,  10,  (unsigned int)& LXI_B,
    1,   7,  (unsigned int)& STAX_B,
    1,   5,  (unsigned int)& INX_B,

    1,   5,  (unsigned int)& INR_B,
    1,   5,  (unsigned int)& DCR_B,
    2,   7,  (unsigned int)& MVI_B,
    1,   4,  (unsigned int)& RLC,

    // x8 - xF
    1,   4,  (unsigned int)& NOP,
    1,  10,  (unsigned int)& DAD_B,
    1,   7,  (unsigned int)& LDAX_B,
    1,   5,  (unsigned int)& DCX_B,
             
    1,   5,  (unsigned int)& INR_C,
    1,   5,  (unsigned int)& DCR_C,
    2,   7,  (unsigned int)& MVI_C,
    1,   4,  (unsigned int)& RRC,

    // 10 - 17
    1,   4,  (unsigned int)& NOP,
    3,  10,  (unsigned int)& LXI_D,
    1,   7,  (unsigned int)& STAX_D,
    1,   5,  (unsigned int)& INX_D,
             
    1,   5,  (unsigned int)& INR_D,
    1,   5,  (unsigned int)& DCR_D,
    2,   7,  (unsigned int)& MVI_D,
    1,   4,  (unsigned int)& RAL,

    // 18 - 1F
    1,   4,  (unsigned int)& NOP,
    1,  10,  (unsigned int)& DAD_D,
    1,   7,  (unsigned int)& LDAX_D,
    1,   5,  (unsigned int)& DCX_D,
             
    1,   5,  (unsigned int)& INR_E,
    1,   5,  (unsigned int)& DCR_E,
    2,   7,  (unsigned int)& MVI_E,
    1,   4,  (unsigned int)& RAR,

    // 20 - 27
    1,   4,  (unsigned int)& NOP,
    3,  10,  (unsigned int)& LXI_H,
    3,  16,  (unsigned int)& SHLD,
    1,   5,  (unsigned int)& INX_H,
    
    1,   5,  (unsigned int)& INR_H,
    1,   5,  (unsigned int)& DCR_H,
    2,   7,  (unsigned int)& MVI_H,
    1,   4,  (unsigned int)& DAA,

    // 28 - 2f
    1,   4,  (unsigned int)& NOP,
    1,  10,  (unsigned int)& DAD_H,
    3,  16,  (unsigned int)& LHLD,
    1,   5,  (unsigned int)& DCX_H,
    
    1,   5,  (unsigned int)& INR_L,
    1,   5,  (unsigned int)& DCR_L,
    2,   7,  (unsigned int)& MVI_L,
    1,   4,  (unsigned int)& CMA,

    // 30 - 37
    1,   4,  (unsigned int)& NOP,
    3,  10,  (unsigned int)& LXI_SP,
    3,  13,  (unsigned int)& STA,
    1,   5,  (unsigned int)& INX_SP,
             
    1,  10,  (unsigned int)& INR_M,
    1,  10,  (unsigned int)& DCR_M,
    2,  10,  (unsigned int)& MVI_M,
    1,   4,  (unsigned int)& STC,

    // 38 - 3f
    1,   4,  (unsigned int)& NOP,
    1,  10,  (unsigned int)& DAD_SP,
    3,  13,  (unsigned int)& LDA,
    1,   5,  (unsigned int)& DCX_SP,
    
    1,   5,  (unsigned int)& INR_A,
    1,   5,  (unsigned int)& DCR_A,
    2,   7,  (unsigned int)& MVI_A,
    1,   4,  (unsigned int)& CMC,
    
    // 40 - 47
    1,   5,  (unsigned int)& MOV_B_B,
    1,   5,  (unsigned int)& MOV_B_C,
    1,   5,  (unsigned int)& MOV_B_D,
    1,   5,  (unsigned int)& MOV_B_E,
                    
    1,   5,  (unsigned int)& MOV_B_H,
    1,   5,  (unsigned int)& MOV_B_L,
    1,   7,  (unsigned int)& MOV_B_M,
    1,   5,  (unsigned int)& MOV_B_A,

    // 48 - 4f
    1,   5,  (unsigned int)& MOV_C_B,
    1,   5,  (unsigned int)& MOV_C_C,
    1,   5,  (unsigned int)& MOV_C_D,
    1,   5,  (unsigned int)& MOV_C_E,
                    
    1,   5,  (unsigned int)& MOV_C_H,
    1,   5,  (unsigned int)& MOV_C_L,
    1,   7,  (unsigned int)& MOV_C_M,
    1,   5,  (unsigned int)& MOV_C_A,

    // 50 - 57
    1,   5,  (unsigned int)& MOV_D_B,
    1,   5,  (unsigned int)& MOV_D_C,
    1,   5,  (unsigned int)& MOV_D_D,
    1,   5,  (unsigned int)& MOV_D_E,
                    
    1,   5,  (unsigned int)& MOV_D_H,
    1,   5,  (unsigned int)& MOV_D_L,
    1,   7,  (unsigned int)& MOV_D_M,
    1,   5,  (unsigned int)& MOV_D_A,

    // 58 - 5f
    1,   5,  (unsigned int)& MOV_E_B,
    1,   5,  (unsigned int)& MOV_E_C,
    1,   5,  (unsigned int)& MOV_E_D,
    1,   5,  (unsigned int)& MOV_E_E,
                    
    1,   5,  (unsigned int)& MOV_E_H,
    1,   5,  (unsigned int)& MOV_E_L,
    1,   7,  (unsigned int)& MOV_E_M,
    1,   5,  (unsigned int)& MOV_E_A,
    
    // 60 - 67
    1,   5,  (unsigned int)& MOV_H_B,
    1,   5,  (unsigned int)& MOV_H_C,
    1,   5,  (unsigned int)& MOV_H_D,
    1,   5,  (unsigned int)& MOV_H_E,
                    
    1,   5,  (unsigned int)& MOV_H_H,
    1,   5,  (unsigned int)& MOV_H_L,
    1,   7,  (unsigned int)& MOV_H_M,
    1,   5,  (unsigned int)& MOV_H_A,

    // 68 - 6f
    1,   5,  (unsigned int)& MOV_L_B,
    1,   5,  (unsigned int)& MOV_L_C,
    1,   5,  (unsigned int)& MOV_L_D,
    1,   5,  (unsigned int)& MOV_L_E,
                    
    1,   5,  (unsigned int)& MOV_L_H,
    1,   5,  (unsigned int)& MOV_L_L,
    1,   7,  (unsigned int)& MOV_L_M,
    1,   5,  (unsigned int)& MOV_L_A,

    // 70 - 77
    1,   7,  (unsigned int)& MOV_M_B,
    1,   7,  (unsigned int)& MOV_M_C,
    1,   7,  (unsigned int)& MOV_M_D,
    1,   7,  (unsigned int)& MOV_M_E,

    1,   7,  (unsigned int)& MOV_M_H,
    1,   7,  (unsigned int)& MOV_M_L,
    1,   7,  (unsigned int)& HLT,
    1,   7,  (unsigned int)& MOV_M_A,

    // 78 - 7f
    1,   5,  (unsigned int)& MOV_A_B,
    1,   5,  (unsigned int)& MOV_A_C,
    1,   5,  (unsigned int)& MOV_A_D,
    1,   5,  (unsigned int)& MOV_A_E,
                    
    1,   5,  (unsigned int)& MOV_A_H,
    1,   5,  (unsigned int)& MOV_A_L,
    1,   7,  (unsigned int)& MOV_A_M,
    1,   5,  (unsigned int)& MOV_A_A,

    // 80 - 87
    1,   4,  (unsigned int)& ADD_B,
    1,   4,  (unsigned int)& ADD_C,
    1,   4,  (unsigned int)& ADD_D,
    1,   4,  (unsigned int)& ADD_E,

    1,   4,  (unsigned int)& ADD_H,
    1,   4,  (unsigned int)& ADD_L,
    1,   7,  (unsigned int)& ADD_M,
    1,   4,  (unsigned int)& ADD_A,

    // 88 - 8f
    1,   4,  (unsigned int)& ADC_B,
    1,   4,  (unsigned int)& ADC_C,
    1,   4,  (unsigned int)& ADC_D,
    1,   4,  (unsigned int)& ADC_E,

    1,   4,  (unsigned int)& ADC_H,
    1,   4,  (unsigned int)& ADC_L,
    1,   7,  (unsigned int)& ADC_M,
    1,   4,  (unsigned int)& ADC_A,

    // 90 - 97
    1,   4,  (unsigned int)& SUB_B,
    1,   4,  (unsigned int)& SUB_C,
    1,   4,  (unsigned int)& SUB_D,
    1,   4,  (unsigned int)& SUB_E,
                
    1,   4,  (unsigned int)& SUB_H,
    1,   4,  (unsigned int)& SUB_L,
    1,   7,  (unsigned int)& SUB_M,
    1,   4,  (unsigned int)& SUB_A,
    
    // 98 - 9f
    1,   4,  (unsigned int)& SBB_B,
    1,   4,  (unsigned int)& SBB_C,
    1,   4,  (unsigned int)& SBB_D,
    1,   4,  (unsigned int)& SBB_E,

    1,   4,  (unsigned int)& SBB_H,
    1,   4,  (unsigned int)& SBB_L,
    1,   7,  (unsigned int)& SBB_M,
    1,   4,  (unsigned int)& SBB_A,

    // A0 - A7
    1,   4,  (unsigned int)& ANA_B,
    1,   4,  (unsigned int)& ANA_C,
    1,   4,  (unsigned int)& ANA_D,
    1,   4,  (unsigned int)& ANA_E,

    1,   4,  (unsigned int)& ANA_H,
    1,   4,  (unsigned int)& ANA_L,
    1,   7,  (unsigned int)& ANA_M,
    1,   4,  (unsigned int)& ANA_A,
    
    // A8 - Af
    1,   4,  (unsigned int)& XRA_B,
    1,   4,  (unsigned int)& XRA_C,
    1,   4,  (unsigned int)& XRA_D,
    1,   4,  (unsigned int)& XRA_E,

    1,   4,  (unsigned int)& XRA_H,
    1,   4,  (unsigned int)& XRA_L,
    1,   7,  (unsigned int)& XRA_M,
    1,   4,  (unsigned int)& XRA_A,

    // B0 - B7
    1,   4,  (unsigned int)& ORA_B,
    1,   4,  (unsigned int)& ORA_C,
    1,   4,  (unsigned int)& ORA_D,
    1,   4,  (unsigned int)& ORA_E,

    1,   4,  (unsigned int)& ORA_H,
    1,   4,  (unsigned int)& ORA_L,
    1,   7,  (unsigned int)& ORA_M,
    1,   4,  (unsigned int)& ORA_A,
    
    // B8 - Bf
    1,   4,  (unsigned int)& CMP_B,
    1,   4,  (unsigned int)& CMP_C,
    1,   4,  (unsigned int)& CMP_D,
    1,   4,  (unsigned int)& CMP_E,

    1,   4,  (unsigned int)& CMP_H,
    1,   4,  (unsigned int)& CMP_L,
    1,   7,  (unsigned int)& CMP_M,
    1,   4,  (unsigned int)& CMP_A,

};

#endif

