/* $begin select */
#include "csapp.h"
void echo(int connfd);
void command(void);

int main(int argc, char **argv) 
{
    int listenfd, connfd, port, clientlen = sizeof(struct sockaddr_in);
    struct sockaddr_in clientaddr;
    fd_set read_set, ready_set;

    if (argc != 2) {
	fprintf(stderr, "usage: %s <port>\n", argv[0]);
	exit(0);
    }
    port = atoi(argv[1]);
    listenfd = Open_listenfd(port);

    FD_ZERO(&read_set); 
    FD_SET(STDIN_FILENO, &read_set); 
    FD_SET(listenfd, &read_set); 

    while (1) {
	ready_set = read_set;
	Select(listenfd+1, &ready_set, NULL, NULL, NULL); 
	if (FD_ISSET(STDIN_FILENO, &ready_set))
	    command(); /* read command line from stdin */
	if (FD_ISSET(listenfd, &ready_set)) {
	    connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
	    echo(connfd); /* echo client input until EOF */
	}
    }
}

void command(void) {
    char buf[MAXLINE];
    if (!Fgets(buf, MAXLINE, stdin))
	exit(0); /* EOF */
    printf("%s", buf); /* Process the input command */
}
/* $end select */


