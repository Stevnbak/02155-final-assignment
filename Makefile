CC = gcc
CFLAGS = -Wall -g

all: isaSim runTests

isaSim: singleFile.c program.c formats/B.c formats/I.c formats/J.c formats/R.c formats/S.c formats/U.c cpu.c
	$(CC) $(CFLAGS) -o isaSim singleFile.c formats/B.c formats/I.c formats/J.c formats/R.c formats/S.c formats/U.c cpu.c
runTests: allTests.c program.c formats/B.c formats/I.c formats/J.c formats/R.c formats/S.c formats/U.c cpu.c
	$(CC) $(CFLAGS) -o runTests allTests.c formats/B.c formats/I.c formats/J.c formats/R.c formats/S.c formats/U.c cpu.c -w
clean:
	rm -f isaSim