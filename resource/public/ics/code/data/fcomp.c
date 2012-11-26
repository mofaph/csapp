/* Test of floating point comparison */
#include <stdio.h>
#include <stdlib.h>

/* $begin fcomp1-c */
double recip(int denom)
{
  return 1.0/(double) denom;
}

void do_nothing() {} /* Just like the name says */

void test1(int denom)
{
  double r1, r2;
  int t1, t2;
 
  r1 = recip(denom);  /* Stored in memory               */
  r2 = recip(denom);  /* Stored in register             */
  t1 = r1 == r2;      /* Compares register to memory    */
  do_nothing();       /* Forces register save to memory */
  t2 = r1 == r2;      /* Compares memory to memory      */
  printf("test1 t1: r1 %f %c= r2 %f\n", r1, t1 ? '=' : '!', r2);  
  printf("test1 t2: r1 %f %c= r2 %f\n", r1, t2 ? '=' : '!', r2);  
}
/* $end fcomp1-c */

/* $begin fcomp2-c */
void test2(int denom)
{
  double r1;
  int t1;
  r1 = recip(denom);             /* Default: register, Forced store: memory */
  t1 = r1 == 1.0/(double) denom; /* Compares register or memory to register */
  printf("test2 t1: r1 %f %c= 1.0/10.0\n", r1, t1 ? '=' : '!');  
}
/* $end fcomp2-c */

/* $begin fcomp3-c */
long double recip_l(int denom)
{
  return 1.0/(long double) denom;
}

void test3(int denom)
{
  long double r1, r2;
  int t1, t2, t3;
 
  r1 = recip_l(denom); /* Stored in memory               */
  r2 = recip_l(denom); /* Stored in register             */
  t1 = r1 == r2;       /* Compares register to memory    */
  do_nothing();        /* Forces register save to memory */
  t2 = r1 == r2;       /* Compares memory to memory      */
  t3 = r1 == 1.0/(long double) denom; /* Compare memory to register */
  printf("test3 t1: r1 %f %c= r2 %f\n",
	 (double) r1, t1 ? '=' : '!', (double) r2);  
  printf("test3 t2: r1 %f %c= r2 %f\n",
	 (double) r1, t2 ? '=' : '!', (double) r2);  
  printf("test3 t3: r1 %f %c= 1.0/10.0\n",
	 (double) r1, t2 ? '=' : '!');  
}
/* $end fcomp3-c */

/* $begin fcomp4-c */
void test4(int denom)
{
  double r1, r2;
  int t1, t2;
 
  r1 = recip(denom);  /* Stored in memory               */
  r2 = 1.0/(double) denom;  /* Stored in register       */
  t1 = r1 == r2;      /* Compares register to memory    */
  do_nothing();       /* Forces register save to memory */
  t2 = r1 == r2;      /* Compares memory to memory      */
  printf("test4 t1: r1 %f %c= r2 %f\n", r1, t1 ? '=' : '!', r2);  
  printf("test4 t2: r1 %f %c= r2 %f\n", r1, t2 ? '=' : '!', r2);  
}
/* $end fcomp4-c */

/* $begin fcomp5-c */
void test5(int denom)
{
  double r1;
  int t1, t2;
 
  r1 = recip(denom);  /* Stored in memory               */
  t1 = r1 == 0.1;     /* Compares register to register  */
  do_nothing();       /* Forces register save to memory */
  t2 = r1 == 0.1;     /* Compares register to register  */
  printf("test5 t1: r1 %f %c= 0.1\n", r1, t1 ? '=' : '!');  
  printf("test5 t2: r1 %f %c= 0.1\n", r1, t2 ? '=' : '!');  
}
/* $end fcomp5-c */

int main(int argc, char *argv[])
{
    int denom = 10;
  /*
  int denom = atoi(argv[1]);
  */
  test1(denom);
  test2(denom);
  test3(denom);
  test4(denom);
  test5(denom);
  printf("A long double on this machine requires %d bytes\n", sizeof(long double));
  return 0;
}



