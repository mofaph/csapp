/* $begin mysystem-ans */
#include "csapp.h"

int mysystem(char *command) 
{
    pid_t pid;
    int status;

    if (command == NULL)
	return -1;

    if ((pid = fork()) == -1)
	return -1;
    
    if (pid == 0) { /* child */
	char *argv[4];
	argv[0] = "sh";
	argv[1] = "-c";
	argv[2] = command;
	argv[3] = NULL;
	execve("/bin/sh", argv, environ);
	exit(-1); /* control should never reach here */
    }

    /* parent */
    while (1) {
	if (waitpid(pid, &status, 0) == -1) {
	    if (errno != EINTR) /* restart waitpid if interrupted */
		return -1;
	} 
	else {
	    if (WIFEXITED(status))
		return WEXITSTATUS(status);
	    else
		return status;
	}
    }
}
/* $end mysystem-ans */

int main() 
{
    char buf[MAXLINE];

    while(1) {
	printf("> ");
	Fgets(buf, MAXLINE, stdin);
	printf("retcode = %d\n", mysystem(buf));
    }
}
