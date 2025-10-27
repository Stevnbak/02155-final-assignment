CC = gcc
CFLAGS = -Wall -O2

all: isaSim

isaSim: main.c
	$(CC) $(CFLAGS) -o isaSim main.c
clean: rm -f isaSim