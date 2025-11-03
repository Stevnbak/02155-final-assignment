#include <stdint.h>
#include "../cpu.h"

int executeSFormat(
    uint8_t rd,
    uint8_t rs1,
    uint8_t rs2,
    uint8_t funct3,
    uint8_t funct7
) {
    uint16_t imm = ((uint16_t)funct7 << 5) + rd;
    switch(funct3) {
        case 0x0:
            *(uint8_t*)(&dataMemory[getRegister(rs1) + imm]) = (uint8_t)getRegisterUnsigned(rs2);
            break;
        case 0x1:
            *(uint16_t*)(&dataMemory[getRegister(rs1) + imm]) = (uint16_t)getRegisterUnsigned(rs2);
            break;
        case 0x2:
            *(uint32_t*)(&dataMemory[getRegister(rs1) + imm]) = (uint32_t)getRegisterUnsigned(rs2);
            break;
        default: 
            return -1;
    }
    return 0;
}