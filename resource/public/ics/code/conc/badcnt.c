/* 
 * badcnt.c - An improperly synchronized counter program 
 */
/* $begin badcnt */
#include "csapp.h"

#define NITERS 200000000
void *count(void *arg);

/* shared counter variable */
unsigned int cnt = 0;

int main() 
{
    pthread_t tid1, tid2;

    Pthread_create(&tid1, NULL, count, NULL);
    Pthread_create(&tid2, NULL, count, NULL);
    Pthread_join(tid1, NULL);
    Pthread_join(tid2, NULL);

    if (cnt != (unsigned)NITERS*2)
	printf("BOOM! cnt=%d\n", cnt);
    else
	printf("OK cnt=%d\n", cnt);
    exit(0);
}

/* thread routine */
void *count(void *arg) 
{
    int i;
    for (i = 0; i < NITERS; i++)
	cnt++;
    return NULL;
}
/* $end badcnt */

