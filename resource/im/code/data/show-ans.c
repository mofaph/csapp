#include <stdlib.h>

#include <stdio.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, int len)
{
    int i;
    for (i = 0; i < len; i++)
	printf(" %.2x", start[i]);
    printf("\n");
}

void show_int(int x)
{
    show_bytes((byte_pointer) &x, sizeof(int));
}

void show_float(float x)
{
    show_bytes((byte_pointer) &x, sizeof(float));
}

void show_pointer(void *x)
{
    show_bytes((byte_pointer) &x, sizeof(void *));
}

/* $begin show-ans */
void show_short(short int x)
{
    show_bytes((byte_pointer) &x, sizeof(short int));
}

void show_long(long int x)
{
    show_bytes((byte_pointer) &x, sizeof(long));
}

void show_double(double x)
{
    show_bytes((byte_pointer) &x, sizeof(double));
}
/* $end show-ans */

/* $begin endian-ans */
int is_little_endian(void)
{
    /* MSB = 0, LSB = 1 */
    int x = 1;

    /* Return MSB when big-endian, LSB when little-endian */
    return (int) (* (char *) &x); 
}
/* $end endian-ans */

void test(int val)
{
    int ival = val;
    long int lival = (long int) ival;
    short int sival = (short int) ival;
    float fval = (float) ival;
    double dval = (double) fval;
    int *pval = &ival;

    printf("This machine is %s-Endian\n",
	   is_little_endian() ? "Little" : "Big");
    printf("(int) %d\n", val);
    show_int(ival);
    printf("(long) %d\n", val);
    show_long(lival);
    printf("(short) %d\n", val);
    show_short(sival);
    printf("(float) %d\n", val);
    show_float(fval);
    printf("(double) %d\n", val);
    show_double(dval);
    printf("&ival\n");
    show_pointer(pval);
}

int main(int argc, char *argv[])
{
    int val = 12345;

    if (argc > 1)
	sscanf(argv[1], "%d", &val);
    test(val);
    return 0;
}
