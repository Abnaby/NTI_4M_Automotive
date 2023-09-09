/*
 * extint_reg.h
 *
 *  Created on: Jul 5, 2023
 *      Author: reBuyTech
 */

#ifndef EXTINT_REG_H_
#define EXTINT_REG_H_

#define EXTINT_BASE_ADDR			(0x40010400)

#define EXTI_IMR1_REG				(*(volatile u32*)(EXTINT_BASE_ADDR + 0x00))
#define EXTI_IMR2_REG				(*(volatile u32*)(EXTINT_BASE_ADDR + 0x20))

#define EXTI_EMR1_REG				(*(volatile u32*)(EXTINT_BASE_ADDR + 0x04))
#define EXTI_EMR2_REG				(*(volatile u32*)(EXTINT_BASE_ADDR + 0x24))

#define EXTI_RTSR1_REG				(*(volatile u32*)(EXTINT_BASE_ADDR + 0x08))
#define EXTI_RTSR2_REG				(*(volatile u32*)(EXTINT_BASE_ADDR + 0x28))

#define EXTI_FTSR1_REG				(*(volatile u32*)(EXTINT_BASE_ADDR + 0x0C))
#define EXTI_FTSR2_REG				(*(volatile u32*)(EXTINT_BASE_ADDR + 0x2C))

#define EXTI_SWIER1_REG				(*(volatile u32*)(EXTINT_BASE_ADDR + 0x10))
#define EXTI_SWIER2_REG				(*(volatile u32*)(EXTINT_BASE_ADDR + 0x30))

#define EXTI_PR1_REG				(*(volatile u32*)(EXTINT_BASE_ADDR + 0x14))
#define EXTI_PR2_REG				(*(volatile u32*)(EXTINT_BASE_ADDR + 0x34))



#endif /* EXTINT_REG_H_ */
