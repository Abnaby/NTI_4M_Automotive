/*
 * extint.h
 *
 *  Created on: Jul 5, 2023
 *      Author: reBuyTech
 */

#ifndef EXTINT_H_
#define EXTINT_H_

#include "std_types.h"
#include "extint_types.h"

#define EXTI0					0
#define EXTI1					1
#define EXTI2					2
#define EXTI3					3
#define EXTI4					4
#define EXTI5					5
#define EXTI6					6
#define EXTI7					7
#define EXTI8					8
#define EXTI9					9
#define EXTI10					10
#define EXTI11					11
#define EXTI12					12
#define EXTI13					13
#define EXTI14					14
#define EXTI15					15

/*****************************************PROTOTYPES*********************************************/

void extint_enableLine(u8 lineId, extint_sense_t inSense,void (*clbk)(void));
void extint_disbleLine(u8 lineId);

void extint_SofwareInterrupt(u8 lineId);
void extint_clearFlag(u8 lineId);




#endif /* EXTINT_H_ */
