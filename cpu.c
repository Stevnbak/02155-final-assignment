#include "cpu.h"

uint32_t instructionMemory[1 * 1000];
char dataMemory[1 * 1024 * 1024];

uint8_t running = 1;
uint32_t PC = 0;
int returnCode = 0;

int registers[32];

int getRegister(uint8_t reg) {
    if(reg == 0) return 0;
    return registers[reg];
}
void setRegister(uint8_t reg, int value) {
    if(reg == 0) return;
    registers[reg] = value;
}

uint32_t getRegisterUnsigned(uint8_t reg) {
    if(reg == 0) return 0;
    return ((uint32_t*)registers)[reg];
}
void setRegisterUnsigned(uint8_t reg, uint32_t value) {
    if(reg == 0) return;
    ((uint32_t*)registers)[reg] = value;
}