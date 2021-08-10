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
#define CEASAR_CHOCIE (1)
#define VIGENERE_CHOCIE (2)
#define EXIT_CHOCIE (3)

void check_ptr(const void *ptr)
{
  if (!ptr)
  {
    fprintf(stderr, "Error: NULL pointer\n");
    exit(EXIT_FAILURE);
  }
}

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
  fclose(fp_input);
  fclose(fp_output);
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
  fclose(fp_input);
  fclose(fp_output);
}

FILE *get_file(const char *file_mode)
{
  char file_name[20];
  scanf(" %s", file_name);
  FILE *fp = fopen(file_name, file_mode);
  check_ptr(fp);
  return fp;
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

void cryptography_menu(int choice)
{
  char encrypt;
  printf("Encrypt or decrypt [e/d]: ");
  scanf(" %c", &encrypt);
  printf("Enter input file name: ");
  FILE *fp_input = get_file("r");
  printf("Enter ouput file name: ");
  FILE *fp_output = get_file("w");
  void (*func)(FILE *, FILE *, bool) = (choice == 1) ? ceasar : vigenere;
  func(fp_input, fp_output, encrypt == 'e');
}

int main(int argc, char const *argv[])
{
  int choice;
  do
  {
    printf("%d. Ceasar\n", CEASAR_CHOCIE);
    printf("%d. Vigenere\n", VIGENERE_CHOCIE);
    printf("%d. Exit\n", EXIT_CHOCIE);
    printf("Enter a number: ");
    scanf("%d", &choice);
    switch (choice)
    {
    case CEASAR_CHOCIE:
    case VIGENERE_CHOCIE:
      cryptography_menu(choice);
      break;
    case EXIT_CHOCIE:
      break;
    default:
      printf("Invalid number. Enter again\n");
    }
  } while (choice != EXIT_CHOCIE);

  return EXIT_SUCCESS;
}
