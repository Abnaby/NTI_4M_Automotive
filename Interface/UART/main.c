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
#include <uart.h>
#include <avr/interrupt.h>


void RX_CompleteString(u8 *ptrBuffer , u8 BufferSize)
{
	lcd_vidClrDislay();
	lcd_vidDisplyStr((u8*)"Received String -- "); 
	lcd_vidGotoRowColumn(1,4);	
	lcd_vidDisplyStr((u8*)ptrBuffer); 
}
int main(void)
{
	// LCD Init
	lcd_vidInit();
	// UART Init
	dio_vidConfigChannel(DIO_PORTD,DIO_PIN1,OUTPUT);
	UART_Init(UART_BAUDRATE_9600);
	UART_ReceiveStringAsynch(RX_CompleteString);
	sei();
    while (1) 
    {
		__asm("NOP");
    }
}