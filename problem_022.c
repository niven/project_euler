#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/*

Using problem_022_names.txt, a 46K text file containing over five-thousand first names, begin by sorting it into alphabetical order.
Then working out the alphabetical value for each name, multiply this value by its alphabetical position in the list to 
obtain a name score.

For example, when the list is sorted into alphabetical order, COLIN, which is worth 3 + 15 + 12 + 9 + 14 = 53, 
is the 938th name in the list. So, COLIN would obtain a score of 938 × 53 = 49714.

What is the total of all the name scores in the file?

Ugh, more of a Perl than a C problem :)

OK:
Find out how many names (5K+)
run through the file, parsing a name at a time
encode the whole name as LEN + chars, pad with NUL to be 20 or so (or whatever the longest name is)
put the name in an array
insertion sort the array

Go over all the names and do the bookkeeping

Note: file reading is inefficient, "parsing" the names is poor style. Sorting is nice.
*/

#define name_length 20

typedef struct name {
	int length;
	char characters[name_length];
} name;

typedef int (*comparator)(const void* a, const void* b);

int compare_name(const void* a, const void* b) {

	name* na = (name*)a;
	name* nb = (name*)b;	

	int length = na->length > nb->length ? nb->length : na->length;
	
	for( int i=0; i<length; i++ ) {
		if( na->characters[i] < nb->characters[i] ) {
			return -1;
		}
		if( na->characters[i] > nb->characters[i] ) {
			return 1;
		}
	}

	// all the same up to the shortest one at least
	if( na->length == nb->length ) {
		return 0;
	}
	
	// shorter one comes first
	return na->length < nb->length ? -1 : 1;
}

void insertionsort( void* base, size_t nel, size_t width, comparator compare ) {
	
	char* list = (char*)base;
	void* value = malloc( width );
	if( value == NULL ) {
		perror("malloc()");
		exit( EXIT_FAILURE );
	}
	
	int hole_index;
	for(int i=0; i<nel*width; i+=width ) {
		memcpy( value, list+i, width ); // take value and keep it safe
		hole_index = i; // this is where we took the value from, it's vacant
		
		// printf( "Moving value %d and creating a hole at %d\n", *(int*)value, hole_index );
		
		while( hole_index > 0 && compare( list+hole_index-width, value ) == 1 ) { // if elements are higher, we shift them 
			memcpy( list+hole_index, list+hole_index-width, width ); // move the element right
			hole_index -= width; // move the hole left
		}
		memcpy( list+hole_index, value, width );
		
	}
	
	free( value );
}


int main( int argc, char** argv ) {

	uint64_t result = 0;
	
	char temp[ name_length ];
	int count_names = 0;
	name names[ 6000 ];
	memset( names, 0, sizeof(names) );

	FILE* in;
	char* filename = "problem_022_names.txt";
	in = fopen( filename, "ra" );
	if( in == NULL ) {
			perror("fopen()");
			printf( "%s:%d filename = %s\n", __FILE__, __LINE__, filename);
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
			if( len > 0 ) { // end of name
				
				if( len > 255 || len > name_length ) {
					printf("NAME TOO LONG!\n");
					exit(0);
				}
				// printf("Name: '%s' (%d)\n", temp, len);
				// store
				names[count_names].length = len;
				strncpy( names[count_names].characters, temp, len );
				// printf("Stored: '%s'\n", names[count_names].characters );
				count_names++;
				// reset
				len = 0;
				memset( temp, 0, sizeof(temp) );
				// eat the ,
				fread( &buf, sizeof(buf), 1, in);
			}
		} else {
			// just append
			temp[len++] = buf;
		}
	}
	assert( feof(in ) );
	fclose( in );
	
	// sort
	insertionsort( names, count_names, sizeof(name), &compare_name );
	
	// bookkeeping
	for( int i=0; i<count_names; i++ ) {
		int pos = i+1;
		int name_score = 0;
		for(int s=0; s<names[i].length; s++) {
			name_score += (names[i].characters[s] - 'A') + 1; // 'A' is 1
		}
		result += name_score*pos;
	}
	
	printf("Problem 022: %llu\n", result);

}