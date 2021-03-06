#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/*

Triangle, pentagonal, and hexagonal numbers are generated by the following formulae:
Triangle 	  	Tn=n(n+1)/2 	  	1, 3, 6, 10, 15, ...
Pentagonal 	  	Pn=n(3n−1)/2 	  	1, 5, 12, 22, 35, ...
Hexagonal 	  	Hn=n(2n−1) 	  		1, 6, 15, 28, 45, ...

It can be verified that T(285) = P(165) = H(143) = 40755.

Find the next triangle number that is also pentagonal and hexagonal.

So just going over the Hex numbers and then checking for is_p and is_t just overflows Hex before we find anything.
Could just go with digit vectors, doesn't seem like there is any math to help out much here

Maybe starting with that number, and squaring it or something else that maintains the right properties?

T: 1/2 * t^2 + 1/2 * t = X
P: 3/2 * p^2 + 1/2 * p = X
H: 2/1 * h^2 - 1/1 * h = X

Hmm, algebra seems pointless.

Maybe some way to compare these things _without_ generating those large overflow numbers?
H(143) == P(X) maybe some way to find if there is an X that is valid?

So H(143) = 143*285, can we turn that into:
286*570 = p * (3p-1)
or
286*570 = 3p^2 - p
The right hand of that solves as:
( 1 +- sqrt( 1 - 12*(-286*570)  ) ) / 6
so that's more or less
(1 + sqrt(12)*sqrt(286)*sqrt(570)) / 6
and then we search aroung that number maybe?
Then we still end up with 286*570 =? AAA * BBB

Maybe easier for triangles?
H(143) = 

New thought:
H(143) = 143 * 285, which factors to (11*13)*(3*5*19)
Then checking if that fits P(x):
x * (3*x-1) / 2
So that means taking every combination A of
B = F(H(143))(2,3,5,11,13,19) and checking if (B-A) == 3x-1 where x is Product(A)

So that is annoying (but also what computers are for) but will we end up with large intermediate results?
(like A=(2) and B-A = 3*5*11*13*19 ? Not sure how to avoid that

Note: (3*5*11) * (2*13*19) == x*(3x-1) == P(x=165)

 
I get the strong feeling there must be a better way to go about this..

Strong feeling confirmed:
the hexagonal() function took a param int n, and then did uint64_t result = n*n leading the int to overflow and the hex
number to endup as int64_max-something. Sigh

Now the is_triangular check is slooooowwww
but we can just it by -b +- sqrt(b^2 - 4ac) / 2a since we know the triangle formula and t to test.
(same for is_pent, don't feel like it ATM)

Did it anyway, since otherwise it was 
*/

uint64_t hexagonal( int n ) {

	uint64_t result = n;

	result = result * (2*result - 1);
	
	return result;	
}

uint64_t triangular( int n ) {

	uint64_t result = n;
	
	result = ( result * (result+1) ) / 2;
	
	return result;
}


uint64_t pentagonal( int n ) {
	
	uint64_t result = n;
	
	// do it like this to avoid problems with dividing odd numbers too soon
	result = (result * (3*result - 1 ) ) / 2;
	
	return result;
}


int is_pentagonal( uint64_t p ) {

	// p must be of the form n(3n-1)/2
	// or 3/2 * n^2 - 1/2*n
	
	// a = 3/2, b = -1/2, c = -p
	// or: a = 3, b = -1, c = -2p
	uint64_t a = 3;
	uint64_t b = 1;
	uint64_t c = 2 * p; // factor out minuses to avoid underflow
	uint64_t result_1 = (b + sqrt( b*b + 4*a*c ))/(2*a);

	if( pentagonal(result_1) == p ) {
		return result_1;
	}
	
	return 0;
}

int is_triangular( uint64_t t ) {
	// t must be of the form n(n+1)/2
	// or 1/2 * n^2 + 1/2*n
	// which means that n < t/2
	// but that is a terrible bound
	// maybe we can solve it algebraically?
	
	// (-b +- sqrt( b*b - 4*a*c )) / 2*a
	// a=1/2, b=1/2, c = -t
	// or: a=1, b=1, c=2t
	// and we can skip result 2 as it is negative
	uint64_t result_1 = (-1 + sqrt( 1 + 4*2*t ))/2;
	
	// uint64_t result_2 = (-1 - sqrt( 1 + 4*2*t ))/2;
	// now check result 1:

	if( triangular(result_1) == t ) {
		return result_1;
	}
	
	return 0;
}


int main(int argc, char** argv) {
	
	uint64_t result = 0;

	uint64_t Hex = 0;
	int h = 144;
	int t, p; 
	while( 1 ) {
		
		Hex = hexagonal( h );
		// printf("H(%d) = %llu\n", h, Hex);

		p = is_pentagonal( Hex );
		if( p != 0 ) {
			assert( pentagonal(p) == Hex );
			t = is_triangular( Hex );
			if( t != 0 ) {
				break;
			}
		}
		
		h++;
	}
	
	assert( triangular( t ) == Hex );
	assert( pentagonal( p ) == Hex );

	result = Hex;
	// printf("H(%d) = P(%d) = T(%d) = %llu\n", h, p, t, Hex );
	
	printf("Problem 045: %llu\n", result );

}