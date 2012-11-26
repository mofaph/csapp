/* $begin cpfile1-ans */
#include "csapp.h"

int main(int argc, char **argv) 
{
    int n;
    char buf[MAXBUF];

    while((n = Rio_readn(STDIN_FILENO, buf, MAXBUF)) != 0) 
	Rio_writen(STDOUT_FILENO, buf, n);
    exit(0);
}
/* $end cpfile1-ans */



