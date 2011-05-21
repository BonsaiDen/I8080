
#ifndef CPU_8080_H
#define CPU_8080_H

#include <stdint.h>

/* Structs ------------------------------------------------------------------ */
typedef struct CPU {

    uint8_t reg[12];

    uint8_t *A;
    uint8_t *F;
    uint16_t *PSW;

    uint8_t *B;
    uint8_t *C;
    uint16_t *BC;

    uint8_t *D;
    uint8_t *E;
    uint16_t *DE;

    uint8_t *H;
    uint8_t *L;
    uint16_t *HL;

    uint16_t *SP;
    uint16_t *PC;

    uint8_t *mem;
    unsigned long cycles;

    void (*run)(struct CPU *cpu);

} CPU;


/* Constructor -------------------------------------------------------------- */
CPU *cpu(uint8_t *mem);

#endif

