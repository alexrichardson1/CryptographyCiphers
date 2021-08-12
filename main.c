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

void ceasar_menu(void)
{
  FILE *fp_input = get_input_file();
  FILE *fp_output = get_output_file();
  bool encrypt = get_encrypt();
  int shift;
  printf("Enter shift key: ");
  scanf(" %d", &shift);
  ceasar_cipher(fp_input, fp_output, shift, encrypt);
  fclose(fp_input);
  fclose(fp_output);
}

void vigenere_menu(void)
{
  FILE *fp_input = get_input_file();
  FILE *fp_output = get_output_file();
  bool encrypt = get_encrypt();
  char key[20];
  printf("Enter shift key: ");
  scanf(" %s", key);
  vigenere_cipher(fp_input, fp_output, key, encrypt);
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
      ceasar_menu();
      break;
    case VIGENERE_CHOCIE:
      vigenere_menu();
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