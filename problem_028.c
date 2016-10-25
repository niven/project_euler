#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/*

Starting with the number 1 and moving to the right in a clockwise direction a 5 by 5 spiral is formed as follows:

21 22 23 24 25
20  7  8  9 10
19  6  1  2 11
18  5  4  3 12
17 16 15 14 13

It can be verified that the sum of the numbers on the diagonals is 101.

What is the sum of the numbers on the diagonals in a 1001 by 1001 spiral formed in the same way?

Hmm. n=6
43 44 45 46 47 48 49
42 21 22 23 24 25 26
41 20  7  8  9 10 27
40 19  6  1  2 11 28
39 18  5  4  3 12 29
38 17 16 15 14 13 30
37 36 35 34 33 32 31



For spirals of n=3 and higher, the top right corner is always NxN
so the right-up diagonal is 1 + 9 + 25 + 49 aka sum of squares

So what would go for: 
left-up: 1 + 7 + 21 + 43
left-dn: 1 + 5 + 17 + 37
right-d: 1 + 3 + 13 + 31

Let's subtract:
01 09 25 49 (right-up)
01 07 21 43 (left-down)
----------- -
00 02 04 06

(spirals are: 1 3 5 7 so every left-up diagonal is the same as the right-up minus spiral width + 1, makes sense)


01 09 25 49 (right-up)
01 05 17 37 (left-down)
----------- -
00 04 08 12 (so twice the distance from the right-up)

01 09 25 49 (right-up)
01 03 13 31 (right down)
----------- -
00 06 12 18 (thrice)

so maybe it's easier:
spiral 1: 1
spiral 3: right top is 3x3=9, left top=7, left bottom=5, right bottom=3 (each time -2)
spiral 5: RT is 5x5=25, LT=21, LD=17, RD=13
spiral 7: RT is 7x7=49, LT=43, LD=37, RD=31
etc

maybe it's even easier:
Spiral 5:
RT=5x5 - 0x(5-1) = 25
LT=5x5 - 1x(5-1) = 21
LD=5x5 - 2x(5-1) = 17
RD=5x5 - 3x(5-1) = 13

Of course 5x5 = 5x(5-1) + 5
So
(4x (5x(5-1) + 5)) - ( 6x (5-1) ) (4 and 6 are constants)

Thus:
  4n(n-1) + 4n - 6(n-1)
= 4n^2 - 4n + 4n - 6n + 1
= 4n^2 - 6n + 6

Spiral(1) = 1 (function is correct except that all 4 points overlap)
Spiral(3) = 4 x 3^2 - 6x3 + 6 = 36 - 18 + 6 = 24
Spiral(5) = 4 x 5^2 - 6x5 + 6 = 100 - 30 + 6 = 76
So Sum-Diagonals = 1 + 24 + 76 = 101

An amusing diversion.

*/

uint64_t sum_corners_spiral( int dim ) {
	
	if( dim == 1 ) {
		return 1;
	}
	
	uint64_t result;
	
	result = (4 * dim * dim) - (6 * dim) + 6;
	
	return result;
}

int main(int argc, char** argv) {
	
	uint64_t result = 0;
	
	for(int i=1; i<=1001; i+=2) {
		result += sum_corners_spiral( i );
		// printf("Spiral[%d] = %llu\n", i, result);
	}

	printf("Problem 028: %llu\n", result);

}
