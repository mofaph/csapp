/* $begin waitprob2-ans */
#include "csapp.h"

#define NCHILDREN 2

int main() 
{
    int status, i;
    pid_t pid;
    char buf[MAXLINE];

    for (i = 0; i < NCHILDREN; i++) {
	pid = Fork();
	if (pid == 0)  /* child */
	    /* child attempts to modify first byte of main */
	    *(char *)main = 1; 
    }

    /* parent waits for all children to terminate */
    while ((pid = wait(&status)) > 0) {
	if (WIFEXITED(status))  
	    printf("child %d terminated normally with exit status=%d\n",
		   pid, WEXITSTATUS(status));
	else
	    if (WIFSIGNALED(status)) {
		sprintf(buf, "child %d terminated by signal %d",
			pid, WTERMSIG(status));
		psignal(WTERMSIG(status), buf);
	    }
    }
    if (errno != ECHILD)
	unix_error("wait error");

    return 0;
}
/* $end waitprob2-ans */
