#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h> /* islower */

/*

If the numbers 1 to 5 are written out in words: one, two, three, four, five, then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.

If all the numbers from 1 to 1000 (one thousand) inclusive were written out in words, how many letters would be used?

NOTE: Do not count spaces or hyphens. For example, 342 (three hundred and forty-two) contains 23 letters and 115 (one hundred and fifteen) contains 20 letters. The use of "and" when writing out numbers is in compliance with British usage.

*/

/*

Grammar for numbers:

1-10: one|two|...|nine
1-20: 1-10|eleven|..|nineteen|twenty

21-99: twenty + '-' + 1-0 | thirty ...
100+: [1-10] hundred and ( 1-20 | 21-99 )
1000+: [1-10] thousand

Sigh, don't really like this one, not bothering to do every number

*/

char* one_nine( char* buf, int n ) {
	
	switch( n ) {
		case 1:
			return stpncpy( buf, "one", 3 );
		case 2:
			return stpncpy( buf, "two", 3 );
		case 3:
			return stpncpy( buf, "three", 5 );
		case 4:
			return stpncpy( buf, "four", 4 );
		case 5:
			return stpncpy( buf, "five", 4 );
		case 6:
			return stpncpy( buf, "six", 3 );
		case 7:
			return stpncpy( buf, "seven", 5 );
		case 8:
			return stpncpy( buf, "eight", 5 );
		case 9:
			return stpncpy( buf, "nine", 4 );
		default:
			return stpncpy( buf, "FAIL", 4 ); 
	}
	
}

char* ten_ninety( char* buf, int n ) {
	
	switch( n ) {
		case 10:
			return stpncpy( buf, "ten", 3 );
		case 20:
			return stpncpy( buf, "twenty", 6 );
		case 30:
			return stpncpy( buf, "thirty", 6 );
		case 40:
			return stpncpy( buf, "forty", 5 );
		case 50:
			return stpncpy( buf, "fifty", 5 );
		case 60:
			return stpncpy( buf, "sixty", 5 );
		case 70:
			return stpncpy( buf, "seventy", 7 );
		case 80:
			return stpncpy( buf, "eighty", 6 );
		case 90:
			return stpncpy( buf, "ninety", 6 );
		default:
			return stpncpy( buf, "TODO", 4);
	}
	
}

char* ten_twenty( char* buf, int n ) {
	
	switch( n ) {
		case 10:
			return stpncpy( buf, "ten", 3 );
		case 11:
			return stpncpy( buf, "eleven", 6 );
		case 12:
			return stpncpy( buf, "twelve", 6 );
		case 13:
			return stpncpy( buf, "thirteen", 8 );
		case 14:
			return stpncpy( buf, "fourteen", 8 );
		case 15:
			return stpncpy( buf, "fifteen", 7 );
		case 16:
			return stpncpy( buf, "sixteen", 7 );
		case 17:
			return stpncpy( buf, "seventeen", 9 );
		case 18:
			return stpncpy( buf, "eighteen", 8 );
		case 19:
			return stpncpy( buf, "nineteen", 8 );
		case 20:
			return stpncpy( buf, "twenty", 8 );
		default:
			return stpncpy( buf, "TODO", 4);
	}
	
}


void write_out( int num, char* buf, int sz ) {
	
	memset( buf, 0, sz );
	
	if( num > 0 && num < 10 ) {
		one_nine( buf, num );
		return;
	}
	
	if( num > 9 && num <= 20 ) {
		ten_twenty( buf, num );
		return;
	}
	
	
	
	if( num > 19 && num < 100 ) {
		int tens = 10 * (num / 10);
		char* next = ten_ninety( buf, tens );
		if( num-tens == 0 ) {
			return;
		}
		next = stpncpy( next, "-", 1 );
		one_nine( next, num-tens );
		return;
	}
	
	if( num == 1000 ) {
		strcpy( buf, "one thousand" );
		return;
	}
	
	if( num > 99 ) {
		int hundreds = num / 100;
		char* next = one_nine( buf, hundreds ); 
		next = stpncpy( next, " hundred", 8 );
		if( num % 100 == 0 ) {
			return;
		}
		next = stpncpy( next, " and ", 5 );
		write_out( num - (hundreds * 100), next, sz - (next-buf) ); // ugh
		return;
	}
	
}

int main(int argc, char** argv) {
	
	uint64_t result = 0;

	int n = 1001;
	
	int sz = 500;
	char buf[sz];
	int letter_count;
	for( int i=0; i<n; i++ ) {
		write_out( i, buf, sz );
		letter_count = 0;
		for( int j=0; j<sz; j++ ) {
			if( islower( buf[j] ) ) {
				// printf( "\tLETTER: %c (%d)\n", buf[j], letter_count+1);
				letter_count++;
			}
		}
		// printf(" %d: '%s' = %d\n", i, buf, letter_count);
		result += letter_count;
	}


	printf("Problem 017: %llu\n", result);

}
