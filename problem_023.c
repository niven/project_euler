#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/*

A perfect number is a number for which the sum of its proper divisors is exactly equal to the number. For example, the sum of the proper divisors of 28 would be 1 + 2 + 4 + 7 + 14 = 28, which means that 28 is a perfect number.

A number n is called deficient if the sum of its proper divisors is less than n and it is called abundant if this sum exceeds n.

As 12 is the smallest abundant number, 1 + 2 + 3 + 4 + 6 = 16, the smallest number that can be written as the sum of two abundant numbers is 24. By mathematical analysis, it can be shown that all integers greater than 28123 can be written as the sum of two abundant numbers. However, this upper limit cannot be reduced any further by analysis even though it is known that the greatest number that cannot be expressed as the sum of two abundant numbers is less than this limit.

Find the sum of all the positive integers which cannot be written as the sum of two abundant numbers.

*/

int is_abundant_number( int n ) {
	
	int result = 0;
	
	for( int i=1; i<n; i++ ) {
		if( n % i == 0 ) {
			result += i;
		}
	}
	
	return result > n;
}


int main(int argc, char** argv) {
	
	uint64_t result = 0;
	
	int n = 28124; //28124;
	int abundant[n];
	memset( abundant, 0, sizeof(abundant) );
	
	// find all abundant numbers
	for( int i=1; i<n; i++ ) {
		// count as a divisor all multiples of i
		for( int j=2*i; j<n; j+=i ) {
			abundant[j] += i;
		}
	}

	// turn into bools
	for( int i=1; i<n; i++ ) {
		abundant[i] = abundant[i] > i;
	}


	// now I want to loop over the abundant ones, but the abundant[] has gaps
	int abundant_packed[n];
	memset( abundant_packed, 0, sizeof(abundant_packed) );
	int ap = 0;
	for( int i=0; i<n; i++ ) {
		if( abundant[i] ) {
			abundant_packed[ap++] = i;
		}
	}
	
	// for each number, check if it is a sum of 2
	for( int i=1; i<n; i++ ) {

		// check against each abundant one
		int is_sum = 0;
 
		for( int a=0; a<ap; a++ ) {

			if( abundant_packed[a] >= i ) {
				break;
			}

			if( abundant[ i - abundant_packed[a] ] ) {
				is_sum = 1;
				break;
			}
		}
		if( !is_sum ) {
			result += i;
		}
		
	}
	
	printf("Problem 023: %llu\n", result);

}
