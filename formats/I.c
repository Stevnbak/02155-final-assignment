#include <stdint.h>
#include <stdio.h>
#include "../cpu.h"

int executeIFormat(
    uint8_t opcode,
    uint8_t rd,
    uint8_t rs1,
    uint8_t rs2,
    uint8_t funct3,
    uint8_t funct7
) {
    uint16_t immu = (((uint16_t)funct7) << 5) + rs2;
    int16_t imm = (((int8_t)((*(int8_t*)&funct7) << 1) >> 1) << 5) + rs2;

    switch(opcode) {
        case 0x13: //0010011
            switch(funct3){
                case 0x0: // addi
                    setRegister(rd, getRegister(rs1) + imm);
                    break;
                case 0x1: // slli
                    setRegister(rd, getRegister(rs1) << rs2);
                    break;
                case 0x2: // slti
                    setRegister(rd, (getRegister(rs1) < imm) ? 1 : 0);
                    break;
                case 0x3: // sltiu
                    int32_t temp = (int32_t)imm;
                    uint32_t tempu = *((uint32_t*)(&temp));
                    setRegisterUnsigned(rd, (getRegisterUnsigned(rs1) < tempu) ? 1 : 0);
                    break;
                case 0x4: //xori
                    setRegister(rd, getRegister(rs1) ^ immu);
                    break;
                case 0x5:
                    if (funct7 == 0x00){ // srli
                        setRegisterUnsigned(rd, getRegisterUnsigned(rs1) >> rs2);
                    } else if (funct7 & 0x20) { // srai
                        setRegister(rd, getRegister(rs1) >> rs2);
                    }
                    break;
                case 0x6: // ori
                    setRegister(rd, getRegister(rs1) | immu);
                    break;
                case 0x7: // andi
                    setRegister(rd, getRegister(rs1) & immu);
                    break;
                default:
                    return -1;
            }
            break;
        case 0x3:  //0000011
            switch(funct3) {
                case 0x0: // lb
                    setRegister(rd, *((int8_t*)&memory[getRegisterUnsigned(rs1) + imm]));
                    break;
                case 0x1: // lh
                    setRegister(rd, *((int16_t*)&memory[getRegisterUnsigned(rs1) + imm]));
                    break;
                case 0x2: // lw
                    setRegister(rd, *((int32_t*)&memory[getRegisterUnsigned(rs1) + imm]));
                    break;
                case 0x4: // lbu
                    setRegister(rd, *((uint8_t*)&memory[getRegisterUnsigned(rs1) + imm]));
                    break;
                case 0x5: // lhu
                    setRegister(rd, *((uint16_t*)&memory[getRegisterUnsigned(rs1) + imm]));
                    break;
                default:
                    return -1;
            }
            break;
        case 0x67: //1100111
            if(funct3 != 0) return -1;
            setRegister(rd, PC);
            PC = getRegister(rs1) + imm;
            break;
        case 0x73: //1110011
            if (imm != 0) return -1;
            uint32_t a7 = getRegisterUnsigned(17);
            uint32_t a0 = getRegisterUnsigned(10);
            switch(a7) {
                case 1: // print_int
                    printf("%d", *((int32_t*)&a0));
                    break;
                case 2: // print_float
                    printf("%f", *((float*)&a0));
                    break;
                case 4: // print_string
                    while(memory[a0] != 0) {
                        printf("%c", memory[a0++]);
                    }
                    break;
                case 10: // exit
                    running = 0;
                    break;
                case 11: // print_char
                    printf("%c", a0);
                    break;
                case 34: // print_hex
                    printf("%#x", a0);
                    break;
                case 35: // print_bin
                    for(uint8_t i = 0; i < 32; i++) {
                        printf("%u", a0 & 0x80000000);
                        a0 = a0 << 1;
                    }
                    break;
                case 36: // print_unsigned
                    printf("%u", a0);
                    break;
                case 93: // exit
                    running = 0;
                    returnCode = a0;
                    break;
                default:
                    return -1;
            }
            break;
        default:
            return -1;
    }
    return 0;
}