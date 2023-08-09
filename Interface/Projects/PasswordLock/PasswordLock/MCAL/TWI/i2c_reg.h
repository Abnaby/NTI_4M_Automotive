 /********************************************************************************************************************
 *  File		: I2c_Reg.h
 *	Module		: I2C
 *	Target		: ATMEGA32
 *	Author		: mFawzi
 *  Description	:
 *********************************************************************************************************************/
#ifndef I2C_PRIVATE_H
#define I2C_PRIVATE_H
/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "std_types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define I2C_TWDR_REG      		(*(volatile u8*)0x23)


#define I2C_TWAR_REG			(*(volatile u8*)0x22)
#define TWGCE	0


#define I2C_TWCR_REG			(*(volatile u8*)0x56)
#define TWIE	0
#define TWEN	2
#define TWWC	3
#define TWSTO	4
#define TWSTA	5
#define TWEA	6
#define TWINT	7


#define I2C_TWSR_REG			(*(volatile u8*)0x21)
#define I2C_TWBR_REG			(*(volatile u8*)0x20)









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

#endif  /* I2C_PRIVATE_H */

/**********************************************************************************************************************
 *  END OF FILE: I2c_Private.h
 *********************************************************************************************************************/
