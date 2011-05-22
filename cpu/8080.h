
#ifndef CPU_8080_H
#define CPU_8080_H

#include <stdint.h>

struct CPU_8080;
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

    unsigned long cycle_count;
    uint8_t instruction;

    uint8_t ime;
    uint8_t halt;

    void (*fetch)(struct CPU_8080 *cpu);
    uint8_t (*exec)(struct CPU_8080 *cpu);
    void (*reset)(struct CPU_8080 *cpu);
    void (*destroy)(struct CPU_8080 **cpu);


} CPU_8080;

CPU_8080 *cpu_create();

inline void cpu_flag_szp(CPU_8080 *cpu, uint8_t *r);
inline void cpu_flag_szap(CPU_8080 *cpu, uint8_t *r);

#endif

