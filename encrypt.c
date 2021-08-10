#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ALPHABET_SIZE (26)
#define ALPHABET_MIN (97)
#define ALPHABET_MAX (122)
#define PLAIN_TEXT_FILE (1)
#define CIPHER_TEXT_FILE (2)
#define SHIFT (3)

char shift_letter(char character, const int shift)
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
    cipher_letter = shift_letter(letter, shift);
    fputc(cipher_letter, fp_cipher);
  }
  fclose(fp_plain);
  fclose(fp_cipher);
}

void vigenere(FILE *fp_plain, FILE *fp_cipher, const char *key)
{
  char letter;
  char cipher_letter;
  int shift = key[0];
  int counter = 0;
  int length = strlen(key);

  while ((letter = fgetc(fp_plain)) != EOF)
  {
    shift = key[counter++ % length] - ALPHABET_MIN + 1;
    cipher_letter = shift_letter(letter, shift);
    fputc(cipher_letter, fp_cipher);
  }
  fclose(fp_plain);
  fclose(fp_cipher);
}

void ceasar_menu()
{
  char plain_file[20];
  char cipher_file[20];
  int shift;

  printf("Enter plain text file name: ");
  scanf(" %s", plain_file);

  printf("Enter new file name: ");
  scanf(" %s", cipher_file);

  printf("Enter shift key: ");
  scanf(" %d", &shift);

  FILE *fp_plain = fopen(plain_file, "r");
  FILE *fp_cipher = fopen(cipher_file, "w");
  ceasar_cipher(fp_plain, fp_cipher, shift);
}

void vigenere_menu()
{
  char plain_file[20];
  char cipher_file[20];
  char key[20];

  printf("Enter plain text file name: ");
  scanf(" %s", plain_file);

  printf("Enter new file name: ");
  scanf(" %s", cipher_file);

  printf("Enter shift key: ");
  scanf(" %s", key);

  FILE *fp_plain = fopen(plain_file, "r");
  FILE *fp_cipher = fopen(cipher_file, "w");
  vigenere(fp_plain, fp_cipher, key);
}

int main(int argc, char const *argv[])
{
  int choice;
  do
  {
    printf("1. Ceasar\n");
    printf("2. Vigenere\n");
    printf("3. Exit\n");
    printf("Enter a number: ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
      ceasar_menu();
      break;
    case 2:
      vigenere_menu();
      break;
    case 3:
      break;
    default:
      printf("Invalid number. Enter again\n");
    }
  } while (choice != 3);

  return 0;
}
