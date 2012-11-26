/* $begin tfgets-ans */
#include "csapp.h"

static sigjmp_buf env;

static void handler(int sig) 
{
    Alarm(0);
    siglongjmp(env, 1);
}

char *tfgets(char *s, int size, FILE *stream) 
{
    Signal(SIGALRM, handler);

    Alarm(5);
    if (sigsetjmp(env, 1) == 0)
	return(Fgets(s, size, stream)); /* return user input */
    else 
	return NULL;  /* return NULL if fgets times out */
}

int main() 
{
    char buf[MAXLINE];
  
    while (1) {
	bzero(buf, MAXLINE);
	if (tfgets(buf, sizeof(buf), stdin) != NULL)
	    printf("read: %s", buf);
	else
	    printf("timed out\n");
    }
    exit(0);
}
/* $end tfgets-ans */
