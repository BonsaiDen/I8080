// Intel 8080 Emulator --------------------------------------------------------
// ----------------------------------------------------------------------------
#ifndef CPU_INTEL_8080_H
#define CPU_INTEL_8080_H

#include <stdint.h>

struct Intel8080;
typedef struct Intel8080 {

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
    uint16_t *stack_top;

    uint8_t ime;
    uint8_t halt;

    unsigned long (*exec)(struct Intel8080 *cpu, unsigned long cycles);
    void (*reset)(struct Intel8080 *cpu);
    void (*destroy)(struct Intel8080 **cpu);

    uint8_t (*read_mem)(uint16_t addr);
    void (*write_mem)(uint16_t addr, uint8_t val);

} Intel8080;

Intel8080 *cpu_create(uint8_t (*read_mem)(uint16_t addr),
                      void (*write_mem)(uint16_t addr, uint8_t val),
                      uint16_t *stack_top);

#endif

