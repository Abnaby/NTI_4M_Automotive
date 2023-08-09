 /******************************************
 *  File		: exti.h
 *	Module		: EXTI
 *	Target		: ATMEGA32
 *	Author		: Mohamed Abd El-Naby
 *  Description	:
 *******************************************/
#ifndef EXTI_REG_H
#define EXTI_REG_H

#include "std_types.h"
#include "exti.h"


#define GICR_INT0   6
#define GICR_INT1   7
#define GICR_INT2   5

#define SREG_GIE    7

#define MCUCR_ISC00 0
#define MCUCR_ISC01 1
#define MCUCR_ISC10 2
#define MCUCR_ISC11 3

#define GIFR_INTF1	7
#define GIFR_INTF0	6
#define GIFR_INTF2	5

#define  MCUCSR_ISC2	6


/*!<*************************** MCU Control Register **********************/
#define EXTINT_MCUCR      *((volatile u8 *) (0x55))
/*!<***************************  MCU Control and Status Register **********************/
#define EXTINT_MCUCSR     *((volatile u8 *) (0x54))
/*!<*************************** General Interrupt Control Register **********************/
#define EXTINT_GICR       *((volatile u8 *) (0x5B))
/*!<*************************** General Interrupt Control Register **********************/
#define EXTINT_GIFR       *((volatile u8 *) (0x5A))
/*!<*************************** General Interrupt Control Register **********************/
#define SREG              *((volatile u8 *) (0x5F))


#endif  /* UART_PRIVATE_H */
