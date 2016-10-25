#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/*

Euler discovered the remarkable quadratic formula:

n² + n + 41

It turns out that the formula will produce 40 primes for the consecutive values n = 0 to 39. 
However, when n = 40, 40^2 + 40 + 41 = 40(40 + 1) + 41 is divisible by 41, 
and certainly when n = 41, 41² + 41 + 41 is clearly divisible by 41.

The incredible formula  n² − 79n + 1601 was discovered, 
which produces 80 primes for the consecutive values n = 0 to 79. 
The product of the coefficients, −79 and 1601, is −126479.

Considering quadratics of the form:

    n² + an + b, where |a| < 1000 and |b| < 1000

    where |n| is the modulus/absolute value of n
    e.g. |11| = 11 and |−4| = 4

Find the product of the coefficients, a and b, for the quadratic expression that produces the maximum number 
of primes for consecutive values of n, starting with n = 0.

So for n^2 + an + b to produce a prime for n=0 we can eliminate all b that are not prime.
Then for n=1 we can eliminate all a and b that do not produce a prime
(although, that might mean a large amout of trials, let's count ops as well)
So it's good to have some primes around I guess?


*/

// Ghetto memoization to avoid checking for primality over and over again
#define num_memoize 4000
static int primes[num_memoize];

int is_prime( uint64_t n ) {

	if( n < num_memoize && primes[n] != -1 ) {
		return primes[n];	
	}
	
	// printf("isp: %llu\n", n);
	if( n <= 1 ) {
		return 0;
	}
	
	if( n == 2 ) {
		return 1;
	}
	
	for(uint64_t i=2; i<=sqrt(n); i+=1 ) {
		if( n % i == 0 ) {
			if( n < num_memoize ) {
				primes[n] = 0;				
			}
			return 0;
		}
	}
	if( n < num_memoize ){
		primes[n] = 1;		
	}
	return 1;
}

/*



*/

int main(int argc, char** argv) {
	
	uint64_t result = 0;

	int range = 1000;
	int min = -range;
	int max = range;
	
	int bc[max - min];

	memset( bc, 0, sizeof(bc) );
	memset( primes, -1, sizeof(primes) );
	
	int result_n, result_a, result_b;
	
	for( int i=min; i<max; i++ ) {
		if( i > 1 && is_prime(i) ) {
			bc[ i + range ] = 1;
		}
	}

	int n;
	for( int a=min; a<max; a++ ) {
		for( int b=min; b<max; b++ ) {

			int b_index = b + range;
			if( bc[b_index] ) {
				n = 0;
				do {
					result_n = n*n + n*a + b;
					n++;
				} while( result_n > 0 && is_prime(result_n) );

				if( n > result ) {
					result = n;
					result_a = a;
					result_b = b;
				} 
			}
		}
	}

	/*
	printf("n^2 + %dn + %d -> %d consecutive primes\n", result_a, result_b, n);
	for( int i=0; i<=n; i++ ) {
		int r = i*i + i*result_a + result_b;
		printf("n=%d => %d => prime: %d\n", i, r, is_prime(r));
	}
	printf("r: %d\n", result_a * result_b);
*/	
	printf("Problem 027: %d\n", result_a * result_b);

}
