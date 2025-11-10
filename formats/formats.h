#include <stdint.h>

int executeRFormat(
    uint8_t rd,
    uint8_t rs1,
    uint8_t rs2,
    uint8_t funct3,
    uint8_t funct7
);

int executeIFormat(
    uint8_t opcode,
    uint8_t rd,
    uint8_t rs1,
    uint8_t rs2,
    uint8_t funct3,
    uint8_t funct7
);

int executeBFormat(
    uint8_t rd,
    uint8_t rs1,
    uint8_t rs2,
    uint8_t funct3,
    uint8_t funct7
);

int executeJFormat(
    uint8_t rd,
    uint8_t rs1,
    uint8_t rs2,
    uint8_t funct3,
    uint8_t funct7
);

int executeUFormat(
    uint8_t opcode,
    uint8_t rd,
    uint32_t instruction
);

int executeSFormat(
    uint8_t rd,
    uint8_t rs1,
    uint8_t rs2,
    uint8_t funct3,
    uint8_t funct7
);