#include "avr/io.h"
#include "util/delay.h"
#include "dio.h"
#include "avr/interrupt.h"
#include "TIMERS_Interface.h"


volatile u8 Program = 0; 
volatile u8 Direction = 0; 
static Timer1Config_t ChangeProgram_Timer;

// Callback 
static void TIMER1_CallbackFunction(void)
{
	// 1-Min Code
	static u32 numOfFourSeconds=0 ; 
	if(numOfFourSeconds == 15 )
	{
		numOfFourSeconds = 0 ; 
		// Change Direction 
		Direction = ~Direction ; 
		// Change Program 
		Program++ ; 
	}
	numOfFourSeconds++;	
	if(Program == 4)
		Program = 0 ; 
}
// Timer Inits 
void Timer_init(void)
{
	// TIMER 
	ChangeProgram_Timer.operationModeTIM1			 = TIM_CTC_Mode     ; 
	ChangeProgram_Timer.clockSourceAndPrescalerTimer1 = TIMER1_CLK_OVR_1024; 
	Timer_voidInitTimer1(&ChangeProgram_Timer); 
	// 4sec = 1024 / 160000 * Ticks (Ticks = 62500) 
	Timer_voidSetCompareValue(TIMER1,62500-1);
	Timer_voidStopTimer(TIMER1);
	Timer_voidSetCompMatchInterrupState(TIMER1  , TIM_OCM_ENABLE) ; 
	Timer_voidSetCompareMatchCallback(TIMER1 , TIMER1_CallbackFunction);
	Timer_voidStartTimer(TIMER1);
}
void PWM_init(void)
{
	/************* PWM **********************/
	TCNT0 = 0;		
	// Fast PWM Mode 
	TCCR0 = (1<<WGM00)|(1<<WGM01);
	// OC0 Mode : non-inverting mode
	TCCR0 |= (1<<COM01) ; 
	// 
	TCCR0 |= (1<<CS00)|(1<<CS01);	
	/*set OC0 pin as output*/
	DDRB= 0xFF; // direction of port B as output
	DDRB|=(1<<PB3); 
}
void analogWrite(u8 copy_u8AnalogValue)
{
	// Inits 
	OCR0 = copy_u8AnalogValue; 
}

int main(void)
{
	Timer_init();
	PWM_init();
	sei();
	while (1) 
    {
		if(Program == 0 )
		{
			// CW 
			PORTB |= (1<<1); 
			PORTB &= ~(1<<2); 
			analogWrite(100);
		}
		else if(Program == 1)
		{
			// CCW
			PORTB &= ~(1<<1); 
			PORTB |=  (1<<2); 
			analogWrite(100);
		}
		else if(Program == 2)
		{
			// SPEED UP
			PORTB |= (1<<1); 
			PORTB &= ~(1<<2);  
			analogWrite(255);
		}
	}
}
