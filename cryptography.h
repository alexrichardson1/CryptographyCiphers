#ifndef CRYPTOGRAPHY_H
#define CRYPTOGRAPHY_H

#include <stdio.h>
#include <stdbool.h>

extern void ceasar(FILE *fp_input, FILE *fp_output, bool encrypt);
extern void vigenere(FILE *fp_input, FILE *fp_output, bool encrypt);
extern void brute_force(void);

#endif