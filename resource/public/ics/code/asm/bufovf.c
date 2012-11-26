/* Example problem illustrating buffer overflow */

#include <stdio.h>
#include <stdlib.h>

/* Use own versions of strlen and strcpy */
size_t strlen(const char *s)
{
  int len = 0;
  while (*(s++))
    len++;
  return len;
}

char *strcpy(char *dest, const char *src)
{
  char *result = dest;
  char c;
  do {
    c = *(src++);
    *(dest++) = c;
  } while (c);
  return result;
}

/* $begin bufovf-raw-c */
/* This is very low quality code.
   It is intended to illustrate bad programming practices.
   See Practice Problem SLASHrefLBRACKprob:asm:bufovfRBRACK. */
char *getline()
{
    char buf[8];
    char *result;
    gets(buf);
    result = malloc(strlen(buf));
    strcpy(result, buf);
    return(result);
}
/* $end bufovf-raw-c */

int main(int argc, char *argv[])
{
   printf("Input>");
   puts(getline());
   return 0;
}
