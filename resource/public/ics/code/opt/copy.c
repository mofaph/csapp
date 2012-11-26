/* Benchmark list access to measure load / store interactions */
#include <stdio.h>
#include "cpe.h"

#define ASIZE 1024

int data[ASIZE+1];
int data2[ASIZE+1];

static void stationary_clear(int *src, int *dest, int n)
{
    int i;
    for (i = 0; i < n; i++)
	*dest = 0;
}

static void stationary_copy(int *src, int *dest, int n)
{
    int i;
    for (i = 0; i < n; i++)
	*dest = *src;
}

/* $begin write_read */
/* Write to dest, read from src */
void write_read(int *src, int *dest, int n)
{
    int cnt = n;
    int val = 0;

    while (cnt--) {
	*dest = val;
	val = (*src)+1;
    }
}
/* $end write_read */

static void moving_copy(int *src, int *dest, int n)
{
    int i;
    for (i = 0; i < n; i++)
	*dest++ = *src++;
}

static void moving_clear(int *src, int *dest, int n)
{
    int i;
    for (i = 0; i < n; i++)
	*dest++ = 0;
}


/* $begin copy_array */
void copy_array(int *src, int *dest, int n)
{
    int i;

    for (i = 0; i < n; i++)
	dest[i] = src[i];
}
/* $end copy_array */

/* $begin array_clear */
/* Set element of array to 0 */
void array_clear(int *src, int *dest, int n)
{
    int i;

    for (i = 0; i < n; i++)
	dest[i] = 0;
}

/* Set elements of array to 0, unrolling by 8 */
static void array_clear_8(int *src, int *dest, int n)
{
    int i;
    int len = n - 7;

    for (i = 0; i < len; i+=8) {
	dest[i] = 0;
	dest[i+1] = 0;
	dest[i+2] = 0;
	dest[i+3] = 0;
	dest[i+4] = 0;
	dest[i+5] = 0;
	dest[i+6] = 0;
	dest[i+7] = 0;
    }
    for (; i < n; i++)
	dest[i] = 0;
}
/* $end array_clear */


static void mem_clear(int *src, int *dest, int n)
{
    memset((void *) dest, '\0', n*sizeof(int));
}

static void stationary_clear_2(int *src, int *dest, int n)
{
    int i;
    int len = n-1;
    for (i = 0; i < len; i+=2) {
	*dest = 0;
	*dest = 0;
    }
    for (; i < n; i++)
	*dest = 0;
}

static void stationary_copy_2(int *src, int *dest, int n)
{
    int i;
    int len = n-1;
    for (i = 0; i < len; i+=2) {
	*dest = *src;
	*dest = *src;
    }
    for (; i < n; i++)
	*dest = *src;
}

static void moving_copy_2(int *src, int *dest, int n)
{
    int i;
    int len = n-1;
    for (i = 0; i < len; i+=2) {
	*dest = *src;
	*(dest+1) = *(src+1);
	dest += 2;
	src += 2;
    }
    for (; i < n; i++)
	*dest++ = *src++;
}

static void moving_clear_2(int *src, int *dest, int n)
{
    int i;
    int len = n-1;
    for (i = 0; i < len; i+=2) {
	*dest = 0;
	*(dest+1) = 0;
	dest += 2;
    }
    for (; i < n; i++)
	*dest++ = 0;
}


static void array_copy_2(int *src, int *dest, int n)
{
    int i;
    int len = n-1;
    for (i = 0; i < len; i+=2) {
	dest[i] = src[i];
	dest[i+1] = src[i+1];
    }
    for (; i < n; i++)
	dest[i] = src[i];
}

static void array_clear_2(int *src, int *dest, int n)
{
    int i;
    int len = n-1;
    for (i = 0; i < len; i+=2) {
	dest[i] = 0;
	dest[i+1] = 0;
    }
    for (; i < n; i++)
	dest[i] = 0;
}

static void stationary_clear_4(int *src, int *dest, int n)
{
    int i;
    int len = n-3;
    for (i = 0; i < len; i+=4) {
	*dest = 0;
	*dest = 0;
	*dest = 0;
	*dest = 0;
    }
    for (; i < n; i++)
	*dest = 0;
}

static void stationary_copy_4(int *src, int *dest, int n)
{
    int i;
    int len = n-3;
    for (i = 0; i < len; i+=4) {
	*dest = *src;
	*dest = *src;
	*dest = *src;
	*dest = *src;
    }
    for (; i < n; i++)
	*dest = *src;
}

static void moving_copy_4(int *src, int *dest, int n)
{
    int i;
    int len = n-3;
    for (i = 0; i < len; i+=4) {
	*dest = *src;
	*(dest+1) = *(src+1);
	*(dest+2) = *(src+2);
	*(dest+3) = *(src+3);
	dest += 4;
	src += 4;
    }
    for (; i < n; i++)
	*dest++ = *src++;
}

static void moving_clear_4(int *src, int *dest, int n)
{
    int i;
    int len = n-3;
    for (i = 0; i < len; i+=4) {
	*dest = 0;
	*(dest+1) = 0;
	*(dest+2) = 0;
	*(dest+3) = 0;
	dest += 4;
    }
    for (; i < n; i++)
	*dest++ = 0;
}


static void array_copy_4(int *src, int *dest, int n)
{
    int i;
    int len = n-3;
    for (i = 0; i < len; i+=4) {
	dest[i] = src[i];
	dest[i+1] = src[i+1];
	dest[i+2] = src[i+2];
	dest[i+3] = src[i+3];
    }
    for (; i < n; i++)
	dest[i] = src[i];
}

static void array_clear_4(int *src, int *dest, int n)
{
    int i;
    int len = n-3;
    for (i = 0; i < len; i+=4) {
	dest[i] = 0;
	dest[i+1] = 0;
	dest[i+2] = 0;
	dest[i+3] = 0;
    }
    for (; i < n; i++)
	dest[i] = 0;
}


typedef void (*copy_fun)(int *, int *, int);


#define TEST_COUNT 21

static copy_fun copier[TEST_COUNT] = 
{ stationary_copy, moving_copy, copy_array, 
  stationary_clear, moving_clear, array_clear,
  stationary_copy_2, moving_copy_2, array_copy_2, 
  stationary_clear_2, moving_clear_2, array_clear_2,
  stationary_copy_4, moving_copy_4, array_copy_4, 
  stationary_clear_4, moving_clear_4, array_clear_4,
  array_clear_8, mem_clear, write_read
};

static char *test_descr[TEST_COUNT] = 
{"Stationary Copy", "Moving Copy", "Array Copy",
 "Stationary Clear", "Moving Clear", "Array Clear",
 "Stationary Copy x2", "Moving Copy x2", "Array Copy x2",
 "Stationary Clear x2", "Moving Clear x2", "Array Clear x2",
 "Stationary Copy x4", "Moving Copy x4", "Array Copy x4",
 "Stationary Clear x4", "Moving Clear x4", "Array Clear x4",
 "Array Clear x8", "Memset Clear", "Write-Read"
};

int idx = 0;

#define CASE_COUNT 4

static void test2a(int n)
{
    copier[idx](data,data,n);
}

static void test2b(int n)
{
    copier[idx](data,data+1,n);
}
#if CASE_COUNT == 4
static void test2c(int n)
{
    copier[idx](data+1,data,n);
}

static void test2d(int n)
{
    copier[idx](data, data2, n);
}
#endif



typedef void (*test_fun)(int);

static test_fun case_fun[CASE_COUNT] =
{ test2a, test2b
#if CASE_COUNT == 4
  , test2c, test2d
#endif
};

static char *case_descr[CASE_COUNT] = 
{ "data --> data",
  "data --> data+1",
#if CASE_COUNT == 4
  "data+1 --> data",
  "data1 --> data2"
#endif
};

static void run_test(int i, int c) 
{
    double cpe;
    printf("Description: %s, %s, ",
	   test_descr[i], case_descr[c]);
    idx = i;
    cpe = find_cpe(case_fun[c], ASIZE);
    /* print results */
    printf("CPE = %.2f\n", cpe);
}

int main()
{
    int i, c;

    for (i = 0; i < TEST_COUNT; i++)
	for (c = 0; c < CASE_COUNT; c++)
	    run_test(i,c);

    return 0;
}

