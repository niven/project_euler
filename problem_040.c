#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/*

An irrational decimal fraction is created by concatenating the positive integers:

0.12345678910 1 112131415161718192021...

It can be seen that the 12th digit of the fractional part is 1.

If d_n represents the nth digit of the fractional part, find the value of the following expression.

d_1 × d_10 × d_100 × d_1000 × d_10000 × d_100000 × d_1000000

Iiiiiiinteresting....

Maybe somehow find the nth number from d_n?
numbers 1-9 take up 9 digits
numbers 10-99 take up 90*2=180
numbers 100-999 take up 900*3=2700
etc
so we could map them I think
d_100 = in range 10-99 ..eh etc :)
maybe forward is easier
9 digits get you to 9, 91 to go
there are 180 in the next range, each is 2 digits wide
so you need 90/2 = skip 45 and then 1 digit left
skipping 45 means 10+45 = 55
so the first digit of 56, which is 5.
Modulo some off-by-one errors 

So for the number of digits:
(high-low) * width for each width:
1-9 => 9 * 1
10-99 => 90 * 2
100-999 => 900 * 3

so really 9 * 10^n * width
or: 9 * 10^(n-1) * n

123456789
10111213141516171819
20212223242526272829
3031
40
50
60
70
80
90919293949596979899
= 9 * 1 * 1 + 9 * 10 * 2 = 9 + 180 = 189

find 21 digit
make 189 digits, last one is 99 (which is digit 189)
went 189-21 too far: 168
168/2 = 84
99-84 = 15 (target)
remainder 0 (but count back from right!)
so 5
*/

int main(int argc, char** argv) {
	
	uint64_t result = 1;
	
	// ok, so the above allows us to test the d_n to number mapping
	uint64_t indices[] = {1, 10, 100, 1000, 10*1000, 100*1000, 1*1000*1000};
	int num_indices = sizeof(indices)/sizeof(indices[0]);
	uint64_t tens = 1; // 10^0
	int width = 1;
	uint64_t num_digits = 9 * tens * width;
	int current = 0;
	
	while( current < num_indices ) {
		// printf("Looking for digit %llu, have %llu so far\n", indices[current], num_digits);
		if( indices[current] > num_digits ) {
			tens *= 10;
			width++;
			num_digits += 9 * tens * width;
			// printf("Extending to width %d, %llu digits\n", width, num_digits);
		} else {
			// printf("Found the range in width %d, counting back from %llu\n", width, tens*10);
			// now we've overshot in the number of digits
			uint64_t overshot = num_digits - indices[current];// since the count starts at 1, not 0
			// but we're in the right range, width wise
			uint64_t decrement = overshot/width; // int trunc intentional
			// printf("Overshot by %llu, need to count back %llu numbers of width %d\n", overshot, decrement, width);
			uint64_t target_number = (10*tens - 1) - decrement; // 99 is the last of the 2 width numbers, not 100
			// printf("Target number is %llu\n", target_number);
			// now a digit in that number
			int remainder = -(overshot % width); // since we're counting backwards
			// printf("Index-in-number '%llu': %d\n", target_number, remainder);
			char buf[width+1];
			sprintf(buf, "%llu", target_number);
			// printf("Found %llu: %c in %llu\n", indices[current], buf[width+remainder-1], target_number);
			current++;
			result *= buf[width+remainder-1] - '0';
			// printf("\n");
		}
		
		
	}
	
	
	
	printf("Problem 040: %llu\n", result);

}
