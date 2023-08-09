/*
 * PasswordLock.c
 *
 * Created: 8/6/2023 10:35:53 PM
 * Author : Abnaby
 */ 

#include "avr/io.h"
/***************** LIB Include *********************/ 
#include "util/delay.h"
#include "avr/interrupt.h"
#include "PasswordLock.h"
#include <avr/io.h>

int main(void)
{
	PasswordLock_voidInit(); 
    while (1) 
    {
		PasswordLock_voidStart();
    }
}
