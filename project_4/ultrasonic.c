/*-----------------------------------------------------------*
 * [FILE NAME]: ultrasonic.c
 *
 * [AUTHOR]: YOUSEF KHALED
 *
 * [DATE CREATED]: 17/10/2021
 *
 * [DESCRIPTION]: Source file for ULTRASONIC driver
 *-----------------------------------------------------------*/


#include "ultrasonic.h"
#include "icu.h"
#include "gpio.h"
#include <util/delay.h>

/* it is the variable that stores the value of 'ICR1' register and *
 * it's 16 bits 'ICR1' is a 16-bit register.                       */
uint16 g_timerValue = 0;

/* this variable will help us what edge we will seek next. */
uint8 counter = 0;

/******************************************************************
 *                     functions                                  *
 ******************************************************************/

/*
 * input: non
 * return: non
 * Description:
 * it is a function that initializes the ULTRASONIC sensor.
 */
void ULTRASONIC_init (void)
{
	/* initializing the ICU */
	ICU_init();
	/* setting the "ULTRASONIC_edgeProcessing" as the function to be called when the interrupt occurs */
	ICU_setCallBack(ULTRASONIC_edgeProcessing);
	/* setting the PB5 as output pin as it is the pin that will send the trigger signal to the ULTRASONIC*/
	GPIO_setupPinDirection(PORTB_ID, PIN5_ID, PIN_OUTPUT);
}


/*
 * input: non
 * return: non
 * Description:
 * it is the function that is responsible for sending a trigger signal to the ULTRASONIC sensor
 * this signal description is a high pulse remain for 10 us.
 */
void ULTRASONIC_trigger(void)
{
	GPIO_writePin(PORTB_ID, PIN5_ID, LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(PORTB_ID, PIN5_ID, LOGIC_LOW);
}


/*
 * input: non
 * return: measured distance
 * Description:
 * it is responsible for firstly sending a trigger signal by calling "ULTRASONIC_trigger"
 * then returning the measured distance
 */
uint16 ULTRASONIC_readDistance(void)
{
	/* is a variable that saves the distance value */
	uint8 distance = 0;

	/* calling the "ULTRASONIC_trigger" function that is responsible for sending trigger signal */
	ULTRASONIC_trigger();

	/* calculating the distance through this equation */
	distance = g_timerValue / 57.5 ;
	return distance ;
}


/*
 * input: non
 * return: non
 * Description:
 * it is called by the ISR so, it won't work except with the interrupt when the expected edge comes
 * and it is used to return the number stored in the ICR1 'interrupt capture register'.
 */
void ULTRASONIC_edgeProcessing (void)
{
	counter++;
	if (counter == 1)
	{
		/* here it detects a rising edge so we should clear the 'ICR1' register to begin counting from 0 */
		ICU_clearTimerValue();

		/* Detect falling edge */
		ICU_setEdgeDetectionType(FALLING);
	}
	if (counter == 2)
	{
		/* storing the value of the 'ICR1' register in the g_timerValue variable where it's global *
		 * as it will be used again in another function which is called "ULTRASONIC_readDistance". */
		g_timerValue = ICU_getInputCaptureValue();

		/* Detect falling edge */
		ICU_setEdgeDetectionType(RISING);

		/* if counter in the reaches 2 then clearing it as if it not it will increase   *
		 * without any restriction so if the real distance changed during the run time  *
		 * the value displayed on the screen WILL NOT change.                           */
		counter = 0;

		/* this for still awhile before sending another trigger */
		_delay_ms(30);
	}
}





