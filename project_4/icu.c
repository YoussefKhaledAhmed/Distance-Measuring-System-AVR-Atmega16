/*-------------------------------------------------------
 * [FILE NAME]: icu.c
 *
 * [AUTHOR]: YOUSEF KHALED
 *
 * [DATE CREATED]: 10/10/2021
 *
 * [DESCRIPTION]: Source file for AVR ICU driver
 -------------------------------------------------------*/

#include "icu.h"
#include "gpio.h"
#include "common_macros.h"
#include <avr/io.h>
#include <avr/interrupt.h>


static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*
 * Description:
 * the following ISR is for calling the function that is passed to the
 * void ICU_setCallBack (void(*a_ptr)(void))
 * where a_ptr is saved in the global pointer g_callBackPtr
 */
ISR(TIMER1_CAPT_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
	}
}

/*
 * Description : Function to initialize the ICU driver
 * 	1. Set the required clock.
 * 	2. Set the required edge detection.
 * 	3. Enable the Input Capture Interrupt.
 * 	4. Initialize Timer1 Registers
 */
void ICU_init(void)
{
	/* Setting the ICP1 as input pin */
	GPIO_setupPinDirection(PORTD_ID , PIN6_ID , PIN_INPUT);

	/* Setting FOC1B(PIN2) , FOC1A(PIN3) for setting the normal mode */
	TCCR1A = 0x0C;

	/* TCCR1B = (0) (INITIAL_EDGE_SELECT) (000) (CS12) (CS11) (CS10) */
	TCCR1B = FCPU_8 | (RISING << 6);

	/* Initialization of timer1 register(TCNT1) */
	TCNT1 = 0 ;

	/* and the input capture register1(ICR1) */
	ICR1 = 0 ;

	/* This for enabling the input capture interrupt enable */
	TIMSK |= (1<<TICIE1);
}


void ICU_setEdgeDetectionType (uint8 a_edgeType)
{
	TCCR1B = (TCCR1B & 0XBF) | (a_edgeType << 6); /* Setting the required edge */
}


void ICU_setCallBack (void(*a_ptr)(void))
{
	g_callBackPtr = a_ptr ; /* Saving the passed pointer to the global g_callBackPtr */
}


uint16 ICU_getInputCaptureValue(void)
{
	return ICR1;/* to return the immediate value of the input capture register */
}


void ICU_clearTimerValue(void)
{
	TCNT1 = 0;/* clearing the timer1 register */
}

/*
 * this function is the opposite to the init function by clearing all the registers to
 * disable Timer1 and consequently disabling the ICU
 */
void ICU_deInit(void)
{
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	ICR1 = 0;
	TIMSK &= ~(1 << TICIE1);
}











