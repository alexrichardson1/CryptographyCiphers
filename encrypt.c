#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#define ALPHABET_SIZE (26)
#define ALPHABET_LOWER_MIN (97)
#define ALPHABET_LOWER_MAX (122)
#define ALPHABET_UPPER_MIN (65)
#define ALPHABET_UPPER_MAX (90)

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
  bool isLower = islower(character);
  int alphabet_min = isLower ? ALPHABET_LOWER_MIN : ALPHABET_UPPER_MIN;
  int alphabet_max = isLower ? ALPHABET_UPPER_MIN : ALPHABET_UPPER_MAX;
  if (alphabet_min <= ascii && ascii <= alphabet_max)
  {
    alphabet_number = (ascii - alphabet_min + shift) % ALPHABET_SIZE;
    encrypted_character = alphabet_number + alphabet_min;
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

void vigenere_cipher(FILE *fp_plain, FILE *fp_cipher, const char *key)
{
  char letter;
  char cipher_letter;
  int shift = key[0];
  int counter = 0;
  int length = strlen(key);

  while ((letter = fgetc(fp_plain)) != EOF)
  {
    shift = tolower(key[counter++ % length]) - ALPHABET_LOWER_MIN + 1;
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

void ceasar(FILE *fp_plain, FILE *fp_cipher)
{
  int shift;
  printf("Enter shift key: ");
  scanf(" %d", &shift);
  ceasar_cipher(fp_plain, fp_cipher, shift);
}

void vigenere(FILE *fp_plain, FILE *fp_cipher)
{
  char key[20];
  printf("Enter shift key: ");
  scanf(" %s", key);
  vigenere_cipher(fp_plain, fp_cipher, key);
}

void cryptography_menu(int choice)
{
  printf("Enter plain text file name: ");
  FILE *fp_plain = get_file("r");
  printf("Enter new file name: ");
  FILE *fp_cipher = get_file("w");
  void (*func)(FILE *, FILE *) = (choice == 1) ? ceasar : vigenere;
  func(fp_plain, fp_cipher);
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
    case 2:
      cryptography_menu(choice);
      break;
    case 3:
      break;
    default:
      printf("Invalid number. Enter again\n");
    }
  } while (choice != 3);

  return 0;
}
