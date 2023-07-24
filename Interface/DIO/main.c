/*
 * main.c
 *
 * Created: 7/24/2023 5:37:50 AM
 *  Author: Abnaby
 */ 


#include <avr/io.h>
#include <util/delay.h>
#include <dio.h>

int main(void)
{
	// PINA2 Output
	dio_vidConfigChannel(DIO_PORTA,DIO_PIN2,OUTPUT);
	
	// PINA0 Input-Pull Up
	dio_vidConfigChannel(DIO_PORTA,DIO_PIN0,INPUT);
	dio_vidEnablePullUp(DIO_PORTA,DIO_PIN0);
	
	// PINA2 HIGH
	dio_vidWriteChannel(DIO_PORTA,DIO_PIN2, STD_HIGH);

	 
    while (1) 
    {
		// Externally Pulled-Up
		if(dio_dioLevelReadChannel(DIO_PORTA,DIO_PIN0) == STD_LOW)
			dio_vidFlipChannel(DIO_PORTA,DIO_PIN2); 
		// Every 10 ms
		_delay_ms(10);
		
    }
}
