/*-------------------------------------------------------
 * [FILE NAME]: ICU.h
 *
 * [AUTHOR]: YOUSEF KHALED
 *
 * [DATE CREATED]: 10/10/2021
 *
 * [DESCRIPTION]: header file for AVR ICU driver
 -------------------------------------------------------*/

#ifndef ICU_H_
#define ICU_H_

#include "std_types.h"

typedef enum
{
	FALLING , RISING
}ICU_EdgeType;

typedef enum
{
	NO_CLOCK , FCPU , FCPU_8 , FCPU_64 , FCPU_256 , FCPU_1024 , EXT_RISING_T1 , EXT_FALLING_T1
}ICU_clockType;

/*---------------------------------*
 *       functions prototype       *
 *---------------------------------*/
void ICU_init(void);
void ICU_setEdgeDetectionType (uint8 a_edgeDirection);
void ICU_setCallBack (void(*a_ptr)(void));
uint16 ICU_getInputCaptureValue(void);
void ICU_clearTimerValue(void);
void ICU_deInit(void);



/*---------------------------------*
 *        Definitions              *
 *---------------------------------*/

/*
 * clock sources:
 * 0: NO clock
 * 1: CLK/1
 * 2: CLK/8
 * 3: CLK/64
 * 4: CLK/256
 * 5: CLK/1024
 * 6: External clock source on T1 pin. Clock on falling edge.
 * 7: External clock source on T1 pin. clock on rising edge.
 */
#define COLCK_SOURCE 2

/*
 * 0: Falling edge
 * 1: Rising edge
 */
#define INITIAL_EDGE_TYPE 1



#endif /* ICU_H_ */
