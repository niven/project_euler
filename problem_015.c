#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/*

Starting in the top left corner of a 2×2 grid, and only being able to move to the right and down, there are exactly 6 routes to the bottom right corner.

How many such routes are there through a 20×20 grid?

1. rotate the grid 45degrees clockwise, now you have a tree.
2. enumerate all the path that lead to the 2nd row (this will be 1 path for both points)
3. repeat 2 and see you get a pascal triangle
4. realize that going further down, where the routes are constrained, you get less than exponential paths
5. (note: up to the middle, there are 2^n paths)
6. this is a symmetrical thing, so you can also reach the center from the bottom, with the same numbers of paths
7. every point on the center line can be reached by P_i paths
8. Calculate the inner product of that vector
9. success!

Example N=4:
        1
       / \
      1   1
     / \ / \
    1   2   1
	/ \ / \ / \
  1   3   3   1
 / \ / \ / \ / \
1   4   6   4   1

(1 4 6 4 1) x (1 4 6 4 1) = 70

*/

int main(int argc, char** argv) {
	
	uint64_t result = 0;
	
	int n = 20;
	int diagonal = n+1;
	uint64_t pascal_vector[diagonal];
	memset( pascal_vector, 0, sizeof(pascal_vector) );

	pascal_vector[0] = 1;
	for( int p=0; p<n; p++ ) {
		for(int i=diagonal; i>0; i--) {
			pascal_vector[i] += pascal_vector[i-1];
		}
	}
	
	// inner product
	for( int i=0; i<diagonal; i++ ) {
		result += pascal_vector[i] * pascal_vector[i];
	}
	
	printf("Problem 015: %llu\n", result);

}
