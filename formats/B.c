#include <stdint.h>
#include "../cpu.h"
int executeBFormat(
    uint8_t rd,
    uint8_t rs1,
    uint8_t rs2,
    uint8_t funct3,
    uint8_t funct7
) {
    uint16_t bit11 = (uint16_t)(rd & 0x1) << 11;
    uint16_t bit12 = (uint16_t)(funct7 & 0x40) << 6;
    uint16_t bit1_4 = (uint16_t)(rd & 0x1e);
    uint16_t bit5_10 = (uint16_t)(funct7 & 0x3f) << 5;
    int16_t imm = ((int16_t)((*(int16_t*)&bit12) << 3) >> 3) + bit11 + bit5_10 + bit1_4;

    switch (funct3){
        case 0x0: // beq
            if (getRegister(rs1) == getRegister(rs2)){
                PC += imm - 4;
            }
            break;
        case 0x1: // bne
            if (getRegister(rs1) != getRegister(rs2)){
                PC += imm - 4;
            }
            break;
        case 0x4: // blt
            if (getRegister(rs1) < getRegister(rs2)){
                PC += imm - 4;
            }
            break;
        case 0x5: // bge
            if (getRegister(rs1) >= getRegister(rs2)){
                PC += imm - 4;
            }
            break;
        case 0x6: // bltu
            if (getRegister(rs1) < getRegister(rs2)){
                PC += imm - 4;
            }
            break;
        case 0x7: // bgeu
            if (getRegister(rs1) <= getRegister(rs2)){
                PC += imm - 4;
            }
            break;
        default:
            return -1;
    }
    return 0;
}