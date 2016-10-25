#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


/*

2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.

What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?

Factoring those numbers:
10: 2x5
9: 3x3
8: 2x2x2
7: 7
6: 3x2
5: 5
4: 2x2
3: 3
2: 2
1: 1

We want this base:
1x(2x2x2)x(3x3)x(5)x(7) = 2520

From this minimal set we can reconstruct all the factorings of all the numbers.


*/
int is_prime( uint64_t n ) {
	
	if( n == 2 ) {
		return 1;
	}
	
	for(uint64_t i=2; i<sqrt(n); i+=2 ) {
		if( n % i == 0 ) {
			return 0;
		}
	}
	
	return 1;
}

uint64_t first_factor( uint64_t n, uint64_t start ) {

	for( uint64_t i=start; i<=n; i++ ) {
		if( is_prime(i) && (n % i == 0) ) {
			return i;
		}
	}

	return n;
}



uint64_t smallest_number_all_divisors( int max_divisor ) {
	
	uint64_t result;
	
	int factors[ max_divisor+1 ];
	int min_spanning_factors[ max_divisor + 1 ];
	
	memset( factors, 0, sizeof(int) * (max_divisor+1));
	memset( min_spanning_factors, 0, sizeof(int) * (max_divisor+1));
	
	for( int i=max_divisor; i > 1; i-- ) {
		
		uint64_t current = i;
		uint64_t factor = 2;
	
		while( current != 1 ) {
			factor = first_factor( current, factor ); // skip the same factor
			assert( current % factor == 0 );
			current = current / factor;
			factors[factor]++;
		}
		
		for(int k=0; k<=max_divisor; k++ ) {
			if( min_spanning_factors[k] < factors[k] ) {
				min_spanning_factors[k] = factors[k];
			}
			factors[k] = 0;
		}
	}

	result = 1;
	for(int k=0; k<=max_divisor; k++ ) {
		// printf("Min Factor[%d] = %d\n", k, min_spanning_factors[k]);
		while( min_spanning_factors[k] > 0 ) {
			result *= k;
			min_spanning_factors[k]--;
		}
	}

	return result;
}

int main(int argc, char** argv) {
	
	uint64_t result = 0;

	result = smallest_number_all_divisors(20);

	printf("Problem 005: %llu\n", result);

}
