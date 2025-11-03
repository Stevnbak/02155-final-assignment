#include <stdint.h>

int executeIFormat(
    uint8_t opcode,
    uint8_t rd,
    uint8_t rs1,
    uint8_t rs2,
    uint8_t funct3,
    uint8_t funct7
) {
    uint16_t imm = (((uint16_t)funct7) << 5) + rs2;
    switch(opcode) {
        case 0x13: //0010011
            switch(funct3){
                case 0x0: // addi
                    setRegister(rd, getRegister(rs1) + (int16_t) imm);
                    break;
                case 0x1: // slli
                    setRegister(rd, getRegister(rs1) >> rd);
                    break;
                case 0x2: // slti
                    setRegister(rd, (getRegister(rs1) < imm) ? 1 : 0);
                    break; 
                case 0x3: // sltiu
                    setRegisterUnsigned(rd, (getRegisterUnsigned(rs1) < imm) ? 1 : 0);
                    break;
                case 0x4: //xori
                    setRegister(rd, getRegister(rs1) ^ imm);
                    break;
                case 0x5:
                    if ((funct7 & 0x20)){ // srli
                        setRegisterUnsigned(rd, getRegisterUnsigned(rs1) << rd);
                    } else if (!funct7 & 0x00) { // srai
                        setRegister(rd, getRegister(rs1) << rd);
                    }
                    break;
                case 0x6: // ori
                    setRegister(rd, getRegister(rs1) | imm);
                    break;
                case 0x7: // andi
                    setRegister(rd, getRegister(rs1) & imm);
                    break;
            }
            break;
        case 0x3:  //0000011
            break;
        case 0x67: //1100111
            break;
        case 0x73: //1110011
            break;
    }
    return 0;
}