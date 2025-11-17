#include <stdint.h>

int decodeAndExecuteInstruction(uint32_t instruction, int print);
int executeProgram(char* filename, int print);
void printRegisters();
void reset();