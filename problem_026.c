#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/*

A unit fraction contains 1 in the numerator. The decimal representation of the unit fractions with denominators 2 to 10 are given:

    1/2	= 	0.5
    1/3	= 	0.(3)
    1/4	= 	0.25
    1/5	= 	0.2
    1/6	= 	0.1(6)
    1/7	= 	0.(142857)
    1/8	= 	0.125
    1/9	= 	0.(1)
    1/10	= 	0.1

Where 0.1(6) means 0.166666..., and has a 1-digit recurring cycle. It can be seen that 1/7 has a 6-digit recurring cycle.

Find the value of d < 1000 for which 1/d contains the longest recurring cycle in its decimal fraction part.

So you get a cycle when the remainder after division repeats.
Easiest way to not mess around with fractions etc is just to shift the numerator untl its bigger than the
denominator.

*/

int main(int argc, char** argv) {
	
	uint64_t result = 0;
	
	int num_reps = 0;
	int n = 1;
	int rest = -1;
	int divisor = 7;
	int quot = 0;
	int max_rem = 1000;
	int rems[max_rem];
	
	for( int a=2; a<1000; a++ ) {

		n = 1;
		divisor = a;
		rest = -1;
		// printf( "%d / %d = 0.", n, a);
		memset( rems, 0, sizeof(rems) );
		while( rest != 0 ) {
		
			while( n < divisor ) {
				n *= 10;
			}

			quot = n / divisor;
			// printf("%llu", quot );
			rest = n % divisor;

			if( rems[rest] ) {
				int reps = 0;
				for(int i=0; i<max_rem; i++) {
					reps += rems[i];
				}

				if( reps > num_reps ) {
					num_reps = reps;
					result = a;
				}
				break;
			}
			rems[rest] = 1;
			n = rest;
		}

		
	}
	
	printf("Problem 026: %llu\n", result);

}
