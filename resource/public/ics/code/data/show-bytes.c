/* $begin show-bytes */
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
/* $end show-bytes */


/* $begin test-show-bytes */
void test_show_bytes(int val)
{
    int ival = val;
    float fval = (float) ival;
    int *pval = &ival;
    show_int(ival);
    show_float(fval);
    show_pointer(pval);
}
/* $end test-show-bytes */

void simple_show()
{
/* $begin simple-show */
int val = 0x12345678;
byte_pointer valp = (byte_pointer) &val;
show_bytes(valp, 1); /* A. */
show_bytes(valp, 2); /* B. */
show_bytes(valp, 3); /* C. */
/* $end simple-show */
}

void float_eg()
{
/* $begin float-show */
int x = 3490593;
float f = (float) x;
show_int(x);
show_float(f);
/* $end float-show */
}

void string_eg()
{
/* $begin show-string */
char *s = "ABCDEF";
show_bytes(s, strlen(s)); 
/* $end show-string */
}

void show_twocomp() 
{
/* $begin show-twocomp */
    short int x = 12345; 
    short int mx = -x; 
    
    show_bytes((byte_pointer) &x, sizeof(short int)); 
    show_bytes((byte_pointer) &mx, sizeof(short int)); 
/* $end show-twocomp */
}

int main(int argc, char *argv[])
{
    int val = 12345;

    if (argc > 1) {
      if (argv[1][0] == '0' && argv[1][1] == 'x')
	sscanf(argv[1]+2, "%x", &val);
      else
	sscanf(argv[1], "%d", &val);
      printf("calling test_show_bytes\n");
      test_show_bytes(val);
    } else {
      printf("calling show_twocomp\n");
      show_twocomp();
      printf("Calling simple_show\n");
      simple_show();
      printf("Calling float_eg\n");
      float_eg();
      printf("Calling string_eg\n");
      string_eg();
    }
    return 0;
}
