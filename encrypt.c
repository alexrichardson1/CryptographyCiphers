#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ALPHABET_SIZE (26)

char *encrypt(const char *plain_text)
{
  int shift = 1;
  char *cipher_text = malloc(sizeof(plain_text));
  for (int i = 0; i < strlen(plain_text); i++)
  {
    cipher_text[i] = plain_text[i] + shift;
  }
  return cipher_text;
}

int main(int argc, char const *argv[])
{
  const char *plain_text = argv[1];
  char *cipher_text = encrypt(plain_text);
  printf("Encrypted text: %s\n", cipher_text);
  free(cipher_text);
  return 0;
}
