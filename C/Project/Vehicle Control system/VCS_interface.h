/**
* @file VCS_interface.h
* @author Mohamed Abd El-Naby (mahameda.naby@gmail.com)
* @brief The header file of Vehicle Control system.
* @version 1.0
* @date 2022-7-17
*
*/

#ifndef HEADER_VCS_INTERFACE_C_
#define HEADER_VCS_INTERFACE_C_

/******************************************************************************
* Includes
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>



/******************************************************************************
* Preprocessor Constants
 *******************************************************************************/
#define SCANF_BUFFER() 	fflush(stdout); fflush(stdout)
#define u8 char

#define ENABLE  1
#define DISABLE 0
/******************************************************************************
* User Preprocessor Options
 *******************************************************************************/
#define WITH_ENGINE_TEMP_CONTROLLER ENABLE

/******************************************************************************
* Typedefs
*******************************************************************************/
typedef enum
{
	SCR_MAIN_SCREEN	= 0 ,
	SCR_STATE_SCREEN,
	SCR_SENSOR_SET_MENU,
	SCR_TRAFFIC_LIGHT,
	SCR_TEMPERATURE,
	SCR_ENGINE
}Screen_t;

typedef enum
{
	ERR_NO_ERROR = 0 ,
	ERR_WRONG_CHOICE
}Error_Handling_t;

typedef enum
{
    OFF = 0 ,
    ON

}SystemStates_t;
typedef struct
{
    int                 Vehicle_Speed ;  // in KM/H
    SystemStates_t      AC_State ;      // Choose One of @SystemStates_t
    SystemStates_t      Engine_State ;   //Choose One of @SystemStates_t
    float                 Room_Temp   ;     // in c
    #if WITH_ENGINE_TEMP_CONTROLLER == ENABLE
    int                 engineTempController ;
    int                 engineTemperature ;
    #endif // WITH_ENGINE_TEMP_CONTROLLER
}VehicleState;
/******************************************************************************
* Global Variables
*******************************************************************************/




/******************************************************************************
* Function / Macro Function Prototype
*******************************************************************************/



/**
 * @brief This Function is used to Initialize the system
 *
 */
Error_Handling_t VCS_InitSystem(Screen_t *ptrToDisplayedScrren);


/**
 * @brief This Function is used to Display on of screens in @ref  Screen_t
 *
 * @param copy_ScreenNumber           Screen number
 * @return Error_Handling_t			one of @ref Error_Handling_t
 */
Error_Handling_t VCS_DisplayScreen(Screen_t copy_ScreenNumber);


/**
 * @brief This Function is used to scan the inputs
 *
 * @param VAR_NAME           The Variable Name

 */
#define VCS_GetSelected(VAR_NAME)	printf("Select One Option ");scanf(" %c",&VAR_NAME);


/**
 * @brief This Function is used to Display on of screens in @ref  Screen_t
 *
 * @param copy_ScreenNumber           Screen number
 * @param copy_u8Selection			Selection Number
 * @return Error_Handling_t			one of @ref Error_Handling_t
 */
Error_Handling_t VCS_SystemSelection(Screen_t copy_ScreenNumber , u8 copy_u8Selection);




#endif /* HEADER_VCS_INTERFACE_C_ */
