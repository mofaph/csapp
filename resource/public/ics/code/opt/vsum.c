#define N 1024
int a[N], b[N], c[N];

/* $begin vsum */
void vsum1(int n)
{
    int i;

    for (i = 0; i < n; i++)
	c[i] = a[i] + b[i];
}

/* Sum vector of n elements (n must be even) */
void vsum2(int n)
{
    int i;

    for (i = 0; i < n; i+=2) { 	
	/* Compute two elements per iteration */
	c[i]   = a[i]   + b[i];
	c[i+1] = a[i+1] + b[i+1];
    }
}
/* $end vsum */
