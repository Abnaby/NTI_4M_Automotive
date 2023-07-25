 /**************************************************
 *  File		: exti.c
 *	Module		: EXTI
 *	Target		: ATMEGA32
 *	Author		: Mohamed Abd El-Naby 
 *  Description	:
 *
 ***************************************************/
#include "exti.h"


void EXT_Init(interrupt_source copy_interruptNumber ,event_state copy_InterruptState)
{
	switch(copy_interruptNumber)
	{
		case int0:
		{
			if(copy_InterruptState == falling   )
			{
				/*	CLEAR ISC00 AND SET ISC01 IN MCUCR	*/
				CLEAR_BIT(EXTINT_MCUCR,MCUCR_ISC00);
				SET_BIT(EXTINT_MCUCR,MCUCR_ISC01);
			}
			else if(copy_InterruptState ==  rising )
			{
				/*	SER ISC00 AND ISC01 IN MCUCR	*/
				SET_BIT(EXTINT_MCUCR,MCUCR_ISC00);
				SET_BIT(EXTINT_MCUCR,MCUCR_ISC01);
			}
			else if(copy_InterruptState == low)
			{
				/*	CLEAR ISC00 AND ISC01 IN MCUCR	*/
				CLEAR_BIT(EXTINT_MCUCR,MCUCR_ISC00);
				CLEAR_BIT(EXTINT_MCUCR,MCUCR_ISC01);
			}
			else if(copy_InterruptState == any_logic_change)
			{
				/*	SET ISC00 AND CLEAR ISC01 IN MCUCR	*/
				CLEAR_BIT(EXTINT_MCUCR,MCUCR_ISC01);
				SET_BIT(EXTINT_MCUCR,MCUCR_ISC00);
			}
			else
			{
				
				// Todo Error
			}
			
			/*		ENABLE INT0		*/
			SET_BIT(EXTINT_GICR,GICR_INT0);
		}
		break; 
		case int1:
		{
			if(copy_InterruptState == falling   )
			{
				/*	CLEAR ISC00 AND SET ISC01 IN MCUCR	*/
				CLEAR_BIT(EXTINT_MCUCR,MCUCR_ISC10);
				SET_BIT(EXTINT_MCUCR,MCUCR_ISC11);
			}
			else if(copy_InterruptState ==  rising )
			{
				/*	SER ISC00 AND ISC01 IN MCUCR	*/
				SET_BIT(EXTINT_MCUCR,MCUCR_ISC10);
				SET_BIT(EXTINT_MCUCR,MCUCR_ISC11);
			}
			else if(copy_InterruptState == low)
			{
				/*	CLEAR ISC00 AND ISC01 IN MCUCR	*/
				CLEAR_BIT(EXTINT_MCUCR,MCUCR_ISC10);
				CLEAR_BIT(EXTINT_MCUCR,MCUCR_ISC11);
			}
			else if(copy_InterruptState == any_logic_change)
			{
				/*	SET ISC00 AND CLEAR ISC01 IN MCUCR	*/
				CLEAR_BIT(EXTINT_MCUCR,MCUCR_ISC11);
				SET_BIT(EXTINT_MCUCR,MCUCR_ISC10);
			}
			else
			{
				
				// Todo Error
			}
			/*		ENABLE INT1 	*/
			SET_BIT(EXTINT_GICR,GICR_INT1);
		}
		break;
		case int2:
		{
			if(copy_InterruptState == falling   )
			{
				/*	CLEAR ISC2 IN MCUCSR	*/
				CLEAR_BIT(EXTINT_MCUCSR,MCUCSR_ISC2);
			}
			else if(copy_InterruptState ==  rising )
			{
				/*	SET ISC2 IN MCUCSR	*/
				SET_BIT(EXTINT_MCUCSR,MCUCSR_ISC2);
			}
			else
			{
				//copy_InterruptState == low | any_logic_change Not Supported 
				// Todo Error

			}
			/*		ENABLE INT2		*/
			SET_BIT(EXTINT_GICR,GICR_INT2);
		}
		break;
		default:
		break ; 
	}
}

void Global_Int(enable_disable copy_State )
{
	if(copy_State == enable)
	{
		/*	ENABLE GLOBAL INTTERUPT	*/
		SET_BIT(SREG,SREG_GIE);
	}
	else if (copy_State == disable)
	{	
		/*	Disable GLOBAL INTTERUPT	*/
		CLEAR_BIT(SREG,SREG_GIE);
	}
	else
	{
		// Todo Error
	}
}