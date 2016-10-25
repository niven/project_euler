#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/*

The first two consecutive numbers to have two distinct prime factors are:

14 = 2 × 7
15 = 3 × 5

The first three consecutive numbers to have three distinct prime factors are:

644 = 2² × 7 × 23
645 = 3 × 5 × 43
646 = 2 × 17 × 19.

Find the first four consecutive integers to have four distinct prime factors. What is the first of these numbers?

So there are distinct primes, not consecutive and destinct primes (though that would be more cool)

So contructing numbers from 4 distinct factors is terrible (I think) since there is no way to say which ones are
involved so we need to keep track of all of them.

Starting with numbers and factoring them (moving on when there are not exactly 4) and then repeating seems the most
straightforward (except the fact that you endlessly factor numbers that don't have exactly 4 factors)

More crazy idea: find 4 composite numbers in a row, then test for 16 unique factors
That happens 194,075 times under a million, and it does involve checking every number for primality

Muhahahaha!
if we multiply 644 * 645 * 646 we get 268335480 which has all the factors of the 3 numbers!

Sigh: seems like the meaning is have T distinct prime factors each :(

So this is fine, except for target=4 it takes too long (15.70 seconds)
Bailing out after factoring the first number and missing the target reduces that to 15.09 seconds.

So, next try (since 259368 is incorrect, though it matches it's probably not the first one):

Go over all numbers, and only count factors (since primes have 1, it doesn't matter)
So answer: 134043
But takes 15.89 seconds (skipping the matches so far saves 0.11 seconds)
Not trying to find even factors makes this 7.50 seconds

Ugh, so not even probing (not that kind) in increments of target make this any faster.
Only outstading idea: provide a list of the first 1000 primes or so to the count_factors() function.

*/

int count_factors( uint64_t n ) {
	// printf("\tfactors of %llu\n", n);
	int num_factors = 0;
	
	// first strip off all powers of 2
	if( n % 2 == 0 ) {
		num_factors++;
		do {
			n /= 2;
		} while( n % 2 == 0 );
	}
	
	uint64_t divisor = 3;
	while( n != 1 ) {

		// find the next divisor
		while( n % divisor != 0 ) {
			divisor += 2; // skip all even numbers
		}
		// account for 2x2x2x3 etc
		// int power = 0;
		while( n % divisor == 0 ){
			n /= divisor;
			// power++;
		}
		// printf("\tfactor: %llu ^ %d\n", divisor, power);
		num_factors++;
	}
	
	return num_factors;
}

int main(int argc, char** argv) {
	
	uint64_t result = 0;

	int target = 4;
	uint64_t i = 1;

	// we're going to go in increments of target
	// and when we find one we look both ways to see if we're done
	// this to hopefully avoid checking every single number
	// turns out for targets up to 4 that still means pretty much factoring every number :(
	// so not doing that.

	while( 1 ) {

		// find a possible start
		if( count_factors( i ) == target ) {

			int matches = 1;
			for( int j=1; j<=target; j++ ) {
				if( count_factors( i+j ) == target ) {
					matches++;
				} else {
					break;
				}
			}
			
			if( matches == target ) {
				result = i;
				break;
			} else {
				i += matches - 1;
			}

		} 
	
		i++;
	}


	printf("Problem 047: %llu\n", result);

}
