#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/*


The following iterative sequence is defined for the set of positive integers:

n → n/2 (n is even)
n → 3n + 1 (n is odd)

Using the rule above and starting with 13, we generate the following sequence:
13 → 40 → 20 → 10 → 5 → 16 → 8 → 4 → 2 → 1

It can be seen that this sequence (starting at 13 and finishing at 1) contains 10 terms. Although it has not been proved yet (Collatz Problem), it is thought that all starting numbers finish at 1.

Which starting number, under one million, produces the longest chain?

NOTE: Once the chain starts the terms are allowed to go above one million.

*/

int main(int argc, char** argv) {
	
	uint64_t result = 0;
	int max = 1*1000*1000;

	// memoize everything so we can reuse those counts
	uint64_t terms_per_number[max];
	memset( terms_per_number, 0, sizeof(uint64_t)*max );

	uint64_t current;
	for( int i=1; i<max; i++ ) {
		current = i;
		
		while( current != 1 ) {
			
			if( current < max && terms_per_number[current] != 0 ) {
				terms_per_number[i] += terms_per_number[current] - 1; // avoid counting the break number double
				break;
			}
			
			if( current % 2 == 0 ) {
				current /= 2;				
			} else {
				current = current * 3 + 1;
			}
			terms_per_number[i]++;
		}
		terms_per_number[i]++; // count the last term
	}

	int num = 0;
	int most_terms =0;
	for( int i=0; i<max; i++ ) {
		if( terms_per_number[i] > most_terms ) {
			most_terms = terms_per_number[i];
			num = i;
		}
	}
	result = num;

	printf("Problem 014: %llu\n", result);

}
