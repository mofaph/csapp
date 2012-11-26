#include <stdlib.h>

typedef int row3_t[3];
typedef row3_t array4_3_t[4];

array4_3_t A;

int get_value(array4_3_t A, int i, int j)
{
    return A[i][j];
}

row3_t row0, row1, row2, row3;
int *B[4] = {row0, row1, row2, row3};

int get_value2(int *B[4], int i, int  j)
{
    return B[i][j];
}

/* $begin fixprodele-c */
/* $begin fixmatrixdef-c */
#define N 16
typedef int fix_matrix[N][N];
/* $end fixmatrixdef-c */

/* Compute i,k of fixed matrix product */
int fix_prod_ele (fix_matrix A, fix_matrix B,  int i, int k)
{
    int j;
    int result = 0;

    for (j = 0; j < N; j++)
	result += A[i][j] * B[j][k];

    return result;
}
/* $end fixprodele-c */

/* $begin fixprodeleopt-c */
/* Compute i,k of fixed matrix product */
int fix_prod_ele_opt(fix_matrix A, fix_matrix B, int i, int k)
{
    int *Aptr = &A[i][0];
    int *Bptr = &B[0][k];
    int cnt = N - 1;
    int result = 0;

    do {
	result += (*Aptr) * (*Bptr);
	Aptr += 1;
	Bptr += N;
	cnt--;
    } while (cnt >= 0);

    return result;
}
/* $end fixprodeleopt-c */

int fix_ele(fix_matrix A, int i, int j)
{
    return A[i][j];
}

/* $begin varmatrixdef-c */
/* $begin varprodele-c */
typedef int *var_matrix;
/* $end varprodele-c */
/* $end varmatrixdef-c */

/* $begin varnewmatrix-c */
var_matrix new_var_matrix(int n)
{
    return (var_matrix) calloc(sizeof(int), n * n);
}
/* $end varnewmatrix-c */

/* $begin varele-c */
int var_ele(var_matrix A, int i, int j, int n)
{
    return A[(i*n) + j];
}
/* $end varele-c */

/* $begin varprodele-c */

/* Compute i,k of variable matrix product */
int var_prod_ele(var_matrix A, var_matrix B, int i, int k, int n)
{
    int j;
    int result = 0;

    for (j = 0; j < n; j++)
	result += A[i*n + j] * B[j*n + k];

    return result;
}
/* $end varprodele-c */


/* $begin varprodeleopt-c */
/* Compute i,k of variable matrix product */
int var_prod_ele_opt(var_matrix A, var_matrix B, int i, int k, int n)
{
    int *Aptr = &A[i*n];
    int nTjPk = k;
    int cnt = n;
    int result = 0;

    if (n <= 0)
	return result;

    do {
        result += (*Aptr) * B[nTjPk];
	Aptr += 1;
	nTjPk += n;
	cnt--;
    } while (cnt);

    return result;
}
/* $end varprodeleopt-c */

/* $begin fixdiag-c */
/* Set all diagonal elements to val */
void fix_set_diag(fix_matrix A, int val)
{
  int i;
  for (i = 0; i < N; i++)
    A[i][i] = val;
}
/* $end fixdiag-c */

/* $begin fixdiagopt-c */
/* Set all diagonal elements to val */
void fix_set_diag_opt(fix_matrix A, int val)
{
  int *Aptr = &A[0][0] + 255;
  int cnt = N-1;
  do {
    *Aptr = val;
    Aptr -= (N+1);
    cnt--;
  } while (cnt >= 0);
}
/* $end fixdiagopt-c */

