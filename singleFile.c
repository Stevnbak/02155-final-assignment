#include "src/program.h"
#include "src/cpu.h"

#include <stdio.h>

// Execute single program
int main(int argc, char* argv[]) {
    if(argc < 2) return 1;
    executeProgram(argv[1], 1);
    FILE* output = fopen("output.res", "wb");
    for(uint8_t i = 0; i < 32; i++) {
        uint32_t v =  getRegisterUnsigned(i);
        fwrite(&v, 1, sizeof(uint32_t), output);
    }
    fclose(output);
}