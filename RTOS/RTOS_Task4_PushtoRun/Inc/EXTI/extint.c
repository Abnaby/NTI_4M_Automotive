/*
 * extint.c
 *
 *  Created on: Jul 5, 2023
 *      Author: reBuyTech
 */
#include "extint.h"
#include "std_types.h"
#include "extint_reg.h"
#include "bit_math.h"

void (*extint0_Callback[15])(void) = {NULL,NULL};
void extint_enableLine(u8 lineId, extint_sense_t inSense,void (*clbk)(void))
{
	if (lineId>=0 && lineId<32)
	{
			/* Enable Interrupt on the line */
			SET_BIT(EXTI_IMR1_REG, lineId);
			if (inSense == FAILING)
			{
				SET_BIT(EXTI_FTSR1_REG, lineId);
			}
			else if (inSense == RISING)
			{
				SET_BIT(EXTI_RTSR1_REG, lineId);
			}
			else
			{
				SET_BIT(EXTI_FTSR1_REG, lineId);
				SET_BIT(EXTI_RTSR1_REG, lineId);
			}
		extint0_Callback[lineId]=clbk;
	}
	else
	{
		/* Enable Interrupt on the line */
		SET_BIT(EXTI_IMR2_REG, lineId);
		if (inSense == FAILING)
		{
			SET_BIT(EXTI_FTSR2_REG, lineId);
		}
		else if (inSense == RISING)
		{
			SET_BIT(EXTI_RTSR2_REG, lineId);
		}
		else
		{
			SET_BIT(EXTI_FTSR2_REG, lineId);
			SET_BIT(EXTI_RTSR2_REG, lineId);
		}
	extint0_Callback[lineId]=clbk;
	}
}
void extint_clearFlag(u8 lineId)
{
	if (lineId>=0 && lineId<32)
	{
		/* clearing Interrupt on the line */
		SET_BIT(EXTI_PR1_REG, lineId);
	}
	else
	{
		SET_BIT(EXTI_PR2_REG, lineId);
	}
}


void EXTI0_IRQHandler(void)
{
		extint_clearFlag(EXTI0);
		if (extint0_Callback[EXTI0] != NULL)
		{
			extint0_Callback[EXTI0]();
		}
}
void EXTI15_10_IRQHandler(void)
{
		extint_clearFlag(EXTI13);
		if (extint0_Callback[EXTI13] != NULL)
		{
			extint0_Callback[EXTI13]();
		}
}
