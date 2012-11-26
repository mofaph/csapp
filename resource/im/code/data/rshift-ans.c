#include <stdlib.h>
#include <stdio.h>

/* $begin srl-ans */
unsigned srl(unsigned x, int k) 
{ 
    /* Perform shift arithmetically */ 
    unsigned xsra = (int) x >> k; 
    /* Make mask of low order 32-k bits */ 
    unsigned mask = k ? ((1 << (32-k)) - 1) : ~0; 

    return xsra & mask;  
} 
/* $end srl-ans */
   
/* $begin sra-ans */
int sra(int x, int k) 
{ 
    /* Perform shift logically */ 
    int xsrl = (unsigned) x >> k; 
    /* Make mask of high order k bits */ 
    unsigned mask = k ? ~((1 << (32-k)) - 1) : 0; 

    return (x < 0) ? mask | xsrl : xsrl; 
} 
/* $end sra-ans */


int main(int argc, char *argv[])
{
  int i, v, s;
  for (i = 1; i < argc; i++) {
    v = atoi(argv[i]);
    s = 0;
    printf("0x%x >> %d: Logical 0x%x, Arithmetic 0x%x\n",
	   v, s, srl(v,s), sra(v,s));
    s = 2;
    printf("0x%x >> %d: Logical 0x%x, Arithmetic 0x%x\n",
	   v, s, srl(v,s), sra(v,s));

    s = 31;
    printf("0x%x >> %d: Logical 0x%x, Arithmetic 0x%x\n",
	   v, s, srl(v,s), sra(v,s));
  }
  return 0;
}
