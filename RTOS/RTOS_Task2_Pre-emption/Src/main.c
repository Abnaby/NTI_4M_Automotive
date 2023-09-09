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
#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOSConfig.h"

/*******************************	LEDs		********************************/
#define GREEN_BUILT_IN_LED		PORTA, PIN5
#define YELLOW_EXTERNAL_LED		PORTA,PIN6

/*******************************	Task Handlers ******************************/
xTaskHandle T1_GreenLedHandle = NULL ;
xTaskHandle T2_RedLedHandle = NULL ;

/*******************************	Tasks **************************************/
void T1_voidGreenLed(void * pvParam)
{
	while(1)
	{
		GPIO_voidTogglePinValue(GREEN_BUILT_IN_LED);
		vTaskDelay(500);
	}
}
void T2_voidRedLed(void * pvParam)
{
	while(1)
	{
		GPIO_voidTogglePinValue(YELLOW_EXTERNAL_LED);
		vTaskDelay(500);
	}
}
int main(void)
{

	/********************************** Task Configuration *****************************************/
	(void)xTaskCreate(T1_voidGreenLed, "T1_GreenLED", 85 , NULL, 1, &T1_GreenLedHandle) ;
	(void)xTaskCreate(T2_voidRedLed, "T2_RedLED"  , 85 , NULL, 2, &T2_RedLedHandle) ;		//	Task 2 Higher priority
	/********************************** System Inits ***********************************************/
	RCC_voidInitSysClocks() ;		 		// Init Clock
	RCC_voidEnableClock(RCC_AHB, PORTA);	/*	PORTA	*/
	GPIO_voidSetPinDirection(GREEN_BUILT_IN_LED, GPIO_OUTPUT_LOW_SPD_PUSH_PULL);
	GPIO_voidSetPinDirection(YELLOW_EXTERNAL_LED, GPIO_OUTPUT_LOW_SPD_PUSH_PULL);

	/********************************** Start Scheduler ******************************************/
	vTaskStartScheduler();
	while(1)
	{
		__asm("NOP");
	}
}