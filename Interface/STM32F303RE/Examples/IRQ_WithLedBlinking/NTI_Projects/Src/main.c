/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
#include "std_types.h"
#include "bit_math.h"
#include "../Inc/RCC/RCC_interface.h"
#include "../Inc/GPIO/GPIO_interface.h"
#include "../Inc/NVIC/nvic.h"
#include "../Inc/EXTI/extint.h"


#define SYSCFG_EXTICR4		*((u32 *)  (0x40010000+0x14))

#define EXTI_13()			SYSCFG_EXTICR4 |= (0b0010 << 4)


// Not Accurate
void xDelay(u32 ms)
{
	int i , j ;
	for (i=0; i<ms; i++)
	for (j=0; j<1000;j++)
	{
		__asm("NOP");
	}
}
void callBack(void)
{
	GPIO_voidSetPinValue(PORTA, PIN5, HIGH);
	xDelay(1000);
	GPIO_voidSetPinValue(PORTA, PIN5, LOW);
	xDelay(1000);
}
int main(void)
{
	// Init Clock
	RCC_voidInitSysClocks() ;

	/*	PORTA	*/
	RCC_voidEnableClock(RCC_AHB, PORTA);
	/*	EXTI	*/

	RCC_voidEnableClock(RCC_APB2, 0);	//AFIO


	RCC_voidEnableClock(RCC_AHB, PORTC);
	GPIO_voidSetPinDirection(PORTA, PIN5, GPIO_OUTPUT_LOW_SPD_PUSH_PULL);
	/*		PORTC13			*/
	GPIO_voidSetPinDirection(PORTC, PIN13, GPIO_INPUT_FLOATING);
	EXTI_13();
	extint_enableLine(EXTI13, BOTH, callBack) ;
	nvic_enableInterrupt(40);
	while(1)
	{
		__asm("NOP");
	}
}
