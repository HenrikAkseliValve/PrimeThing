/*
< TASK description:
< Find the first prime number with 10 digits, and the first prime
< number with 11 digits.
< Once found, multiply them and print out the last 15 digits of the
< result.
*/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "Primality.h"

/*
 * Find the next (or equal) prime number from given ODD number.
 * Just support function that hopefully in-lines.
 */
static inline long long findNextSmallestPrime(long long oddstart){
	static_assert(sizeof(long long)==8,"isPrime function is for 64 bit numbers!");
	// Jump by two since given number is odd.
	for(long long test=oddstart;true;test+=2){
		if(isPrime(test)){
			return test;
		}
	}
}

int main(){
	puts("---PROGRAM STARTS---");

	// Find smallest 10 digit prime.
	// Start at 1000000001 because 1000000000 is even.
	long long digit10prime = findNextSmallestPrime(1000000001ll);
	printf("Found %llu as 10 digit prime\n",digit10prime);

	// Find smallest 11 digit prime.
	long long digit11prime = findNextSmallestPrime(10000000001ll);
	printf("Found %llu as 11 digit prime\n",digit11prime);
	// Multiply.

	// Take out the last 15 digits (meaning
	// 15 least significant base 10 digits).
	long long product = digit10prime*digit11prime;

	// Print the result.
	printf("Answer %.15llu\n",product%1000000000000000ll);

	return 0;
}
