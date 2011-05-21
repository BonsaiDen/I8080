
#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

inline uint8_t read8(uint16_t addr);
inline uint16_t read16(uint16_t addr);
inline void write8(uint16_t addr, uint8_t *val);
inline void write16(uint16_t addr, uint16_t *val);

#endif

