/* Benchmark list access to measure load latency */
#include <stdio.h>
#include "cpe.h"

#define ASIZE 1024

/* $begin list_len */
typedef struct ELE {
    struct ELE *next;
    int data;
} list_ele, *list_ptr;

/* $end list_len */

list_ele main_list[ASIZE];

void mylink(int len)
{
    int i;

    for (i = 0; i < len-1; i++) {
	main_list[i].data = i;
	main_list[i].next = &main_list[i+1];
    }
    main_list[len-1].data = len-1;
    main_list[len-1].next = NULL;
}

/* $begin list_len */
int list_len(list_ptr ls)
{
    int len = 0;

    for (; ls; ls = ls->next)
	len++;
    return len;
}
/* $end list_len */

int list_len_clear(list_ptr ls)
{
    int len = 0;
    while(ls) {
	ls->data = 0;
	ls = ls->next;
	len++;
    }
    return len;
}

int list_sum_clear(list_ptr ls)
{
    int sum = 0;
    while(ls) {
	sum += ls->data;
	ls->data = 0;
	ls = ls->next;
    }
    return sum;
}


/* $begin list_sum */
int list_sum(list_ptr ls)
{
    int sum = 0;

    for (; ls; ls = ls->next)
	sum += ls->data;
    return sum;
}
/* $end list_sum */

/* $begin list_sum2 */
int list_sum2(list_ptr ls)
{
    int sum = 0;
    list_ptr old;

    while (ls) {
	old = ls;
	ls = ls->next;
	sum += old->data;
    }
    return sum;
}
/* $end list_sum2 */

int pipe_sum2(list_ptr ls)
{
    int sum = 0;
    list_ptr next;
    while (ls) {
	next = ls->next;
	sum += ls->data;
	ls = next;
    }
    return sum;
}

int rlist_len(list_ptr ls)
{
    if (!ls)
	return 0;
    return 1+rlist_len(ls->next);
}

int rlist_sum(list_ptr ls)
{
    if (!ls)
	return 0;
    return ls->data+rlist_sum(ls->next);
}

/* List copying to exercise load/store interactions */
void list_copy(list_ptr src, list_ptr dest)
{
    while (src && dest) {
	dest->data = src->data;
	src = src->next;
	dest = dest->next;
    }
}

/* Same thing, but with pipelining */
void plist_copy(list_ptr src, list_ptr dest)
{
    list_ptr osrc = src;
    list_ptr odest = dest;
    if (!osrc || !odest)
	return;
    do {
	odest = dest;
	dest = dest->next;
	osrc = src;
	src = src->next;
	odest->data = osrc->data;
    } while (src && dest);
}


void plist_copy2(list_ptr src, list_ptr dest)
{
    list_ptr nsrc, ndest;  
    while (src && dest) {
	nsrc = src->next;
	ndest = dest->next;
	dest->data = src->data;
	src = nsrc;
	dest = ndest;
    }
}

void stationary_copy(list_ptr src, list_ptr dest)
{
    int i;
    for (i = 0; i < ASIZE; i++) {
	dest->data = src->data;
    }
}

typedef int (*list_fun)(list_ptr);



#define TEST_COUNT 8
static list_fun test_fun[TEST_COUNT] = 
{list_len, list_sum, list_sum2, pipe_sum2, rlist_len, rlist_sum, 
 list_len_clear, list_sum_clear};
static char * test_descr[TEST_COUNT] =
{"Iterative List Length",
 "Iterative List Sum",
 "Pipelined List Sum with old",
 "Pipelined List Sum with new",
 "Recursive List Length",
 "Recursive List Sum",
 "List Length with Clear",
 "List Sum with Clear"};

static int myindex = 0;

static void test(int n)
{
    /* Temporarily set list length to n */
    list_ptr onext = main_list[n-1].next;
    main_list[n-1].next = NULL;
    test_fun[myindex](main_list);
    main_list[n-1].next = onext;
}


/* Perform test of one of the list functions */
static void run_test(int i)
{
    double cpe;
    int len = ASIZE;
    mylink(len);
    printf("Description: %s, f(%d) = %d, ",
	   test_descr[i], len, test_fun[i](main_list));
    myindex = i;
    cpe = find_cpe(test, ASIZE);
    /* print results */
    printf("CPE = %.2f\n", cpe);
}


typedef void (*list2_fun)(list_ptr, list_ptr);

#define TEST2_COUNT 4
static list2_fun test2_fun[TEST2_COUNT] = 
{ list_copy, plist_copy, plist_copy2, stationary_copy };
static char *test2_descr[TEST2_COUNT] = 
{"List Copy", "Pipelined List Copy Do-While", "Pipelined List Copy While",
 "Stationary Copy"};

static void test2a(int n)
{
    list_ptr onext = main_list[n-1].next;
    main_list[n-1].next = NULL;
    test2_fun[myindex](main_list,main_list);
    main_list[n-1].next = onext;
}

static void test2b(int n)
{
    list_ptr onext = main_list[n-1].next;
    main_list[n-1].next = NULL;
    test2_fun[myindex](main_list,main_list->next);
    main_list[n-1].next = onext;
}

static void test2c(int n)
{
    list_ptr onext = main_list[n-1].next;
    main_list[n-1].next = NULL;
    test2_fun[myindex](main_list->next,main_list);
    main_list[n-1].next = onext;
}

#define CASE2_COUNT 3

typedef void (*test_fun2)(int);

static test_fun2 case_fun[CASE2_COUNT] =
{ test2a, test2b, test2c };

static char *case2_descr[CASE2_COUNT] = 
{ "list --> list",
  "list --> list->next",
  "list->next --> list"
};

static void run_test2(int i, int c) 
{
    double cpe;
    int len = ASIZE;
    mylink(len);
    printf("Description: %s, %s, ",
	   test2_descr[i], case2_descr[c]);
    myindex = i;
    cpe = find_cpe(case_fun[c], ASIZE);
    /* print results */
    printf("CPE = %.2f\n", cpe);
}

int main()
{
    int i, c;
    for (i = 0; i < TEST_COUNT; i++)
	run_test(i);

    for (i = 0; i < TEST2_COUNT; i++)
	for (c = 0; c < CASE2_COUNT; c++)
	    run_test2(i,c);

    return 0;
}

