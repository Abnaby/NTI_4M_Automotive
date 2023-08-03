/*
 * main.c
 *
 * Created: 7/24/2023 5:37:50 AM
 *  Author: Abnaby
 */ 


#include "avr/io.h"
#include "util/delay.h"
#include "dio.h"
#include "lcd.h"
#include "uart.h"
#include "exti.h"
#include "spi.h"
#include "avr/interrupt.h"

// Macros 
#define SEND_MSG_REQ()	dio_vidFlipChannel(DIO_PORTD,DIO_PIN2)				// Make Sending Request
#define SLAVE_LISTENING_WHILE_MSTR_TRANSMIT				'^'					// Used When Master Transmit Data Slave Will Replay With '^'
#define SLVE_STRING_END_CHAR							'#'			// Used as end string indicator
#define DEBUG_ENABLE									 0

// Global Variables 
u8 *ReceievedFromUART = 0 ;													// Pointer to received buffer from UART
volatile u8 SPI_ComingData = 0 ;											// Coming Data From SPI
u8 SPI_DataExchangeHappens = 0 ;									// Indicator for data exchange 
u8 G_RX_Buffer[20] ;												// Buffer For Received Data
u8 RequestTransmit = 0	;											// Request Transmit from Master 
u8 G_AfterReceiption = 0 ;
// Prototypes 
void ExchangeDataISR(u8 comingData);
void TX_Complete(void)
{

}
void TransmitStringThroughSpi(u8 *ptrString)
{
	u8 LOC_u8Counter = 0 ;
	// Dummy 
	spi_SlaveSendByte(ptrString[LOC_u8Counter]);
	SPI_DataExchangeHappens = 0 ; 
	while(SPI_DataExchangeHappens == 0);	
	if(RequestTransmit == 1)
	{
		do
		{
			// Send Next Char 
			spi_SlaveSendByte(ptrString[LOC_u8Counter]);
			LOC_u8Counter++; 
			// Wait for Next Request 
			SPI_DataExchangeHappens = 0 ; 
			while(SPI_DataExchangeHappens == 0);			
		}while(ptrString[LOC_u8Counter-1] != SLVE_STRING_END_CHAR);	
		// Send Null
		spi_SlaveSendByte(SLVE_STRING_END_CHAR);
		// Set Null Char 
		ptrString[LOC_u8Counter-1] = '\0' ; 
		RequestTransmit = 0 ; 
		SPI_DataExchangeHappens = 0 ;
		G_AfterReceiption = 1;

		
	}
}
void ReceiveStringThroughSpi(u8 *ptrString)
{
	u8 LOC_u8Counter = 0 ;
	if(SPI_DataExchangeHappens == 1)
	{
		do
		{
			ptrString[LOC_u8Counter] = SPI_ComingData ;
			// Send Predefined Char 
			spi_SlaveSendByte(SLAVE_LISTENING_WHILE_MSTR_TRANSMIT);
			LOC_u8Counter++ ; 
			// Wait Next Char 
			SPI_DataExchangeHappens = 0 ; 
			while(SPI_DataExchangeHappens == 0)
			{
				if(ptrString[LOC_u8Counter-1] == '\0' )
					break ;
			}
			
		}while(ptrString[LOC_u8Counter-1] != '\0');		
		// Reset Flag 
		G_AfterReceiption = 0 ;
		SPI_DataExchangeHappens = 0 ;
		#if DEBUG_ENABLE == 1 
		// Display Buffer 
		lcd_vidClrDislay();
		lcd_vidDisplyStr((u8*)ptrString); 
		#endif 
		UART_voidTransmitStringAsynch("\r\n",TX_Complete);
		UART_voidTransmitStringAsynch(&ptrString[0], TX_Complete) ;
	}
}

void RX_CompleteString(u8 *ptrBuffer , u8 BufferSize)
{
	u8 Locu8Counter =  0 ; 
	lcd_vidClrDislay();
	lcd_vidDisplyStr((u8*)"Received String -- "); 
	lcd_vidGotoRowColumn(1,4);	
	lcd_vidDisplyStr((u8*)ptrBuffer); 
	ReceievedFromUART = ptrBuffer ; 
	RequestTransmit = 1 ; 
	ptrBuffer[BufferSize-1] = '\0' ; 
	ptrBuffer[BufferSize] = SLVE_STRING_END_CHAR ;
	for (Locu8Counter = BufferSize+1; Locu8Counter >= 1; Locu8Counter--) {
		ptrBuffer[Locu8Counter] = ptrBuffer[Locu8Counter-1];
	}
	ptrBuffer[0] = '>' ;
		UART_TransmitString("\r\n");
	UART_TransmitString(ptrBuffer);
}
int main(void)
{
	// LCD Init 
	lcd_vidInit();
	
	// GPIO
	// Set Pin Output PD2 as Output
	dio_vidConfigChannel(DIO_PORTD,DIO_PIN2,OUTPUT);
	dio_vidWriteChannel(DIO_PORTD,DIO_PIN2,STD_HIGH);
	
	// UART Init
	dio_vidConfigChannel(DIO_PORTD,DIO_PIN1,OUTPUT);
	UART_Init(UART_BAUDRATE_9600);
	// Call Asynch Function
	UART_ReceiveStringAsynch(RX_CompleteString);
	UART_voidTransmitStringAsynch(ReceievedFromUART, TX_Complete) ;
	//UART_voidTransmitStringAsynch("\r\n SLAVE TERMINAL \r\n", TX_Complete) ;

	// SPI 
	spi_slaveInit(ExchangeDataISR); 
	
	sei();
	RequestTransmit = 0 ; 
	SPI_DataExchangeHappens = 0 ;
	
	while(1)
	{
		if(RequestTransmit == 1)
		{
			// Request Transmit From Master
			SEND_MSG_REQ();
			// Start Transmit
			TransmitStringThroughSpi(ReceievedFromUART);
			
			// Reset Buffer 
			RequestTransmit = 0 ; 
			
		}
				
		ReceiveStringThroughSpi(G_RX_Buffer);
		//_delay_ms(1000);
	}
}

void ExchangeDataISR(u8 comingData)
{
	// Recieved Byte 
	SPI_ComingData = comingData ; 
	SPI_DataExchangeHappens = 1 ;
}