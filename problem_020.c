#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


/*

n! means n × (n − 1) × ... × 3 × 2 × 1

For example, 10! = 10 × 9 × ... × 3 × 2 × 1 = 3628800,
and the sum of the digits in the number 10! is 3 + 6 + 2 + 8 + 8 + 0 + 0 = 27.

Find the sum of the digits in the number 100!

Digit at place 1: is ...1 x ....2 x ....3 x blah, a hundred times
Which is 1^10 x 2^10 etc =  means we find that digit

Can we do the same for all digits?

I think we can, but I'd have to go find that book.

if we calculate this doing repeated addition:
1x2x3x4=
1: 1 = 1
2: 1+1 = 2
3: 2+2+2 = 6
4: 6+6+6+6 = 24
etc
that is 100*101/2=5050 additions of vectors of length say 200 = 1.010.000 additions which is very doable.

*/

void add_digit_vectors( int* accumulator, int* number, int size ) {

	// now perform old skool digit by digit addition
	int carry = 0;
	int next = 0;

	for(int i=0; i<size; i++) {
		next = accumulator[i] + number[i] + carry;
		carry = 0;
		if( next > 9 ) {
			next -= 10;
			carry = 1;
		}
		accumulator[i] = next;
	}
	
}

void mul_digit_vectors( int* accumulator, int n, int size ) {

	int temp[size];
	memcpy( temp, accumulator, sizeof(temp) );
	
	for( int j=1; j<n; j++ ) {
		add_digit_vectors( accumulator, temp, size );					
	}
	
}

void print_vector( int* vector, int size ) {

	for( int i=size-1; i>=0; i-- ) {
		printf("%d", vector[i]);
	}
	printf("\n");
	
}

uint64_t factorial( int n ) {
	uint64_t result = 1;
	
	for( int i=1; i<=n; i++ ) {
		result *= i;
	}
	
	return result;
}

int main(int argc, char** argv) {
	
	uint64_t result = 0;
	int n = 100;
	
	int vector_size = 160;
	int accumulator[vector_size];
	memset( accumulator, 0, sizeof(accumulator) );
	
	accumulator[0] = 1;
	for( int i=1; i<=n; i++ ) {
		mul_digit_vectors( accumulator, i, vector_size );
		// print_vector( accumulator, vector_size );
	}
	
	// sum the digits
	for( int i=0; i<vector_size; i++ ) {
		result += accumulator[i];
	}
	
	printf("Problem 020: %llu\n", result);

}

	