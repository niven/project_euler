#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


/*

The number 3797 has an interesting property. Being prime itself, it is possible to continuously 
remove digits from left to right, and remain prime at each stage: 3797, 797, 97, and 7. 
Similarly we can work from right to left: 3797, 379, 37, and 3.

Find the sum of the only eleven primes that are both truncatable from left to right and right to left.

NOTE: 2, 3, 5, and 7 are not considered to be truncatable primes.

Obvious: Can't end or start with a non-prime: 4,6,8,9
Can't actually contain 4,6,8 since abc6d would imply abc6 which isn't prime
same goes for 5:
abc5 is always a multiple of 5
and similar for 0: abc0 is a multiple of 10
and same for 2: abc2 is even

So only allowed digits are 1,3,7,9

now 9 can't be at any end since that would leave 9 as the last truncation.

So maybe start with 1,3,7 and put {1,3,7,9} around those ensuring all options are prime?
Doesn't show how there are 11 though

Also: 3797, 797, 97, 379, 37 are all included so there are 6 outstanding
(unless it refers to some largest number that is truncatablea dn the 'truncations' don't count)

Let's try by hand:

1:
13, 31, 17, 71, 19, 91, 11 as options
eliminate 91 as it is not prime

Eh, except that 1 is not prime :)

Let's try again:
7:
37, 73, 79, 97, 77
eliminate 77
Note: 79 is not legal because it ends up as 9, 97 not valid
But: 73 is valid (number 7)

37:
337, 373, 379, 937, 737, 377
737 not prime, 379 not valid, 377 not prime, 337 not valid, 937 not valid, 377 not valid
But: 373 valid (number 8)

hmm, it's a bit irritating since 379 might be valid post extension

Algorithm time I guess.

So just running a simple loop, we just find all of them since the largest is 739,397

Now, that doesn't explain why there are only 11 which the search would prove.

I don't think this problem is interesting enough to write more fancy code for though.

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

int is_truncatable( uint64_t n ) {
	
	// check left

	uint64_t temp = n;
	while( temp > 10 ) {
		int p10 = pow(10, (int)(log(temp)/log(10)));
		temp = temp % p10;
		if( !is_prime(temp) ) {
			return 0;
		}
	}		

	// check right truncatione
   temp = n;
	while( temp > 10 ) {
		temp /= 10;
		if( !is_prime(temp) ) {
			return 0;
		}
	}

	
	return 1;
	
}


int main(int argc, char** argv) {
	
	uint64_t result = 0;

	int count = 0;
	int i = 11;
	while( count < 11 ) {
		if( is_prime(i) && is_truncatable(i) ) {
			// printf("Trunc prime: %d\n", i);
			result += i;
			count++;
		}
		i += 2;
	}

	printf("Problem 037: %llu\n", result);

}
