/**
* @file SW_UART.c
* @author Mohamed Abd El-Naby (mahameda.naby@gmail.com) 
* @brief 
* @version 0.1
* @date 2023-08-16
*
*/


/******************************************************************************
* Includes
*******************************************************************************/

#include "dio.h"
#include <util/delay.h>
#include "std_types.h"
#include "SW_UART.h"



/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/
#define WAIT_BIT_TIME()     _delay_us(Glob_u8SamplingTimeinUS)

#define MAX_DATA_BITS   8u   

/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/




/******************************************************************************
* Typedefs
*******************************************************************************/




/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
static u8 Glob_u8SamplingTimeinUS  ; 


/******************************************************************************
* Function Prototypes
*******************************************************************************/




/******************************************************************************
* Function Definitions
*******************************************************************************/



void SW_UART_Init(void)
{
    // Set Sampling Time in US  = 1/BR   * 10^6 
    Glob_u8SamplingTimeinUS = (u8)((1.0 / (float)SW_UART_BUAD_RATE) * 1000000) ; 

    // Set TX Pin to Output 
    if (PIN_DISABLED != SW_UART_TX_PORT_PIN)
    {
        // Set it as Output 
        dio_vidConfigChannel(SW_UART_TX_PORT_PIN,OUTPUT) ; 
        // IDLE State 
        dio_vidWriteChannel(SW_UART_TX_PORT_PIN , STD_HIGH ) ;
    }  
    // Set RX Pin to INPUT 
    if (PIN_DISABLED != SW_UART_RX_PORT_PIN)
    {
        // Set it as INPUT 
        dio_vidConfigChannel(SW_UART_TX_PORT_PIN,INPUT) ; 
    } 
    
}


void SW_UART_Transmit(u8 copy_u8Data)
{
    u8 LOC_u8Counter = 0 ; 
    if (PIN_DISABLED != SW_UART_TX_PORT_PIN)
    {
        // Change IDLE State 
        dio_vidWriteChannel(SW_UART_TX_PORT_PIN , STD_LOW );
        // Wait 
        WAIT_BIT_TIME(); 

        // Send Bit by Bit 
        for(LOC_u8Counter = 0 ; LOC_u8Counter < MAX_DATA_BITS  ; LOC_u8Counter++)
        {
            // Get Bit Number LOC_u8Counter
            if(copy_u8Data & (1<<LOC_u8Counter) == 1)
            {
                // High Bit 
                dio_vidWriteChannel(SW_UART_TX_PORT_PIN , STD_HIGH ) ;
            }
            else
            {
                dio_vidWriteChannel(SW_UART_TX_PORT_PIN , STD_LOW ) ;
            }
            // Wait 
            WAIT_BIT_TIME(); 
        }

        // Stop Bit - IDLE State 
        dio_vidWriteChannel(SW_UART_TX_PORT_PIN , STD_HIGH ) ;
        // Wait 
        WAIT_BIT_TIME(); 
    }
    else
    {
        // <!TODO> Error UART Transmit Pin Not Connected
    }
}


void SW_UART_Receive(u8 *ptr_u8Data)
{
    u8 LOC_u8ComingData = 0 , LOC_u8Counter = 0  ; 

    // Polling Until RX pin Gets LOW 
    while (dio_dioLevelReadChannel(SW_UART_RX_PORT_PIN) != 0)
    {
        ; // Do Nothing Waiting Second Device Send Any Data 
    }
    // Wait 
    WAIT_BIT_TIME(); 

    // Receive Data 
    for(LOC_u8Counter = 0 ; LOC_u8Counter < MAX_DATA_BITS  ; LOC_u8Counter++)
    {
        if(dio_dioLevelReadChannel(SW_UART_RX_PORT_PIN) == STD_HIGH)
        {
            // High Bit 
            LOC_u8ComingData |= (1<<LOC_u8Counter);
        }
        else
        {
            LOC_u8ComingData &= ~(1<<LOC_u8Counter);
        }
        // Wait 
        WAIT_BIT_TIME(); 

        // Wait Stop Bit
    }

    // Polling Until RX pin Gets LOW 
    while (dio_dioLevelReadChannel(SW_UART_RX_PORT_PIN) != 1)
    {
        ; // Do Nothing Waiting Second Device Send Stop Bit
    }
}


/************************************* End of File ******************************************/