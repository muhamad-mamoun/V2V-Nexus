/*
 * Timers.h
 *
 * Created: 11/16/2023 
 *  Author: Ahmed Wael
 */



#ifndef _TIMERS_H_
#define _TIMERS_H_

#include "std_types.h"
/****** Timer_Name ******/
#define TIMER_2	0
#define TIMER_3	1
#define TIMER_4 2

/******** Timer_Direction ********/
#define TIMER_DIR_UP   0
#define TIMER_DIR_DOWN 1
/******** Timer_OnePulseMode *******/
#define TIMER_OPM_OFF 0
#define TIMER_OPM_ON  1



typedef struct
{
	u8 Timer_Name;
	u8 Timer_Direction;
	u8 Timer_OnePulseMode;
	//u8 Timer_CounterEnable;
	//Update Interrupt Flag
}Timerx_t;


void Timers_voidInit(Timerx_t* Add_TimerS);
void Timers_voidSetPrescaler(Timerx_t* Add_TimerS, u16 Copy_u16Prescaler);
void Timers_voidSetAutoReloadVal(Timerx_t* Add_TimerS, u32 Copy_u16AutoReloadVal);

void Timers_voidStartCounter(Timerx_t* Add_TimerS);
void Timers_voidStopCounter(Timerx_t* Add_TimerS);
u32 Timers_u32GetCount(Timerx_t* Add_TimerS);






#endif


