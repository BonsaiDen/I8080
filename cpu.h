
#ifndef CPU_8080_H
#define CPU_8080_H

#include <stdint.h>

typedef struct CPU_8080 {

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

    unsigned long cycles;

} CPU_8080;

CPU_8080 *cpu_create();
inline cpu_flag_szap_inc(uint16_t *r);
inline void cpu_flag_szap_dec(uint16_t *r);
void cpu_step();
uint8_t *cpu_next();

#endif

