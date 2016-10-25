#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/*

The number, 1406357289, is a 0 to 9 pandigital number because it is made up of each of the digits 0 to 9 in some order, 
but it also has a rather interesting sub-string divisibility property.

Let d1 be the 1st digit, d2 be the 2nd digit, and so on. In this way, we note the following:

    d2 d3 d4 = 406 is divisible by 2
    d3 d4 d5 = 063 is divisible by 3
    d4 d5 d6 = 635 is divisible by 5
    d5 d6 d7 = 357 is divisible by 7
    d6 d7 d8 = 572 is divisible by 11
    d7 d8 d9 = 728 is divisible by 13
    d8 d9 d10 = 289 is divisible by 17

Find the sum of all 0 to 9 pandigital numbers with this property.

a) all pandigitals and check (slow, boring)
b) construct valid pandigitals based on restrictions:
d3+d4+d5 must be divisible by 3
d4 must be 0,2,4,6,8
etc
Kind of 'progression of constraints' approach. This won't help too much though:
the only restrictions are really on division by 2,3,5 (rule for 11 won't eliminate that much)

c) 'backtracking'? Start with all 3 digit numbers without repetition that are divisible by 17, can't be that many..


*/

uint64_t extend_number( int* candidate, int pos, int* divs ) {

	uint64_t result = 0;

	// Because d1 d2 d3 is divisible by 1 anyway
	if( pos == 9 ) {

		// turn it into a number
		for( int i=0; i<10; i++ ) {
			result *= 10;
			result += candidate[9-i];
		}
		// printf("Result: %llu\n", result);
		return result;
	}
	
	int save = candidate[pos];
	int test_num;
	for( int j=pos; j<10; j++ ) {

		test_num = 100 * candidate[j] + 10 * candidate[pos-1] + candidate[pos-2];
		if( test_num % divs[pos-3] == 0 ) {

			// set that number at the right place
			candidate[pos] = candidate[j];
			candidate[j] = save;

			result += extend_number( candidate, pos+1, divs );

			// put the numbers back in case there are more valid swaps
			candidate[j] = candidate[pos];
			candidate[pos] = save;
		}
	}
	
	return result;
}

int main(int argc, char** argv) {
	
	uint64_t result = 0;
	
	int divs[] = { 13, 11, 7, 5, 3, 2 };
	int num_divs = sizeof(divs)/sizeof(divs[0]);
	
	for( int i=1; i<1000/17; i++ ) { // last 3 digits could be 017
		int mul_17 = i*17;

		int candidate[] = { mul_17%10, (mul_17/10)%10, mul_17/100, 0, 0,0,0, 0,0,0 };

		// skip this one if it has repeated digits, it can't be pandigital
		if( candidate[0] == candidate[1] || candidate[1] == candidate[2] || candidate[0] == candidate[2] ) {
			continue;
		}
		
		
		// fill up the rest of candidate with the unused numbers
		int pos = 3;
		for( int j=0; j<10; j++ ) {
			if( candidate[0] != j && candidate[1] != j && candidate[2] != j ) {
				candidate[pos++] = j;
			}
		}
		assert( pos == 10 );

		// try remaining digits in the next position, and check the next divisor
		// (this ensures we never repeat digits and so do the least amount of work)
		result += extend_number( candidate, 3, divs );
	}

	
	printf("Problem 043: %llu\n", result );

}

