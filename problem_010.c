#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <pthread.h>


/*

The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.

Find the sum of all the primes below two million.

Note: maybe it's time for a better is_prime function

Note 2: I didn't like this being the slowest problem (up to problem 45)
so changed it to use 20 threads since this is totally cpu bound anyway
*/


int is_prime( uint64_t n ) {

	if( n <= 1 ) {
		return 0;
	}
	if( n == 2 ) {
		return 1;
	}
	if( n % 2 == 0 ) {
		return 0;
	}
	for(uint64_t i=3; i<=sqrt(n); i+=2 ) {
		if( (n % i == 0) ) {
			return 0;
		}
	}

	return 1;
}

// [start, end)
typedef struct arg {
	int start;
	int end;
	uint64_t sum;
} arg;

void* sum_primes_between( void* thread_args ) {
	
	arg* in = (arg*) thread_args;
	for( int i=in->start; i<in->end; i++ ) {
		if( is_prime(i) ) {
			// printf("prime: %d\n",i);
			in->sum += i;
		}
	}
	// printf("Sum [%d,%d) = %llu\n", in->start, in->end, in->sum);
	
	return NULL;
}

int main(int argc, char** argv) {
	
	uint64_t result = 2;
	uint64_t max = 2*1000*1000;
	
	// for( int i=3; i<max; i+=2 ) {
	//
	// 	if( is_prime(i) ) {
	// 		// printf("p: %d\n", i);
	// 		result += i;
	// 	}
	//
	// }

	int chunks = 20;
	assert( max % chunks == 0 );
	
	int numbers_per_chunk = max / chunks;
	pthread_t thread[chunks];
	arg thread_args[chunks];
	
	int status;
	for( int i=0; i<chunks; i++ ) {
		thread_args[i].start = i*numbers_per_chunk;
		thread_args[i].end = thread_args[i].start + numbers_per_chunk;
		thread_args[i].sum = 0;
		status = pthread_create( &thread[i], NULL, sum_primes_between, &thread_args[i] );
	}
	
	for( int i=0; i<chunks; i++ ) {
		pthread_join( thread[i], NULL );
	}
	
	uint64_t threaded_result = 0;
	for( int i=0; i<chunks; i++ ) {
		threaded_result += thread_args[i].sum;
	}
	result = threaded_result;
	
	printf("Problem 010: %llu\n", result);

}
