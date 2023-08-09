/*
 * eeprom_reg.h
 *
 * Created: 8/5/2023 2:27:08 PM
 *  Author: reBuyTech
 */ 


#ifndef EEPROM_REG_H_
#define EEPROM_REG_H_

#include "std_types.h"

#define EEPROM_EECR_REG			(*(volatile u8*)0x3C)
#define EEPROM_EEDR_REG			(*(volatile u8*)0x3D)
#define EEPROM_EEAR_REG			(*(volatile u16*)0x3E)

#define EEPROM_EEWE_BIT_NO			(1)
#define EEPROM_EEMWE_BIT_NO			(2)
#define EEPROM_EERE_BIT_NO			(0)
#endif /* EEPROM_REG_H_ */