#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/* $begin tod */
#include <sys/time.h>
#include <unistd.h>

static struct timeval tstart;

/* Record current time */
void start_timer()
{
    gettimeofday(&tstart, NULL);
}

/* Get number of seconds since last call to start_timer */
double get_timer()
{
    struct timeval tfinish;
    long sec, usec;

    gettimeofday(&tfinish, NULL);
    sec = tfinish.tv_sec - tstart.tv_sec;
    usec = tfinish.tv_usec - tstart.tv_usec;
    return sec + 1e-6*usec;
}
/* $end tod */

/* Determine how many "seconds" are in tod counter */
static void callibrate_tod()
{
    double quick, slow;
    start_timer();
    quick = get_timer();
    start_timer();
    sleep(1);
    slow = get_timer();
    printf("%.2f - %f = %.2f seconds/sleep second\n",
	   slow, quick, slow-quick);
    
}

static void run_timer()
{
    int i = 0;
    double t1, t2, t3, t4;
    start_timer();
    t1 = get_timer();
    do {
	t2 = get_timer();
    } while (t2 == t1);
    do {
	t3 = get_timer();
	i++;
    } while (t3 == t2);
    printf("Time = %f usecs, in %d iterations, %f usec/iteration\n",
	   1e6 *(t3-t2), i,
	   1e6 *(t3-t2)/i);
    start_timer();
    i = 0;
    do {
	t4 = get_timer();
	i++;
    } while (t4 < 1.0);
    printf("%d iterations in %f secs = %f usec/iteration\n",
	   i, t4, 1e6*t4/i);
}

static void check_time()
{
    long e;
    int s, m, h, d, y;
    start_timer();
    e = tstart.tv_sec;

    s = e % 60;
    e = e / 60;
    m = e % 60;
    e = e / 60;
    h = e % 24;
    e = e / 24;
    d = e % 365;
    e = e / 365;
    y = e;

    printf("This clock started %d years, %d days, %d hours, %d minutes, %d seconds ago\n",
	   y, d, h, m, s);
}

int main(int arg, char *argv[])
{

    callibrate_tod();
    run_timer();
    check_time();
    return 0;
}
