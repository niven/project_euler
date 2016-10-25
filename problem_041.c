#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/*

We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n exactly once. 
For example, 2143 is a 4-digit pandigital and is also prime.

What is the largest n-digit pandigital prime that exists?

So generate all the 9-pandigitals, check for primality
repeat for 8,7,6.. etc.

So that would be checking 9! = 362,880 primes at least
That sucks :)
we can limit that by avoiding ones that end in 2 or 5 but still

Alternatively, generate all primes up to 987,654,321, which by way of the Prime Number Theorem
(enjoy finding out really quickly how little math you know if you google that ;)

PI(987654321) = 50,251,452 so that is way, way more than starting on the pandigital end.

Maybe there is some way to figure out acceptable pandigital primes?
for n=4
abcd is a pandigital number, can we 'rule out' digits maybe to ensure primeness?

we know the max prime divisor (worst case) is <= sqrt(4321)
So we make all primes smaller than that.
start with
a = (1,2,3,4)
b = (1,2,3,4)
c = (1,2,3,4)
d = (1,2,3,4)

first prime: 2
abcd/2 is prime implies that d can't be 2 (but how to formalize that?)
second prime: 3
abcd/3 is prime means that? eh, there are some rules for divisibilty I think
for 3, sum of digits must be divisible by 3, so (a+b+c+d)/3 != 3
Interesting, so that doesn't actually depend on the arrangement of the numbers!
so 1+2+3+4=10 so not divisible by 3 however you arrange the numbers!
That's pretty cool.
let's check n=9:
1+2+3+4+5+6+7+8+9 = 45 which is divisible by 3 so no 9 pandigital is prime
Wow, that's pretty cool :)

p8: sums to 36 which can't harbour primes either!

p7: sums to 28, any arrangement of 1..7 will produce a number that is not divisible by 3.

next prime: 5
last digit can't be 5 so that at least reduces the p7 case:
numbers can't end in 2,4,5,6

The rule for 11 implies the difference of the sums of alternating digits are divisible by 11
Example: 3425617 -> 3+2+6+7 - 4+5+1 -> 18-10 -> 8, not divisible by 11, therefore 3,425,617 is not divisible by 11
That does seem unwieldy :)
anyway, there are 7! = 5040 options, of which any ending in 2,4,5,6 we don't have to factor.

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
		if( n % i == 0 ) {
			return 0;
		}
	}
	return 1;
}

uint64_t check_all_pandigitals( char* src, int offset, int len ) {
	
	uint64_t result = 0;
	
	if( offset == len ) {

		switch( src[len-1] ) {
			case '2':
			case '4':
			case '5':
			case '6':
				return 0;
			default:
			{				
				uint64_t number = atol( src );
				return is_prime( number ) ? number : 0;	
			}
		}
		
	}
	
	char buf[len+1];
	strcpy( buf, src );

	char temp;
	for( int i=offset; i<len; i++ ) {
		temp = buf[offset];
		buf[offset] = buf[i];
		buf[i] = temp;
		result = check_all_pandigitals( buf, offset+1, len );
		if( result != 0 ) {
			break;
		}
	}
	
	return result;
}


int main(int argc, char** argv) {
	
	uint64_t result = 0;

	char src[] = "7654321"; // start with the highest number

	// check all p7, then p6 etc
	uint64_t prime_pandigital;
	for( int p=0; p<6; p++ ) {
		prime_pandigital = check_all_pandigitals( src+p, 0, strlen(src+p) );
		if( prime_pandigital != 0 ) {
			break;
		}
	}
	result = prime_pandigital;
	
	printf("Problem 041: %llu\n", result);

}
