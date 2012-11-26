/* $begin switchbody-ans-c */
int switch_prob(int x) 
{ 
    int result = x; 

    switch(x) { 
    case 50: 
    case 52: 
	result <<= 2; 
	break; 
    case 53: 
	result >>= 2; 
	break; 
    case 54: 
	result *= 3; 
	/* Fall through */ 
    case 55: 
	result *= result; 
	/* Fall through */
    default: 
	result += 10; 
    } 

    return result; 
} 
/* $end switchbody-ans-c */


int main() {
    int val = switch_prob(53);
    return val;
}
