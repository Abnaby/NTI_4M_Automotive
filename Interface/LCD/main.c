/*
 * NTI_Projects.c
 *
 * Created: 7/23/2023 2:50:30 PM
 * Author : Abnaby
 */ 

#include <avr/io.h>
#include <dio.h>
#include <lcd.h>



int main(void)
{
  
	lcd_vidInit();
	
	lcd_vidGotoRowColumn(0,2);
	lcd_vidDisplyChar(0x02); 
	lcd_vidDisplyStr((u8*)"Welcome to NTI"); 
	lcd_vidDisplyChar(0x02); 
	
	lcd_vidGotoRowColumn(1,6);
	lcd_vidDisplyStr((u8*)"Abnaby ");
	lcd_vidDisplyChar(0x01); 
	
	lcd_vidGotoRowColumn(2,5);
	
	lcd_vidDisplayNumbers(4294967295);
		
    while (1) 
    {
	//	lcd_vidDisplyStr((u8*)"Welcome to NTI"); 
    }
}

