/* Benchmark versions of string-lower-casing function */
#include <stdio.h>
#include <stdlib.h>
#include "clock.h"
#include "fcyc.h"

#define LSIZE 250000
#define LINCR  5000

#define ESIZE (1<<18)
#define EMIN (1<<13)

#define ASIZE (LSIZE < ESIZE ? ESIZE : LSIZE)

/* Keep track of a number of different procedures */
#define MAX_BENCHMARKS 10

static char data[ASIZE];

static double clock_rate = 0.0;

static void init()
{
  int i;
  for (i = 0; i < LSIZE; i++)
    data[i] = 'a' + i%26;
}

static void set_len(int len)
{
  data[len] = '\0';  
}

static void unset_len(int len)
{
  data[len] = 'a' + len%26;
}

/* $begin strfuns */
/* Convert string to lower case: slow */
void lower1(char *s)
{
    int i;

    for (i = 0; i < strlen(s); i++)
	if (s[i] >= 'A' && s[i] <= 'Z')
	    s[i] -= ('A' - 'a');
}

/* Convert string to lower case: faster */
void lower2(char *s)
{
    int i;
    int len = strlen(s);

    for (i = 0; i < len; i++)
	if (s[i] >= 'A' && s[i] <= 'Z')
	    s[i] -= ('A' - 'a');
}

/* Implementation of library function strlen */
/* Compute length of string */
size_t strlen(const char *s)
{
    int length = 0;
    while (*s != '\0') {
	s++; 
	length++;
    }
    return length;
}
/* $end strfuns */

void test_lower1(int *lenp)
{
  int len = *lenp;
  set_len(len);
  lower1(data);
  unset_len(len);
}

void test_lower2(int *lenp)
{
  int len = *lenp;
  set_len(len);
  lower2(data);
  unset_len(len);
}

/* Perform test of function */
static double run_test(test_funct fun, int len)
{
  double cycs;
  double time;
  
  set_fcyc_compensate(0);
  cycs = fcyc(fun,&len);
  time = cycs/(clock_rate*1e6);
  return time;
}



void linear()
{
  int size;
  printf("Length\tlower1\tlower2\n");
  for (size = LINCR; size <= LSIZE; size+=LINCR) {
    printf("%d", size);
    printf("\t%f", run_test(test_lower1, size));
    printf("\t%f\n", run_test(test_lower2, size));
  }
}

void expo()
{
  int size;
  for (size = EMIN; size <= ESIZE; size += size)
    printf("& %d ", size);
  printf(" \\\\\n");
  for (size = EMIN; size <= ESIZE; size += size)
    printf("& %.2f ", run_test(test_lower1, size));
  printf(" \\\\\n");
  for (size = EMIN; size <= ESIZE; size += size)
    printf("& %.4f ", run_test(test_lower2, size));
  printf(" \\\\\n");
}

int main(int argc, char *argv[])
{
  init();
  clock_rate = mhz(1);
  if (argc > 1)
    expo();
  else
    linear();
  return 0;
}

