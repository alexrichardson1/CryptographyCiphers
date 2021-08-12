#ifndef CRYPTOGRAPHY_H
#define CRYPTOGRAPHY_H

#include <stdio.h>
#include <stdbool.h>

extern void ceasar_cipher(FILE *fp_input, FILE *fp_output, const int shift, bool encrypt);
extern void vigenere_cipher(FILE *fp_input, FILE *fp_output, const char *key, bool encrypt);
extern void brute_force(void);

#endif