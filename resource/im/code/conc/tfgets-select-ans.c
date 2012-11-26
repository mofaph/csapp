/*
 * tfgets-select.c - timeout version of fgets based on select
 *                   (assumes that stream is stdin)
 */
/* $begin tfgetsselect-ans */
#include "csapp.h"

#define TIMEOUT 5

char *tfgets(char *s, int size, FILE *stream) 
{
    struct timeval tv;
    fd_set rfds;
    int retval;

    FD_ZERO(&rfds);
    FD_SET(0, &rfds);

    /* Wait for 5 seconds for stdin to be ready */
    tv.tv_sec = 5; 
    tv.tv_usec = 0;
    retval = select(1, &rfds, NULL, NULL, &tv);
    if (retval)
	return fgets(s, size, stream);
    else
	return NULL;
}
/* $end tfgetsselect-ans */

