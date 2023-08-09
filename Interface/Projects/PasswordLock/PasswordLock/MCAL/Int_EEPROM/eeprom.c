/*
 * eeprom.c
 * Created: 8/5/2023 2:26:53 PM
 *  Author: reBuyTech
 */ 
#include "eeprom.h"
#include "util/delay.h"
void EEPROM_write(u16 uiAddress, u8 ucData)
{
	/* Wait for completion of previous write */
	while(CHECK_BIT(EEPROM_EECR_REG, EEPROM_EEWE_BIT_NO) == 1)
	{
			;/*	Do Nothing	*/
	}
	/* Set up address and data registers */
	EEPROM_EEAR_REG = uiAddress;
	EEPROM_EEDR_REG = ucData;
	/* Write logical one to EEMWE */
	SET_BIT(EEPROM_EECR_REG,EEPROM_EEMWE_BIT_NO);
	/* Start eeprom write by setting EEWE */
	SET_BIT(EEPROM_EECR_REG, EEPROM_EEWE_BIT_NO);
}
void EEPROM_writeBlock(u16 uiAddress , u8 *ptrBuffer , u32 bufferSize)
{
	volatile u32 Loc_u32Counter ; 
	

	lcd_vidDisplyStr("Buffer Size : ");
	lcd_vidDisplayNumbers(bufferSize);
	_delay_ms(4000);
	for(Loc_u32Counter = 0 ; Loc_u32Counter < bufferSize ; Loc_u32Counter++)
	{
		lcd_vidClrDislay();
		lcd_vidDisplayNumbers(Loc_u32Counter);
		EEPROM_write(uiAddress,ptrBuffer[Loc_u32Counter] );
		uiAddress++;  
	}
}
u8 EEPROM_read(u16 uiAddress)
{
	/* Wait for completion of previous write */
	while(CHECK_BIT(EEPROM_EECR_REG, EEPROM_EEWE_BIT_NO) == 1)
	{
		;/*	Do Nothing	*/
	}
	/* Set up address register */
	EEPROM_EEAR_REG = uiAddress;
	/* Start eeprom read by writing EERE */
	SET_BIT(EEPROM_EECR_REG,EEPROM_EERE_BIT_NO);
	/* Return data from data register */
	return EEPROM_EEDR_REG;
}
void EEPROM_readBlock(u16 uiAddress , u8 *ptrBuffer , u32 length)
{
	u32 Loc_u32Counter ; 
	for(Loc_u32Counter = 0 ; Loc_u32Counter < length ; Loc_u32Counter++,uiAddress++)
	{
		ptrBuffer[Loc_u32Counter] = EEPROM_read(uiAddress); 
	}
}
