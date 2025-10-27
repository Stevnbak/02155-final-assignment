#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "memory.h"

#include "B.c";
#include "I.c";
#include "J.c";
#include "R.c";
#include "S.c";
#include "U.c";

typedef enum Type {
    R,
    I,
    S,
    B,
    U,
    J
} Type;

int decodeAndExecuteInstruction(uint32_t instruction) {
    // Decode info
    uint8_t opcode = instruction & 0x7f;
    uint8_t rd = (instruction >> 7) & 0x1f;
    uint8_t rs1 = (instruction >> 15) & 0x1f;
    uint8_t rs2 = (instruction >> 20) & 0x1f;
    uint8_t funct3 = (instruction >> 12) & 0x1f;
    uint8_t funct7 = (instruction >> 25) & 0x1f;

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
            executeBFormat(rd, rs1, rs2, funct3, funct7); 
            break;
        case I: 
            executeIFormat(opcode, rd, rs1, rs2, funct3, funct7); 
            break;
        case J: 
            executeJFormat(rd, rs1, rs2, funct3, funct7); 
            break;
        case R: 
            executeRFormat(rd, rs1, rs2, funct3, funct7); 
            break;
        case S: 
            executeSFormat(rd, rs1, rs2, funct3, funct7); 
            break;
        case U: 
            executeUFormat(opcode, rd, rs1, rs2, funct3, funct7); 
            break;
    }
}

int main(int argc, char* argv[]) {
    // Open binary file
    if(argc < 2) return 1;
    char* filename = argv[1];
    FILE* file = fopen(filename, "r");
    if(file == NULL) {
        printf("Failed to open file\n");
        return 1;
    }
    printf("Opened file\n");

    // Read binary file
    uint32_t instruction;
    uint16_t i = 0;
    while(1) {
        if(fread(&instruction, 4, 1, file) < 1) break;
        instructionMemory[i++] = instruction;
    };

    // Execute program
    while(running) {
        if(decodeAndExecuteInstruction(instructionMemory[PC / 4]) < 0) {
            printf("Instruction failed!\n");
            break;
        }
    }

    // Close file again
    fclose(file);
}