/* $begin fork */
#include "csapp.h"

int main() 
{
    pid_t pid;
    int x = 1;

    pid = Fork();
    if (pid == 0) {  /* child */
	printf("child : x=%d\n", ++x);
	exit(0);
    }

    /* parent */
    printf("parent: x=%d\n", --x);
    exit(0);
}
/* $end fork */

