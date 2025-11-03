#include <stdint.h>
#include "../cpu.h"

int executeIFormat(
    uint8_t opcode,
    uint8_t rd,
    uint8_t rs1,
    uint8_t rs2,
    uint8_t funct3,
    uint8_t funct7
) {
    switch(opcode) {
        case 0x13: //0010011
            break;
        case 0x3:  //0000011
            switch(funct3) {
                case 0x0: // lb
                    setRegister(rd, *((int8_t*)&dataMemory[getRegister(rs1) + imm]));
                case 0x1: // lh
                    setRegister(rd, *((int16_t*)&dataMemory[getRegister(rs1) + imm]));
                case 0x2: // lw
                    setRegister(rd, *((int32_t*)&dataMemory[getRegister(rs1) + imm]));
                case 0x4: // lbu
                    setRegister(rd, *((uint8_t*)&dataMemory[getRegister(rs1) + imm]));
                case 0x5: // lhu
                    setRegister(rd, *((uint16_t*)&dataMemory[getRegister(rs1) + imm]));
                default:
                    return -1;
            }
            break;
        case 0x67: //1100111
            break;
        case 0x73: //1110011
            break;
    }
    return 0;
}