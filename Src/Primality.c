/*
< Source file for primality testing module.
*/
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

/*
 * Calculate integer square root of 64 bit unsigned integer.
 * Outputs 64 bit number for consistent input output.
 * TODO: Move this it's own source file if too many other math operations pop up.
*/
static uint64_t isqrt(uint64_t num){
	// Using Heron's method to calculate isqrt(S).
	// Iteration rule is x_{n+1}=floor((x_n+S/x_n)/2)
	// Stop when x_{i+1}>=x_i as x_i is correct answer.
	// According to references the initial estimate is important
	// for efficiently. Problem is how to calculate good estimate
	// without that estimate calculation taking away performance.
	// Estimate has to be more then isqrt(S) to estimation to
	// converge.
	//
	// Wikipedia example just calculates half of the initial value
	// which is fast. Other one calculates ceil(2^(log2(n)/2)) which
	// is the smallest power of two bigger than or equal to isqrt(S).
	// With ceil(2^(log2(S)/2)) as initial estimate log2(log2(S)) loop
	// iterations are performed. Wikipedia has example where half
	// version needs 13 iterations for 2000000. The ceil(2^(log2(S)/2))
	// version needs 4.
	//
	// Calculation of 2^x is just bit-shifting operation on 0x1 so log2
	// is the bottle neck. Stackoverflow has pretty good list of algorithms.
	// Best one is to use __builtin_clz which is GCC and Clang specific so
	// for backup have the halving version. (There are other algorithms in
	// stackoverflow list to consider for integer log2 but one could just
	// could test dividing by four for initial estimate x_0 and get better
	// results.)
	//
	// __builtin_clz gives number of zeros after most significant bit. This
	// has relation to log2 by equation log2(x)=w-1-clz(x) where w is
	// types length in bits.
	// NOTE: stdbit.h coming in C23.
	//
	// Reference: https://www.akalin.com/computing-isqrt
	//            https://en.wikipedia.org/wiki/Integer_square_root
	//            https://stackoverflow.com/questions/11376288/fast-computing-of-log2-for-64-bit-integers
	//            https://en.wikipedia.org/wiki/Find_first_set

#if 0 // Optimizing since zero or one is never given to the isqrt in the program.
	// Automaticly return zero or one when
	// given zero or one.
	if(num<=1) return num;
#endif

	// Estimate for the isqrt.
	// Loop handles initialization.
	uint64_t x0;
	// Support storage. Starts as initial estimate
	// to have update rule in one place.
	uint64_t x1;
	#if !defined(ISQRT_DO_NOT_USE_LOG) || __GNUC__ || __clang__
		// Make sure that correct ctz is called since ctzll which uses long long
		// could be more then 64 bits.
		// TODO: Is GCC smart enough to detect uint64_t and correct?
		#if __SIZEOF_LONG__==8
			int clzl = __builtin_clzl(num);
		#else
			int clzl = __builtin_clzll(num);
		#endif
		static_assert(sizeof(uint64_t)==8,"Program assumes that uint64_t is 8");
		x1 = 0x1<<((sizeof(uint64_t)*8-1-clzl)/2);
	#else
		x1 = num/2;
	#endif

	// Initial estimate is bigger then or
	// equal to final result.
	do{
		x0 = x1;
		x1 = (x0+num/x0)/2;
	}while(x1<x0);

	// Return the answer.
	return x0;
}

/*
 * Function to test that given number is a prime.
*/
bool isPrime(uint64_t num){
	// Primality test implemented is trial division and deterministic Miller-Rabin for 64 bit unsigned integer.
	// In octaves files threshold of >195e8 enables Miller-Rabin. This is 2-3 bits over 32 bit unsigned integer.
	// TODO: Investigate other methods like Baillie-PSW and APR-CL, and underline mathematical test them self.
	//
	// References:
	//   https://hg.octave.org/octave/file/tip/scripts/specfun/isprime.m (Retrieved 14.03.2023).

	// The trial by division calculates isqrt and then checks every odd number between it and 3.
	// It is guaranteed that isqrt is biggest number which could divisible with given number.
	// If we check divisibility of 2 and 3 manually then next possible number is +6 from previous.
	// This is because after 2 and 3 is check every prime is 6k±1. So start at 5 and +6. NOTE: CITETATION NEEDED!
	//
	// Reference:
	//  https://en.wikipedia.org/wiki/Primality_test
	if(num==2 || num==3) return true;
	if(num<=1 || num%2==0 || num%3==0) return false;

	uint64_t sqrtnum = isqrt(num);
	for(uint64_t b=5;b<sqrtnum;b+=6){
		// b is now 6k-1 for some k so b+2=6k+1 for same k.
		if(num%b==0 || num%(b+2)==0) return false;
	}
	// Number survived our tests.
	return true;
}
