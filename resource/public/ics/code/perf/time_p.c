#include "clock.h"

void P(void);

/* $begin clear_cache */
/* Number of bytes in the largest cache to be cleared */ 
#define CBYTES (1<<19)   
#define CINTS (CBYTES/sizeof(int)) 

/* A large array to bring into cache */ 
static int dummy[CINTS]; 
volatile int sink; 
 
/* Evict the existing blocks from the data caches */
void clear_cache() 
{
    int i; 
    int sum = 0; 

    for (i = 0; i < CINTS; i++) 
	dummy[i] = 3; 
    for (i = 0; i < CINTS; i++) 
	sum += dummy[i]; 
    sink = sum; 
}
/* $end clear_cache */

/* $begin time_p_warm */
double time_P_warm() 
{
    P(); /* Warm up the cache */
    start_counter(); 
    P(); 
    return get_counter(); 
}
/* $end time_p_warm */

/* $begin time_p_cold */
double time_P_cold() 
{
    P(); /* Warm up instruction cache */ 
    clear_cache(); /* Clear data cache */ 
    start_counter(); 
    P(); 
    return get_counter(); 
}
/* $end time_p_cold */

/* $begin time_p */
double time_P() 
{
    start_counter(); 
    P(); 
    return get_counter(); 
}
/* $end time_p */
