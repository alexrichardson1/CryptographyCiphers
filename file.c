#include <stdio.h>
#include <stdlib.h>

static void check_ptr(const void *ptr)
{
  if (!ptr)
  {
    fprintf(stderr, "Error: NULL pointer\n");
    exit(EXIT_FAILURE);
  }
}

static FILE *get_file(const char *file_mode)
{
  char file_name[20];
  scanf(" %s", file_name);
  FILE *fp = fopen(file_name, file_mode);
  check_ptr(fp);
  return fp;
}

FILE *get_input_file(void)
{
  printf("Enter input file name: ");
  return get_file("r");
}

FILE *get_output_file(void)
{
  printf("Enter ouput file name: ");
  return get_file("w");
}