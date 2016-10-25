#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


/*

Surprisingly there are only three numbers that can be written as the sum of fourth powers of their digits:

    1634 = 1^4 + 6^4 + 3^4 + 4^4
    8208 = 8^4 + 2^4 + 0^4 + 8^4
    9474 = 9^4 + 4^4 + 7^4 + 4^4

As 1 = 1^4 is not a sum it is not included.

The sum of these numbers is 1634 + 8208 + 9474 = 19316.

Find the sum of all the numbers that can be written as the sum of fifth powers of their digits.


Ehhhhrrrrr ? Wut?

I'm thinking there aren't very many
Let's list all 5th powers of digits
0^5 = 0
1^5 = 1
2^5 = 32
3^5 = 243
4^5 = 1024
5^5 = 3125
6^5 = 7776
7^5 = 16807
8^5 = 32786
9^5 = 59049

I guess we could just count from 10-something and then check things? Since per the question this must be a limited set,
I feel there is a better way...

Just playing a bit has generated:
4150
4151
54748
92727
93084
194979

(checking up to 100M, so I think that's all of them, but that doesn't explain why though)

Maybe some constraints:
9s only occur in numbers with 5-6 digits
And now that I think about it, that puts the max around 6 digits, since even if you fill that up with 9s you get another 
number with 6 digits. And more than 6 digits will only produce numbers with less digits than itself. 
(unless you have like 20x9, which sums to a 7-8 digit number but is much longer itself)
So testing up to 999999 seems reasonable.

*/

static int to_the_fifth[10];

uint64_t sum_5th_powers_of_digits( uint64_t n ) {
	
	uint64_t result = 0;
	
	int digit;
	int raised;
	while( n > 0 ) {
		digit = n % 10;
		result += to_the_fifth[digit];
		n /= 10;
	}
	
	return result;
}

int main(int argc, char** argv) {
	
	uint64_t result = 0;

	for( int i=0; i<10; i++ ) {
		to_the_fifth[i] = i*i*i*i*i;
	}

	uint64_t sum;
	for(uint64_t i=10; i<999999; i++ ) {

		sum = sum_5th_powers_of_digits(i);
		if( sum == i ) {
			// printf("Sum 5th %llu = %llu\n", i, sum);
			result += i;
		}
	}

	printf("Problem 030: %llu\n", result);

}
