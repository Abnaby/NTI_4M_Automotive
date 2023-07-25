/*
 * main.c
 *
 * Created: 7/24/2023 5:37:50 AM
 *  Author: Abnaby
 */ 


#include <avr/io.h>
#include <util/delay.h>
#include <dio.h>
#include <lcd.h>
#include <exti.h>
#include <avr/interrupt.h>
// Interrupts 
u8 Global_Var ;
void main(void)
{
	// GPIO Init 	
	// PINA0 Input-Pull Up
	dio_vidConfigChannel(DIO_PORTD,DIO_PIN2,INPUT);
	dio_vidConfigChannel(DIO_PORTD,DIO_PIN3,INPUT);
	dio_vidConfigChannel(DIO_PORTB,DIO_PIN2,INPUT);
	
	
	dio_vidEnablePullUp(DIO_PORTD,DIO_PIN2);
	dio_vidEnablePullUp(DIO_PORTD,DIO_PIN3);
	dio_vidEnablePullUp(DIO_PORTB,DIO_PIN2);
	
	
	// LCD Init
	lcd_vidInit();
	
	EXT_Init(int0 ,falling); 
	EXT_Init(int1 ,falling); 
	EXT_Init(int2 ,falling); 

	
	lcd_vidDisplyStr((u8*)"IRQ Initialized >>>>"); 

	
	Global_Int(enable);
	while(1)
	{
		if(Global_Var)
		{
			lcd_vidClrDislay();
			lcd_vidDisplyStr((u8*)"Welcome to Main -- "); 
			Global_Var = 0 ; 
		}
	}
}


ISR(INT0_vect)
{
	lcd_vidClrDislay();
	Global_Var = 1 ;
	lcd_vidDisplyStr((u8*)"Welcome to INT0 -- "); 
	_delay_ms(1000);

}
ISR(INT1_vect)
{

	lcd_vidClrDislay();
	Global_Var = 1 ;
	lcd_vidDisplyStr((u8*)"Welcome to INT1 -- "); 
	_delay_ms(1000);
	
}
ISR(INT2_vect)
{
	lcd_vidClrDislay();
	Global_Var = 1 ;
	lcd_vidDisplyStr((u8*)"Welcome to INT2 -- "); 
	_delay_ms(1000);
	
}