/*
 * Timers.c
 *
 * Created: 11/16/2023 11:15:51 AM
 *  Author: Ahmed Wael
 */

#include "std_types.h"
#include "bit_math.h"
#include "Timers_prv.h"
#include "Timers.h"



void Timers_voidInit(Timerx_t* Add_TimerS)
{
	switch(Add_TimerS->Timer_Name)
	{
		case TIMER_2:
		WRITE_BIT(TIMER_2_REGS->Timerx_CR1,4,Add_TimerS->Timer_Direction); //DIR
		WRITE_BIT(TIMER_2_REGS->Timerx_CR1,3,Add_TimerS->Timer_OnePulseMode); //OPM
		//WRITE_BIT(TIMER_2_REGS->Timerx_CR1,0,Add_TimerS->Timer_CounterEnable); //CEN
		break;
		
		case TIMER_3:
		WRITE_BIT(TIMER_3_REGS->Timerx_CR1,4,Add_TimerS->Timer_Direction); //DIR
		WRITE_BIT(TIMER_3_REGS->Timerx_CR1,3,Add_TimerS->Timer_OnePulseMode); //OPM
		//WRITE_BIT(TIMER_3_REGS->Timerx_CR1,0,Add_TimerS->Timer_CounterEnable); //CEN
		break;
		
		case TIMER_4:
		WRITE_BIT(TIMER_4_REGS->Timerx_CR1,4,Add_TimerS->Timer_Direction); //DIR
		WRITE_BIT(TIMER_4_REGS->Timerx_CR1,3,Add_TimerS->Timer_OnePulseMode); //OPM
		//WRITE_BIT(TIMER_4_REGS->Timerx_CR1,0,Add_TimerS->Timer_CounterEnable); //CEN
		break;
	}
	
}

void Timers_voidStartCounter(Timerx_t* Add_TimerS)
{
	switch(Add_TimerS->Timer_Name)
	{
		case TIMER_2:
		SET_BIT(TIMER_2_REGS->Timerx_CR1,0);
		break;
		
		case TIMER_3:
		SET_BIT(TIMER_3_REGS->Timerx_CR1,0);
		break;
		
		case TIMER_4:
		SET_BIT(TIMER_4_REGS->Timerx_CR1,0);
		break;
	}
}

void Timers_voidStopCounter(Timerx_t* Add_TimerS)
{
	switch(Add_TimerS->Timer_Name)
	{
		case TIMER_2:
		CLR_BIT(TIMER_2_REGS->Timerx_CR1,0);
		TIMER_2_REGS->Timerx_ARR = 0;
		break;
		
		case TIMER_3:
		CLR_BIT(TIMER_3_REGS->Timerx_CR1,0);
		TIMER_3_REGS->Timerx_ARR = 0;
		break;
		
		case TIMER_4:
		CLR_BIT(TIMER_4_REGS->Timerx_CR1,0);
		TIMER_4_REGS->Timerx_ARR = 0;
		break;
	}
}

u32 Timers_u32GetCount(Timerx_t* Add_TimerS)
{
	u32 Local_u32ReturnC = 0;
	switch(Add_TimerS->Timer_Name)
	{
		case TIMER_2:
		Local_u32ReturnC = TIMER_2_REGS->Timerx_CNT;
		break;
		
		case TIMER_3:
		Local_u32ReturnC = TIMER_3_REGS->Timerx_CNT;
		break;
		
		case TIMER_4:
		Local_u32ReturnC = TIMER_4_REGS->Timerx_CNT;
		break;
	}
	return Local_u32ReturnC;
}

void Timers_voidSetPrescaler(Timerx_t* Add_TimerS, u16 Copy_u16Prescaler)
{
	switch(Add_TimerS->Timer_Name)
	{
		case TIMER_2:
		TIMER_2_REGS->Timerx_PSC = Copy_u16Prescaler;
		break;
		
		case TIMER_3:
		TIMER_3_REGS->Timerx_PSC = Copy_u16Prescaler;
		break;
		
		case TIMER_4:
		TIMER_4_REGS->Timerx_PSC = Copy_u16Prescaler;
		break;
	}
}


void Timers_voidSetAutoReloadVal(Timerx_t* Add_TimerS, u32 Copy_u16AutoReloadVal)
{
	switch(Add_TimerS->Timer_Name)
	{
		case TIMER_2:
		TIMER_2_REGS->Timerx_ARR = Copy_u16AutoReloadVal;
		break;
		
		case TIMER_3:
			if(Copy_u16AutoReloadVal > 0xFFFF)
			{
				//return error
			}
			else
			{
				 TIMER_3_REGS->Timerx_ARR = Copy_u16AutoReloadVal;
			}
		break;
		
		case TIMER_4:
			if(Copy_u16AutoReloadVal > 0xFFFF)
			{
				//return error
			}
			else
			{
				TIMER_4_REGS->Timerx_ARR = Copy_u16AutoReloadVal;
			}
		break;
	}
}
