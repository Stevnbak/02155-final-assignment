#include <stdint.h>

uint32_t instructionMemory[1 * 1000];
char dataMemory[1 * 1000 * 1000];

uint8_t running = 1;
uint32_t PC = 0;