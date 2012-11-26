/* $begin shp-proto */
    int signed_high_prod(int x, int y);
/* $end shp-proto */

/* $begin uhp-proto */
    unsigned int unsigned_high_prod(unsigned x, unsigned y); 
/* $end uhp-proto */



/* $begin uhp-ans */
unsigned unsigned_high_prod(unsigned x, unsigned y) 
{ 
    unsigned p = (unsigned) signed_high_prod((int) x, (int) y); 

    if ((int) x < 0) /* x_{w-1} = 1 */ 
	p += y; 
    if ((int) y < 0) /* y_{w-1} = 1 */ 
	p += x; 
    return p; 
} 
/* $end uhp-ans */

