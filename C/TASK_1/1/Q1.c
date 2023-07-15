// mention 1 ways to create a variable without allocate space in ram.

// 1st Way 
#include <stdio.h>
/*
Usage MACRO example :
                       VAR(Variable_Name) ; 
                       Variable_Name = 7 ; // integer Value
*/
#define VAR(VAR_NAME)   int VAR_NAME
int main(void)
{
	VAR(myVar) =  5 ; 
	myVar++ ; 
	printf("%d", myVar) ;  // Output Will Be 6 
}

/*
// 2nd Way 
#include <stdio.h>

int main(void)
{
	// the compiler may ignore register keyword.
	register int my var =  6; 
	printf("%d", myVar) ;  // Output Will Be 6 
}
*/
