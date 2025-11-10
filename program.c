#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "cpu.h"
#include "formats/formats.h"

typedef enum Type {
    R,
    I,
    S,
    B,
    U,
    J
} Type;

int decodeAndExecuteInstruction(uint32_t instruction, int print) {
    // Decode info
    uint8_t opcode = instruction & 0x7f;
    uint8_t rd = (instruction >> 7) & 0x1f;
    uint8_t rs1 = (instruction >> 15) & 0x1f;
    uint8_t rs2 = (instruction >> 20) & 0x1f;
    uint8_t funct3 = (instruction >> 12) & 0x7;
    uint8_t funct7 = (instruction >> 25) & 0x7f;

    if(print) printf("PC=%u:\tInstruction=%#04x\tOpcode=%#04x;rd=%#04x;rs1=%#04x;rs2=%#04x;funct3=%#04x;funct7=%#04x\n", PC, instruction, opcode, rd, rs1, rs2, funct3, funct7);

    // Get instruction format type
    Type type;
    if(opcode == 0x33) type = R;
    else if(opcode == 0x13 || opcode == 0x3 || opcode == 0x67 || opcode == 0x73) type = I;
    else if(opcode == 0x23) type = S;
    else if(opcode == 0x63) type = B;
    else if(opcode == 0x6f) type = J;
    else if(opcode == 0x37 || opcode == 0x17) type = U;
    else return -1;

    // Execute instructions
    switch(type) {
        case B:
            return executeBFormat(rd, rs1, rs2, funct3, funct7);
        case I:
            return executeIFormat(opcode, rd, rs1, rs2, funct3, funct7);
        case J:
            return executeJFormat(rd, instruction);
        case R:
            return executeRFormat(rd, rs1, rs2, funct3, funct7);
        case S:
            return executeSFormat(rd, rs1, rs2, funct3, funct7);
        case U:
            return executeUFormat(opcode, rd, instruction);
        default:
            return -1;
    }
}

void printRegisters() {
    for(uint8_t r = 0; r < 32; r++) {
        uint32_t u = getRegisterUnsigned(r);
        int32_t i = getRegister(r);
        printf("x%u:\tUnsigned=%u\tSigned=%i\tHex=%#x\n", r, u, i, u);
    }
}

int executeProgram(char* filename, int print) {
    // Open binary file
    if(print) printf("Trying to open \"%s\"\n", filename);
    FILE* file = fopen(filename, "r");
    if(file == NULL) {
        printf("Failed to open file\n");
        return 1;
    }
    if(print) printf("Opened file\n");

    // Read binary file
    uint32_t instruction;
    uint16_t i = 0;
    while(1) {
        if(fread(&instruction, 4, 1, file) < 1) break;
        instructionMemory[i++] = instruction;
    };

    // Close file again
    fclose(file);

    // Execute program
    PC = 0;
    running = 1;
    while(running) {
        instruction = instructionMemory[PC / 4];
        PC += 4;
        if(decodeAndExecuteInstruction(instruction, print) < 0) {
            if(print) printf("Instruction at PC %u failed!\n", PC);
            break;
        }
        if(print) printRegisters();
    }

    // Print register contents
    if(print) {
        printf("Final registers:\n");
        printRegisters();
    }

    return returnCode;
}

void reset() {
    for(int i = 0; i < 32; i++) setRegister(i, 0);
}