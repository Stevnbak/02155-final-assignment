#include <stdint.h>
#include "../cpu.h"
int executeBFormat(
    uint8_t rd,
    uint8_t rs1,
    uint8_t rs2,
    uint8_t funct3,
    uint8_t funct7
) {
    
    
    uint16_t imm_temp = (((uint16_t) funct7 << 7) + rd) << 1;
    uint16_t imm = (imm_temp & 0x1000 >> 1) + ((imm_temp & 0x7E0)) + ((imm_temp & 0x3E)) + ((imm_temp & 0x800) >> 11);
    switch (funct3){
        case 0x0: // beq
            if (getRegister(rs1) == getRegister(rs2)){
                PC += imm;
            }
            break;
        case 0x1: // bne
            if (getRegister(rs1) != getRegister(rs2)){
                PC += imm;
            }
            break;
        case 0x4: // blt
            if (getRegister(rs1) < getRegister(rs2)){
                PC += imm;
            }
            break;
        case 0x5: // bge
            if (getRegister(rs1) >= getRegister(rs2)){
                PC += imm;
            }
            break;
        case 0x6: // bltu
            if (getRegister(rs1) < getRegister(rs2)){
                PC += imm;
            }
            break;
        case 0x7: // bgeu
            if (getRegister(rs1) <= getRegister(rs2)){
                PC += imm;
            }
            break;
        default:
            return -1;
    }
    return 0;
}