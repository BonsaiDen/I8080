
#ifndef OP_CODES_H
#define OP_CODES_H

#include <stdint.h>
#include "ops.c"
#include "ops_16bit.c"
#include "ops_8bit.c"

typedef void (*OPC)();

#define op (unsigned int)&


// byte size /min cycle length / function
unsigned int OP_CODES[768] = {

    // x0 - x7
    1,   4,  op NOP,
    3,  10,  op LXI_B,
    1,   7,  op STAX_B,
    1,   5,  op INX_B,

    1,   5,  op INR_B,
    1,   5,  op DCR_B,
    2,   7,  op MVI_B,
    1,   4,  op RLC,

    // x8 - xF
    1,   4,  op NOP,
    1,  10,  op DAD_B,
    1,   7,  op LDAX_B,
    1,   5,  op DCX_B,
             
    1,   5,  op INR_C,
    1,   5,  op DCR_C,
    2,   7,  op MVI_C,
    1,   4,  op RRC,

    // -----------------------

    // 10 - 17
    1,   4,  op NOP,
    3,  10,  op LXI_D,
    1,   7,  op STAX_D,
    1,   5,  op INX_D,
             
    1,   5,  op INR_D,
    1,   5,  op DCR_D,
    2,   7,  op MVI_D,
    1,   4,  op RAL,

    // 18 - 1F
    1,   4,  op NOP,
    1,  10,  op DAD_D,
    1,   7,  op LDAX_D,
    1,   5,  op DCX_D,
             
    1,   5,  op INR_E,
    1,   5,  op DCR_E,
    2,   7,  op MVI_E,
    1,   4,  op RAR,

    // -----------------------

    // 20 - 27
    1,   4,  op NOP,
    3,  10,  op LXI_H,
    3,  16,  op SHLD,
    1,   5,  op INX_H,
    
    1,   5,  op INR_H,
    1,   5,  op DCR_H,
    2,   7,  op MVI_H,
    1,   4,  op DAA,

    // 28 - 2f
    1,   4,  op NOP,
    1,  10,  op DAD_H,
    3,  16,  op LHLD,
    1,   5,  op DCX_H,
    
    1,   5,  op INR_L,
    1,   5,  op DCR_L,
    2,   7,  op MVI_L,
    1,   4,  op CMA,

    // -----------------------

    // 30 - 37
    1,   4,  op NOP,
    3,  10,  op LXI_SP,
    3,  13,  op STA,
    1,   5,  op INX_SP,
             
    1,  10,  op INR_M,
    1,  10,  op DCR_M,
    2,  10,  op MVI_M,
    1,   4,  op STC,

    // 38 - 3f
    1,   4,  op NOP,
    1,  10,  op DAD_SP,
    3,  13,  op LDA,
    1,   5,  op DCX_SP,
    
    1,   5,  op INR_A,
    1,   5,  op DCR_A,
    2,   7,  op MVI_A,
    1,   4,  op CMC,

    // ---------------------- the next quarter is just moves... and halt!
    
    // 40 - 47
    1,   5,  op MOV_B_B,
    1,   5,  op MOV_B_C,
    1,   5,  op MOV_B_D,
    1,   5,  op MOV_B_E,
                    
    1,   5,  op MOV_B_H,
    1,   5,  op MOV_B_L,
    1,   7,  op MOV_B_M,
    1,   5,  op MOV_B_A,

    // 48 - 4f
    1,   5,  op MOV_C_B,
    1,   5,  op MOV_C_C,
    1,   5,  op MOV_C_D,
    1,   5,  op MOV_C_E,
                    
    1,   5,  op MOV_C_H,
    1,   5,  op MOV_C_L,
    1,   7,  op MOV_C_M,
    1,   5,  op MOV_C_A,

    // 50 - 57
    1,   5,  op MOV_D_B,
    1,   5,  op MOV_D_C,
    1,   5,  op MOV_D_D,
    1,   5,  op MOV_D_E,
                    
    1,   5,  op MOV_D_H,
    1,   5,  op MOV_D_L,
    1,   7,  op MOV_D_M,
    1,   5,  op MOV_D_A,

    // 58 - 5f
    1,   5,  op MOV_E_B,
    1,   5,  op MOV_E_C,
    1,   5,  op MOV_E_D,
    1,   5,  op MOV_E_E,
                    
    1,   5,  op MOV_E_H,
    1,   5,  op MOV_E_L,
    1,   7,  op MOV_E_M,
    1,   5,  op MOV_E_A,
    
    // 60 - 67
    1,   5,  op MOV_H_B,
    1,   5,  op MOV_H_C,
    1,   5,  op MOV_H_D,
    1,   5,  op MOV_H_E,
                    
    1,   5,  op MOV_H_H,
    1,   5,  op MOV_H_L,
    1,   7,  op MOV_H_M,
    1,   5,  op MOV_H_A,

    // 68 - 6f
    1,   5,  op MOV_L_B,
    1,   5,  op MOV_L_C,
    1,   5,  op MOV_L_D,
    1,   5,  op MOV_L_E,
                    
    1,   5,  op MOV_L_H,
    1,   5,  op MOV_L_L,
    1,   7,  op MOV_L_M,
    1,   5,  op MOV_L_A,

    // 70 - 77
    1,   7,  op MOV_M_B,
    1,   7,  op MOV_M_C,
    1,   7,  op MOV_M_D,
    1,   7,  op MOV_M_E,

    1,   7,  op MOV_M_H,
    1,   7,  op MOV_M_L,
    1,   7,  op HLT,
    1,   7,  op MOV_M_A,

    // 78 - 7f
    1,   5,  op MOV_A_B,
    1,   5,  op MOV_A_C,
    1,   5,  op MOV_A_D,
    1,   5,  op MOV_A_E,
                    
    1,   5,  op MOV_A_H,
    1,   5,  op MOV_A_L,
    1,   7,  op MOV_A_M,
    1,   5,  op MOV_A_A,


    // up next
    // ADD
    // SUB
    // AND / XOR
    // OR / CMP



};

#undef op
#endif

