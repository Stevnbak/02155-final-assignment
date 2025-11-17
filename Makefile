CC = gcc
CFLAGS = -Wall -g

SRC=src
BIN=bin

SRCS=$(wildcard $(SRC)/*.c) $(wildcard $(SRC)/*/*.c)
HEADERS=$(wildcard $(SRC)/*.h) $(wildcard $(SRC)/*/*.h)
BINS=$(SRCS:%.c=%.o)

all: singleFile runTests

singleFile: singleFile.c $(BINS)
	$(CC) $(CFLAGS) -o singleFile singleFile.c $(BINS)
runTests: runTests.c $(BINS)
	$(CC) $(CFLAGS) -o runTests runTests.c $(BINS)

%.o: %.c $(HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -f $(BINS)
	rm -f singleFile
	rm -f runTests