 /*********************************************
 *  File		: I2c.c
 *	Module		: I2C
 *	Target		: ATMEGA32
 *	Author		: mFawzi
 *  Description	:
 *
 ***********************************************/
 #define F_CPU	16000000UL

#include <util/delay.h>
#include "std_types.h"
#include "bit_math.h"
#include "i2c.h"
#include "i2c_reg.h"
#include "lcd.h"
#include <avr/interrupt.h>

void I2C_MasterInit(void)
{
    /* Bit Rate: 400 KHZ */
	I2C_TWBR_REG=0X0C;
    /* enable I2C Module	*/
	/* enable ACK check	*/
	I2C_TWCR_REG|=(1<<TWEN);
}

void I2C_SlaveInit(u8 addr)
{
	/*	enable general call response in slave mode	*/
		SET_BIT(I2C_TWAR_REG,TWGCE);
    /* I2C Bus Slave Address	*/
		I2C_TWAR_REG|=(addr<<1);
    /* enable I2C Module	*/
	/*	enable ACK check	*/
		I2C_TWCR_REG|=(1<<TWEA);
}
boolean I2C_StartCondition(void)
{
	/*	send start condition	*/
		I2C_TWCR_REG|=(1<<TWSTA)|(1<<TWINT);
    /*	Wait until start condition sent successfully	*/
		while(!CHECK_BIT(I2C_TWCR_REG,TWINT));
		//CLEAR_BIT(I2C_TWCR_REG,TWSTA);
	/*	check I2C status then return ture or false	*/
		if((I2C_TWSR_REG&0xf8)!=0x08)
		{
			return FALSE;
		}
    return TRUE;
}
boolean I2C_RepeatedStartCondition(void)
{
	/*	send start condition	*/
	I2C_TWCR_REG|=(1<<TWSTA)|(1<<TWINT);
	/*	Wait until start condition sent successfully	*/
	//_delay_ms(5);
	while(CHECK_BIT(I2C_TWCR_REG,TWINT)==0);
	//CLEAR_BIT(I2C_TWCR_REG,TWSTA);
	/*	check I2C status then return ture or false	*/
	if(I2C_ReadStatus()!=0x10)
	{
		return FALSE;
	}
	return TRUE;
}
void I2C_StopCondition(void)
{
	/*	send stop condition	*/
			I2C_TWCR_REG|=(1<<TWSTO)|(1<<TWINT);
	/*	Wait until stop condition sent successfully	*/
		
}
void I2C_WriteByte(u8 data)
{
    /*	Put data On I2C data Register	*/
		I2C_TWDR_REG=data;
	/*trigger data send*/
		CLEAR_BIT(I2C_TWCR_REG,TWSTA);
		I2C_TWCR_REG|=(1<<TWINT);


	/*	Wait until data sent successfully	*/
		while(!CHECK_BIT(I2C_TWCR_REG,TWINT));
}
boolean I2C_Send_SlaveAddressWriteOperation(u8 addr)
{
		

		/*	prepare address+W	*/
			I2C_TWDR_REG=addr<<1;
		/*	send addr+W on i2c	*/
		I2C_TWCR_REG|=(1<<TWINT);
		while(!CHECK_BIT(I2C_TWCR_REG,TWINT));
		/*	check I2C status then return ture or false	*/
		//LCD_WriteNumber(I2C_TWSR_REG&0xf8);
		if((I2C_TWSR_REG&0xf8)!=I2C_SLA_W_ACK)
		{
			return FALSE;
		}
    return TRUE;

}
boolean I2C_Send_SlaveAddressReadOperation(u8 addr)
{
		
		u8 add_write=0;
		/*	prepare address+W	*/
		add_write|=(addr<<1)|(0x01);
		
		/*	send addr+R on i2c	*/
		I2C_WriteByte(add_write);
		/*	check I2C status then return ture or false	*/
		if((I2C_TWSR_REG&0xf8)!=I2C_SLA_R_ACK)
		{
			return FALSE;
		}
		return TRUE;
}
u8 I2C_ReadByte(void)
{
	/*	Wait until data read successfully	*/
	CLEAR_BIT(I2C_TWCR_REG,TWSTA);
		I2C_TWCR_REG|=(1<<TWINT);
		while(!CHECK_BIT(I2C_TWCR_REG,TWINT));
		
    return I2C_TWDR_REG;
}
u8 I2C_ReadStatus(void)
{
    u8 status;
    status = I2C_TWSR_REG & 0xF8; // 1111 1000
    return status;
}
/*
ISR(TWI_vect)
{
	
}
*/
