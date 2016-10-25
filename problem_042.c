#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


/*

The nth term of the sequence of triangle numbers is given by, t_n = ½n(n+1); so the first ten triangle numbers are:

1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...

By converting each letter in a word to a number corresponding to its alphabetical position and 
adding these values we form a word value. 
For example, the word value for SKY is 19 + 11 + 25 = 55 = t_10. If the word value is a triangle number 
then we shall call the word a triangle word.

Using words.txt (right click and 'Save Link/Target As...'), a 16K text file containing nearly 
two-thousand common English words, how many are triangle words?

Seems like the easiest problem so far, without interesting properties.

*/

int is_triangle( uint64_t n ) {
	
	int t = 1;
	uint64_t t_val = (t*(t+1)) / 2;
	
	while( t_val < n ) {
		t++;
		t_val = (t*(t+1)) / 2;
	}
	
	return t_val == n;
	
}

int main(int argc, char** argv) {
	
	uint64_t result = 0;
	
	int word_length = 100;
	char temp[ word_length ];
	uint64_t word_value = 0;

	FILE* in;
	char* fileword = "problem_042_words.txt";
	in = fopen( fileword, "ra" );
	if( in == NULL ) {
			perror("fopen()");
			printf( "%s:%d fileword = %s\n", __FILE__, __LINE__, fileword);
			exit( EXIT_FAILURE );
	}
	
	char buf;
	size_t objects_read;
	int len = 0;
	while( !feof(in) ) {
		
		objects_read = fread( &buf, sizeof(buf), 1, in);
		if( objects_read != 1 ) {
			break;
		}
		// printf("len=%d, temp='%s' read: '%c'\n", len, temp, buf);
		if( buf == '"' ) {
			if( len > 0 ) { // end of word
				
				if( len > 255 || len > word_length ) {
					printf("word TOO LONG!\n");
					exit(0);
				}
				if( is_triangle(word_value) ) {
					// printf("word: '%s' (%d) (%llu)\n", temp, len, word_value);
					result++;					
				}

				// reset
				word_value = 0;
				len = 0;
				memset( temp, 0, sizeof(temp) );
				// eat the ,
				fread( &buf, sizeof(buf), 1, in);
			}
		} else {
			// just append
			temp[len++] = buf;
			word_value += buf - 'A' + 1;
		}
	}
	assert( feof(in ) );
	fclose( in );
	


	printf("Problem 042: %llu\n", result);

}

