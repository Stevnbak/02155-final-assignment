#include <stdint.h>
#include "../cpu.h"

int executeJFormat(
    uint8_t rd,
    uint32_t instruction
) {
    uint32_t bit31 = (instruction & 0x80000000);
    uint32_t bit12_19 = (instruction & 0x0000000F0F000000) << 11;
    uint32_t bit20 = (instruction & 0x0000010000000000) << 2;
    uint32_t bit21_30 = (instruction & 0x070F0E0000000000) >> 9; // måske shift 10?
    int32_t imm = (int32_t)((int32_t*)&bit31) >> 12;
    
    setRegister(rd, PC);
    PC += imm - 4;
    return 0;
}