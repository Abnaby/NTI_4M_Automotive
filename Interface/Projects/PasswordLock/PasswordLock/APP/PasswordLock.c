
/************************************* Includes ********************************/
// LIB
#include "bit_math.h"
#include "dio_types.h"
#include "std_types.h"

// MCAL 
#include "dio.h"
#include "i2c.h"
#include "TIMERS_Interface.h"
#include "avr/interrupt.h"

#if USAGE_EEPROM  == APP_USES_INTERNAL_EEPROM
#include "ATMEGA_EEPROM_Interface.h"
#endif

// HAL
#include "keypad.h"
#include "lcd.h"
#if USAGE_EEPROM  == APP_USES_EXTERNAL_EEPROM
#include "EEPROM_EXT_Interface.h"
#endif
// APP 
#include "PasswordLock_cfg.h"
#include "PasswordLock.h"
/************************************* MACROS ***************************/
#define DEBUG_MODE		0
#define TEST_MODE		0
#define INTERNAL_EEPROM_TST 0
#define EXTERNAL_EEPROM_TST 0

#define IS_FIRST_TIME_ADDRESS_EEPROM	0x00A0
/************************************* TYPEDEFs ***************************/
typedef enum
{
	NOT_FIRST_TIME = 0 ,
	FIRST_TIME ,
}APP_TimeUsage_t;

typedef enum
{
	E_NOK	,
	E_OK
}APP_ErrorHandling_t; 
/************************************* Global Variables ***************************/
static Timer1Config_t PasswordLock_Timer;
static APP_TimeUsage_t Glob_u8IsFirstTime = FIRST_TIME ; 
static u8 APP_GlobalPasswordBuffer[NUM_PASS_DIGITS];
static APP_ErrorHandling_t Global_ErrorHandling = E_NOK ; 
static u8 Global_u8SystemIsLocked = 1 ; 
static u8 Loc_u8SystemPrevState = 1 ; 

/************************************* Private Functions **************************/
static void TIMER1_CallbackFunction(void)
{
#if TEST_MODE == 1 
	// 1-Min Code
	static u32 numOfFourSeconds ,min = 0  ; 
	if(numOfFourSeconds == 15 )
	{
	lcd_vidClrDislay(); 
	min++; 
	numOfFourSeconds = 0 ; 
	lcd_vidDisplayNumbers(min); 		
	}
	numOfFourSeconds++;	
#endif 
// Will Interrupt Every 20 Second
static u8 NumberOf_4_Seconds = 1 ; 
	if( NumberOf_4_Seconds >= 5)
	{
		// 20 Second Happen
		Global_u8SystemIsLocked = 1 ; 
		NumberOf_4_Seconds = 1 ; 
		// Stop Timer 
		Timer_voidStopTimer(TIMER1);

	}
	else
	{
		NumberOf_4_Seconds++ ; 
	}
}
static void APP_WriteEEPROM(u16 uiAddress, u8 ucData)
{
	#if USAGE_EEPROM  == APP_USES_EXTERNAL_EEPROM
	eep_writebyte(uiAddress, ucData);
	#else
	EEPROM_write(uiAddress, ucData);
	#endif 
}
static u8 APP_ReadEEPROM(u16 uiAddress)
{
	u8 LOC_u8ReturnValue = 0xFF ;  // 0xFF init. value for EEPROM
	#if USAGE_EEPROM  == APP_USES_EXTERNAL_EEPROM
	LOC_u8ReturnValue = eep_readByte(uiAddress);
	#else
	LOC_u8ReturnValue = EEPROM_read(uiAddress);
	#endif 	
	return LOC_u8ReturnValue ; 
}
static void APP_FactoryReset(void)
{
	// Clear EEPROM 
	APP_WriteEEPROM(IS_FIRST_TIME_ADDRESS_EEPROM, 0xFF);
	// Soft Reset 
	asm("jmp 0x0000");
}
static void APP_voidDisplayMainScreen(boolean copy_isLocked, u8 copy_u8PageNumber)
{
	lcd_vidClrDislay(); 
	lcd_vidGotoRowColumn(0,0);	
	lcd_vidDisplyStr((u8*)"State : ");
	if(copy_isLocked == 1)
	{
		lcd_vidDisplyStr((u8*)"Locked");
		lcd_vidGotoRowColumn(0,19);	
		lcd_vidDisplyChar(0);
	}
	else
	{
		lcd_vidDisplyStr((u8*)"Unlocked");
		lcd_vidGotoRowColumn(0,19);	
		lcd_vidDisplyChar(1);
	}
	if(copy_u8PageNumber == 0)
	{
		lcd_vidGotoRowColumn(1,3);	
		lcd_vidDisplyStr((u8*)"Select One of: ");
		if(copy_isLocked)
		{
			lcd_vidGotoRowColumn(2,0);	
			lcd_vidDisplyStr((u8*)"1- Unlock ");
		}
		else
		{
			// Unlocked
			lcd_vidGotoRowColumn(2,0);	
			lcd_vidDisplyStr((u8*)"1- Lock ");		
		}
		lcd_vidGotoRowColumn(3,0);	
		lcd_vidDisplyStr((u8*)"2- Change Password ");	
		lcd_vidGotoRowColumn(3,19);	
		lcd_vidDisplyChar(2); // Down Button
			
	}
	else if (copy_u8PageNumber == 1)
	{
		if(copy_isLocked)
		{
			lcd_vidGotoRowColumn(1,0);	
			lcd_vidDisplyStr((u8*)"1- Unlock ");
		}
		else
		{
			// Unlocked
			lcd_vidGotoRowColumn(1,0);	
			lcd_vidDisplyStr((u8*)"1- Lock ");		
		}
		lcd_vidGotoRowColumn(2,0);	
		lcd_vidDisplyStr((u8*)"2- Change Password ");	
		lcd_vidGotoRowColumn(2,19);	
		lcd_vidGotoRowColumn(3,0);	
		lcd_vidDisplyStr((u8*)"3- Factory Reset ");	
		lcd_vidGotoRowColumn(3,19);	
		
		lcd_vidDisplyChar(3); // Up Button		
	}
	
}
static APP_ErrorHandling_t APP_u8SetPassword(void)
{
	u8 LOC_u8PasswordFlag = 1;
	u8 LOC_u8PasswordCounter = 0 ; 
	u8  LOC_u8key = 0xff ; 
	u8 LOC_u8ComingEEPROM_Data ; 
	APP_ErrorHandling_t  LOC_u8Result = E_OK ; 

	lcd_vidClrDislay(); 
	lcd_vidDisplyStr((u8*)"Enter ");
	lcd_vidDisplayNumbers(NUM_PASS_DIGITS);
	lcd_vidDisplyStr((u8*)"-digit Pass:");
	lcd_vidGotoRowColumn(1,6);
	while(LOC_u8PasswordCounter < NUM_PASS_DIGITS)
	{
		LOC_u8key = keypad_u8GetKey();
		if(	LOC_u8key != 0xFF)
		{
			// Pressed 
			APP_GlobalPasswordBuffer[LOC_u8PasswordCounter] = LOC_u8key ; 
			LOC_u8PasswordCounter++ ; 
			lcd_vidDisplyChar('*');
		}
		_delay_ms(100);
	}	
			
	// Reset Password Counter
	LOC_u8PasswordCounter = 0 ; 
	lcd_vidGotoRowColumn(2,0);
	lcd_vidDisplyStr((u8*)"Repeat Password ");
	lcd_vidGotoRowColumn(3,6);
	while(LOC_u8PasswordCounter < NUM_PASS_DIGITS)
	{
		LOC_u8key = keypad_u8GetKey();
		if(	LOC_u8key != 0xFF)
		{
			// Pressed 
			if (LOC_u8key != APP_GlobalPasswordBuffer[LOC_u8PasswordCounter])
			{
				LOC_u8PasswordFlag = 0 ; 
			}
			LOC_u8PasswordCounter++ ; 
			lcd_vidDisplyChar('*');	
			_delay_ms(100);
		}
	}
	// Check Identical Or Not 
	if(LOC_u8PasswordFlag == 1)
	{
	// Saving in EEPROM
		// Identical 
		lcd_vidClrDislay(); 
		lcd_vidGotoRowColumn(1,5);
		lcd_vidDisplyStr((u8*)"Good... ");
		// Set To Not First Time 
		APP_WriteEEPROM(IS_FIRST_TIME_ADDRESS_EEPROM, NOT_FIRST_TIME);
		LOC_u8ComingEEPROM_Data = APP_ReadEEPROM(IS_FIRST_TIME_ADDRESS_EEPROM);
		// Confirm Write Operation 
		if(NOT_FIRST_TIME != LOC_u8ComingEEPROM_Data)
		{
			// Print Failure in system
			lcd_vidClrDislay(); 
			lcd_vidGotoRowColumn(0,3);
			lcd_vidDisplyStr((u8*)"EEPROM FAIL");
			lcd_vidGotoRowColumn(2,5);	
			lcd_vidDisplyStr((u8*)"Power Mode");	
			_delay_ms(2000);	
			#if EEPROM_FAILURE_HANDLE_EN == 1 
			LOC_u8Result = E_OK; 
			#else
			LOC_u8Result = E_NOK; 
			#endif
		}
		else
		{
			Glob_u8IsFirstTime = NOT_FIRST_TIME ; 
			// Store Password In EEPROM 
			for(LOC_u8PasswordCounter = 0 ;  LOC_u8PasswordCounter < NUM_PASS_DIGITS ; LOC_u8PasswordCounter++)
			{
				// Write Password in EEPORM 
				APP_WriteEEPROM((IS_FIRST_TIME_ADDRESS_EEPROM+LOC_u8PasswordCounter+1) , 	APP_GlobalPasswordBuffer[LOC_u8PasswordCounter]);
				// Confirm That Everything is clear 
				while(APP_ReadEEPROM(IS_FIRST_TIME_ADDRESS_EEPROM+LOC_u8PasswordCounter+1) !=APP_GlobalPasswordBuffer[LOC_u8PasswordCounter])
				{
					// Rewrite Operation
					APP_WriteEEPROM((IS_FIRST_TIME_ADDRESS_EEPROM+LOC_u8PasswordCounter+1) , 	APP_GlobalPasswordBuffer[LOC_u8PasswordCounter]);
				}
			}
		}			
		_delay_ms(1000);		
	}
	else 
	{
		// Not Identical
		lcd_vidClrDislay(); 
		lcd_vidGotoRowColumn(1,2);
		lcd_vidDisplyStr((u8*)"Not Identical...");
		_delay_ms(1000);
		LOC_u8Result = E_NOK ; 
	}				
	return LOC_u8Result ; 
}
static APP_ErrorHandling_t APP_HandleFirstTime(void)
{
	u8 LOC_u8PasswordCounter = 0 ; 
	// Vars 
	u8 LOC_u8ComingEEPROM_Data = 0 ; 
	APP_ErrorHandling_t  LOC_u8Result = E_OK ; 
	
	LOC_u8ComingEEPROM_Data = APP_ReadEEPROM(IS_FIRST_TIME_ADDRESS_EEPROM);
	if(NOT_FIRST_TIME != LOC_u8ComingEEPROM_Data)
	{
		lcd_vidClrDislay(); 
		lcd_vidGotoRowColumn(1,0);	
		lcd_vidDisplyStr((u8*)"Welcome to safe area");
		_delay_ms(1500);
		// Get Password 
		LOC_u8Result = APP_u8SetPassword();
	}
	else if (NOT_FIRST_TIME == LOC_u8ComingEEPROM_Data)
	{
		#if DEBUG_MODE == 1 
		lcd_vidClrDislay(); 
		lcd_vidDisplyStr((u8*)"NOT_FIRST== Data");
		_delay_ms(1000);

		#endif
		Glob_u8IsFirstTime = NOT_FIRST_TIME ; 
		// Reload Password From EEPROM to APP_GlobalPasswordBuffer
		#if DEBUG_MODE == 1 
		lcd_vidClrDislay(); 
		#endif
		for(LOC_u8PasswordCounter = 0 ;  LOC_u8PasswordCounter < NUM_PASS_DIGITS ; LOC_u8PasswordCounter++)
		{
			// Write Password in EEPORM 
			APP_GlobalPasswordBuffer[LOC_u8PasswordCounter]	 = APP_ReadEEPROM(IS_FIRST_TIME_ADDRESS_EEPROM+LOC_u8PasswordCounter+1);
			#if DEBUG_MODE == 1 
			lcd_vidDisplyChar(APP_GlobalPasswordBuffer[LOC_u8PasswordCounter]);
			_delay_ms(1000);
			#endif
		}
		APP_GlobalPasswordBuffer[LOC_u8PasswordCounter]	 = '\0';
		#if DEBUG_MODE == 1 
		lcd_vidClrDislay(); 
		lcd_vidDisplyStr((u8*)"Password From EEPROM"); 
		lcd_vidGotoRowColumn(1,0);
		lcd_vidDisplyStr((u8*)APP_GlobalPasswordBuffer); 
		_delay_ms(1000);
		#endif
		LOC_u8Result = E_OK ;
	}
	else
	{
		// Never goes here.	
		LOC_u8Result = E_NOK ;
		#if DEBUG_MODE == 1 
		lcd_vidClrDislay(); 
		lcd_vidDisplyStr((u8*)"What a fuck"); 
		#endif
	}
	return LOC_u8Result; 
}
static u8 APP_u8PasswordAuthentication(u8* ptrToInputPassword)
{
	u8 Loc_u8IsEqual = 1 ; 
	u8 Loc_u8Counter = 0 ; 
	for(Loc_u8Counter = 0 ; Loc_u8Counter<NUM_PASS_DIGITS ;  Loc_u8Counter++)
	{
		if(ptrToInputPassword[Loc_u8Counter] != APP_GlobalPasswordBuffer[Loc_u8Counter])
		{
			Loc_u8IsEqual = 0 ; 
		}
	}
	return Loc_u8IsEqual ; 
}
static void APP_voidGetPassword(u8* Buffer)
{
	u8 LOC_u8PasswordCounter = 0 ; 
	u8 LOC_u8key = 0xFF ; 
	lcd_vidClrDislay(); 
	lcd_vidDisplyStr((u8*)"Enter Password ");
	lcd_vidGotoRowColumn(1,6);
	while(LOC_u8PasswordCounter < NUM_PASS_DIGITS)
	{
		LOC_u8key = keypad_u8GetKey();
		if(	LOC_u8key != 0xFF)
		{
			// Pressed 
			Buffer[LOC_u8PasswordCounter] = LOC_u8key ; 
			LOC_u8PasswordCounter++ ; 
			lcd_vidDisplyChar('*');
		}
		_delay_ms(100);
	}	
}
/************************************* Definitions ********************************/
void PasswordLock_voidInit(void)
{
	/********************************** Inits *****************************/
	// TIMER 
	PasswordLock_Timer.operationModeTIM1			 = TIM_CTC_Mode     ; 
	PasswordLock_Timer.clockSourceAndPrescalerTimer1 = TIMER1_CLK_OVR_1024; 
	Timer_voidInitTimer1(&PasswordLock_Timer); 
	// 4sec = 1024 / 160000 * Ticks (Ticks = 62500) 
	Timer_voidSetCompareValue(TIMER1,62500-1);
	Timer_voidStopTimer(TIMER1);
	Timer_voidSetCompMatchInterrupState(TIMER1  , TIM_OCM_ENABLE) ; 
	Timer_voidSetCompareMatchCallback(TIMER1 , TIMER1_CallbackFunction);
	Timer_voidStartTimer(TIMER1);
	// I2C 
	I2C_MasterInit();
	// LCD Init 
	lcd_vidInit();	
	// Keypad Init
	keypad_vidInit(); 
	// Enable Interrupts 
	sei();
	/**************************************** Check Operation Times ******************/ 
	//APP_FactoryReset();
	while(Global_ErrorHandling != E_OK )
	{
		Global_ErrorHandling = APP_HandleFirstTime();
	}
	APP_voidDisplayMainScreen(Global_u8SystemIsLocked,0);	
	/**************************************** Test Mode *****************************/
	#if TEST_MODE == 1 
	LCD_voidTest();
	#if INTERNAL_EEPROM_TST == 1
	InternalEEPROM_Test();
	#endif
	#if EXTERNAL_EEPROM_TST == 1
	ExternalEEPROM_Test();
	#endif
	#endif 
}

void PasswordLock_voidStart(void)
{
	u8 LOC_u8PressedKey = 0xFF;
	u8 LOC_u8PasswordBuffer[NUM_PASS_DIGITS] = {0}; 
	u8 LOC_u8Result = 0 ;
	/**************** Keypad Test ***********************/ 
	#if TEST_MODE == 1 
	Keypad_voidTest();
	#endif 
	/**************** Application ************************/
	if(Global_u8SystemIsLocked != Loc_u8SystemPrevState)
	{
		// Password Buffer is Ready 
		APP_voidDisplayMainScreen(Global_u8SystemIsLocked,0);	
		Loc_u8SystemPrevState = Global_u8SystemIsLocked ;	
	}
	// Check Pressed Key 
	LOC_u8PressedKey = keypad_u8GetKey(); 
	if(LOC_u8PressedKey == '1')
	{
		if(Global_u8SystemIsLocked == 1)
		{
			// Ready to Unlock
			APP_voidGetPassword(LOC_u8PasswordBuffer); 
			LOC_u8Result = APP_u8PasswordAuthentication(LOC_u8PasswordBuffer); 
			if(LOC_u8Result == 1)
			{
				Global_u8SystemIsLocked = 0 ;
				Timer_voidStartTimer(TIMER1);
			}
			else
			{
				Global_u8SystemIsLocked = 1 ;
				lcd_vidClrDislay(); 
				lcd_vidDisplyStr((u8*)"Wrong Password"); 
				_delay_ms(1000);
				APP_voidDisplayMainScreen(Global_u8SystemIsLocked,0);	
			}
		}
		else
		{
			// Ready to Locked
			Global_u8SystemIsLocked = 1 ; 
		}
		
	}
	else if ( LOC_u8PressedKey == '2' )
	{
		APP_voidGetPassword(LOC_u8PasswordBuffer); 
		LOC_u8Result = APP_u8PasswordAuthentication(LOC_u8PasswordBuffer); 
		if(LOC_u8Result == 1)
		{
			APP_u8SetPassword();
		}
		else
		{
			lcd_vidClrDislay(); 
			lcd_vidDisplyStr((u8*)"Wrong Password"); 
			_delay_ms(1000);
		}
		APP_voidDisplayMainScreen(Global_u8SystemIsLocked,0);	
	}
	else if (LOC_u8PressedKey == UP_BTN)
	{
		APP_voidDisplayMainScreen(Global_u8SystemIsLocked,0);	
	}
	else if(LOC_u8PressedKey == DOWN_BTN)
	{
		APP_voidDisplayMainScreen(Global_u8SystemIsLocked,1);
	}
	else if (LOC_u8PressedKey == '3')
	{
		APP_voidGetPassword(LOC_u8PasswordBuffer); 
		LOC_u8Result = APP_u8PasswordAuthentication(LOC_u8PasswordBuffer); 
		if(LOC_u8Result == 1)
		{
			APP_FactoryReset(); 
		}
		else
		{
			lcd_vidClrDislay(); 
			lcd_vidDisplyStr((u8*)"Wrong Password"); 
			_delay_ms(1000);
			APP_voidDisplayMainScreen(Global_u8SystemIsLocked,0);	

		}


	}
	else if(LOC_u8PressedKey != 0xFF)
	{
		lcd_vidClrDislay(); 
		lcd_vidDisplyStr((u8*)"Wrong Choice"); 
		_delay_ms(700);
		APP_voidDisplayMainScreen(Global_u8SystemIsLocked,0);	
	}
	else
	{
		// Not Supported 
	}
}









/************************************* Tests ********************************/

#if TEST_MODE == 1 
void LCD_voidTest(void)
{
	lcd_vidClrDislay(); 
	lcd_vidGotoRowColumn(0,2);
    // Display Custom Character 
	lcd_vidDisplyChar(0x02); 
    // Display String
	lcd_vidDisplyStr((u8*)"Welcome to NTI"); 
    // Display Custom Character 
	lcd_vidDisplyChar(0x02); 
    // Change Cursor Position
	lcd_vidGotoRowColumn(1,6);
    // Display String
	lcd_vidDisplyStr((u8*)"Abnaby ");
    // Display Custom Character 
	lcd_vidDisplyChar(0x01); 
    // Change Cursor Position
	lcd_vidGotoRowColumn(2,5);
    // Display Number
	lcd_vidDisplayNumbers(1017743725);
	_delay_ms(1000)	;
}
void Keypad_voidTest()
{
	u8 key = keypad_u8GetKey(); 
	if(key != 0xFF)
	{
		lcd_vidClrDislay(); 
		lcd_vidDisplyChar(key); 
	}	
}

void InternalEEPROM_Test()
{
	lcd_vidInit();
	lcd_vidClrDislay(); 
//	u8 named[9] = "xMohamed\0" ; 
//  u8 rxName[9] ; 
//  EEPROM_writeBlock(0x00AB , named, 9 );
//  EEPROM_readBlock(0x00AB,rxName,9);
	EEPROM_write(0x00AA , 'K');
	u8 data = EEPROM_read(0x00AA);
//  lcd_vidDisplyStr(rxName);
    lcd_vidDisplyChar(data);
}
void ExternalEEPROM_Test()
{
	lcd_vidInit();

	lcd_vidClrDislay(); 
	lcd_vidDisplyStr((u8*)"External EEPROM->");
	
	eep_writebyte(0x00AA , 'M');
	u8 data = eep_readByte(0x00AA);
	lcd_vidDisplyChar(data);
}
#endif