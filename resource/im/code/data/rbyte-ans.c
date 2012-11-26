/* $begin rbyte-proto */
unsigned replace_byte (unsigned x, int i, unsigned char b); 
/* $end rbyte-proto */

/* $begin rbyte-ans */
unsigned replace_byte (unsigned x, int i, unsigned char b) 
{ 
    int itimes8 = i << 3; 
    unsigned mask = 0xFF << itimes8; 

    return (x & ~mask) | (b << itimes8);
} 
/* $end rbyte-ans */

