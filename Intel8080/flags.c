// Intel 8080 Flag handling ---------------------------------------------------
// ----------------------------------------------------------------------------
#include "Cpu.h"


static const unsigned int ParityTable256[256] = {
#   define P2(n) n, n^1, n^1, n
#   define P4(n) P2(n), P2(n^1), P2(n^1), P2(n)
#   define P6(n) P4(n), P4(n^1), P4(n^1), P4(n)
    P6(0), P6(1), P6(1), P6(0)
};

inline void cpu_flag_szap(Intel8080 *cpu, uint8_t *r) {
    
    (*cpu->F) = 0; // clear flags

    // TODO double check these
    if (*r & 128)              (*cpu->F) |= 128; // set SIGN flag
    if (*r == 0)               (*cpu->F) |=  64; // set ZERO flag
    if (!(*r & 15 && *r & 31)) (*cpu->F) |=  16; // set AUXILLARY CARRY flag
    if (ParityTable256[*r])    (*cpu->F) |=   4; // set PARITY flag
    
}

inline void cpu_flag_szp(Intel8080 *cpu, uint8_t *r) {

    (*cpu->F) = 0; // clear flags

    if (*r & 128)              (*cpu->F) |= 128; // set SIGN flag
    if (*r == 0)               (*cpu->F) |=  64; // set ZERO flag
    if (ParityTable256[*r])    (*cpu->F) |=   4; // set PARITY flag

}

