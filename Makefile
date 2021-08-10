CC=gcc
CFLAGS=-g -Wall -Werror

encrypt: cryptography.c
		$(CC) $(CFLAGS) cryptography.c -o cryptography

.PHONY: clean

clean:
		rm cryptography
