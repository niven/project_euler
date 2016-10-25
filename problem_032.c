#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


/*

We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n exactly once; 
for example, the 5-digit number, 15234, is 1 through 5 pandigital.

The product 7254 is unusual, as the identity, 39 × 186 = 7254, containing multiplicand, multiplier, 
and product is 1 through 9 pandigital.

Find the sum of all products whose multiplicand/multiplier/product identity can be written as a 1 through 9 pandigital.
HINT: Some products can be obtained in more than one way so be sure to only include it once in your sum.

First thoughts: this seems like a sudoku kind of thing:
nnnnK x nnnnP fixes the digit in nnnnnnQ
3x4 = ......2 etc
which then reduces the search space vastly

Then there is something with the length of the numbers maybe? 2x3=12 and then we're missing digits
so
n(k) x n(p) = n(max(k,p)+1) at maxium

More boringly: take all numbers 1-9 (9! = 362880) and just factor them, except that you need digits on the left side as
well, so it's really 9 choose 7 = 181440 as a ceiling.
Even just constructing the numbers on the left would be easier than factoring I guess.

Hmm. Maybe there is a more elegant way, maybe by construction?


01

01
10

123
132 swap 1,2
312 swap 0,1
321 swap 1,2
231 swap 0,1
213 swap 1,2

1234 
1243 23
1324 
1342


multipying numbers will always result in a result that has at least digits
equal to the min length of multiplicand and multiplier
well, the above is true but not useful. Some thinking will show that N3 must be 4 digits
which I then put in the for loop condition: but it is even better to just generate all unqiue permutations
of 4 out of 9 digits. C(9, 4) = 126 ( 9*8*7*6 / 4*3*2*1  = 9*7*6 / 3 = 9*7*2 = 63*2 = 126)

But how to generate those? (after that: either pick out the remaining numbers and form into multiplicand/multiplier
 or just factor the number in all ways an check for pandigitalness)

C(3,2) = 3*2/2 = 3
123:
12
23

C(4,2) = 4*3/2 = 6
1234:

12
13
14
23
24
34

Seems quite regular
C(4,3) = 4*3*2 / 3*2 = 4
1234:

123
124
134
234

Pattern C(4,3):
	1 + C(3,2) = 3x'1'
		2 + C(2,1) = 2x'2'
			3,4
		3 + C(1,1) = 1x'3'
			4
	2 + C(2,2) = 1x'2'
			34

So to produce C(4,3):
	element[0] + C(3,2)
	element[1] + C(2,2)
	done (since n == k)

So the idea is to C(9,4) to find all unique sets of 4 digits (9*8*7*6 / 4*3*2 = 126), 
then for each of those find all permutations so we end up all unique P (for N x M = P )
so we never check any double results.

Then take the remaining digits, find all permutations and split them into multiplicand/multipliers (N x M)
and check if N x M == P
This means 5! = 120 combinations of 5 digits, which each split into 1,4 2,3 3,2 4,1 parts for N x M (4 ways each)
But since we are permiting, 1234 split as 12x34 is the same as 34x12 so we end up with half that
(and just swapping N and M when N>M lets us skip the doubles)

Example:

123:
123
1 x 23 KEEP
12 x 3 N>M
132
1 x 32 KEEP
13 x 2 N>M
213
2 x 13 KEEP
21 x 3 N>M
231
2 x 31 KEEP
23 x 1 N>M
312
3 x 12 KEEP
31 x 2 N>M
321
3 x 21 KEEP
32 x 1 N>M

KEEP:
1 x 23
1 x 32
2 x 13
2 x 31
3 x 12
3 x 21

Optimization: make sure length N <= length M. In this case the number of elements is 5, so we need only 1,4 and 2,3 splits :)


So ultimately:
C(9,4) = 126 result sets
4! permutations of the result sets = 24
Then 5! permutations of the remainders = 120
Then for each of those 4 ways to split into N x M of which each occurs twice


126 x 24 x 120 x 4 / 2 = 725,760 things to check



*/

// generate the unique N x M sums for a 5 digit string
void calculate_nxm_results( char* src, int offset, int len, int* results, int* results_index ) {


	if( offset == len ) {

		// now we split it into 1,4 and 2,3 parts as N and M
		
		// split into 1,4
		int N = src[0] - '0';
		int M = atoi( src + 1 );
		results[ (*results_index)++ ] = N * M;
		
		// split into 2,3
		N = (src[0] - '0') * 10 + (src[1] - '0');
		M = atoi( src + 2 );
		results[ (*results_index)++ ] = N * M;
				
		return;
	}

	// this is just lexicographic permutations (and we pass the nxm results along for later)
	char buf[len+1];
	strcpy( buf, src);

	char temp;
	for( int i=offset; i<len; i++ ) {
		temp = buf[offset];
		buf[offset] = buf[i];
		buf[i] = temp;
		calculate_nxm_results( buf, offset+1, len, results, results_index );
	}


}


/*
Generate all unique len! permutations of src in O(len) in lexicographic order
and check each on if it is the nxm_results list
*/
uint64_t check_permutations_against_nxm( char* src, int offset, int len, int* nxm_results ) {

	uint64_t result = 0;
	
	if( offset == len ) {
		int P = atoi( src );
		// printf("PE: %s == %d\n", src, P);
		// now we have a unique sum result P and an array containing all ways the remaining digits
		// can be permuted, assembled into NxM sums and evaluated.
		// So here we just check against nxm_results
		for( int i=0; i<240; i++ ) {
			if( P == nxm_results[i] ) {
				// printf("SCORE: %d\n", P);
				
				// return immediately to avoid counting P twice if it can be written as N1 x M1 and N2 x M2
				return P;
			}
		}
		
		return 0;
	}
	
	// more permuting. Lifting this out would involve callbacks and I don't feel like it
	// a macro would be nice maybe?
	char buf[len+1];
	strcpy( buf, src);

	char temp;
	for( int i=offset; i<len; i++ ) {
		temp = buf[offset];
		buf[offset] = buf[i];
		buf[i] = temp;
		// printf("%c - %s\n", buf[offset], buf);
		result += check_permutations_against_nxm( buf, offset+1, len, nxm_results );
	}

	return result;
}


/*
Choosing K out of N elements C(n,k) = n! / ((n-k)! k!)
Then after that find for each the remaining digits, find all permutations of those,
reduce those to unique NxM sums and calculate the results.
*/	
uint64_t binomial_permutations( char* src, char* buf, int offset, int n, int k ) {

	uint64_t result = 0;
	// printf("C(%d,%d) for %s\n", n, k, src);

	if( k == 1 ) {
		for( int i=0; i<n; i++ ) {
			buf[offset] = src[i];
			
			// find the unused elements of 1-9 (0 is unused)
			int all[] = { 0, 0,0,0, 0,0,0, 0,0,0 };
			// mark the used ones
			for( int i=0; i<offset+1; i++ ) {
				all[ buf[i]-'0' ] = 1;
			}
			char remaining[7];
			memset( remaining, 0, 7 );
			int r_index = 0;
			for( int i=1; i<10; i++ ) {
				if( all[i] == 0 ) {
					remaining[r_index++] = '0' + i;
				}
			}
			// printf("BUF: %s\n", buf);
			// printf("REM: %s\n", remaining);
			// remaining is 5 elements, which permute into 120 options which split 4 ways (2 unique ways)
			// so 240 distinct N x M results
			// Note: I think we could have some doubles still if aa x bbb == cc x ddd, but I don't think so
			// 		and that also won't be a big impact
			int nxm_results[240];
			int results_index = 0;
			calculate_nxm_results( remaining, 0, strlen(remaining), nxm_results, &results_index );
			
			result += check_permutations_against_nxm( buf, 0, offset+1, nxm_results );
		}
		return result;
	}

	int element_index = 0;
	while( n --> k-1 ) {
		buf[offset] = src[element_index++];
		result += binomial_permutations( src + element_index, buf, offset + 1, n, k-1 );
	}

	return result;
}

int main(int argc, char** argv) {
	
	uint64_t result = 0;

	char numbers[] = "123456789";
	int num_len = strlen(numbers);
	char buf[num_len+1];
	memset( buf, 0, num_len+1);
		
	result = binomial_permutations( numbers, buf, 0, num_len, 4 );
	

	printf("Problem 032: %llu\n", result );

}
