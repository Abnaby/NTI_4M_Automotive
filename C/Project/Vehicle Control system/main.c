/*
 ============================================================================
 Name        : main.c
 Author      : Mohamed Abd EL-Naby
 Version     : V1.0
 Copyright   :
 Description : The main program of Vehicle Control system
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include "VCS_interface.h"

int main(void) {

    // Current Screen Should be Displayed
    Screen_t DisplayedScreen = SCR_MAIN_SCREEN ;

    // User Inputs Variables
	u8 userInputs ;

	// Initialize System
	VCS_InitSystem(&DisplayedScreen);

	while(1)
	{
        // Display Screen
		VCS_DisplayScreen(DisplayedScreen);
		//SCANF_BUFFER();
		// Get Selected
		VCS_GetSelected(userInputs);
		// Determine What Happens Based on Displayed screen and the user inputs
		VCS_SystemSelection(DisplayedScreen,userInputs) ;
		//SCANF_BUFFER();
	}
	return 0 ;
}
