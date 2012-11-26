/* $begin switch-c */
int switch_eg(int x) 
{ 
    int result = x; 

    switch (x) { 

    case 100: 
	result *= 13; 
	break; 

    case 102: 
	result += 10; 
	/* Fall through */ 

    case 103: 
	result += 11; 
	break; 

    case 104: 
    case 106: 
	result *= result; 
	break; 

    default: 
	result = 0;       
    } 

    return result; 
} 
/* $end switch-c */


#if 0
/* $begin switch-impl-c */
/* Next line is not legal C */ 
code *jt[7] = {
    loc_A, loc_def, loc_B, loc_C,  
    loc_D, loc_def, loc_D
}; 
 
int switch_eg_impl(int x) 
{ 
    unsigned xi = x - 100; 
    int result = x; 

    if (xi > 6) 
	goto loc_def; 

    /* Next goto is not legal C */ 
    goto jt[xi]; 

 loc_A:      /* Case 100 */ 
    result *= 13; 
    goto done; 

 loc_B:      /* Case 102 */ 
    result += 10; 
    /* Fall through */ 
    
 loc_C:    /* Case 103 */ 
    result += 11; 
    goto done; 

 loc_D:    /* Cases 104, 106 */ 
    result *= result; 
    goto done; 

 loc_def:  /* Default case*/ 
    result = 0; 

 done: 
    return result; 
} 
/* $end switch-impl-c */
#endif 
