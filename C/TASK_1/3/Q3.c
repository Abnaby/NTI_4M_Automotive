// mention 2 ways to print your name inside main function using printf function ( without writing ; at the end of this line )


#include <stdio.h>

/**
 * @brief _SELECT_WAY_NUMBER_ is used to select the way number x --> x= 1|2
 *
 */
#define _SELECT_WAY_NUMBER_		1

int main(void)
{
	#if  _SELECT_WAY_NUMBER_ == 1 
	if(printf("My Name is Mohamed\n")); 
	#elif _SELECT_WAY_NUMBER_ == 2 
	while(!(printf("My Name is Mohamed\n"))); 
	#endif 
	return 0;
}
