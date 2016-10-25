#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/*


2^15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.

What is the sum of the digits of the number 2^1000?


*/

void add_digit_vectors( int* accumulator, int* number, int number_size, int accumulator_size ) {

	// now perform old skool digit by digit addition
	int carry = 0;
	int next = 0;
	int num = 0;
	for(int i=0; i<accumulator_size; i++) {
		num = i >= number_size ? 0 : number[i]; // though it would be more clear if all digit vectors were the same size
		next = accumulator[i] + num + carry;
		carry = 0;
		if( next > 9 ) {
			next -= 10;
			carry = 1;
		}
		accumulator[i] = next;
	}
	
}


int main(int argc, char** argv) {
	
	uint64_t result = 1;
	
	int n = 1000;
	int vector_size = n; // will be too much as the length of 2^n grows as ln(n) I assume
	int accumulator[vector_size];
	memset( accumulator, 0, sizeof(accumulator) );
	
	accumulator[0] = 1;

	// just double the value n times
	for( int i=0; i<n; i++ ) {
		add_digit_vectors( accumulator, accumulator, vector_size, vector_size );		
	}
	
	result = 0;
	for(int i=vector_size-1; i>=0; i--) {
		result += accumulator[i];
	}
	
	
	printf("Problem 016: %llu\n", result);

}
