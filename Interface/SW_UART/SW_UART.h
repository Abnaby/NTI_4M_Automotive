/**
* @file SW_UART.h
* @author Mohamed Abd El-Naby (mahameda.naby@gmail.com) 
* @brief 
* @version 0.1
* @date 2023-08-16
*
*/
#ifndef SW_UART__H 
#define SW_UART__H 





/******************************************************************************
* Includes
*******************************************************************************/
#define PIN_DISABLED    0



/******************************************************************************
* User Configuration
*******************************************************************************/

/**
 * @brief Set buadrate of UART 
 * 
 */
#define SW_UART_BUAD_RATE           9600

/**
 * @brief Define TX pin in form of pair PORT,PIN 
 * @details while SW_UART_TX_PORT_PIN != PIN_DISABLED TX pin is working
 * 
 */
#define SW_UART_TX_PORT_PIN         DIO_PORTA,DIO_PIN0

/**
 * @brief Define RX pin in form of pair PORT,PIN 
 * @details while SW_UART_RX_PORT_PIN != PIN_DISABLED RX pin is working
 * 
 */
#define SW_UART_RX_PORT_PIN         DIO_PORTA,DIO_PIN0



/******************************************************************************
* Preprocessor Constants
 *******************************************************************************/




/******************************************************************************
* Configuration Constants
*******************************************************************************/




/******************************************************************************
* Macros
*******************************************************************************/




/******************************************************************************
* Typedefs
*******************************************************************************/




/******************************************************************************
* Variables
*******************************************************************************/




/******************************************************************************
* Function Prototypes
*******************************************************************************/

/**
 * @brief This Function is used to initialize software uart based on @ref SW_UART_BUAD_RATE param.
 * 
 */
void SW_UART_Init(void); 

/**
 * @brief  This Function is used to transmit byte through software UART. 
 * 
 * @param copy_u8Data copy of data to be transmitted.
 */
void SW_UART_Transmit(u8 copy_u8Data); 

/**
 * @brief  This Function is used to recieve byte from software UART 
 * 
 * @param ptr_u8Data pointer to variable that will hold comming byte 
 */
void SW_UART_Receive(u8 *ptr_u8Data); 


#endif
/************************************* End of File ******************************************/