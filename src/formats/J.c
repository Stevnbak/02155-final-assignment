#include <stdint.h>
#include "../cpu.h"

int executeJFormat(
    uint8_t rd,
    uint32_t instruction
) {
    uint32_t bit31 = (instruction & 	0x80000000); 		// 1000 0000 0000 0000 0000 0000 0000 0000 -> 1000 0000 0000 0000 0000 0000 0000 0000
    uint32_t bit12_19 = (instruction & 	0x000FF000) << 11; 	// 0000 0000 0000 1111 1111 0000 0000 0000 -> 0111 1111 1000 0000 0000 0000 0000 0000
    uint32_t bit20 = (instruction & 	0x00100000) << 2;  	// 0000 0000 0001 0000 0000 0000 0000 0000 -> 0000 0000 0100 0000 0000 0000 0000 0000
    uint32_t bit21_30 = (instruction & 	0x7FE00000) >> 9; 	// 0111 1111 1110 0000 0000 0000 0000 0000 -> 0000 0000 0011 1111 1111 0000 0000 0000
    uint32_t combined = bit31 + bit12_19 + bit20 + bit21_30;
    int32_t imm = ((int32_t)(*(int32_t*)&combined)) >> 11;

    setRegister(rd, PC);
    PC += imm - 4;
    return 0;
}