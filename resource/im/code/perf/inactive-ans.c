/* $begin inactive-ans */
#include <stdio.h>
#include <stdlib.h>
#include "clock.h"

/* $begin inactive-proto */
int inactive_duration(int thresh); 
/* $end inactive-proto */

int main (int argc, char *argv[])
{
    int i;

    for (i = 0; i < 5; i++) {
	int d = inactive_duration(1000);
	printf("%d cycles\n", d);
    }
    return 0;
}

int inactive_duration(int thresh) 
{
    double oldt, newt;
    int delta;
    start_counter();
    newt = get_counter();

    do {
	oldt = newt;
	newt = get_counter();
	delta = (int) (newt - oldt);
    } while (delta < thresh);
    return delta;
}

/* $end inactive-ans */
