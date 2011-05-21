
#include <stdlib.h>
#include "cpu.h"


/* Lookups ------------------------------------------------------------------ */
static const unsigned int ParityTable256[256] = {
#   define P2(n) n, n^1, n^1, n
#   define P4(n) P2(n), P2(n^1), P2(n^1), P2(n)
#   define P6(n) P4(n), P4(n^1), P4(n^1), P4(n)
    P6(0), P6(1), P6(1), P6(0)
};


/* 16 bit helpers ----------------------------------------------------------- */
static inline uint16_t read16(uint8_t *mem) {
    return *mem << 8 | *(mem + 1); 
    // TODO implement page protection

//    return (*(uint16_t*)value << 8) | (*(uint16_t*)value >> (16 - 8));
}

static inline void write16(uint8_t *mem, uint16_t *r) {
    *mem = *r >> 8;
    *(mem + 1) = *r & 0xff;
}


/* Flag helpers ------------------------------------------------------------- */
static inline void check_szap_inc(CPU *c, uint16_t *r) {

    (*c->F) = 0; // clear flags

    if (!(*r & 128))           (*c->F) |= 128; // set SIGN flag
    if (*r == 0)               (*c->F) |=  64; // set ZERO flag
    if (!(*r & 15 && *r & 31)) (*c->F) |=  16; // set AUXILLARY CARRY flag
    if (ParityTable256[*r])    (*c->F) |=   4; // set PARITY flag

}

static inline void check_szap_dec(CPU *c, uint16_t *r) {

    (*c->F) = 0; // clear flags

    if (!(*r & 128))           (*c->F) |= 128; // set SIGN flag
    if (*r == 0)               (*c->F) |=  64; // set ZERO flag
    if (!(*r & 7 && *r & 15))  (*c->F) |=  16; // set AUXILLARY CARRY flag
    if (ParityTable256[*r])    (*c->F) |=   4; // set PARITY flag

}

