
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

    // state info
    uint8_t instruction;
    unsigned long cycle_count;
    uint8_t ime;

    // Pins
    uint8_t halt;
    uint8_t reset;

} CPU_8080;

CPU_8080 *CPU;

void cpu_init();
void cpu_fetch();
unsigned int cpu_exec();
void cpu_reset();
void cpu_destroy();

inline void cpu_flag_szp(uint8_t *r);
inline void cpu_flag_szap(uint8_t *r);

#endif

