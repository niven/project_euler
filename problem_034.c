#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/*

145 is a curious number, as 1! + 4! + 5! = 1 + 24 + 120 = 145.

Find the sum of all numbers which are equal to the sum of the factorial of their digits.

Note: as 1! = 1 and 2! = 2 are not sums they are not included.

So checking any of this is trivial, finding out some max sounds like the real problem.

What if a number has N digits? it means that the sum of it's digits is between 1 (1 + (N-1)x0) and Nx362880 (Nx9)

So that suggests that numbers with more than 7 digits can't have this property, because even they were all 9s
it would sum up to 2540160 (for 7 9s)
*/

uint64_t factorial( int n ) {
	
	if( n == 0 ) {
		return 1;
	}
	
	uint64_t result = n;
	while( n --> 1 ) {
		result *= n;
	}
	
	
	return result;
}

int main(int argc, char** argv) {
	
	uint64_t result = 0;
	int f[10];
	for( int i=0; i<10; i++ ) {
		f[i] = factorial( i );
	}


	for( uint64_t i=3; i<f[9]*7; i++ ) {
		int j = i;
		uint64_t sum = 0;
		while( j > 0 && sum <= i ) {
			sum += f[ j % 10 ];
			j /= 10;
		}
		// printf("\tSum: %llu\n", sum);
		if( sum == i ) {
			// printf("Digit factorial: %llu\n", sum);
			result += sum;
		}
	}


	printf("Problem 034: %llu\n", result );

}
