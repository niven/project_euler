#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


/*

You are given the following information, but you may prefer to do some research for yourself.

    1 Jan 1900 was a Monday.
    Thirty days has September,
    April, June and November.
    All the rest have thirty-one,
    Saving February alone,
    Which has twenty-eight, rain or shine.
    And on leap years, twenty-nine.
    A leap year occurs on any year evenly divisible by 4, but not on a century unless it is divisible by 400.

How many Sundays fell on the first of the month during the twentieth century (1 Jan 1901 to 31 Dec 2000)?


Seriously, fsck date/time math :(

Anyway:
1. Start at 1 Jan 1900
2. Number of days this month
3. Move that many days
4. day_of_week = (days moved % 7, treating monday as 0, sunday as 6)
5. if month == 2, advance the year and goto month 1

Note: advance to 1 Jan 1901 to start counting Sundays
*/

int days( int month, int year ) {
	
	switch( month ) {
		case 4:
		case 6:
		case 9:
		case 11:
			return 30;
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			return 31;
		default: // feb
		if( year % 400 == 0 ) {
			return 29;
		}
		if( year % 100 == 0 ) {
			return 28;
		}
		if( year % 4 == 0 ) {
			return 29;
		}
		return 28;
	}
}

int main(int argc, char** argv) {
	
	uint64_t result = 0;
	
	int monday = 0;
	int sunday = 6;

	char* daynames[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

	int year = 1900;
	int month = 1;
	// don't care about the day, since it is always 1
	int day_of_week = monday;

	while( month != 1 || year != 2001 ) {
		
		int days_in_month = days( month, year );
		// printf("01/%02d/%d = %s (days: %d)\n", month, year, daynames[day_of_week], days_in_month);
		day_of_week += days_in_month;
		day_of_week = day_of_week % 7;
		
		if( year > 1900 && day_of_week == sunday ) {
			result++;
		}
		
		month++;
		if( month == 13 ) {
			month = 1;
			year++;
		}
		
		
	}
	
	
	printf("Problem 019: %llu\n", result);

}
