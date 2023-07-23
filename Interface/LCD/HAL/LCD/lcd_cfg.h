/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  lcd_cfg.h
 *       Module:  lcd
 *
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/
#ifndef LCD_CFG_H
#define LCD_CFG_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "std_types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define LCD_RS_PORT				DIO_PORTA
#define LCD_RS_CHANNEL			DIO_PIN3

#define LCD_EN_PORT     		DIO_PORTA
#define LCD_EN_CHANNEL			DIO_PIN2

#define LCD_D4_PORT				DIO_PORTB
#define LCD_D4_CHANNEL			DIO_PIN0

#define LCD_D5_PORT				DIO_PORTB
#define LCD_D5_CHANNEL			DIO_PIN1

#define LCD_D6_PORT				DIO_PORTB
#define LCD_D6_CHANNEL			DIO_PIN2

#define LCD_D7_PORT				DIO_PORTB
#define LCD_D7_CHANNEL			DIO_PIN4


#define NO_CSTOM_CHAR			8
#define NO_CSTOM_CHAR_BYTES		8

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
  
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

 
#endif  /* LCD_CFG_H */

/**********************************************************************************************************************
 *  END OF FILE: lcd_cfg.h
 *********************************************************************************************************************/
