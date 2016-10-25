#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


/*

Let d(n) be defined as the sum of proper divisors of n (numbers less than n which divide evenly into n).
If d(a) = b and d(b) = a, where a ≠ b, then a and b are an amicable pair and each of a and b are called amicable numbers.

For example, the proper divisors of 220 are 1, 2, 4, 5, 10, 11, 20, 22, 44, 55 and 110; therefore d(220) = 284. 
The proper divisors of 284 are 1, 2, 4, 71 and 142; so d(284) = 220.

Evaluate the sum of all the amicable numbers under 10000.

Approach:
make an array of N
iterate over every n
add n to every mutliple of n

iterate again and do a lookup to find amicable numbers

*/

int main(int argc, char** argv) {
	
	uint64_t result = 0;
	int n = 10*1000;
	
	int divisor_sums[n];
	memset( divisor_sums, 0, sizeof(divisor_sums));
	// sum all divisors
	for( int i=1; i<n; i++) {
		for( int k=i*2; k<n; k+=i ) { // every multiple of k gets a k as their divisor, excluding n itself
			divisor_sums[k] += i;
		}
	}

	for( int i=1; i<n; i++ ) {
		if( i < n && divisor_sums[i] < n // check bounds, we don't have divisor_sums for numbers > n
			&& i == divisor_sums[divisor_sums[i]] // amicable
			&& i != divisor_sums[i] // exclude perfect numbers ( a != b )
			) {
			// printf("%d - %d\n", i, divisor_sums[i]);
			result += i; // when we check divisor_sums[i] we add the other one of the pair
		}
	}

	printf("Problem 021: %llu\n", result);

}
