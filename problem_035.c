#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/*

The number, 197, is called a circular prime because all rotations of the digits: 197, 971, and 719, are themselves prime.

There are thirteen such primes below 100: 2, 3, 5, 7, 11, 13, 17, 31, 37, 71, 73, 79, and 97.

How many circular primes are there below one million?

First, there are 78,498 primes below 1M, and that calculates in about 1-2 seconds

*/



int is_prime( uint64_t n ) {

	if( n <= 1 ) {
		return 0;
	}
	
	if( n == 2 ) {
		return 1;
	}
	
	if( n % 2 == 0 ) {
		return 0;
	}
	
	for(uint64_t i=3; i<=sqrt(n); i+=2 ) {
		if( n % i == 0 ) {
			return 0;
		}
	}
	return 1;
}


int main(int argc, char** argv) {
	
	uint64_t result = 0;

	
	int max = 1*1000*1000;
	double log_10 = log(10);
	result = 1; // since 2 is a rotating prime
	for( int i=3; i<max; i+=2 ) {

		if( is_prime(i) ) {
			// printf("%d\n", i);
			int rotated = i;
			int all_rotations_are_prime = 1;
			do {
				int last_digit = rotated % 10;
				int power_10 = log(i)/log_10;
				rotated = last_digit * pow( 10, power_10 ) + (rotated / 10);
				// printf("Rot: %d\n", rotated);
				all_rotations_are_prime = all_rotations_are_prime && is_prime( rotated );	
			} while( rotated != i );
			if( all_rotations_are_prime ) {
				// printf("All rot prime: %d\n", i);
				result++;
			}
		}
	}

	printf("Problem 035: %llu\n", result );

}
