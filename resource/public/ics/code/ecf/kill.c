/* $begin kill */
#include "csapp.h"

int main() 
{
    pid_t pid;

    /* child sleeps until SIGKILL signal received, then dies */   
    if ((pid = Fork()) == 0) {   
	Pause();  /* wait for a signal to arrive */  
	printf("control should never reach here!\n");
	exit(0);
    }

    /* parent sends a SIGKILL signal to a child */
    Kill(pid, SIGKILL);
    exit(0);
}
/* $end kill */
