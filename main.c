
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

uint8_t PAGE;

struct CPU_8080 *CPU;

#include "cpu.h"
#include "mmu.h"
#include "inst.h"

uint8_t *MEMORY;


int main(int argc, const char *argv[]) {

    MEMORY = calloc(65536, sizeof(uint8_t));
    
    // load from mem, and do some stuf
    //
    //
    //
    uint8_t TEST[65536] = {
        LHLD, 0, 100,

        LXI_B, 0, 42,

        DAD_B,

        SHLD, 0, 110,

        LXI_H, 0, 0,

        LHLD, 0, 110,
        
        NOP
    };

    TEST[100] = 128;
    TEST[101] = 255;

    memcpy(MEMORY, TEST, sizeof(TEST));
    
    CPU = cpu_create();
    cpu_run();

    free(CPU);
    return 0;
}

