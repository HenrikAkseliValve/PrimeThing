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
#include "Primality.h"

/*
 * Since C formatting does not have nbit format length modifier.
 * Use macro to know which one to use.
 */
#if __SIZEOF_LONG__==8
	#define UINT64_T_FMARK "%lu"
#else
#define UINT64_T_FMARK "%llu"
#endif

/*
 * Find the next (or equal) prime number from given ODD number.
 * Just support function that hopefully in-lines.
 */
static inline uint64_t findNextSmallestPrime(uint64_t oddstart){
	// Jump by two since given number is odd.
	for(uint64_t test=oddstart;true;test+=2){
		if(isPrime(test)){
			return test;
		}
	}
}

int main(){
	puts("---PROGRAM STARTS---");

	// Find smallest 10 digit prime.
	// Start at 1000000001 because 1000000000 is even.
	uint64_t digit10prime = findNextSmallestPrime(1000000001ll);
	printf("Found " UINT64_T_FMARK " as 10 digit prime\n",digit10prime);

	// Find smallest 11 digit prime.
	uint64_t digit11prime = findNextSmallestPrime(10000000001ll);
	printf("Found " UINT64_T_FMARK " as 11 digit prime\n",digit11prime);
	// Multiply.

	// Take out the last 15 digits (meaning
	// 15 least significant base 10 digits).
	uint64_t product = digit10prime*digit11prime;

	// Print the result.
	printf("Answer %.15llu\n",product%1000000000000000ll);

	return 0;
}
