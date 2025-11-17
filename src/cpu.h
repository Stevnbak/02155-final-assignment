#include <stdint.h>

// 1MB of memory
extern char memory[1 * 1024 * 1024];

int32_t getRegister(uint8_t reg);
void setRegister(uint8_t reg, int32_t value);
uint32_t getRegisterUnsigned(uint8_t reg);
void setRegisterUnsigned(uint8_t reg, uint32_t value);

extern uint8_t running;
extern uint32_t PC;
extern int returnCode;