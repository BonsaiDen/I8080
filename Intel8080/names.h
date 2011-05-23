// Intel 8080 OP Code Names ---------------------------------------------------
// ----------------------------------------------------------------------------
#ifndef INTEL_8080_OP_CODE_NAMES_H
#define INTEL_8080_OP_CODE_NAMES_H

const char *INTEL_8080_OP_CODE_NAMES[256] = {

    // x0 - x7
    "NOP",
    "LXI_B",
    "STAX_B",
    "INX_B",

    "INR_B",
    "DCR_B",
    "MVI_B",
    "RLC",

    // x8 - xF
    "NOP_8",
    "DAD_B",
    "LDAX_B",
    "DCX_B",
    
    "INR_C",
    "DCR_C",
    "MVI_C",
    "RRC",

    // 10 - 17
    "NOP_10",
    "LXI_D",
    "STAX_D",
    "INX_D",
    
    "INR_D",
    "DCR_D",
    "MVI_D",
    "RAL",

    // 18 - 1F
    "NOP_18",
    "DAD_D",
    "LDAX_D",
    "DCX_D",
    
    "INR_E",
    "DCR_E",
    "MVI_E",
    "RAR",

    // 20 - 27
    "NOP_20",
    "LXI_H",
    "SHLD",
    "INX_H",
    
    "INR_H",
    "DCR_H",
    "MVI_H",
    "DAA",

    // 28 - 2f
    "NOP_28",
    "DAD_H",
    "LHLD",
    "DCX_H",
    
    "INR_L",
    "DCR_L",
    "MVI_L",
    "CMA",

    // 30 - 37
    "NOP_30",
    "LXI_SP",
    "STA",
    "INX_SP",
    
    "INR_M",
    "DCR_M",
    "MVI_M",
    "STC",

    // 38 - 3f
    "NOP_38",
    "DAD_SP",
    "LDA",
    "DCX_SP",
    
    "INR_A",
    "DCR_A",
    "MVI_A",
    "CMC",

    // 40 - 47
    "MOV_B_B",
    "MOV_B_C",
    "MOV_B_D",
    "MOV_B_E",

    "MOV_B_H",
    "MOV_B_L",
    "MOV_B_M",
    "MOV_B_A",

    // 48 - 4f
    "MOV_C_B",
    "MOV_C_C",
    "MOV_C_D",
    "MOV_C_E",
        
    "MOV_C_H",
    "MOV_C_L",
    "MOV_C_M",
    "MOV_C_A",

    // 50 - 57
    "MOV_D_B",
    "MOV_D_C",
    "MOV_D_D",
    "MOV_D_E",
        
    "MOV_D_H",
    "MOV_D_L",
    "MOV_D_M",
    "MOV_D_A",

    // 58 - 5f
    "MOV_E_B",
    "MOV_E_C",
    "MOV_E_D",
    "MOV_E_E",
        
    "MOV_E_H",
    "MOV_E_L",
    "MOV_E_M",
    "MOV_E_A",
    
    // 60 - 67
    "MOV_H_B",
    "MOV_H_C",
    "MOV_H_D",
    "MOV_H_E",
        
    "MOV_H_H",
    "MOV_H_L",
    "MOV_H_M",
    "MOV_H_A",

    // 68 - 6f
    "MOV_L_B",
    "MOV_L_C",
    "MOV_L_D",
    "MOV_L_E",
        
    "MOV_L_H",
    "MOV_L_L",
    "MOV_L_M",
    "MOV_L_A",

    // 70 - 77
    "MOV_M_B",
    "MOV_M_C",
    "MOV_M_D",
    "MOV_M_E",

    "MOV_M_H",
    "MOV_M_L",
    "HLT",
    "MOV_M_A",

    // 78 - 7f
    "MOV_A_B",
    "MOV_A_C",
    "MOV_A_D",
    "MOV_A_E",
        
    "MOV_A_H",
    "MOV_A_L",
    "MOV_A_M",
    "MOV_A_A",

    // 80 - 87
    "ADD_B",
    "ADD_C",
    "ADD_D",
    "ADD_E",

    "ADD_H",
    "ADD_L",
    "ADD_M",
    "ADD_A",

    // 88 - 8f
    "ADC_B",
    "ADC_C",
    "ADC_D",
    "ADC_E",

    "ADC_H",
    "ADC_L",
    "ADC_M",
    "ADC_A",

    // 90 - 97
    "SUB_B",
    "SUB_C",
    "SUB_D",
    "SUB_E",

    "SUB_H",
    "SUB_L",
    "SUB_M",
    "SUB_A",
    
    // 98 - 9f
    "SBB_B",
    "SBB_C",
    "SBB_D",
    "SBB_E",

    "SBB_H",
    "SBB_L",
    "SBB_M",
    "SBB_A",

    // A0 - A7
    "ANA_B",
    "ANA_C",
    "ANA_D",
    "ANA_E",

    "ANA_H",
    "ANA_L",
    "ANA_M",
    "ANA_A",
    
    // A8 - Af
    "XRA_B",
    "XRA_C",
    "XRA_D",
    "XRA_E",

    "XRA_H",
    "XRA_L",
    "XRA_M",
    "XRA_A",

    // B0 - B7
    "ORA_B",
    "ORA_C",
    "ORA_D",
    "ORA_E",

    "ORA_H",
    "ORA_L",
    "ORA_M",
    "ORA_A",
    
    // B8 - Bf
    "CMP_B",
    "CMP_C",
    "CMP_D",
    "CMP_E",

    "CMP_H",
    "CMP_L",
    "CMP_M",
    "CMP_A",

    // C0 - C7
    "RNZ",
    "POP_B",
    "JNZ",
    "JMP",

    "CNZ",
    "PUSH_B",
    "ADI",
    "RST_0",

    // C8 - Cf
    "RZ",
    "RET",
    "JZ",
    "JMP",

    "CZ",
    "CALL",
    "ACI",
    "RST_1",

    // D0 - D7
    "RNC",
    "POP_D",
    "JNC",
    "OUT",

    "CNC",
    "PUSH_D",
    "SUI",
    "RST_2",

    // D8 - Df
    "RC",
    "RET",
    "JC",
    "IN",

    "CC",
    "CALL",
    "SBI",
    "RST_3",

    // E0 - E7
    "RPO",
    "POP_H",
    "JPO",
    "XTHL",

    "CPO",
    "PUSH_H",
    "ANI",
    "RST_4",

    // E8 - Ef
    "RPE",
    "PCHL",
    "JPE",
    "XCHG",

    "CPE",
    "CALL",
    "XRI",
    "RST_5",

    // F0 - F7
    "RP",
    "POP_PSW",
    "JP",
    "DI",

    "CP",
    "PUSH_PSW",
    "ORI",
    "RST_6",

    // F8 - Ff
    "RM",
    "SPHL",
    "JM",
    "EI",

    "CM",
    "CALL",
    "CPI",
    "RST_7"

};

#endif

