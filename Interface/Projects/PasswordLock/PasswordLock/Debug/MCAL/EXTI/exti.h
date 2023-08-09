 /***************************************
 *  File		: exti.h
 *	Module		: EXTI
 *	Target		: ATMEGA32
 *	Author		: Mohamed Abd El-Naby
 *  Description	:
 ****************************************/
#ifndef EXTI_H
#define EXTI_H

#include "bit_math.h"
#include "std_types.h"
#include "exti_reg.h"
#include "exti_types.h"

void EXT_Init(interrupt_source ,event_state );
void EXT_Disable(interrupt_source copy_interruptNumber );
void Global_Int( enable_disable );

#endif  /* EXTI_H */
