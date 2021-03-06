#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/*


The sequence of triangle numbers is generated by adding the natural numbers. So the 7th triangle number would be 1 + 2 + 3 + 4 + 5 + 6 + 7 = 28. The first ten terms would be:

1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...

Let us list the factors of the first seven triangle numbers:

     1: 1
     3: 1,3
     6: 1,2,3,6
    10: 1,2,5,10
    15: 1,3,5,15
    21: 1,3,7,21
    28: 1,2,4,7,14,28

We can see that 28 is the first triangle number to have over five divisors.

What is the value of the first triangle number to have over five hundred divisors?

*/

int count_divisors( uint64_t n ) {
	
	int result = 0;
	uint64_t square_root_int = (uint64_t)sqrt(n);
	
	for( uint64_t i=1; i<=square_root_int; i++ ) {
		if( n % i == 0 ) {
			result += 2;
		}
	}
	
	// we counted the sqrt double if that was a divisor
	if( (double)square_root_int == sqrt(n) ) {
		result--;
	}
	
	return result;
}

uint64_t sum_up_to_n( uint64_t n ) {
	
	// save division until last, to avoid fractions
	return ((n+1)*n)/2;	
}


int main(int argc, char** argv) {
	
	uint64_t result = 0;
	
	uint64_t i=0;
	uint64_t triangle_number = 0;
	uint64_t num_divisors = 0;
	while( num_divisors < 500 ) {
		i++;
		triangle_number = sum_up_to_n( i );
		num_divisors = count_divisors( triangle_number );
	}
	result = triangle_number;

	printf("Problem 012: %llu\n", result);

}

