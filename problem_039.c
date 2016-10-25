#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/*

If p is the perimeter of a right angle triangle with integral length sides, {a,b,c}, 
there are exactly three solutions for p = 120.

{20,48,52}, {24,45,51}, {30,40,50}

For which value of p ≤ 1000, is the number of solutions maximised?

So to check sides of a right angle triangle: a^2 + b^2 = c^2 where a and b are the smallest numbers

We could
a) find all right triangles for all p and track the one with the most
b) find all right triangles where a+b+c<1000 and see what p's they correspond to

for a)
that means a 1000 times: p*(p-a)*(p-a-b) checks for right triangle
Seems doable

for b)
a:1 .. 1000
b:a .. 1000
c:sqrt(a^2 + b^2)
check for right angleness
count p
which is 498,501 options to check, but limiting to p <= 1000
only takes 76,764 checks
*/


int main(int argc, char** argv) {
	
	uint64_t result = 0;

	int max = 1000;
	int perimeter[max+1]; // just skip 0
	memset( perimeter, 0, sizeof(perimeter) );
	
	uint64_t count = 0;
	int max_ways = 0;
	for( int a=1; a<=max-2; a++ ) {
		for( int b=a; b<=max-a-1; b++ ) {
			int c = sqrt( a*a + b*b ); // ensure triangle, hah!
			int p = a + b + c;
			if( p > max ) {
				break;
			}
			if( c*c == (a*a + b*b) ) { // check for double trunc to nice int
				perimeter[ p ]++;
				// printf("%d^2 + %d^2 = %d^2 = %d (p=%d)\n", a, b, c, c*c, p);
				if( perimeter[p] > max_ways ) {
					max_ways = perimeter[p];
					result = p;
				}
			}
			
			count++;
		}
	}

	printf("Problem 039: %llu\n", result);

}
