const char *INST_NAMES[256] = {

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

    // -----------------------

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

    // -----------------------

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

    // -----------------------

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
    "CMC"
};



