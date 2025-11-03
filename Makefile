CC = gcc
CFLAGS = -Wall -O2 -g

all: isaSim

isaSim: main.c formats/B.c formats/I.c formats/J.c formats/R.c formats/S.c formats/U.c cpu.c
	$(CC) $(CFLAGS) -o isaSim main.c formats/B.c formats/I.c formats/J.c formats/R.c formats/S.c formats/U.c cpu.c
clean:
	rm -f isaSim