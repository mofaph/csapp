/*
 * tfgets-proc.c - timeout version of fgets based on processes,
 *                signals, and nonlocal jumps
 */
/* $begin tfgetsproc-ans */
#include "csapp.h"
#define TIMEOUT 5

static sigjmp_buf env; /* buffer for non-local jump */
static char *str;      /* global to keep gcc -Wall happy */

/* SIGCHLD signal handler */
static void handler(int sig) 
{
    Wait(NULL);
    siglongjmp(env, 1);
}

char *tfgets(char *s, int size, FILE *stream) 
{
    pid_t pid;

    str = NULL;

    Signal(SIGCHLD, handler);

    if ((pid = Fork()) ==  0) { /* child */
	Sleep(TIMEOUT);
	exit(0);
    }
    else {  /* parent */
	if (sigsetjmp(env, 1) == 0) {
	    str = fgets(s, size, stream);
	    Kill(pid, SIGKILL);
	    pause();
	}
	return str;
    }
}
/* $end tfgetsproc-ans */

