#include <stdint.h>
#include "../cpu.h"

int executeJFormat(
    uint8_t rd,
    uint8_t rs1,
    uint8_t rs2,
    uint8_t funct3,
    uint8_t funct7
) {
    uint32_t ordered_imm = ((uint32_t)funct7 << 13) + ((uint32_t)rs2 << 8) + ((uint32_t)rs1 << 3) + funct3;
    uint32_t immu =
        (ordered_imm & 0x80000) +
        ((ordered_imm & 0x7F800) >> 12) +
        ((ordered_imm & 0x400) >> 3) +
        ((ordered_imm & 0x3FF) << 9);
    int32_t imm = *(int32_t*)&immu;
    setRegister(rd, PC);
    PC += imm;
    return 0;
}