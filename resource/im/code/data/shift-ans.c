/* $begin shift-ans */
int int_shifts_are_arithmetic()
{
    int x = ~0; /* All 1's */
    
    return (x >> 1) == x;
}
/* $end shift-ans */

