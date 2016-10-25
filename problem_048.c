#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/*

The series, 1^1 + 2^2 + 3^3 + ... + 10^10 = 10405071317.

Find the last ten digits of the series, 1^1 + 2^2 + 3^3 + ... + 1000^1000.

So we could just do the calculation MOD 10,000,000,000
(max uint64_t is 18,446,744,073,709,551,615) so that would fit.

That means we'd do 1000*1001/2 = 500,500 calculations, seems doable.

Trying that first.
So that was really fast. I was thinking of complicated things to find the nth digit after M iterations
of a multiplication etc. Guess there is no need :)

*/

int main(int argc, char** argv) {
	
	uint64_t result = 0;

	uint64_t temp;
	int max = 1000;
	int last_digits = 10;
	uint64_t last_digits_mask = pow(10, last_digits);
	
	for( int i=1; i<=max; i++ ) {
		
		temp = i;
		for( int j=1; j<i; j++ ) {
			temp *= i;
			temp = temp % last_digits_mask;
		}
		
		result += temp;
	}

	result = result % last_digits_mask;

	printf("Problem 048: %llu\n", result);

}
