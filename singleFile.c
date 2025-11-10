#include "program.c"

// Execute single program
int main(int argc, char* argv[]) {
    if(argc < 2) return 1;
    executeProgram(argv[1], 1);
    reset();
}