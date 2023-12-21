/*
 * T2DELAY_program.c
 *
 *  Created on: February 2, 2023
 *      Author: beshoy
 */
#include "../Inc/LIB/STD_TYPES.h"
#include "../Inc/LIB/BIT_MATH.h"

#include "../Inc/MCAL/T2DELAY/T2DELAY_interface.h"
#include "../Inc/MCAL/T2DELAY/T2DELAY_private.h"
#include "../Inc/MCAL/T2DELAY/T2DELAY_config.h"
#ifndef	NULL
#define NULL	(void *)0
#endif
void (*GLOBALPTR_FUNC)(void)=NULL;
void MTIMER2_voidInitTimer2Delay(void)
{
	TIMER2->CR1=0;
	TIMER2->CR2=0;
	TIMER2->PSC=7;

}
void MTIMER2_voidSetinterruptTimer(void)
{
	SET_BIT(TIMER2->CR1,ARPE);
	SET_BIT(TIMER2->CR1,DIR);
	SET_BIT(TIMER2->DIER,UIE);
	TIMER2->PSC=7999;
	TIMER2->ARR = 2999;
	SET_BIT(TIMER2->CR1, CEN);
}

void MTIMER2_voidStartDealyInMicroSeconds(u32 Copy_u32Delay)
{
	u32 Local_u32NumOfUnderFlow = Copy_u32Delay / 65536;
	u32 Local_u32Rest = Copy_u32Delay % 65536;
	u32 Local_u32Counter = 0;
	if(Local_u32Counter != Local_u32NumOfUnderFlow)
	{
		CLR_BIT(TIMER2->CR1, CEN);
		TIMER2->ARR = 65535;
		TIMER2->CNT = 0;

		SET_BIT(TIMER2->CR1, CEN);

	}
	while(Local_u32Counter != Local_u32NumOfUnderFlow)
	{
		if(GET_BIT(TIMER2->SR, 0) == 1)
		{
			CLR_BIT(TIMER2->SR , 0);
			CLR_BIT(TIMER2->CR1, CEN);
			TIMER2->ARR = 65535;
			TIMER2->CNT = 0;
			SET_BIT(TIMER2->CR1, CEN);
			Local_u32Counter++;

		}			
	}
	CLR_BIT(TIMER2->CR1, CEN);
	TIMER2->ARR = Local_u32Rest;
	TIMER2->CNT = 0;

	SET_BIT(TIMER2->CR1, CEN);
	while(GET_BIT(TIMER2->SR, 0) == 0)
	{

	}
	CLR_BIT(TIMER2->SR , 0);
}
void MTIMER2_voidSetCallBack(void (*ptr)(void))
{
	if(ptr != NULL)
	{
		GLOBALPTR_FUNC=ptr;
	}
}
void TIM3_IRQHandler(void)
{
	GLOBALPTR_FUNC();
	CLR_BIT(TIMER2->SR,0);
}
