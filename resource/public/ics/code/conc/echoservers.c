/* 
 * echoservers.c - A concurrent echo server based on select
 */
/* $begin echoserversmain */
#include "csapp.h"

typedef struct { /* represents a pool of connected descriptors */
    int maxfd;        /* largest descriptor in read_set */   
    fd_set read_set;  /* set of all active descriptors */
    fd_set ready_set; /* subset of descriptors ready for reading  */
    int nready;       /* number of ready descriptors from select */   
    int maxi;         /* highwater index into client array */
    int clientfd[FD_SETSIZE];    /* set of active descriptors */
    rio_t clientrio[FD_SETSIZE]; /* set of active read buffers */
} pool;
/* $end echoserversmain */
void init_pool(int listenfd, pool *p);
void add_client(int connfd, pool *p);
void check_clients(pool *p);
/* $begin echoserversmain */

int byte_cnt = 0; /* counts total bytes received by server */

int main(int argc, char **argv)
{
    int listenfd, connfd, port, clientlen = sizeof(struct sockaddr_in);
    struct sockaddr_in clientaddr;
    static pool pool; 

    if (argc != 2) {
	fprintf(stderr, "usage: %s <port>\n", argv[0]);
	exit(0);
    }
    port = atoi(argv[1]);

    listenfd = Open_listenfd(port);
    init_pool(listenfd, &pool); 
    while (1) {
	/* Wait for listening/connected descriptor(s) to become ready */
	pool.ready_set = pool.read_set;
	pool.nready = Select(pool.maxfd+1, &pool.ready_set, NULL, NULL, NULL);

	/* If listening descriptor ready, add new client to pool */
	if (FD_ISSET(listenfd, &pool.ready_set)) { 
	    connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
	    add_client(connfd, &pool);
	}
	
	/* Echo a text line from each ready connected descriptor */
	check_clients(&pool);
    }
}
/* $end echoserversmain */

/* $begin init_pool */
void init_pool(int listenfd, pool *p) 
{
    /* Initially, there are no connected descriptors */
    int i;
    p->maxi = -1;   
    for (i=0; i< FD_SETSIZE; i++)
	p->clientfd[i] = -1; 

    /* Initially, listenfd is only member of select read set */
    p->maxfd = listenfd; 
    FD_ZERO(&p->read_set);
    FD_SET(listenfd, &p->read_set);
}
/* $end init_pool */

/* $begin add_client */
void add_client(int connfd, pool *p) 
{
    int i;
    p->nready--;
    for (i = 0; i < FD_SETSIZE; i++)  /* Find an available slot */
	if (p->clientfd[i] < 0) { 
	    /* Add connected descriptor to the pool */
	    p->clientfd[i] = connfd;
	    Rio_readinitb(&p->clientrio[i], connfd);

	    /* Add the descriptor to descriptor set */
	    FD_SET(connfd, &p->read_set);

	    /* Update max descriptor and pool highwater mark */
	    if (connfd > p->maxfd)
		p->maxfd = connfd; 
	    if (i > p->maxi)
		p->maxi = i;  
	    break;
	}
    if (i == FD_SETSIZE) /* Couldn't find an empty slot */
	app_error("add_client error: Too many clients");
}
/* $end add_client */

/* $begin check_clients */
void check_clients(pool *p) 
{
    int i, connfd, n;
    char buf[MAXLINE]; 
    rio_t rio;

    for (i = 0; (i <= p->maxi) && (p->nready > 0); i++) {
	connfd = p->clientfd[i];
	rio = p->clientrio[i];

	/* If the descriptor is ready, echo a text line from it */
	if ((connfd > 0) && (FD_ISSET(connfd, &p->ready_set))) { 
	    p->nready--;
	    if ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0) {
		byte_cnt += n;
		printf("Server received %d (%d total) bytes on fd %d\n", 
		       n, byte_cnt, connfd);
		Rio_writen(connfd, buf, n);
	    }

	    /* EOF detected, remove descriptor from pool */
	    else { 
		Close(connfd);
		FD_CLR(connfd, &p->read_set);
		p->clientfd[i] = -1;
	    }
	}
    }
}
/* $end check_clients */

