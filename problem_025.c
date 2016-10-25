#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/*

The Fibonacci sequence is defined by the recurrence relation:

    Fn = Fn−1 + Fn−2, where F1 = 1 and F2 = 1.

Hence the first 12 terms will be:

    F1 = 1
    F2 = 1
    F3 = 2
    F4 = 3
    F5 = 5
    F6 = 8
    F7 = 13
    F8 = 21
    F9 = 34
    F10 = 55
    F11 = 89
    F12 = 144

The 12th term, F12, is the first term to contain three digits.

What is the index of the first term in the Fibonacci sequence to contain 1000 digits?

So I know there is a function Fib(n) which avoids all the tedious addition, but I don't know it by heart and can't derive it either, so that's out.

the most straightforward way would be a digit vector and while( digit[999] != 0)

After doing some scribbling offline:

1. F(n) = F(n-1) + F(n-2)

Now let's look for the ratio of 2 subsequent Fs: Phi

Then we could see if F(n) = Phi^n

1. F(n) = F(n-1) + F(n-2)
2. Phi = F(n)/F(n-1) (it must be a ratio > 1)
3. Phi = F(n-1)/F(n-1) + F(n-2)/F(n-1) (by 1.)
4. Phi = 1 + F(n-2)/F(n-1) (simplify)
5. Phi = 1 + F(n-1)/F(n) (That ratio should be always the same)
6. Phi = 1 + 1/Phi (by 2.)
7. Phi^2 = Phi + 1
8. Phi^2 - Phi - 1 = 0
9. Solving 2nd order polynomial: ax^2 + bx + c => (-b +/- sqrt( b^2 - 4ac ) / 2a
10. (1 +/- sqrt(1 - 4*1*-1) ) / 2 
11. 1/2 +/- sqrt(5)/2
12. Now choose 1/2 + sqrt(5)/2 since we need the positive ratio
13. Phi = 1/2 + sqrt(5)/2

So that seems nice and I'll have to look that up. Just running some numbers seems we don't get a Fibonacci sequence 
(though the magnitudes of the numbers are fairly close)

Back to adding digit vectors I guess


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

void print_vector( int* vector, int size ) {

	for( int i=size-1; i>=0; i-- ) {
		printf("%d", vector[i]);
	}
	printf("\n");
	
}

int main(int argc, char** argv) {
	
	uint64_t result = 2; // starting with F1,F2 given
	int size = 1000;
	int a[size];
	int b[size];
	int temp[size];
	memset( a, 0, sizeof(a) );
	memset( b, 0, sizeof(b) );
	memset( temp, 0, sizeof(temp) );
	
	a[0] = 1; // F1
	b[0] = 1; // F2
	while( a[999] == 0 ) {
		memcpy( temp, a, sizeof(a) ) ;
		add_digit_vectors( a, b, size );
		memcpy( b, temp, sizeof(temp) );
		result++;
	}
	// print_vector( a, size );
	

	printf("Problem 025: %llu\n", result);

}

