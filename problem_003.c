#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>


/*

The prime factors of 13195 are 5, 7, 13 and 29.

What is the largest prime factor of the number 600851475143 ?

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

int main(int argc, char** argv) {

	uint64_t result = 0;

	uint64_t current = 600851475143;
	uint64_t f = 2;
	
	while( current != 1 ) {
		f = first_factor( current, f );
		assert( current % f == 0 );
		current = current / f;
		// printf("factor: %llu, remaining: %llu\n", f, current);
	}	

	result = f;
	printf("Problem 003: %llu\n", result);
}