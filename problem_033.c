#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/*

The fraction 49/98 is a curious fraction, as an inexperienced mathematician in attempting to simplify it may incorrectly believe that 49/98 = 4/8, which is correct, is obtained by cancelling the 9s.

We shall consider fractions like, 30/50 = 3/5, to be trivial examples.

There are exactly four non-trivial examples of this type of fraction, less than one in value, and containing two digits in the numerator and denominator.

If the product of these four fractions is given in its lowest common terms, find the value of the denominator.

So this is total BS. This only happens to work and I was mostly confused why anyone could ever think this makes
sense.

Anyway: jsut try all a/b for 2 digit a,b where b>a and skip the ones where a,b % 10 == 0
then it turns out you get a fraction with denominator % numerator == 0 so I didn't even bother to GCD them

*/


int main(int argc, char** argv) {
	
	uint64_t result = 0;
	int max = 100;
	char numerator[3];
	char denominator[3];
	numerator[2] = denominator[2] = 0;
	
	int num_result = 1;
	int den_result = 1;

	for( int num=10; num<max; num++ ) {
		numerator[0] = '0' + (num / 10);
		numerator[1] = '0' + (num % 10);
		// ensure 'less than one in value' and avoid num == den
		for( int den=num+1; den<max; den++ ) {
			denominator[0] = '0' + (den / 10);
			denominator[1] = '0' + (den % 10);
			if( num % 10 == 0 && den % 10 == 0 ) {
				continue; // skip the trivial ones
			}
			int bs_num, bs_den;
			for( int a=0; a<2; a++ ) {
				for( int b=0; b<2; b++ ) {
					if( numerator[a] == denominator[b] ) {
						// BS 'cancellation'
						bs_num = numerator[ (a+1) % 2 ] - '0'; // keep the other one
						bs_den = denominator[ (b+1) % 2 ] - '0';
						int happens_to_work = bs_num*den == bs_den*num;
						if( happens_to_work ){
							// printf("%d/%d = %s/%s\n", num, den, numerator, denominator);
							// printf("\tBS: %d/%d => %d*%d == %d*%d?-> %s\n", bs_num, bs_den, bs_num, den, bs_den, num, happens_to_work ?"TRUE" : "fail");
							num_result *= num;
							den_result *= den;
						}
					}
				}
			}
			
		}
	}
	// printf("%d/%d\n", num_result, den_result);
	result = den_result / num_result;

	printf("Problem 033: %llu\n", result );

}
