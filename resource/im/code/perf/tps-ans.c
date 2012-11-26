/* $begin tps-ans */
#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <sys/times.h>

int tps()
{
    clock_t tstart;
    struct tms t;

    tstart = times(&t);
    sleep(1);
    return (int) (times(&t) - tstart);
}


int main(int argc, char *argv[])
{
    printf("%d ticks/second\n", tps());
    return 0;
}
/* $end tps-ans */
