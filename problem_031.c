#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


/*


In England the currency is made up of pound, £, and pence, p, and there are eight coins in general circulation:

    1p, 2p, 5p, 10p, 20p, 50p, £1 (100p) and £2 (200p).

It is possible to make £2 in the following way:

    1×£1 + 1×50p + 2×20p + 1×5p + 1×2p + 3×1p

How many different ways can £2 be made using any number of coins?


Seem to recall this is an NP kind of thing, maybe from a book on crypto. Regardless, this is a very limited problem of course.

5
2 2 1
2 1 1 1
1 1 1 1 1

10
5 5
5 2 2 1
5 2 1 1 1
5 1 1 1 1 1
2 2 1 1 1 1 1 1
2 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1

Missing:
2 2 2 2 2
2 2 2 2 1 1
2 2 2 1 1 1 1
etc


Starting by highest first:
10
5 5
5 2 2 1
2 2 1 2 2 1 (but now we miss 2 2 2 2 2)
but all end up as 1 ..... 1

Maybe start from the bottom?

5 =>
1 1 1 1 1
2 1 1 1
2 2 1
5
OK

1 1 1 1 1 1 1 1 1 1
2 1 1 1 1 1 1 1 1
2 2 1 1 1 1 1 1
Now we can make 5, or convert another 11 -> 2
maybe both?
5 =>
5 1 1 1 1 1
5 2 1 1 1
5 2 2 1
5 5
10
2=>
2 2 2 1 1 1 1
now 5=>
5 2 1 1 1
5 2 2 1
5 5
10
 Cont' 2:
2 2 2 2 1 1
make 5 again
5 2 2 1
5 5
Con't 2
2 2 2 2 2
can't make 5
10
Now 55 happens twice, 10 happens 3x


Maybe do 'all options, all levels'
10
5 5
2 2 2 2 2
1 1 1 1 1 1 1 1 1 1
Now we have 3 options
5 5:
2 2 1 5
2 2 1 2 2 1
1 1 1 1 1 1 1 1 1 1 1 <- double
cont'
1 1 2 1 5
1 1 1 1 5
2 2 1 2 2 1 -< double
etc
Still doubles

We can do any of the 'gen all options' if we track the options we already had to eliminate duplicates.
Don't like that though.

Is there a way to generate all options so that the doubles are consecutive? Doesn't seem like it.

How about trying all vectors of coins?
we know the max is 10x1, so we can do the entire vector from 0-10:
10-5-2-1
 0,0,0,1
 0,0,0,2
 ...
 0,0,0,10
 ....
 5,3,7,8
 ....
 10,10,10,10

That means just checking unique combinations, but we don't have to keep track of anything and can just count the ones that sum to 10.

This means 10^4 for 10
and 8^200 = 2^600 combinations to check, which is bad :)

On the optimizing hand, this would mean that whenever the last sum is higher than the target, we can skip incrementing the highest 
(any and higher coin)

Going to write some code for that.
Addendum: we can limit the loop for each coin by the max it could be, so for target=10:
1 x 2 x 5 x 10 = 100 combinations to check.

So for 50 (no break loops) this means 525096 sums for 451 combinations
For 100 (NBL) this is 42835716 checks for 4563 ways that are valid
200 is running now and making my CPU weep :)
5,768,123,130 checks for 73682 ways to split that.

Of course this is spending half the time in checking if anything is possible when we use 1x200

On the gripping hand this is easy to understand and doesn't use a clever algorithm and no memory.

Then I came to my senses and just wrote the obvious recursive function that tries all valid vectors
by limiting the remaining vector by a lower target to avoid all the needless overshooting.
It helps to realize the 1 coin doesn't matter: we can always fill out with that one.
Then function calls are better than goto's to avoid keeping checking when the vector is already over.
I also got confused by the 'obvious' recursive solution because I was thinking in 'splitting the target value', which you
can do in different ways  and if you then recurse you encounter double results.

Current algorithm makes 77308 calls which is great and not thus not NP :)
*/

static int coins[] = {200, 100, 50, 20, 10, 5, 2, 1};
static int num_coins = sizeof(coins)/sizeof(coins[0]);

uint64_t try_all_coin_vectors( int coin_index, int target ) {

	uint64_t result = 0;
	
	if( coin_index == num_coins-1 ) {
		return 1;
	}
	
	int sum = 0;
	for( int i=0; i <= target/coins[coin_index]; i++ ) {
		sum = i*coins[coin_index];
		result += try_all_coin_vectors( coin_index+1, target-sum );
	}
	
	
	return result;
}


int main(int argc, char** argv) {
	
	uint64_t result = 0;

	int target = 200;

	result = try_all_coin_vectors( 0, target );
	
	printf("Problem 031: %llu\n", result);

}
