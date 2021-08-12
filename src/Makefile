CC=gcc
CFLAGS=-g -Wall -Werror


main: main.c cryptography.o file.o
		$(CC) $(CFLAGS) main.c cryptography.o file.o -o main

cryptography.o: cryptography.c file.o
		$(CC) $(CFLAGS) -c cryptography.c

file.o: file.c file.h
		$(CC) $(CFLAGS) -c file.c


.PHONY: clean

clean:
		rm -f main
		rm -f *.o
