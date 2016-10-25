#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/*

A permutation is an ordered arrangement of objects. For example, 3124 is one possible permutation of the digits 1, 2, 3 and 4.
If all of the permutations are listed numerically or alphabetically, we call it lexicographic order. 
The lexicographic permutations of 0, 1 and 2 are:

012   021   102   120   201   210

What is the millionth lexicographic permutation of the digits 0, 1, 2, 3, 4, 5, 6, 7, 8 and 9?

I'm thinking we don't actually need to generate all of them :)
Let's try to find permutation 5 for {0,1,2}

012   
021   
102   
120   
201   
210

Obviously the first column goes in order, and since there are 2 permutations left,
it means that p0 should be ceil(5/2) = 3, or the third item, or 2

now we have 2..

Imagine starting at 201 (the first possible permutation where p0=2)
How many to go before we hit 5? We've already come 4 (2x2) so this is the fifth one, so we're done.

Hmm, that seems promising: recursively find the leftmost digit, and move towards the target number.

012
3 elements
6 perms
need 5
2 per element
so 2 first

2.. (4th)

01
elements
2 perms
need 1
so 01
201=5th

0123
4 elements
24 perms
6 per el
want 8th
1 first
left 023
1023 = (6th)

023
3 elements
6 perms
2 per el
need 2
10..
still need 2 (since going to the next one will be 6)

10..
2 elements
2 perms
need 2
103.

1
1 elements
1 perm
need 0
done
1032 = 8th?

Check:
0123
0132
0213
0231
0312
0321
1023
1032
1203
1230
1302
1320
2013
2031
2103
2130
2301
2310
3012
3021
3102
3120
3201
3210

*/

uint64_t factorial( int i ) {
	uint64_t result = 1;
	
	do {
		result *= i;
	} while( i --> 1 );
	
	return result;
}

void lexicographic_permutation( char* elements, int length, uint64_t goal_permutations ) {
	
	int elements_start = 0;
	uint64_t permutations_per_element;

	while( length > 1 ) {

		permutations_per_element = factorial( length ) / length;

		// pick the first one to not overshoot the goal (and the very first is 1st, not 0th)
		int element_index = (goal_permutations-1) / permutations_per_element;
	
		// extract the element at that index, and shift stuff right to fill the gap
		assert( element_index < length );
		char first_element = elements[elements_start + element_index];
		memmove( &elements[elements_start+1], &elements[elements_start], element_index );
		elements[elements_start++] = first_element;

		// how far do we have to go now?
		// the first one gives you 1st-permutations_per_element-th etc
		// so at any interval we could be overshooting (example: n=4, permutations=24, goal=4 => index=0 => 1st-6th)
		goal_permutations = goal_permutations - (element_index * permutations_per_element);
		length--;
	
	}	

}


int main(int argc, char** argv) {
	
	uint64_t result = 0;
	
	int target = 1*1000*1000;
	char out[] = "0123456789";
	int len = strlen(out);

	lexicographic_permutation( out, len, target );

	printf("Problem 024: %s\n", out);

}
