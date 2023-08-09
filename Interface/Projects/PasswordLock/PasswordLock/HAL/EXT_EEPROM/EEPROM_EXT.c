/*
 * EEPROM_EXT.c
 *
 * Created: 8/4/2023 3:51:06 PM
 *  Author: Amr
 */ 
#define F_CPU	16000000UL
#include <util/delay.h>
#include "std_types.h"
#include "bit_math.h"
#include "i2c.h"
#include "i2c_reg.h"

void eep_writebyte(u8 addr,u8 data)
{
	I2C_StartCondition();
	I2C_Send_SlaveAddressWriteOperation(0b01010000);
	I2C_WriteByte(addr);
	I2C_WriteByte(data);
	I2C_StopCondition();
	_delay_ms(2);
}

u8 eep_readByte(u8 addr)
{
	u8 x=0;
	I2C_StartCondition();
	I2C_Send_SlaveAddressWriteOperation(0b01010000);
	I2C_WriteByte(addr);
	I2C_RepeatedStartCondition();
	I2C_Send_SlaveAddressReadOperation(0b01010000);
	x=I2C_ReadByte();
	I2C_StopCondition();
	return x;
}