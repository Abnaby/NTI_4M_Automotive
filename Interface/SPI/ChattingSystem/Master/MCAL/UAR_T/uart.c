 /**************************************************
 *  File		: Uart.c
 *	Module		: UART
 *	Target		: ATMEGA32
 *	Author		: mFawzi
 *  Description	:
 *
 ***************************************************/
#include "uart.h"
#include <avr/interrupt.h>

/*************************** Static Function ***********************/
static void (*Global_TxComplate) (void) = NULL;
static void (*Global_RxComplate) (u8) = NULL;
static void (*Global_RxComplateString) (u8* ,u8) = NULL;

static u8 Global_u8SendString = 0 ; 
static u8 Global_u8ReceiveString = 0 ;
static u8 *Global_ptrStringToBeTransmitted ; 

static u8 Global_u8ReceiveBuffer[MAX_BUFFER_SIZE] ; 
void UART_Init(u16 baudRate)
{
	/* Set baud rate */
	UART_UBRRH_REG = (u8)(baudRate>>8);
	UART_UBRRL_REG = (u8)baudRate;
	/* Enable receiver and transmitter */
	SET_BIT(UART_UCSRB_REG,RXEN_BIT_NO);  /* Enable Receiver*/
	SET_BIT(UART_UCSRB_REG,TXEN_BIT_NO);  /* Enable Transmitter */
	/* Set frame format: 8data, 1stop bit, Even Parity */
	UART_UCSRC_REG |= (1 << URSEL_BIT_NO)|UART_8_BIT_DATA | UART_EVEN_PARITY;
}

void UART_TransmitChr(u8 data)
{
	/* Wait for empty transmit buffer */
	while (!(CHECK_BIT(UART_UCSRA_REG,UDRE_BIT_NO)))
			;
	/* Put data into buffer, sends the data */
	UART_UDR_REG = data;
}
void UART_TransmitString(u8 *data)
{
	/* Wait for empty transmit buffer */
	u8 LOC_u8Counter = 0 ; 
	while(data[LOC_u8Counter] != '\0')
	{
		while (!(CHECK_BIT(UART_UCSRA_REG,UDRE_BIT_NO)));
		/* Put data into buffer, sends the data */
		UART_UDR_REG = data[LOC_u8Counter];	
		LOC_u8Counter++ ; 	
	}

}

u8 UART_ReceiveChr(void)
{
	/* Wait for data to be received */
	while (!(CHECK_BIT(UART_UCSRA_REG,RXC_BIT_NO)))
			;
	/* Get and return received data from buffer */
	return UART_UDR_REG;
}

void UART_voidTransmitCharAsynch(u8 copy_u8Data , void(*Tx_CallBack)(void))
{
	
	if(Tx_CallBack!= NULL)
	{
		// Sending Char
		Global_u8SendString = 0 ; 
		// Set Callback Function 
		Global_TxComplate = Tx_CallBack ;
		// Set Data 
		UART_UDR_REG = copy_u8Data  ;  
		// Enable UART IRQ
		UART_UCSRB_REG |= (1<<TXCIE_BIT_NO) ; 
	}
}
void UART_voidTransmitStringAsynch(u8 *ptr_u8Data , void(*Tx_CallBack)(void))
{
	
	if(Tx_CallBack!= NULL)
	{

		// Link Global Pointer to user string
		Global_ptrStringToBeTransmitted = ptr_u8Data   ; 
		// Set Callback Function 
		Global_TxComplate = Tx_CallBack ;
		// Set Data 
		UART_UDR_REG = Global_ptrStringToBeTransmitted[0]  ;  

		// Sending String
		Global_u8SendString = 1 ;
		// Enable UART IRQ
		UART_UCSRB_REG |= (1<<TXCIE_BIT_NO) ;
	}
}
void UART_ReceiveChrAsynch(void(*Rx_CallBack)(u8 Copy_CommingData))
{
	if(Rx_CallBack!= NULL)
	{
		Global_u8ReceiveString = 0 ; 
		// Link With Callback 
		Global_RxComplate = Rx_CallBack ;
		// Enable RX Interrupt
		UART_UCSRB_REG |= (1<<RXCIE_BIT_NO) ;
	}
	
}
void UART_ReceiveStringAsynch(void(*Rx_CallBack)(u8 *ptr_CommingData,u8 copy_u8BufferSize))
{
	if(Rx_CallBack!= NULL)
	{
		Global_u8ReceiveString = 1 ; 
		// Link With Callback 
		Global_RxComplateString = Rx_CallBack ;
		// Enable RX Interrupt
		UART_UCSRB_REG |= (1<<RXCIE_BIT_NO) ;
	}
	
}
ISR(USART_RXC_vect)
{
	if(Global_u8ReceiveString)
	{
		static u8 LOC_u8Counter = 0 ;
		// Check The Comming Data is terminal char or not and check if exceed the max buffer size 
		if(Global_u8ReceiveBuffer[(LOC_u8Counter==0)?0:LOC_u8Counter-1] != UART_RX_ENDING_CHAR && LOC_u8Counter < MAX_BUFFER_SIZE)
		{
			// Available to Store Data 
			Global_u8ReceiveBuffer[ LOC_u8Counter ] = UART_UDR_REG ;
			UART_UCSRB_REG |= (1<<RXCIE_BIT_NO) ;
			LOC_u8Counter++ ;
		}
		else
		{
			// Clear Flag By Reading UDR 
			(void)UART_UDR_REG;
			// Clear UART_RX_ENDING_CHAR From Array 
			Global_u8ReceiveBuffer[LOC_u8Counter-1] = '\0' ; 
			// Call User Function
			Global_RxComplateString(Global_u8ReceiveBuffer,LOC_u8Counter);
			LOC_u8Counter = 0 ; 
		}
		 
	}
	else
	{
		// Char
		Global_RxComplate(UART_UDR_REG);
	}
	// Clear Flag 
	
	
}
ISR(USART_TXC_vect)
{	// Clear Flag 
	CLEAR_BIT( UART_UCSRB_REG, TXCIE_BIT_NO);
	// TX IRQ When Complete 
	if(Global_u8SendString)
	{
		// Send String from Buffer 
		static u8 LOC_u8Counter = 0 ;
		LOC_u8Counter++ ; 
		// Chack Current Char
		if ( Global_ptrStringToBeTransmitted[LOC_u8Counter] != '\0')
		{
			// Send Next Char 
			// Set Data 
			UART_UDR_REG = Global_ptrStringToBeTransmitted[LOC_u8Counter]  ;  
			// Enable UART IRQ
			UART_UCSRB_REG |= (1<<TXCIE_BIT_NO)  ; 
		}
		else
		{
			LOC_u8Counter = 0 ; 
			// Clear Flag 
			CLEAR_BIT( UART_UCSRB_REG, TXCIE_BIT_NO);
			Global_TxComplate();
			Global_u8SendString++;
			
		}
		
	}
	else
	{
		// Send Char	
		Global_TxComplate();
		
	}
	//SET_BIT( UART_UCSRA_REG, TXC_BIT_NO);
}
