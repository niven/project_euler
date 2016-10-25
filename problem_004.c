#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>


/*


A palindromic number reads the same both ways. 
The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 × 99.

Find the largest palindrome made from the product of two 3-digit numbers.


Note: 
- generate all products of 3 digit numbers: 900x900 numbers, check for palindrome = 810.000 ops
- generate all palindromic numbers between 10000-998001 might be much faster, but then checking to see if they are products of 3 digit intergers might be more complicated. (well, there are only 900, so sqrt(900) x palindromes)

Generating palindromes looks more interesting.

palindromes: abcba OR abba in form (where a,b,c can be any digit)
we need the ones for 10000-99999 (5 digits, abcba form) (A)
and the ones for 100000-998001 (6 digits, abccba form) (B)

For (A), c is choice of 0-9, and all options for ab are (1-9 x 0-9) = 90 so there are 90x10 = 900 palindromic numbers in A

For (B), abc is choice 1-9 x 0-9 x 0-9 = 900

So generating palindromes is 1800x30 = 54.000 ops.

Possible improvements: order palindrome generation as B DESC then A DESC so you can break out when you find the first.
*/

// Even and odd are probably equivalent
int num_palindromes( int string_length ) {
	if( string_length % 2 == 0 ) {
		int n = string_length / 2;
		return 9 /* first char must be 1-9, no 0 */ * pow(10, n-1);
	} else {
		int n = (string_length-1) / 2;
		return 9 * pow(10, n-1) * 10;
	}
}

int is_product_of_3digit_numbers( int n ) {
	
	int a,b;
	for( a=100; a<sqrt(n) && a <1000; a++) {
		if( n % a == 0 ) {
			b = n/a;
			if( b >= 100 && b <= 999 ) {
				return 1;
			}
		}
	}
	
	return 0;
}

int main(int argc, char** argv) {
	
	int result = 0;
	
	char buf[7];
	int n;
	// make all palindromes
	for( int i=1; i<10; i++ ) {
		for( int j=0; j<10; j++ ) {
			for( int m=0; m<10; m++ ){
				sprintf(buf, "%d%d%d%d%d", i, j, m, j, i);
				n = atoi(buf);
				if( is_product_of_3digit_numbers(n) && n > result ) {
					result = n;
				}
				sprintf(buf, "%d%d%d%d%d%d", i, j, m, m, j, i);
				n = atoi(buf);
				if( is_product_of_3digit_numbers(n) && n > result ) {
					result = n;
				}
				
			}
		}		
	}
	
	printf("Problem 004: %d\n", result);

}