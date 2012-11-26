/* $begin waitpid1 */
#include "csapp.h"
#define N 2

int main() 
{
    int status, i;
    pid_t pid;

    for (i = 0; i < N; i++) 
	if ((pid = Fork()) == 0)  /* child */
	    exit(100+i);

    /* parent waits for all of its children to terminate */
    while ((pid = waitpid(-1, &status, 0)) > 0) {
	if (WIFEXITED(status))  
	    printf("child %d terminated normally with exit status=%d\n",
		   pid, WEXITSTATUS(status));
	else
	    printf("child %d terminated abnormally\n", pid);
    }
    if (errno != ECHILD)
	unix_error("waitpid error");

    exit(0);
}
/* $end waitpid1 */
