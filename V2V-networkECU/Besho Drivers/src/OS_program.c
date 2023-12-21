/********************************************
 * OS_program.c 
 * Created on   : Sep 7, 2020
 * Author       : Asmaa Hashim
 *******************************************/



#include"../Inc/LIB/STD_TYPES.h"
#include"../Inc/LIB/BIT_MATH.h"

#include"../Inc/MCAL/SYSTIC/STK_interface.h"


#include"../Inc/OS/OS_interface.h"
#include"../Inc/OS/OS_private.h"
#include"../Inc/OS/OS_config.h"

#define NULL ((void*)0)
	
/* Array of struct  */
static  Task OS_Tasks[NUM_OF_TASKS] = {} ;
volatile u32 TickCounts =0;

void SOS_voidCreatTask(u8 Copy_u8ID , u32 Copy_u16Period , void (*ptr)(void) )
{	
OS_Tasks[Copy_u8ID].period = Copy_u16Period;
OS_Tasks[Copy_u8ID].Fptr = ptr;
//OS_Tasks[Copy_u8ID].firstDelay = Copy_u8firstDelay;
OS_Tasks[Copy_u8ID].state = READY_;
}
void Scheduler(void)
{
	
	u8 i =0;
	for( i=0 ; i < NUM_OF_TASKS ; i++)
	{
		if(TickCounts % OS_Tasks[i].period ==0  )
		{
			OS_Tasks[i].Fptr();

		}
	}
	TickCounts++;
}

void Scheduler_firstDelay(void)
{	
	u8 i =0;
	for( i=0 ; i < NUM_OF_TASKS ; i++)
	{
		if(OS_Tasks[i].Fptr != NULL  && OS_Tasks[i].state == READY_ )
		{
			if(OS_Tasks[i].firstDelay == 0)
			{
				OS_Tasks[i].firstDelay = OS_Tasks[i].period - 1 ;
			    OS_Tasks[i].Fptr();
			}
			else			
			{
				OS_Tasks[i].firstDelay--;	
			}
		}
	}
}

void SOS_voidStart(void)
{
	MSTK_voidInit();
	/*TICK => 1msec*/
	MSTK_voidSetIntervalPeriodic(1000 ,Scheduler );
}

void SOS_voidSetState(u8 Copy_u8ID , Task_state state )
{
     OS_Tasks[Copy_u8ID].state = state;
}

void SOS_voidDeleteTask(u8 Copy_u8ID  )
{
     OS_Tasks[Copy_u8ID].Fptr = NULL;
}


