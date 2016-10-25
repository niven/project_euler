#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/*

By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the 6th prime is 13.

What is the 10 001st prime number?

*/


int is_prime( uint64_t n ) {
	
	if( n == 2 ) {
		return 1;
	}
	
	for(uint64_t i=2; i<=sqrt(n); i+=1 ) {
		if( n % i == 0 ) {
			return 0;
		}
	}
	
	return 1;
}


int main(int argc, char** argv) {
	
	uint64_t result = 0;
	int prime_id = 10001;
	
	uint64_t n = 2;
	for( int i=1; i<=prime_id; i++ ) {
		
		while( !is_prime(n) ) {
			n++;
		}
		// printf("Prime %d: %llu\n", i, n);
		n++;
	}

	result = n-1;
	printf("Problem 007: %llu\n", result);

}
