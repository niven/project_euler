#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/*

It was proposed by Christian Goldbach that every odd composite number can be written as the sum of a prime and twice a square.

9 = 7 + 2×1^2
15 = 7 + 2×2^2
21 = 3 + 2×3^2
25 = 7 + 2×3^2
27 = 19 + 2×2^2
33 = 31 + 2×1^2

It turns out that the conjecture was false.

What is the smallest odd composite that cannot be written as the sum of a prime and twice a square?

Composite number: not a prime

Feels like a sieve type approach maybe?

We can make a list off all squares, then x2
then make another list of all primes, then cross assemble until we find a gap
We can start with 1^2 and 2, and then grow it upward, tracking the lowest odd number
That does sound a bit uninspired

all 2*n^2 are of course even, all primes except 2 are odd
maybe checking all odd numbers in a row, then checking all primes up to that number and
seeing if the remainder is twice a square?

At least this algorithms ends at the first one:
the odd number is X, find all primes smaler than X, all squares smaller than X/2 and check them.
meanwhile you can build up the primes and double squares lists.
The downside is keeping track of those.

First, let's see if dumb code just gets there and the number is like 451 or something

Turns out there is an easy dumb number: 5777

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
		if( (n % i == 0) ) {
			return 0;
		}
	}

	return 1;
}


int main(int argc, char** argv) {
	
	uint64_t result = 9; // first odd composite

	while( 1 ) {

		int conjecture_ok = 0;
		for( uint64_t i=1; i < sqrt(result/2); i++ ) {
			uint64_t remainder = result - 2*i*i;
			// printf("\tsquare: 2*%d^2 = %llu, rem=%llu\n", i, 2*i*i, remainder );
			if( is_prime(remainder) ) {
				// printf("\t%llu = %llu + 2*%llu^2 = %llu + %llu\n", result, remainder, i, remainder, 2*i*i);
				conjecture_ok = 1;
				break;
			}
		}
		
		if( !conjecture_ok ) {
			break;
		}
		
		do {
			result += 2;			
		} while( is_prime(result) );
	}

	printf("Problem 046: %llu\n", result);

}
