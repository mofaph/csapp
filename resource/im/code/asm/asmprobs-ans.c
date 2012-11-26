/* $begin fullumul-ans-proto */
void full_umul(unsigned x, unsigned y, unsigned dest[]); 
/* $end fullumul-ans-proto */


/* $begin fullumul-ans-c */
void full_umul(unsigned x, unsigned y, unsigned dest[]) 
{ 
  asm("movl %2,%%eax; mull %3; movl %%eax,%0; movl %%edx,%1" 
      : "=r" (dest[0]), "=r" (dest[1]) /* Outputs */ 
      : "r"  (x),       "r"  (y)       /* Inputs */  
      : "%eax", "%edx"                 /* Clobbers */ 
     ); 
} 
/* $end fullumul-ans-c */

 
/* $begin longlong-ans-c */
int ok_smul(int x, int y, int *dest) 
{ 
    long long prod = (long long) x * y; 
    int trunc = (int) prod; 

    *dest = trunc; 
    return (trunc == prod); 
} 
/* $end longlong-ans-c */

 
