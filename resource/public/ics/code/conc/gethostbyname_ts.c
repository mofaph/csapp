/* 
 * gethostbyname_ts - A thread-safe wrapper for gethostbyname
 */
#include "csapp.h"

static sem_t mutex; /* protects calls to gethostbyname */

static void init_gethostbyname_ts(void)
{
    Sem_init(&mutex, 0, 1);
}

/* $begin gethostbyname_ts */
struct hostent *gethostbyname_ts(char *hostname)
{
    struct hostent *sharedp, *unsharedp;

    unsharedp = Malloc(sizeof(struct hostent)); 
    P(&mutex);
    sharedp = gethostbyname(hostname);
    *unsharedp = *sharedp; /* copy shared struct to private struct */
    V(&mutex);
    return unsharedp;
}
/* $end gethostbyname_ts */

int main(int argc, char **argv)
{
    char **pp;
    struct in_addr addr;
    struct hostent *hostp;

    if (argc != 2) { 
	fprintf(stderr, "usage: %s <hostname>\n", argv[0]);
	exit(0);
    }

    init_gethostbyname_ts();
    hostp = gethostbyname_ts(argv[1]);
    if (hostp) {
	printf("official hostname: %s\n", hostp->h_name);
	for (pp = hostp->h_aliases; *pp != NULL; pp++)
	    printf("alias: %s\n", *pp);
	for (pp = hostp->h_addr_list; *pp != NULL; pp++) {
	    addr.s_addr = *((unsigned int *)*pp);
	    printf("address: %s\n", inet_ntoa(addr));
	}
    }
    else {
	printf("host %s not found\n", argv[1]);
    }
    exit(0);
}
