
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
    1,   4,  op CMC


};

#undef op
#endif

