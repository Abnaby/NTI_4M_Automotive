# TASK1.1

## Q:  mention 1 ways to create a variable without allocate space in ram.

Will Use the preprocessor directives option `#` to make text replacements for variable names.

```C
/*
Usage MACRO example :
                       VAR(Variable_Name) ; 
                       Variable_Name = 7 ; // integer Value
*/
#define VAR(VAR_NAME)   int VAR_NAME
int main(void)
{
	VAR(myVar) = 5 ; 
	printf("%d", myVar) ; 
}
```

## *Contributing*  
Bug reports, feature requests, and so on are always welcome. Feel free to leave a note in the Issues section.