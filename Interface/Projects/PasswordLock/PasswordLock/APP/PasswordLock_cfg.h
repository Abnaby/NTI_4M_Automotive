/*
 * PasswordLock_cfg.h
 *
 * Created: 8/7/2023 8:11:38 PM
 *  Author: Abnaby
 */ 


#ifndef PASSWORDLOCK_CFG_H_
#define PASSWORDLOCK_CFG_H_

/******************************************* MACROS **********************************/
#define APP_USES_EXTERNAL_EEPROM		0
#define APP_USES_INTERNAL_EEPROM		2

/******************************************* USER CFG *********************************/

/**
 * @brief This Macro is used to define default eeprom used for the passwordLock Program
 * 
 */
#define USAGE_EEPROM						APP_USES_EXTERNAL_EEPROM

#define NUM_PASS_DIGITS						6

#define EEPROM_FAILURE_HANDLE_EN			1	

#define LOCK_BTN							'1'	

#define DOWN_BTN							'D'

#define UP_BTN								'A'

#endif /* PASSWORDLOCK_CFG_H_ */