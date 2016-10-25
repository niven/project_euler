#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


/*


Take the number 192 and multiply it by each of 1, 2, and 3:

    192 × 1 = 192
    192 × 2 = 384
    192 × 3 = 576

By concatenating each product we get the 1 to 9 pandigital, 192384576. 
We will call 192384576 the concatenated product of 192 and (1,2,3)

The same can be achieved by starting with 9 and multiplying by 1, 2, 3, 4, and 5, 
giving the pandigital, 918273645, which is the concatenated product of 9 and (1,2,3,4,5).

What is the largest 1 to 9 pandigital 9-digit number that can be formed as the 
concatenated product of an integer with (1,2, ... , n) where n > 1?

*/

int is_pandigital( uint64_t n ) {
	
	int digits[10]; // just don't use 0
	memset( digits, 0, sizeof(digits) );

	if( n > 987654321 ) {
		return 0;
	}
	
	char buf[10];
	memset( buf, 0, sizeof(buf) );
	sprintf(buf, "%llu", n );
	if( strlen(buf) != 9 ) {
		return 0;
	}

	// now we have 9 digits
	int cur;
	for( int i=0; i<9; i++ ) {
		cur = buf[i] - '0';
		digits[ cur ]++;
		if( digits[ cur ] > 1 ) {
			return 0;
		}
	}
	// every digit hit once, but digit[0] might be hit more than zero
	return digits[0] ? 0 : 1;
	
}

uint64_t concat_number( uint64_t head, uint64_t tail ) {
	
	// printf("concat %d - %d\n", head, tail);
	uint64_t result = 0;

	int pow10 = log(tail)/log(10);
	
	result = head * pow( 10, pow10+1 ) + tail;
	
	return result;
}

int main(int argc, char** argv) {
	
	uint64_t result = 0;

	uint64_t max_pandigital = 987654321;
	uint64_t sum;

	for( int n=2; n<10; n++ ) {

		int candidate;
		for( candidate=1; candidate<max_pandigital; candidate++ ) {
			
			// do the (1..n) * candidate vector/concat
			sum = 0;
			for( int j=1; j<=n; j++ ) {
				// printf("Adding %d x %d = %d\n", j, candidate, j*candidate);
				sum = concat_number(sum, j*candidate);
				// printf("S: %llu\n", sum);
			}
			// no need to try higher candidates
			if( sum > max_pandigital ) {
				break;
			}
			if( is_pandigital(sum) ) {
				// printf("Pandigital: 1..%d/%d => %llu\n", n, candidate, sum);
				if( sum > result ) {
					result = sum;
				}
			}
			
		}
		
	}


	printf("Problem 038: %llu\n", result);

}
