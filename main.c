#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "file.h"
#include "cryptography.h"

#define CEASAR_CHOCIE (1)
#define VIGENERE_CHOCIE (2)
#define BRUTE_FORCE_CHOICE (3)
#define EXIT_CHOCIE (4)

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