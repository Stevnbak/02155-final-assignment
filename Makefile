CC = gcc
CFLAGS = -Wall -O2

all: isaSim

isaSim: main.c
	$(CC) $(CFLAGS) -o isaSim main.c formats/B.c formats/I.c formats/J.c formats/R.c formats/S.c formats/U.c memory.c
clean: rm -f isaSim