CC=gcc
CFLAGS=-g -Wall -Werror

cryptography: cryptography.c file.o
		$(CC) $(CFLAGS) cryptography.c file.o -o cryptography

file.o: file.c file.h
		$(CC) $(CFLAGS) -c file.c


.PHONY: clean

clean:
		rm -f cryptography 
		rm *.o
