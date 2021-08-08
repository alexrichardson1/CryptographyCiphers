#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ALPHABET_SIZE (26)
#define ALPHABET_MIN (97)
#define ALPHABET_MAX (122)

char encrypt_letter(char character, const int shift)
{
  char encrypted_character;
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
  else
  {
    encrypted_character = character;
  }
  return encrypted_character;
}

int main(int argc, char const *argv[])
{
  FILE *fp_plain = fopen(argv[1], "r");
  FILE *fp_cipher = fopen(argv[2], "w");
  int shift = atoi(argv[3]);

  char letter;
  char cipher_letter;

  while ((letter = fgetc(fp_plain)) != EOF)
  {
    cipher_letter = encrypt_letter(letter, shift);
    fputc(cipher_letter, fp_cipher);
  }

  fclose(fp_plain);
  fclose(fp_cipher);
  return 0;
}
