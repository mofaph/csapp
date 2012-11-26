#include <stdio.h>
#include <stdlib.h>

float u2f(unsigned u) {
  union {
    unsigned u;
    float f;
  } a;
  a.u = u;
  return a.f;
}

/* $begin fpwr2-ans */
/* Compute 2**x */ 
float fpwr2(int x) { 
 
    unsigned exp, sig; 
    unsigned u; 

    if (x < -149) { 
	/* Too small.  Return 0.0 */ 
	exp = 0; 
	sig = 0; 
    } else if (x < -126) { 
	/* Denormalized result */ 
	exp = 0; 
	sig = 1 << (x + 149); 
    } else if (x < 128) { 
	/* Normalized result. */ 
	exp = x + 127; 
	sig = 0; 
    } else { 
	/* Too big.  Return +oo */ 
	exp = 255; 
	sig = 0; 
    } 
    u = exp << 23 | sig; 
    return u2f(u); 
} 
/* $end fpwr2-ans */

/* Computation based on squaring */
float tpwr2(int x) {
  double result = 1.0;
  double p2 = 2.0;
  int recip = (x < 0);
  if (recip)
    x = -x;
  while (x > 0) {
    if (x & 0x1)
      result *= p2;
    p2 *= p2;
    x >>= 1;
  }
  return (float) (recip ? 1/result : result);
}

/* Run set of tests */
int tp2() {
  int x;
  int err = 0;
  for (x = -200; x < 200; x++) {
    float f1 = fpwr2(x);
    float f2 = tpwr2(x);
    if (f1 != f2) {
      printf("2**%d: %f != %f\n", x, f1, f2);
      err++;
    }
  }
  return err;
}

int main(int argc, char **argv) {
  int err;
  int i, x;
  if (argc > 1) {
    for (i = 1; i < argc; i++) {
      x = atoi(argv[i]);
      printf("2**%d: %f ?= %f\n", x, fpwr2(x), tpwr2(x));
    }
  } else {
    err = tp2();
    if (err) {
      printf("%d errors\n", err);
    } else {
      printf("All tests passed\n");
    }
  }
  return 0;
}



