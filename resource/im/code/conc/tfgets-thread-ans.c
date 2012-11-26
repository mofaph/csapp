/* 
 * tfgets-thread - timeout version of fgets based on threads
 */ 
/* $begin tfgetsthread-ans */
#include "csapp.h"
#define TIMEOUT 5

void *fgets_thread(void *vargp);
void *sleep_thread(void *vargp);

char *returnval;  /* fgets output string */
typedef struct {  /* fgets input arguments */
    char *s;
    int size;
    FILE *stream;
} args_t; 

char *tfgets(char *str, int size, FILE *stream) 
{ 
    pthread_t fgets_tid, sleep_tid;
    args_t args;

    args.s = str;
    args.size = size;
    args.stream = stdin;
    returnval = NULL;
    Pthread_create(&fgets_tid, NULL, fgets_thread, &args);
    Pthread_create(&sleep_tid, NULL, sleep_thread, &fgets_tid);
    Pthread_join(fgets_tid, NULL);
    return returnval;
}

void *fgets_thread(void *vargp) 
{
    args_t *argp = (args_t *)vargp;
    returnval = fgets(argp->s, argp->size, stdin);
    return NULL;
}

void *sleep_thread(void *vargp) 
{
    pthread_t fgets_tid = *(pthread_t *)vargp;
    Pthread_detach(Pthread_self());
    Sleep(TIMEOUT);
    pthread_cancel(fgets_tid);
    return NULL;
}
/* $end tfgetsthread-ans */
