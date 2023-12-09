/*
 * PWM_interface.h
 *
 *  Created on: April 7, 2023
 *      Author: beshoy
 */

#ifndef PWM_INTERFACE_H_
#define PWM_INTERFACE_H_
typedef enum
{
	TIMER2=0,
	TIMER3,
	TIMER4,
	TIMER5
}TIM_T;

typedef enum
{
	CH1,
	CH2,
	CH3,
	CH4
}CH_T;

void MPWM_voidInit(TIM_T Timer, CH_T CHANNEL, u16 AutoReload_Val);
void MPWM_SETValuesOfPWM(TIM_T Timer, CH_T CHANNEL, u16  MCopy_u16CompareVal);
#endif
