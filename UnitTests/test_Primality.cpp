/*
< File uses unit testing library cpputest to test Primality module.
*/
#include <CppUTest/TestHarness.h>
#include <CppUTest/CommandLineTestRunner.h>
#include "../Src/Primality.h"

int main(int ac,char** av){
	return CommandLineTestRunner::RunAllTests(ac, av);
}

TEST_GROUP(Primality){;};

TEST(Primality,IsPrime){

	// Tests for the first 10 natural numbers.
	CHECK_TEXT(!isPrime(0),"0 is not prime number!");
	CHECK_TEXT(!isPrime(1),"1 is not prime number anymore!");
	CHECK_TEXT( isPrime(2),"2 is prime number!");
	CHECK_TEXT( isPrime(3),"3 is prime number!");
	CHECK_TEXT(!isPrime(4),"4 is not a prime number!");
	CHECK_TEXT( isPrime(5),"5 is a prime number!");
	CHECK_TEXT(!isPrime(6),"6 is not a prime number!");
	CHECK_TEXT( isPrime(7),"7 is a prime number!");
	CHECK_TEXT(!isPrime(8),"8 is not a prime number!");
	CHECK_TEXT(!isPrime(9),"9 is not a prime number!");

	// Test near 2^32.
	CHECK_TEXT( isPrime(UINT32_MAX-4llu),"2^32-5 is a prime number!");
	CHECK_TEXT(!isPrime(UINT32_MAX-3llu),"2^32-4 is not a prime number!");
	CHECK_TEXT(!isPrime(UINT32_MAX-2llu),"2^32-3 is not a prime number!");
	CHECK_TEXT(!isPrime(UINT32_MAX-1llu),"2^32-2 is not a prime number!");
	CHECK_TEXT(!isPrime(UINT32_MAX-0llu),"2^32-1 is not a prime number!");
	CHECK_TEXT(!isPrime(UINT32_MAX+1llu),"2^32+0 is not a prime number!");
	CHECK_TEXT(!isPrime(UINT32_MAX+2llu),"2^32+1 is not a prime number!");
	CHECK_TEXT(!isPrime(UINT32_MAX+3llu),"2^32+2 is not a prime number!");
	CHECK_TEXT(!isPrime(UINT32_MAX+4llu),"2^32+3 is not a prime number!");
	CHECK_TEXT(!isPrime(UINT32_MAX+5llu),"2^32+4 is not a prime number!");
	CHECK_TEXT(!isPrime(UINT32_MAX+6llu),"2^32+5 is not a prime number!");
};
