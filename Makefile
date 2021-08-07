CC=gcc
CFLAGS=-g -Wall -Werror

encrypt: encrypt.c
		$(CC) $(CFLAGS) encrypt.c -o encrypt

.PHONY: clean

clean:
		rm encrypt
