#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


/*



By starting at the top of the triangle below and moving to adjacent numbers on the row below, the maximum total from top to bottom is 23.

   3
  7 4
 2 4 6
8 5 9 3

That is, 3 + 7 + 4 + 9 = 23.

Find the maximum total from top to bottom of the triangle below:

                            75
                          95  64
                        17  47  82
                      18  35  87  10
                    20  04  82  47  65
                  19  01  23  75  03  34
                88  02  77  73  07  63  67
              99  65  04  28  06  16  70  92
            41  41  26  56  83  40  80  70  33
	       41  48  72  33  47  32  37  16  94  29
        53  71  44  65  25  43  91  52  97  51  14
      70  11  33  28  77  73  17  78  39  68  17  57
    91  71  52  38  17  14  91  43  58  50  27  29  48
  63  66  04  68  89  53  67  30  73  16  69  87  40  31
04  62  98  27  23  09  70  98  73  93  38  53  60  04  23

NOTE: As there are only 16384 routes, it is possible to solve this problem by trying every route. However, Problem 67, is the same challenge with a triangle containing one-hundred rows; it cannot be solved by brute force, and requires a clever method! ;o)

*/

typedef struct node {
	int n;
	int left;
	int right;
	int total;
} node;

int main(int argc, char** argv) {
	
	uint64_t result = 0;
	/*
	int triangle[] = {	3, 
								7, 4, 
								2, 4, 6, 
								8, 5, 9, 3};
	int height = 4;
	*/
	int triangle[] = {	75,
                        95, 64,
                        17, 47, 82,
                      	18, 35, 87, 10,
	                     20, 04, 82, 47, 65,
								19, 01, 23, 75, 03, 34,
	                	  	88, 02, 77, 73, 07, 63, 67,
	                	  	99, 65, 04, 28, 06, 16, 70, 92,
	                	  	41, 41, 26, 56, 83, 40, 80, 70, 33,
	 	            		41, 48, 72, 33, 47, 32, 37, 16, 94, 29,
	                	  	53, 71, 44, 65, 25, 43, 91, 52, 97, 51, 14,
	                	  	70, 11, 33, 28, 77, 73, 17, 78, 39, 68, 17, 57,
	                	  	91, 71, 52, 38, 17, 14, 91, 43, 58, 50, 27, 29, 48,
								63, 66, 04, 68, 89, 53, 67, 30, 73, 16, 69, 87, 40, 31,
	 						  	04, 62, 98, 27, 23,  9, 70, 98, 73, 93, 38, 53, 60, 04, 23};


	int height = 15;
								

	int count = sizeof(triangle)/sizeof(int);
	node nodes[count]; // we don't use the lower row, so could save some space
	memset( nodes, 0, sizeof(node) );
	
	// setup the nodes for the lowest row
	int offset = ( (height-1) * (height-1+1) ) / 2;
	for( int x=0; x<height; x++ ) {
		nodes[ offset + x ].n = triangle[ offset + x ];
		nodes[ offset + x ].total = triangle[ offset + x ];
	}
	
	// process all rows, starting at the second to last
	for( int y=height-1; y>0; y-- ) {
		int width = y;
		
		// length of this row is width, so the elements before it are the count of a triangle with base (Width-1)
		offset = ( (width-1) * ((width-1)+1) ) / 2;
		int offset_lower_row = ( (width-1+1) * ((width-1+1)+1) ) / 2;
		
		for( int x=0; x<width; x++ ) {
			// find if it's best to go Left or Right from this point
			int value = triangle[ offset + x ];
			// this is kind of annoying since we both store a triangle as an array, and it is upside down wrt rows
			int l_value = nodes[offset_lower_row+x].total; // one row down, same x
			int r_value = nodes[offset_lower_row+x+1].total; // one row down, x+1

			if( l_value > r_value ) {
				nodes[ offset + x ].left = 1;
				nodes[ offset + x ].right = 0;
				nodes[ offset + x ].n = value;
				nodes[ offset + x ].total = value + l_value;					
			}
			if( r_value > l_value ) {
				nodes[ offset + x ].left = 0;
				nodes[ offset + x ].right = 1;
				nodes[ offset + x ].n = value;
				nodes[ offset + x ].total = value + r_value;					
			}
			if( l_value == r_value ) {
				nodes[ offset + x ].left = 1;
				nodes[ offset + x ].right = 1;
				nodes[ offset + x ].n = value;
				nodes[ offset + x ].total = value + l_value;	
			}
//			printf("Pick: {n=%d, l=%d, r=%d, sum=%d}\n", nodes[ offset + x ].n, nodes[ offset + x ].left, nodes[ offset + x ].right, nodes[ offset + x ].total);
		}

	}
	
	// now the best paths have been propagated up to the root, so descend from the root to find the max-value path
	// Note: nice for checking, though the problem doesn't need it: at node[0].total we have the max value
	// Note: in case of a tie (both paths lead to a max path, we pick the left one)
	/*
	node current = nodes[0];
	int levels = height;
	int y = 0;
	int x = 0;
	int sum = 0;
	while( levels --> 0 )  {
		sum += current.n;
		printf("Level %d: %d go %s\n", height-levels, current.n, current.left ? "left" : "right");
		if( current.right ) {
			x++;
		}
		y++;
		current = nodes[ ( (y+1)*y ) / 2 + x ];
	}
	printf("sum: %d\n", sum);
	assert( sum == nodes[0].total );
	*/
	
	result = nodes[0].total;
	
	printf("Problem 018: %llu\n", result);

}