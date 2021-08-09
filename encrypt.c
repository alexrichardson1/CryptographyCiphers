#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ALPHABET_SIZE (26)
#define ALPHABET_MIN (97)
#define ALPHABET_MAX (122)
#define PLAIN_TEXT_FILE (1)
#define CIPHER_TEXT_FILE (2)
#define SHIFT (3)

char encrypt_letter(char character, const int shift)
{
  char encrypted_character = character;
  int ascii = character;
  if (ALPHABET_MIN <= ascii && ascii <= ALPHABET_MAX)
  {
    if (ascii + shift > ALPHABET_MAX)
    {
      encrypted_character = ascii + shift - ALPHABET_SIZE;
    }
    else
    {
      encrypted_character = ascii + shift;
    }
  }
  return encrypted_character;
}

void ceasar_cipher(FILE *fp_plain, FILE *fp_cipher, const int shift)
{
  char letter;
  char cipher_letter;
  while ((letter = fgetc(fp_plain)) != EOF)
  {
    cipher_letter = encrypt_letter(letter, shift);
    fputc(cipher_letter, fp_cipher);
  }
  fclose(fp_plain);
  fclose(fp_cipher);
}

int main(int argc, char const *argv[])
{
  FILE *fp_plain = fopen(argv[PLAIN_TEXT_FILE], "r");
  FILE *fp_cipher = fopen(argv[CIPHER_TEXT_FILE], "w");
  int shift = atoi(argv[SHIFT]);
  ceasar_cipher(fp_plain, fp_cipher, shift);
  return 0;
}
