#include <stdint.h>

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
            break;
        case 0x67: //1100111
            break;
        case 0x73: //1110011
            break;
    }
    return 0;
}