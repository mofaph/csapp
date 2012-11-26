/*
 * internal.c - A program that responds to interally 
 *              generated events (SIGALARM signals)
 */
#include <stdio.h> 
#include <signal.h> 
 
int beeps = 0; 
 
/* SIGALRM handler */
void handler(int sig) { 
    printf("BEEP\n"); 
    fflush(stdout); 
 
    if (++beeps < 5)   
	alarm(1); 
    else { 
	printf("BOOM!\n"); 
	exit(0); 
    } 
} 

main() { 
    signal(SIGALRM, handler);  
    alarm(1); /* send SIGALRM in
		 1 second */
 
    while (1) { 
	/* handler returns here */ 
    } 
} 
