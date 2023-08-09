/*
 * eeprom.h
 *
 * Created: 8/5/2023 2:26:02 PM
 *  Author: reBuyTech
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

#include "std_types.h"
#include "bit_math.h"
#include "eeprom_reg.h"

void EEPROM_write(u16 uiAddress, u8 ucData);
void EEPROM_writeBlock(u16 uiAddress , u8 *ptrBuffer , u32 bufferSize);
u8 EEPROM_read(u16 uiAddress);
void EEPROM_readBlock(u16 uiAddress , u8 *ptrBuffer , u32 length);


#endif /* EEPROM_H_ */