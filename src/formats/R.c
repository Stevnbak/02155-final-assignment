#include <stdint.h>
#include "../cpu.h"

int executeRFormat(
    uint8_t rd,
    uint8_t rs1,
    uint8_t rs2,
    uint8_t funct3,
    uint8_t funct7
) {
    switch (funct3) {
        case 0x0: 
            if (funct7 == 0x00) { // ADD
                setRegister(rd, getRegister(rs1) + getRegister(rs2));   
            } else if (funct7 == 0x20) { // SUB
                setRegister(rd, getRegister(rs1) - getRegister(rs2));
            } 
            break;
        case 0x1: // sll
            setRegister(rd, getRegister(rs1) << (getRegister(rs2))); 
            break;
        case 0x2: // slt 
            setRegister(rd, (getRegister(rs1) < getRegister(rs2) ? 1 : 0));
            break;
        case 0x3: // sltu
            setRegisterUnsigned(rd, (getRegisterUnsigned(rs1) < getRegisterUnsigned(rs2) ? 1 : 0));
            break;
        case 0x4: // xor
            setRegister(rd, getRegister(rs1) ^ getRegister(rs2));
            break;
        case 0x5: 
            if (funct7 == 0x00){ // srl
                setRegisterUnsigned(rd, getRegisterUnsigned(rs1) >> getRegisterUnsigned(rs2));
            }
            else if (funct7 == 0x20){ // sra
                setRegister(rd, getRegister(rs1) >> getRegister(rs2));
            }
            break;
        case 0x6: // or
            setRegister(rd, getRegister(rs1) | getRegister(rs2));
            break;
        case 0x7: // and
            setRegister(rd, getRegister(rs1) & getRegister(rs2));
            break;
        default:
            return -1;     
    }
    return 0;
}
