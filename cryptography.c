#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "file.h"

#define ALPHABET_SIZE (26)
#define ALPHABET_LOWER_MIN (97)
#define ALPHABET_LOWER_MAX (122)
#define ALPHABET_UPPER_MIN (65)
#define ALPHABET_UPPER_MAX (90)
#define CEASAR_CHOCIE (1)
#define VIGENERE_CHOCIE (2)
#define BRUTE_FORCE_CHOICE (3)
#define EXIT_CHOCIE (4)

char shift_letter(char character, int shift, bool encrypt)
{
  char encrypted_character = character;
  int ascii = character;
  int alphabet_number;
  bool isLower = islower(character);
  shift = encrypt ? shift : (ALPHABET_SIZE - shift);
  int alphabet_min = isLower ? ALPHABET_LOWER_MIN : ALPHABET_UPPER_MIN;
  int alphabet_max = isLower ? ALPHABET_LOWER_MAX : ALPHABET_UPPER_MAX;
  if (alphabet_min <= ascii && ascii <= alphabet_max)
  {
    alphabet_number = (ascii - alphabet_min + shift) % ALPHABET_SIZE;
    encrypted_character = alphabet_number + alphabet_min;
  }
  return encrypted_character;
}

void ceasar_cipher(FILE *fp_input, FILE *fp_output, const int shift, bool encrypt)
{
  char letter;
  char cipher_letter;
  while ((letter = fgetc(fp_input)) != EOF)
  {
    cipher_letter = shift_letter(letter, shift, encrypt);
    fputc(cipher_letter, fp_output);
  }
  rewind(fp_input);
}

void vigenere_cipher(FILE *fp_input, FILE *fp_output, const char *key, bool encrypt)
{
  char letter;
  char cipher_letter;
  int shift = key[0];
  int counter = 0;
  int length = strlen(key);

  while ((letter = fgetc(fp_input)) != EOF)
  {
    shift = tolower(key[counter++ % length]) - ALPHABET_LOWER_MIN + 1;
    cipher_letter = shift_letter(letter, shift, encrypt);
    fputc(cipher_letter, fp_output);
  }
}

void ceasar(FILE *fp_input, FILE *fp_output, bool encrypt)
{
  int shift;
  printf("Enter shift key: ");
  scanf(" %d", &shift);
  ceasar_cipher(fp_input, fp_output, shift, encrypt);
}

void vigenere(FILE *fp_input, FILE *fp_output, bool encrypt)
{
  char key[20];
  printf("Enter shift key: ");
  scanf(" %s", key);
  vigenere_cipher(fp_input, fp_output, key, encrypt);
}

void brute_force(void)
{
  FILE *fp_input = get_input_file();
  FILE *fp_output = get_output_file();
  char shift[12];

  for (int i = 1; i < ALPHABET_SIZE; i++)
  {
    fputs("\n\nShift key: ", fp_output);
    sprintf(shift, "%d", i);
    fputs(shift, fp_output);
    fputs("\n\n", fp_output);
    ceasar_cipher(fp_input, fp_output, i, false);
  }
  fclose(fp_input);
  fclose(fp_output);
}

void cryptography_menu(int choice)
{
  char encrypt;
  printf("Encrypt or decrypt [e/d]: ");
  scanf(" %c", &encrypt);
  FILE *fp_input = get_input_file();
  FILE *fp_output = get_output_file();
  void (*func)(FILE *, FILE *, bool) = (choice == CEASAR_CHOCIE) ? ceasar : vigenere;
  func(fp_input, fp_output, encrypt == 'e');
  fclose(fp_input);
  fclose(fp_output);
}

void menu(void)
{
  int choice;
  do
  {
    printf("%d. Ceasar\n", CEASAR_CHOCIE);
    printf("%d. Vigenere\n", VIGENERE_CHOCIE);
    printf("%d. Brute force\n", BRUTE_FORCE_CHOICE);
    printf("%d. Exit\n", EXIT_CHOCIE);
    printf("Enter a number: ");
    scanf("%d", &choice);
    switch (choice)
    {
    case CEASAR_CHOCIE:
    case VIGENERE_CHOCIE:
      cryptography_menu(choice);
      break;
    case BRUTE_FORCE_CHOICE:
      brute_force();
      break;
    case EXIT_CHOCIE:
      break;
    default:
      printf("Invalid number. Enter again\n");
    }
  } while (choice != EXIT_CHOCIE);
}

int main(int argc, char const *argv[])
{
  menu();
  return EXIT_SUCCESS;
}
