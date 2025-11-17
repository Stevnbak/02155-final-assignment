To compile the Risc-5 Simulator run the following snippet of code:

```
 make clean ; make
```
and then run either a single file, where the output is the register after each instruction, or test run on multiple files in the same folder.

To test run multiple files, a .bin and a .res is needed for each test file, where .bin is the binary code for the assembly code you want to run, and .res contains the final register the assembly should output.
```
 ./runTests <path/to/directory/containing/test_files/>
```

To run a single file, just a .bin file is needed, where .bin is the binary code for the assembly code you want to run.
```
 ./singleFile <path/to/binary_test_file>
```
Link for sheet of func3/func7/opcode for each instruction: https://www.cs.sfu.ca/~ashriram/Courses/CS295/assets/notebooks/RISCV/RISCV_CARD.pdf

Github for project: https://github.com/schoeberl/cae-lab/tree/master/finasgmt

