#include <stdint.h>
#include "../cpu.h"

int executeUFormat(
    uint8_t opcode,
    uint8_t rd,
    uint32_t instruction
) {
    uint32_t imm = (instruction >> 12) << 12;
    switch(opcode){
        case 0x37: // lui
            setRegister(rd, imm);
            break;
        case 0x17: // auipc
            setRegister(rd, PC + imm - 4);
            break;
        default:
            return -1;
    }
    return 0;
}