#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


/*


The sum of the squares of the first ten natural numbers is,
1^2 + 2^2 + ... + 10^2 = 385

The square of the sum of the first ten natural numbers is,
(1 + 2 + ... + 10)^2 = 55^2 = 3025

Hence the difference between the sum of the squares of the first ten natural numbers and the square of the sum is 3025 − 385 = 2640.

Find the difference between the sum of the squares of the first one hundred natural numbers and the square of the sum.

*/

uint64_t sum_n( uint64_t n ) {
	
	// save division until last, to avoid fractions
	return ((n+1)*n)/2;	
}

uint64_t sum_of_squares( uint64_t n ) {

	uint64_t result = 0;
	
	for( uint64_t i=1; i<=n; i++ ) {
		result += i*i;
	}
	
	return result;
}


int main(int argc, char** argv) {
	
	uint64_t result = 0;
	uint64_t n = 100;

	uint64_t square_of_sum = sum_n(n) * sum_n(n);
	
	uint64_t sum_squares = sum_of_squares(n);

	result = square_of_sum - sum_squares;

	printf("Problem 006: %llu\n", result);

}