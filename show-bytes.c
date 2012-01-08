#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, int len) {
  int i;
  for (i = 0; i < len; i++)
    printf(" %.2x", start[i]);
  printf("\n");
}

void show_int(int x) {
  show_bytes((byte_pointer) &x, sizeof(int));
}

void show_float(float x) {
  show_bytes((byte_pointer) &x, sizeof(float));
}

void show_pointer(void *x) {
  show_bytes((byte_pointer) &x, sizeof(void *));
}

int main(void)
{
  int a = 12345;
  int *b;
  char c[4];
  char *cp = "90\0\0";

  c[0] = 57;
  c[1] = 48;
  c[2] = 0;
  c[3] = 0;

  show_bytes((unsigned char *)&c[0], 4);
  b = (int *)&c[0];
  printf("%d\n", *b);
  b = (int *)cp;
  printf("%d\n", *b);
  show_bytes((unsigned char *)cp, 4);
  show_int(a);
  return 0;
}
