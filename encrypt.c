#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define ALPHABET_SIZE (26)
#define ALPHABET_MIN (97)
#define ALPHABET_MAX (122)

void encrypt(char *text, const int shift)
{
  for (int i = 0; i < strlen(text); i++)
  {
    int ascii = text[i];
    if (ALPHABET_MIN <= ascii && ascii <= ALPHABET_MAX)
    {
      if (ascii + shift > ALPHABET_MAX)
      {
        text[i] = ascii + shift - ALPHABET_SIZE;
      }
      else
      {
        text[i] = text[i] + shift;
      }
    }
    else
    {
      text[i] = text[i];
    }
  }
}

int main(int argc, char const *argv[])
{
  FILE *fp = fopen(argv[1], "r");
  int shift = atoi(argv[2]);

  fseek(fp, 0, SEEK_END);
  long size = ftell(fp);
  rewind(fp);
  char *fcontent = malloc(size);
  fread(fcontent, 1, size, fp);
  fclose(fp);
  fp = fopen(argv[3], "w");
  encrypt(fcontent, shift);
  fwrite(fcontent, 1, size, fp);
  fclose(fp);
  free(fcontent);
  return 0;
}
