#include <stdio.h>
#include <stdlib.h>

#include "csapp.h"

int main(void)
{
    if (Fork() == 0) {          /* child */
        printf("a");
    }
    else {                      /* parent */
        printf("b");
        waitpid(-1, NULL, 0);
    }
    printf("c");
    exit(0);
}
