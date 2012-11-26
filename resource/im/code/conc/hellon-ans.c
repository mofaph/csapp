/* 
 * hellon.c - cranks up n hello world threads
 */
/* $begin hellon-ans */
#include "csapp.h"

void *thread(void *vargp);

int main(int argc, char **argv) 
{
    pthread_t *tid;
    int i, n;

    if (argc != 2) {
	fprintf(stderr, "usage: %s <nthreads>\n", argv[0]);
	exit(0);
    }
    n = atoi(argv[1]);
    tid = Malloc(n * sizeof(pthread_t));

    for (i = 0; i < n; i++)
	Pthread_create(&tid[i], NULL, thread, NULL);
    for (i = 0; i < n; i++)
	Pthread_join(tid[i], NULL);
    exit(0);
}

/* thread routine */
void *thread(void *vargp) 
{
    printf("Hello, world!\n"); 
    return NULL;
}
/* $end hellon-ans */
