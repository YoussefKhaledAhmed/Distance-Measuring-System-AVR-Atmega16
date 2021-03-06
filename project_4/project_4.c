/*-------------------------------------------------------
 * [FILE NAME]: project_4.c
 *
 * [AUTHOR]: YOUSEF KHALED
 *
 * [DATE CREATED]: 17/10/2021
 *
 * [DESCRIPTION]: Source file for project_4
 -------------------------------------------------------*/

#include "ultrasonic.h"
#include "lcd.h"
#include <avr/io.h>

/*
 * Description:
 * 1. initializes the ULTRASONIC function
 * 2. initializing LCD
 * 3. enables the GENERAL INTERRUPT (I-bit)
 * 4. displays ("distance=     cm") once as it will still during the whole RUN TIME
 * 5. it takes the reading of the ULTRASONIC SENSOR by calling ULTRASONIC_readDistance() function
 */

int main (void)
{
	/* variable where the distance value is stored */
	uint8 distance ;

	/* initializing the ULTRASONIC sensor */
	ULTRASONIC_init();

	/* initializing the LCD */
	LCD_init();

	/* enabling the general interrupt (I-bit) */
	SREG |= (1<<7);

	/* displaying it once as it will still during the whole RUN TIME */
	LCD_displayString("distance= ");

	while (1)
	{
		distance = ULTRASONIC_readDistance();/* reading the distance value */
		LCD_moveCursor(0, 10);
		LCD_intgerToString(distance);/* displaying the distance value */
		LCD_displayString(" cm  ");
	}
}
