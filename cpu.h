#include <stdint.h>

extern uint32_t instructionMemory[1 * 1000];
extern char dataMemory[1 * 1000 * 1000];

int getRegister(uint8_t reg);
void setRegister(uint8_t reg, int value);
uint32_t getRegisterUnsigned(uint8_t reg);
void setRegisterUnsigned(uint8_t reg, uint32_t value);

extern uint8_t running;
extern uint32_t PC;