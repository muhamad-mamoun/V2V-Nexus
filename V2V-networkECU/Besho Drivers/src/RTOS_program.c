/*
 * RTOS_program.c
 *
 *  Created on: Aug 22, 2022
 *      Author: Loka
 */
#include "../Inc/LIB/STD_TYPES.h"
#include "../Inc/LIB/BIT_MATH.h"


#include "../Inc/RTOS/RTOS_interface.h"
#include "../Inc/RTOS/RTOS_config.h"
#include "../Inc/RTOS/RTOS_private.h"
#include "../Inc/MCAL/SYSTIC/STK_interface.h"
#include "../Inc/MCAL/DIO/DIO_interface.h"


 static TASK_TCB TASKS[NUM_OF_TASKS];
 static u16 Ticks =0;
void RTOS_voidInit(void)
{  /* SYSTICK INIT 1U sec   */
		MSTK_voidInit();
		/* SYSTICK TO BE 1 MSEC WITH INTERRUPT*/
	MSTK_voidSetIntervalPeriodic(1000,RTOS_voidScheduler);

}
void RTOS_voidCreateTask(u8 A_u8Priority , u16 A_u16Periodicity , void(*A_PF)(void),u16 A_u16First_Delay)
{
	TASKS[A_u8Priority].u16_periodicty = A_u16Periodicity;
	TASKS[A_u8Priority].PF =A_PF ;
	TASKS[A_u8Priority].First_Delay=A_u16First_Delay;
}
/*void RTOS_voidScheduler(void)
{
	u8 i ;
	for(i=0 ; i< NUM_OF_TASKS ; i++)
	{
		if((Ticks % TASKS[i].u16_periodicty) ==0)
		{
			TASKS[i].PF();
		}

	}
	Ticks++;

}*/

void RTOS_voidScheduler(void)
{
	u8 i ;
	for(i=0 ; i< NUM_OF_TASKS ; i++)
	{
		if((TASKS[i].First_Delay) ==0)
		{

			TASKS[i].PF();
			TASKS[i].First_Delay=TASKS[i].u16_periodicty -1;

		}
		else
		{
			TASKS[i].First_Delay--;
		}

	}
	Ticks++;

}
/*void RTOS_voidScheduler(void)
{
	u8 i ;
	for(i=0 ; i< NUM_OF_TASKS ; i++)
	{
		if(Ticks % (TASKS[i].u16_periodicty) ==0)
		{
			TASKS[i].PF();
		}

	}
	Ticks++;

}*/
