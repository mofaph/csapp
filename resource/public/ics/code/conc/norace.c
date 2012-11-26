/* 
 * norace.c - fixes the race in race.c
 */
/* $begin norace */
#include "csapp.h"
#define N 4

void *thread(void *vargp);

int main() 
{
    pthread_t tid[N];
    int i, *ptr;

    for (i = 0; i < N; i++) {
	ptr = Malloc(sizeof(int));
	*ptr = i;
	Pthread_create(&tid[i], NULL, thread, ptr);
    }
    for (i = 0; i < N; i++) 
	Pthread_join(tid[i], NULL);
    exit(0);
}

/* thread routine */
void *thread(void *vargp) 
{
    int myid = *((int *)vargp);
    Free(vargp); 
    printf("Hello from thread %d\n", myid);
    return NULL;
}
/* $end norace */
