#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ALPHABET_SIZE (26)
#define ALPHABET_MIN (97)
#define ALPHABET_MAX (122)
#define PLAIN_TEXT_FILE (1)
#define CIPHER_TEXT_FILE (2)
#define SHIFT (3)

void check_ptr(const void *ptr)
{
  if (!ptr)
  {
    fprintf(stderr, "Error: NULL pointer\n");
    exit(EXIT_FAILURE);
  }
}

char shift_letter(char character, const int shift)
{
  char encrypted_character = character;
  int ascii = character;
  int alphabet_number;
  if (ALPHABET_MIN <= ascii && ascii <= ALPHABET_MAX)
  {
    alphabet_number = (ascii - ALPHABET_MIN + shift) % ALPHABET_SIZE;
    encrypted_character = alphabet_number + ALPHABET_MIN;
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

FILE *get_file(const char *file_mode)
{
  char file_name[20];
  scanf(" %s", file_name);
  FILE *fp = fopen(file_name, file_mode);
  check_ptr(fp);
  return fp;
}

void ceasar_menu()
{
  int shift;

  printf("Enter plain text file name: ");
  FILE *fp_plain = get_file("r");

  printf("Enter new file name: ");
  FILE *fp_cipher = get_file("w");

  printf("Enter shift key: ");
  scanf(" %d", &shift);

  ceasar_cipher(fp_plain, fp_cipher, shift);
}

void vigenere_menu()
{
  char key[20];

  printf("Enter plain text file name: ");
  FILE *fp_plain = get_file("r");

  printf("Enter new file name: ");
  FILE *fp_cipher = get_file("w");

  printf("Enter shift key: ");
  scanf(" %s", key);

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
