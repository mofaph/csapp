/* $begin absdiff-c */
int absdiff(int x, int y) 
{ 
    if (x < y) 
	return y - x; 
    else 
	return x - y; 
} 
/* $end absdiff-c */

/* $begin gotodiff-c */
int gotodiff(int x, int y) 
{ 
    int rval; 

    if (x < y) 
	goto less; 
    rval = x - y; 
    goto done; 
 less: 
    rval = y - x; 
 done: 
    return rval; 
} 
/* $end gotodiff-c */

/* $begin absdiff2-c */
int absdiff2(int x, int y) 
{ 
    int result; 

    if (x < y) 
	result = y-x; 
    else 
	result = x-y; 
    return result; 
} 
/* $end absdiff2-c */
