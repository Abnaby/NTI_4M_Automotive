// mention 3 ways to know if a specific number is even or odd.

#include <stdio.h>

/**
 * @brief _SELECT_WAY_NUMBER_ is used to select the way number x --> x= 1|2|3 
 *
 */
#define _SELECT_WAY_NUMBER_		3

int main(void)
{
	int givenNumber = 5 ; 
	#if  _SELECT_WAY_NUMBER_ == 1 
	// Using % operator 
	if(givenNumber%2 == 1)
	{
		// Odd
		printf("Odd Number\n");
	}
	else
	{
		// Even 
		printf("Even Number\n");
	}
	#elif _SELECT_WAY_NUMBER_ == 2 
	
	// Using Binary Method all odd numbers LSB are 1 and all even numbers the LSB are 0
	if(givenNumber&1 == 1)
	{
		// Odd
		printf("Odd Number\n");
	}
	else
	{
		// Even 
		printf("Even Number\n");
	}

	#elif _SELECT_WAY_NUMBER_ == 3 
	// Using Casting... fractions are lost in devision
		if( ((givenNumber/2)*givenNumber) != givenNumber)
	{
		// Odd
		printf("Odd Number\n");
	}
	else
	{
		// Even 
		printf("Even Number\n");
	}


	#endif 
	return 0;
}
