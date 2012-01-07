/*
 * myecho.c
 *
 * 编写一个叫做 myecho 的程序，它打印出它的命令行参数和环境变量
 */

#include <stdio.h>

int main(int argc, char *argv[])
{
  int i;
  extern char **environ;

  printf("Command line arguments:\n");
  for (i = 0; i < argc; i++)
    printf("argv[%d]: %s\n", i, argv[i]);

  printf("Environment variables:\n");
  for (i = 0; environ[i] != NULL; i++)
    printf("envp[%d]: %s\n", i, environ[i]);

  return 0;
}

/* myecho.c ends here */
