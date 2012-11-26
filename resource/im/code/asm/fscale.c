/* Experiments with asm floating point */

#include <stdio.h>
#include <stdlib.h>

static double val;

/* Compute x * 2^n.  Don't like this one very much. */ 
double scale_kludge(double x, int n) 
{
    /* Insert the following assembly code sequence: 
       fildl 16(%ebp)   # Convert n to floating point and push 
       fldl   8(%ebp)   # Push x 
       fscale           # compute x * 2^n 
       fstpl val        # store at val 
       fstp %st(0)      # Pop n off stack 
    */ 
#ifdef WINNT
    asm("fildl 16(%ebp); fldl 8(%ebp); fscale; fstpl _val; fstp %st(0)");
#else
    asm("fildl 16(%ebp); fldl 8(%ebp); fscale; fstpl val; fstp %st(0)");
#endif
    return val; 
} 

/* $begin scale-ans-c */
/* Compute x * 2^n.  Relies on known stack positions for arguments */
void scale(double x, int n, double *dest)
{
  /* Insert the following assembly code sequence:
     fildl 16(%ebp)    # Convert n to floating point and push
     fldl   8(%ebp)    # Push x
     fscale            # Compute x * 2^n
     movl  20(%ebp)    # Get dest
     fstpl   (%eax)    # Store result at *dest
  */
    asm("fildl 16(%%ebp); fldl 8(%%ebp); fscale; movl 20(%%ebp),%%eax;
        fstpl (%%eax); fstp %%st(0)"
      ::: "%eax");

}
/* $end scale-ans-c */

int main(int argc, char *argv[])
{
  double x = atof(argv[1]);
  int n = atoi(argv[2]);
  double z = scale_kludge(x,n);
  printf("scale_kludge: %f * 2**%d = %f\n", x, n, z);
  scale(x,n,&z);
  printf("scale: %f * 2**%d = %f\n", x, n, z);
  return 0;
}
