#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "file.h"
#include "cryptography.h"

#define CEASAR_CHOCIE (1)
#define VIGENERE_CHOCIE (2)
#define BRUTE_FORCE_CHOICE (3)
#define EXIT_CHOCIE (4)

bool get_encrypt(void)
{
  char encrypt_letter;
  printf("Encrypt or decrypt [e/d]: ");
  scanf(" %c", &encrypt_letter);
  return encrypt_letter == 'e';
}

void ceasar_menu(FILE *fp_input, FILE *fp_output, bool encrypt)
{
  int shift;
  printf("Enter shift key: ");
  scanf(" %d", &shift);
  ceasar_cipher(fp_input, fp_output, shift, encrypt);
}

void vigenere_menu(FILE *fp_input, FILE *fp_output, bool encrypt)
{
  char key[20];
  printf("Enter shift key: ");
  scanf(" %s", key);
  vigenere_cipher(fp_input, fp_output, key, encrypt);
}

void menu(void)
{
  int choice;
  FILE *fp_input;
  FILE *fp_output;
  bool encrypt;
  do
  {
    printf("%d. Ceasar\n", CEASAR_CHOCIE);
    printf("%d. Vigenere\n", VIGENERE_CHOCIE);
    printf("%d. Brute force\n", BRUTE_FORCE_CHOICE);
    printf("%d. Exit\n", EXIT_CHOCIE);
    printf("Enter a number: ");
    scanf("%d", &choice);

    if (choice == CEASAR_CHOCIE || choice == VIGENERE_CHOCIE)
    {
      fp_input = get_input_file();
      fp_output = get_output_file();
      encrypt = get_encrypt();
    }

    switch (choice)
    {
    case CEASAR_CHOCIE:
      ceasar_menu(fp_input, fp_output, encrypt);
      break;
    case VIGENERE_CHOCIE:
      vigenere_menu(fp_input, fp_output, encrypt);
      break;
    case BRUTE_FORCE_CHOICE:
      brute_force();
      break;
    case EXIT_CHOCIE:
      break;
    default:
      printf("Invalid number. Enter again\n");
    }
    fclose(fp_input);
    fclose(fp_output);
  } while (choice != EXIT_CHOCIE);
}

int main(int argc, char const *argv[])
{
  menu();
  return EXIT_SUCCESS;
}