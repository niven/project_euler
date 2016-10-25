#include <stdio.h>
#include <pthread.h>

/*

If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3, 5, 6 and 9. The sum of these multiples is 23.

Find the sum of all the multiples of 3 or 5 below 1000.

so we count all multiples of 3 + all multiples of 5, but then we count all multiples of 15 double, so subtract those

*/

typedef struct args {
	int num;
	int max;
	int result;
} args;

void* sum_multiples_below_closed( void* arg ) {
	
	args* in = (args*)arg;
	
	printf("Sum for (%d,%d)\n", in->num, in->max);
	
	in->result = 0;
	
	int num_multiples = (in->max-1) / in->num; // up to, not including
	
	// series sum
	in->result = ((num_multiples+1) * num_multiples) / 2;
	
	in->result *= in->num;

	return NULL;
}

int main(int argc, char** argv) {
	
	int result = 0;

	int max = 1000;

	// multiples of 3:
	// there are 1000/3 of them, and they are a series like 3, 6, 9, 12
	// which we can write as 3 * (1,2,3,4,..)
	// so the sum of all multiples of 3 below 1000 is:
	// 1000/3 = 333
	// ((333+1)*333)/2 = 55,611
	// 55611 * 3 = 166,833

	pthread_t mul3, mul5, mul15;
	
	args sum3 = { .num = 3, .max = 1000 };
	args sum5 = { .num = 5, .max = 1000 };
	args sum15 = { .num = 15, .max = 1000 };
	int status;
	status = pthread_create( &mul3, NULL, sum_multiples_below_closed, &sum3 );
	status = pthread_create( &mul5, NULL, sum_multiples_below_closed, &sum5 );
	status = pthread_create( &mul15, NULL, sum_multiples_below_closed, &sum15 );

	pthread_join( mul3, NULL );
	pthread_join( mul5, NULL );
	pthread_join( mul15, NULL );

	result = sum3.result;
	result += sum5.result;
	result += sum15.result;
		
	printf("Problem 001: %d\n", result);
}