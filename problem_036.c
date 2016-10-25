#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


/*

The decimal number, 585 = 1001001001_2 (binary), is palindromic in both bases.

Find the sum of all numbers, less than one million, which are palindromic in base 10 and base 2.

(Please note that the palindromic number, in either base, may not include leading zeros.)

So 1M in base 2 is 20 digits. With 20 digits you can make 512 palindromes
1M in base 10 is 6 digits (well, up to 999,999) and you can make 900

So it's easier to create all base2 palindromes and then convert that number to base 10
and see if it's also a palindrome.

Alternatively: also create all the base 10 palindromes and find the intersection if any,
though that will imply a search probably

*/

// base 10
int is_palindrome( uint64_t n ) {
	
	char buf[20];
	sprintf(buf, "%llu", n);
	int num_digits = strlen(buf);
	
	for( int i=0; i<(num_digits+1)/2; i++ ) {
		int backwards_index = num_digits-1-i;
		if( buf[i] != buf[backwards_index] ) {
			return 0;
		}
	}
	
	return 1;
}

void add_digit_vectors( int* accumulator, int* number, int size, int base ) {

	// now perform old skool digit by digit addition
	int carry = 0;
	int next = 0;

	for(int i=0; i<size; i++) {
		next = accumulator[i] + number[i] + carry;
		carry = 0;
		if( next > (base-1) ) {
			next -= base;
			carry = 1;
		}
		accumulator[i] = next;
	}
	
}

void print_vector( int* vector, int size ) {

	for( int i=size-1; i>=0; i-- ) {
		printf("%d", vector[i]);
	}
	printf("\n");
	
}

uint64_t count_palindromic_numbers( int num_digits, int base ) {
	
	uint64_t result = 0;

	int available_digits = (num_digits+1) / 2;
	
	result = (base-1) * pow( base, available_digits-1 );
	
	return result;
}

void create_palindromes_base2( int num_digits, char* space ) {
	
	int digit_string_len = num_digits + 1;
	int available_digits = (num_digits+1)/2 - 1;

	int accumulator[available_digits];
	int one[available_digits];
	memset( accumulator, 0, sizeof(accumulator) );
	memset( one, 0, sizeof(one) );
	one[0] = 1;
	
	int num_palindromes = count_palindromic_numbers( num_digits, 2 );

	// dodgy stuff :)
	for( int i=0; i<num_palindromes; i++ ) {
		char* buf = space + (i*digit_string_len);

		
		*(buf + 0) = '1';		
		for( int j=0; j<available_digits; j++ ) {
			*(buf + j + 1) = '0' + accumulator[j];
			*(buf + num_digits - 2 - j) = '0' + accumulator[j];
		}
		add_digit_vectors( accumulator, one, available_digits, 2 );

		*(buf + num_digits - 1) = '1';		
		*(buf + digit_string_len) = 0;
	}
}


int main(int argc, char** argv) {
	
	uint64_t result = 0;

	uint64_t max = 1*1000*1000;
	
	// find out how many digits that is in base 2
	int digits_in_base_2 = 1;
	int temp = max;
	while( temp >>= 1 ) {
		digits_in_base_2++;
	}


	// for each digit length, make and check the palindromic numbers
	for( int digits=1; digits<=digits_in_base_2; digits++ ) {
		
		int digit_string_len = digits + 1;
		int num_palindromes = count_palindromic_numbers( digits, 2 );

		char base2_palindromes[num_palindromes * digit_string_len];
		memset( base2_palindromes, 0, sizeof(base2_palindromes) );
		create_palindromes_base2( digits, base2_palindromes );

		for( int i=0; i<num_palindromes; i++ ) {

			// convert base 2 digit string to base 10 number
			uint64_t number = 0;
			for( int j=0; j<digits; j++ ) {
				int power = digits-j-1;
				char d = *(base2_palindromes + (i*digit_string_len) + j);
				number += (1 << power) * (d-'0'); 
			}

			if( (number < max) && is_palindrome(number) ) {
				// printf("N2=%s N10=%llu -> palindrome=%s\n", base2_palindromes + (i * digit_string_len), number, is_palindrome(number) ? "TRUE" : "false" );
				result += number;
			}
		}
	}

	printf("Problem 036: %llu\n", result);

}
