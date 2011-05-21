
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "cpu.h"
#include "inst.h"


int main(int argc, const char *argv[]) {
    
    // load from mem, and do some stuff
    uint8_t mem[65536] = {
        LHLD, 0, 100,

        LXI_B, 0, 42,

        DAD_B,

        SHLD, 0, 110,

        LXI_H, 0, 0,

        LHLD, 0, 110,
        
        NOP
    };

    mem[100] = 128;
    mem[101] = 255;

    CPU *core = cpu(mem);
    core->run(core);
    free(core);
    return 0;
}

