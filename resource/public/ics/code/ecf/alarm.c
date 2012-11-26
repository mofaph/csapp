/* $begin alarm */
#include "csapp.h"

void handler(int sig) 
{
    static int beeps = 0;

    printf("BEEP\n");
    if (++beeps < 5)  
	Alarm(1); /* next SIGALRM will be delivered in 1s */
    else {
	printf("BOOM!\n");
	exit(0);
    }
}

int main() 
{
    Signal(SIGALRM, handler); /* install SIGALRM handler */
    Alarm(1); /* next SIGALRM will be delivered in 1s */

    while (1) {
	;  /* signal handler returns control here each time */
    }
    exit(0);
}
/* $end alarm */
