/**
* @file VCS_program.c
* @author Mohamed Abd El-Naby (mahameda.naby@gmail.com)
* @brief The main file of Vehicle Control system.
* @version 1.0
* @date 2022-7-17
*
*/


/******************************************************************************
* Includes
*******************************************************************************/

#include "VCS_interface.h"
#include <stdio.h>
#include <stdlib.h>

/******************************************************************************
* Preprocessor Constants
 *******************************************************************************/


#define FIRST_CHOICE 'a'
#define SECND_CHOICE 'b'
#define THIRD_CHOICE 'c'
#define FORTH_CHOICE 'd'

#define G_TRAFFIC_LIGHT     'G'
#define O_TRAFFIC_LIGHT     'O'
#define R_TRAFFIC_LIGHT     'R'

#define PRINT_BOOL(VAL)  (VAL)?"ON" : "OFF"


#define DEBUG_EN    0
/******************************************************************************
* Typedefs
*******************************************************************************/



/******************************************************************************
* Global Variables
*******************************************************************************/

static VehicleState  Global_VehicleState;
static Screen_t *Global_PTR_DisplayedScreen ;


/******************************************************************************
* Static Functions
*******************************************************************************/


/******************************************************************************
* Function Definition
*******************************************************************************/

Error_Handling_t VCS_InitSystem(Screen_t *ptrToDisplayedScrren)
{
    Error_Handling_t LOC_errorHandling = ERR_NO_ERROR ;

    Global_VehicleState.AC_State = OFF ;
    Global_VehicleState.Engine_State = OFF ;

    #if WITH_ENGINE_TEMP_CONTROLLER == ENABLE
    Global_VehicleState.engineTempController = OFF ;
    Global_VehicleState.engineTemperature = 30 ;
    #endif // WITH_ENGINE_TEMP_CONTROLLER

    Global_VehicleState.Engine_State = OFF ;
    Global_VehicleState.Room_Temp   =   30 ;
    Global_VehicleState.Vehicle_Speed = 0 ;
    Global_PTR_DisplayedScreen = ptrToDisplayedScrren ;
    *Global_PTR_DisplayedScreen = SCR_MAIN_SCREEN  ;

    return LOC_errorHandling ;

}

Error_Handling_t VCS_DisplayScreen(Screen_t copy_ScreenNumber)
{
	Error_Handling_t LOC_errorHandling = ERR_NO_ERROR ;
	switch(copy_ScreenNumber)
	{
	case SCR_MAIN_SCREEN :
		printf("a. Turn on the vehicle engine \nb. Turn off the vehicle engine \nc. Quit the system \n");
		LOC_errorHandling = ERR_NO_ERROR ;
		break ;
    case SCR_STATE_SCREEN :
           #if WITH_ENGINE_TEMP_CONTROLLER == ENABLE
            printf("\n\nEngine is : %s\nAC is : %s\nVehicle Speed : %d Km/Hr\nRoom Temperature: %0.1f c\nEngine Temp Controller is %s \nEngine Temperature is : %d C\n\n" ,
          PRINT_BOOL(Global_VehicleState.Engine_State), PRINT_BOOL(Global_VehicleState.AC_State) , Global_VehicleState.Vehicle_Speed,
           Global_VehicleState.Room_Temp ,PRINT_BOOL(Global_VehicleState.engineTempController) , Global_VehicleState.engineTemperature  );
           #elif WITH_ENGINE_TEMP_CONTROLLER == DISABLE
            printf("\n\nEngine is : %s\nAC is : %s\nVehicle Speed : %d Km/Hr\nRoom Temperature: %0.1f c\n\n" ,
          PRINT_BOOL(Global_VehicleState.Engine_State), PRINT_BOOL(Global_VehicleState.AC_State) , Global_VehicleState.Vehicle_Speed,
           Global_VehicleState.Room_Temp  );

           #endif // WITH_ENGINE_TEMP_CONTROLLER
		LOC_errorHandling = ERR_NO_ERROR ;
        break;
    case SCR_SENSOR_SET_MENU :
        printf("\ta. Turn off the engin\n\tb. Set the traffic light color.\n\tc. Set the room temperature (Temperature Sensor)\n\t");
       #if WITH_ENGINE_TEMP_CONTROLLER == ENABLE
       printf("d. Set the engine temperature (Engine Temperature Sensor)\n");
       #else
       printf("\n");
       #endif // WITH_ENGINE_TEMP_CONTROLLER
        break;
    case SCR_TRAFFIC_LIGHT :
        printf("\t\ta.Enter Traffic State : One of  \"G\" \"O\" \"R\"\n");
        break ;
    case SCR_TEMPERATURE :
            printf("\t\tEnter Room Temperature \n");
        break ;
    case SCR_ENGINE :
            printf("\t\tEnter Engine Temperature \n");
        break ;
	default :
		LOC_errorHandling = ERR_WRONG_CHOICE ;
		break ;
	}
	return LOC_errorHandling ;
}

Error_Handling_t VCS_SystemSelection(Screen_t copy_ScreenNumber , u8 copy_u8Selection)
{
	Error_Handling_t LOC_errorHandling = ERR_NO_ERROR ;
	u8  LOC_u8Data = 0 ;
	switch(copy_ScreenNumber)
	{
	case SCR_MAIN_SCREEN :
	{
		 if(copy_u8Selection == FIRST_CHOICE)
		 {
		     // Turn ON Engine
			 LOC_errorHandling = ERR_NO_ERROR ;
			 Global_VehicleState.Engine_State = ON;
			 //VCS_DisplayScreen(SCR_SENSOR_SET_MENU);
             // Set Displayed Screen
			 *Global_PTR_DisplayedScreen = SCR_SENSOR_SET_MENU ;
		 }
		 else if(copy_u8Selection == SECND_CHOICE)
		 {
		     // Turn Off Engine
			 LOC_errorHandling = ERR_NO_ERROR ;
			 // Set Displayed Screen
			 *Global_PTR_DisplayedScreen = SCR_MAIN_SCREEN ;
		 }
		 else if(copy_u8Selection == THIRD_CHOICE)
		 {
		     // Exit
			 LOC_errorHandling = ERR_NO_ERROR ;
			 #if DEBUG_EN == 1
			 printf("thirdOne");
			 #endif
			 exit(0);
		 }
		 else
		 {
			 LOC_errorHandling = ERR_WRONG_CHOICE ;
		 }

	}
	break ;
    case SCR_SENSOR_SET_MENU :
    {

		 if(copy_u8Selection == FIRST_CHOICE)
		 {
		     // Turn off the engine
		     Global_VehicleState.Engine_State = OFF;
            // Set Displayed Screen
			 *Global_PTR_DisplayedScreen = SCR_MAIN_SCREEN ;
			 LOC_errorHandling = ERR_NO_ERROR ;
		 }
		 else if(copy_u8Selection == SECND_CHOICE)
		 {
             LOC_errorHandling = ERR_NO_ERROR ;
		     // Set the traffic light color
            VCS_DisplayScreen(SCR_TRAFFIC_LIGHT); //Display Options
            VCS_GetSelected(LOC_u8Data);          // Get Entered Data
            switch(LOC_u8Data)                    // Set Vehicle Speed
            {
                case G_TRAFFIC_LIGHT : Global_VehicleState.Vehicle_Speed = 100 ; break ;
                case O_TRAFFIC_LIGHT :
                    Global_VehicleState.Vehicle_Speed = 30 ;

                    // Turn On AC
                    Global_VehicleState.AC_State = ON ;
                    Global_VehicleState.Room_Temp = (Global_VehicleState.Room_Temp) * (5.0/4.0) + 1 ;

                    #if WITH_ENGINE_TEMP_CONTROLLER == ENABLE
                    // Turn On Engine
                    Global_VehicleState.engineTempController = ON ;
                    Global_VehicleState.engineTemperature = (Global_VehicleState.engineTemperature) * (5.0/4.0) + 1 ;
                    #endif // WITH_ENGINE_TEMP_CONTROLLER
                    break ;
                case R_TRAFFIC_LIGHT : Global_VehicleState.Vehicle_Speed = 0 ; break ;
                default : LOC_errorHandling = ERR_WRONG_CHOICE ; break ;
            }
		 }
		 else if(copy_u8Selection == THIRD_CHOICE)
		 {
			 LOC_errorHandling = ERR_NO_ERROR ;
			 //Set the room temperature
			 VCS_DisplayScreen(SCR_TEMPERATURE); //Display Options
             VCS_GetSelected(LOC_u8Data);          // Get Entered Data
             // Check Inputs Range
             if(LOC_u8Data < 10 || LOC_u8Data > 30)
             {
                 Global_VehicleState.AC_State = ON ;
                 Global_VehicleState.Room_Temp = 20 ;
             }
             else
             {
                 Global_VehicleState.AC_State = OFF ;
             }
		 }
         #if WITH_ENGINE_TEMP_CONTROLLER == ENABLE
		 else if (copy_u8Selection == FORTH_CHOICE)
         {
             LOC_errorHandling = ERR_NO_ERROR ;
            // Set the engine temperature (Engine Temperature Sensor)
			 VCS_DisplayScreen(SCR_ENGINE); //Display Options
             VCS_GetSelected(LOC_u8Data);          // Get Entered Data
             // Check Inputs Range
             if(LOC_u8Data < 100  || LOC_u8Data > 150 )
             {
                 Global_VehicleState.engineTempController = ON ;
                 Global_VehicleState.engineTemperature = 125 ;
             }
             else
             {
                 Global_VehicleState.engineTempController = OFF ;
             }

         }
         #endif // WITH_ENGINE_TEMP_CONTROLLER
		 else
		 {
			 LOC_errorHandling = ERR_WRONG_CHOICE ;
		 }

        VCS_DisplayScreen(SCR_STATE_SCREEN);
    }
    break ;
	default :
		LOC_errorHandling = ERR_WRONG_CHOICE ;
		break ;
	}
	return LOC_errorHandling ;
}

