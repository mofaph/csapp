typedef int *var_matrix;

/* $begin varprod-ans-c */
int var_prod_ele_opt (var_matrix A, var_matrix B, int i, int k, int n) 
{ 
    int *Aptr = &A[i*n]; 
    int *Bptr = &B[k]; 
    int result = 0; 
    int cnt = n; 

    if (n <= 0) 
	return result; 

    do { 
	result += (*Aptr) * (*Bptr); 
	Aptr += 1; 
	Bptr += n; 
	cnt--; 
    } while (cnt); 

    return result; 
} 
/* $end varprod-ans-c */





