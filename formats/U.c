#include <stdint.h>
#include "../cpu.h"

int executeUFormat(
    uint8_t opcode,
    uint8_t rd,
    uint8_t rs1,
    uint8_t rs2,
    uint8_t funct3,
    uint8_t funct7
) {
    uint32_t imm = (((uint32_t)funct7) << 13) + (((uint32_t)rs2) << 8) + (((uint32_t)rs1) << 3) + (((uint32_t)funct3));
    switch(opcode){
        case 0x37: 
            setRegister(rd, (imm << 12));
            break;
        case 0x17: 
            PC += (imm << 12);
            break;
        default:
            return -1;
    }
    return 0;
}