/* $begin myls-ans */
#include "csapp.h"

int main(int argc, char **argv) {
  Execve("/bin/ls", argv, environ);
  exit(0);
}
/* $end myls-ans */
