enum INSTRUCTIONS {

    // x0 - x7
    NOP,
    LXI_B,
    STAX_B,
    INX_B,

    INR_B,
    DCR_B,
    MVI_B,
    RLC,

    // x8 - xF
    NOP_8,
    DAD_B,
    LDAX_B,
    DCX_B,
    
    INR_C,
    DCR_C,
    MVI_C,
    RRC,

    // -----------------------

    // 10 - 17
    NOP_10,
    LXI_D,
    STAX_D,
    INX_D,
    
    INR_D,
    DCR_D,
    MVI_D,
    RAL,

    // 18 - 1F
    NOP_18,
    DAD_D,
    LDAX_D,
    DCX_D,
    
    INR_E,
    DCR_E,
    MVI_E,
    RAR,

    // -----------------------

    // 20 - 27
    NOP_20,
    LXI_H,
    SHLD,
    INX_H,
    
    INR_H,
    DCR_H,
    MVI_H,
    DAA,

    // 28 - 2f
    NOP_28,
    DAD_H,
    LHLD,
    DCX_H,
    
    INR_L,
    DCR_L,
    MVI_L,
    CMA,

    // -----------------------

    // 30 - 37
    NOP_30,
    LXI_SP,
    STA,
    INX_SP,
    
    INR_M,
    DCR_M,
    MVI_M,
    STC,

    // 38 - 3f
    NOP_38,
    DAD_SP,
    LDA,
    DCX_SP,
    
    INR_A,
    DCR_A,
    MVI_A,
    CMC,

    // 40 - 47
    MOV_B_B,
    MOV_B_C,
    MOV_B_D,
    MOV_B_E,
        
    MOV_B_H,
    MOV_B_L,
    MOV_B_M,
    MOV_B_A,

    // 48 - 4f
    MOV_C_B,
    MOV_C_C,
    MOV_C_D,
    MOV_C_E,
        
    MOV_C_H,
    MOV_C_L,
    MOV_C_M,
    MOV_C_A,

    // 50 - 57
    MOV_D_B,
    MOV_D_C,
    MOV_D_D,
    MOV_D_E,
        
    MOV_D_H,
    MOV_D_L,
    MOV_D_M,
    MOV_D_A,

    // 58 - 5f
    MOV_E_B,
    MOV_E_C,
    MOV_E_D,
    MOV_E_E,
        
    MOV_E_H,
    MOV_E_L,
    MOV_E_M,
    MOV_E_A,
    
    // 60 - 67
    MOV_H_B,
    MOV_H_C,
    MOV_H_D,
    MOV_H_E,
        
    MOV_H_H,
    MOV_H_L,
    MOV_H_M,
    MOV_H_A,

    // 68 - 6f
    MOV_L_B,
    MOV_L_C,
    MOV_L_D,
    MOV_L_E,
        
    MOV_L_H,
    MOV_L_L,
    MOV_L_M,
    MOV_L_A,

    // 70 - 77
    MOV_M_B,
    MOV_M_C,
    MOV_M_D,
    MOV_M_E,

    MOV_M_H,
    MOV_M_L,
    HLT,
    MOV_M_A,

    // 78 - 7f
    MOV_A_B,
    MOV_A_C,
    MOV_A_D,
    MOV_A_E,
        
    MOV_A_H,
    MOV_A_L,
    MOV_A_M,
    MOV_A_A,

};

