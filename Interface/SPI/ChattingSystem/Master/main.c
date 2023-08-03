/*
 * main.c
 *
 * Created: 7/24/2023 5:37:50 AM
 *  Author: Abnaby
 */ 



#include <avr/io.h>
#include <util/delay.h>
#include <dio.h>
#include <keypad.h>
#include <lcd.h>
#include <uart.h>
#include <exti.h>
#include <spi.h>
#include <avr/interrupt.h>


// Macros	
#define MSTR_AVILABLE_TO_RECEIVE						'$'			// Used When Slave Transmit String Will use '$'	 as a dummy
#define SLAVE_LISTENING_WHILE_MSTR_TRANSMIT				'^'			// Used When Master Transmit Data Slave Will Replay With '^'
#define SLVE_STRING_END_CHAR							'#'			// Used as end string indicator
#define DEBUG_ENABLE									0
// Global Variables 
u8 *ReceievedFromUART = 0 ;											// Pointer to received buffer from UART
u8 Is_SPI_Request_Transmit = 0 ;									// Changed by ISR
volatile u8 SPI_ComingData = 0 ;									// Coming Data From SPI
u8 SPI_DataExchangeHappens = 0 ;									// Indicator for data exchange 
u8 Exist_UART_Msg	= 0 ;											// Explaining if new message exist or not
u8 G_RX_Buffer[20] ;		
										// Buffer For Received Data

// Prototypes 
void ExchangeDataISR(u8 ComingData);
void TX_Complete(void)
{

}
void SendStringThroughSpi(u8 *ptrString)
{
	// This Function Will Send Whole string with '\0'
	u8 LOC_u8Counter = 0; 
	// Send Next Character  
	spi_masterSendByteUsingIRQ(ptrString[LOC_u8Counter]);
	do
	{
		// Send Next Character  
		spi_masterSendByteUsingIRQ(ptrString[LOC_u8Counter]);
		// Wait to exchange
		SPI_DataExchangeHappens = 0 ; 
		while(SPI_DataExchangeHappens==0);
		// Increase Ccounter 
		LOC_u8Counter++;
	}while(ptrString[LOC_u8Counter-1] != '\0' );
	// Reset SPI_DataExchangeHappens
	SPI_DataExchangeHappens = 0  ;
	// Reset Flag 
	Exist_UART_Msg = 0 ;
}

void ReceiveStringThroughSpi(u8 *ptrString)
{
	u8 LOC_u8Counter = 0 ;
	// While Is_SPI_Request_Transmit = 1 and The Received String Doesn't Reach to the SLVE_STRING_END_CHAR 
	if(Is_SPI_Request_Transmit == 1)
	{
		do
		{
			// Send Dummy Byte First
			spi_masterReceiveByteUsingIRQ(MSTR_AVILABLE_TO_RECEIVE); 
			// Wait Until Exchange Happens
			SPI_DataExchangeHappens = 0 ; 
			while(SPI_DataExchangeHappens==0);
			// Store Received Data To Buffer 
			ptrString[LOC_u8Counter] = SPI_ComingData ; 
			// Increase Counter 
			LOC_u8Counter++;
		}while(ptrString[LOC_u8Counter-1] != SLVE_STRING_END_CHAR );
		
		// Send Dummy Byte First
		spi_masterReceiveByteUsingIRQ(MSTR_AVILABLE_TO_RECEIVE); 
		
		// Set End with '\0'
		ptrString[LOC_u8Counter-1] = '\0'; 
		
		// Reset SPI_DataExchangeHappens
		SPI_DataExchangeHappens = 0  ;
		
		// Reset Is_SPI_Request_Transmit 
		Is_SPI_Request_Transmit = 0 ;
		
		// Display Coming 
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
	u8 Locu8Counter=0 ; 
	lcd_vidClrDislay();
	lcd_vidDisplyStr((u8*)"Received String -- "); 
	lcd_vidGotoRowColumn(1,4);	
	lcd_vidDisplyStr((u8*)ptrBuffer); 
	ReceievedFromUART = ptrBuffer ; 
	Exist_UART_Msg = 1 ;
	// Shift String By Space 
    // Shift array by 1 position to the right
    for (Locu8Counter = BufferSize; Locu8Counter >= 1; Locu8Counter--) {
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
	
	// UART Init
	dio_vidConfigChannel(DIO_PORTD,DIO_PIN1,OUTPUT);
	UART_Init(UART_BAUDRATE_9600);
	// Call Asynch Function
	UART_ReceiveStringAsynch(RX_CompleteString);
	UART_voidTransmitStringAsynch(ReceievedFromUART, TX_Complete) ;

	// SPI 
	spi_masterInit(ExchangeDataISR); 
	
	// External Interrupt  PINA0 Input-Pull Up
	dio_vidConfigChannel(DIO_PORTD,DIO_PIN2,INPUT);
	dio_vidEnablePullUp(DIO_PORTD,DIO_PIN2);
	_delay_ms(1000);
	EXT_Init(int0 ,any_logic_change); 
	sei();
	
	//SendStringThroughSpi("Hello\r\n\0");
	while(1)
	{		
		// Check Is_SPI_Request_Transmit To Serve it 
		if(Is_SPI_Request_Transmit == 1 )
		{
			// SPI Request to transmit Data 
			ReceiveStringThroughSpi(G_RX_Buffer);
		}
		
		// Check if exist new msg on UART
		if(Exist_UART_Msg == 1)
		{
			// Transmit Buffer 
			SendStringThroughSpi(ReceievedFromUART);
			// Reset Flag
			Exist_UART_Msg = 0 ;
		}
	}
}

ISR(INT0_vect)
{
	// Slave Request Transmit 
	Is_SPI_Request_Transmit = 1 ; 
	#if DEBUG_ENABLE == 1
	// Display Buffer 
	lcd_vidClrDislay();
	lcd_vidDisplyStr((u8*)"ISR"); 
	#endif
	
	
}
void ExchangeDataISR(u8 ComingData)
{
	// Store Data
	SPI_ComingData = ComingData ; 
	// Set Data Exchange Variable
	SPI_DataExchangeHappens = 1 ; 
#if DEBUG_ENABLE == 1
	// For Debug 
	lcd_vidClrDislay();
	lcd_vidDisplyChar(  SPI_ComingData ) ;
	_delay_ms(200);
#endif
}
