#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/*

The arithmetic sequence, 1487, 4817, 8147, in which each of the terms increases by 3330, 
is unusual in two ways: 
(i) each of the three terms are prime, and, 
(ii) each of the 4-digit numbers are permutations of one another.

There are no arithmetic sequences made up of three 1-, 2-, or 3-digit primes, 
exhibiting this property, but there is one other 4-digit increasing sequence.

What 12-digit number do you form by concatenating the three terms in this sequence?

Mathmaticians must sometimes be *really* bored :)

So dumb solution first, as usual:
1. find each 4 digit prime
2. for each prime you find, find its permutations, and check for primality (something something about not all permutations are)
3. check for arithmetic property

OR
Go with arithmetic first, then check for is_permutation

Fact: 1061 primes of 4 digits
Hmm, we can just go over all of the primes, and then sort them by digits, and count in those slots..
That will mean we get the permutations, but maybe not the arithmetic rule..
(though if there is only 1 other, we could just subtract any 2)

So with ghetto sorting and using that as a 'hash' we get 143 permutations of primes.
( the best one is 1237 with 11 permutations that are prime:
Prime: 1237 = 1237
Prime: 1327 = 1237
Prime: 1723 = 1237
Prime: 2137 = 1237
Prime: 2371 = 1237
Prime: 2713 = 1237
Prime: 2731 = 1237
Prime: 3217 = 1237
Prime: 3271 = 1237
Prime: 7213 = 1237
Prime: 7321 = 1237
)

Anyway, that seems fast enough, and more BS will get us there

Restricting the permutations to 3, we get 36 sets:
1118, 1124, 1147, 1169, 1189, 1223, 1229, 1244, 1246, 1259, 1334, 1366, 1469, 1489, 
1777, 2239, 2335, 2336, 2345, 2459, 2479, 2578, 2677, 3337, 3358, 3368, 3389, 3556, 
3599, 4577, 4699, 4789, 5669, 6679, 6689, 6778

Which does not include the example though, so there is a mistake somewhere.
Oh, 1478 permutes to 8 primes (1487,1847,4817,4871,7481,7841,8147,8741)

So we would need to check all of them with >=3 permutations.

Time for a better approach.

Let's visualize:

A-----------B------------C

We can go over all numbers an find primes. At some point we find C
Then we can sort the digits of C and find A and then check if B is a prime and also sorts to A.

That's pretty simple and nice.
One snag:
A------------B-----C-----D
The cycle could be BCD.

So what we need to do is find primes, and when we do sort them to find A, and then point a to B, B to C etc
and then we can find the cycle.
Note: A could still be composite, while B+ are all primes

Actually, there could be inbetween primes, like in the example:


1478----1487----1847----4817----4871----7481----7841----8147
A-------B-------C-------D-------E-------F-------G-------H

Where the cycle is B-D-H

So now, how do we find 3 numbers seperated by the same interval if more numbers could be mixed in?

Well, every point that is not an end point could be a middle (except when the end points are not included)

*/

int is_prime( uint64_t n ) {

	if( n <= 1 ) {
		return 0;
	}
	if( n == 2 ) {
		return 1;
	}
	if( n % 2 == 0 ) {
		return 0;
	}
	for(uint64_t i=3; i<=sqrt(n); i+=2 ) {
		if( (n % i == 0) ) {
			return 0;
		}
	}

	return 1;
}

int sort( int n ) {
	
	int numbers[10] = {0, 0,0,0, 0,0,0, 0,0,0 };
	numbers[ n/1000 ]++;
	numbers[ (n%1000) / 100 ]++;
	numbers[ (n%100) /10 ]++;
	numbers[ n%10 ]++;

	int p = 1000;
	int out = 0;
	for( int i=0; i<10; i++ ) {
		while( numbers[i] --> 0 ) {
			out += p*i;
			p /= 10;			
		}
		
	}

	return out;
}

void find_thing() {
	
	int d = rand() % 50;
	int a = rand() % 50;
	int b = a + d;
	int c = b + d;
	
	int L[100];
	int end = 3; //abc
	
	int pre = rand() % 5;
	end += pre;
	int last = 0;
	for(int i=0; i<pre; i++){
		L[i] = last + (rand() % a);
		last = L[i];
	}
	L[pre] = last + a;
	
	for( int i=0; i<end; i++ ) {
		printf("%d ", L[i]);
	}
	printf(": a-b-c (d) = %d-%d-%d (%d)\n",a ,b,c,d);
	
}

int main(int argc, char** argv) {
	
	uint64_t result = 0;
	int start = 1001, end = 10*1000;
	int sps[end];
	
	// set everything to -1 indicating not prime
	memset( sps, -1, sizeof(sps) );

	for( int i=start; i<end; i+=2 ) {
		
		if( is_prime(i) ) {
			sps[i] = 0; // indicate prime
			int sorted = sort(i); // this will be A
			printf("Prime: %d / %d -> A:%d\n", i, i-sorted, sorted);
			if( sorted < start ) {
				continue;
			}
			if( sorted != i ) {
				
				// start chaining
				if( sps[sorted] <= 0 ) {
					sps[sorted] = i;
				} else {
					int current = sorted;
					while( sps[current] != 0 ) {
						printf("\tlinks to %d / %d\n", sps[current], sps[current]-sorted );
						current = sps[current];
					}
					printf("\tend %d\n", sps[current]);
					sps[current] = i;
				}
			}
		}
	}
#if 0	
	// show the map
	for( int i=start; i<end; i++ ) {
		if( sps[i] > 0 ) {
			printf("Chain %d", i);
			int current = i;
			printf(" %d", sps[current]);
			while( current != 0 ) {				
				printf(" %d", sps[current]);
				current = sps[current];
			}
			// do {
			// 	int current = sps[current];
			// 	printf(" - %d", current);
			// } while( current > 0 );
			printf("\n");
		}
	}
#endif
	
	for( int i=0; i<10; i++ ) {
		find_thing();
	}
	
	
	printf("Problem 049: %llu\n", result);

}
