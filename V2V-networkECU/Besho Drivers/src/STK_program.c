/*
 * STK_program.c
 *
 *  Created on: january 25, 2023
 *      Author: beshoy
 */

#include 	"../Inc/LIB/STD_TYPES.h"
#include 	"../Inc/LIB/BIT_MATH.h"

#include	"../Inc/MCAL/SYSTIC/STK_interface.h"
#include	"../Inc/MCAL/SYSTIC/STK_private.h"
#include	"../Inc/MCAL/SYSTIC/STK_config.h"

#ifndef			NULL
#define			NULL			((void *)0)
#endif

static	void	(*SysTick_CallBack) (void) = NULL ;
static	u8		MSTK_u8ModeOfInterval ;
void	MSTK_voidInit				(void)
{
	#if		MSTK_CLK_SRC	==	MSTK_SRC_AHB_8
		MSTK -> CTRL	=	0x00000000;
	#elif	MSTK_CLK_SRC	==	MSTK_SRC_AHB
		MSTK -> CTRL	=	0x00000004;
	#else
		#error	"Wrong Choice of Clock Source Pre-Scaller"
	#endif
}
void	MSTK_voidSetBusyWait		(u32 Copy_u32Ticks)	//_delay_us
{
	/*	load Ticks to load register		*/
	MSTK -> LOAD	=	Copy_u32Ticks;
	
	/*	Start Timer 					*/
	SET_BIT(MSTK -> CTRL , 0 );
	
	/*	Wait till Flage is raised 		*/
	while((GET_BIT(MSTK -> CTRL , 16)) == 0)
	{
		asm("NOP");
	}
	
	/*	Stop Timer 						*/
	CLR_BIT(MSTK -> CTRL , 0 );
	MSTK -> LOAD	=	0;
	MSTK -> VAL		=	0;
}
void	MSTK_voidSetIntervalSingle	(u32 Copy_u32Ticks , void (*Copy_PF)(void))
{
	/*	Disable	Timer 					*/
	CLR_BIT(MSTK -> CTRL , 0 );
	MSTK -> VAL		=	0;
	
	/*	load Ticks to load register		*/
	MSTK -> LOAD	=	Copy_u32Ticks;
	
	/*	Start Timer 					*/
	SET_BIT(MSTK -> CTRL , 0 );
	
	/*	Save Call Back 					*/
	SysTick_CallBack = Copy_PF;
	
	/*	Set mode to single 				*/
	MSTK_u8ModeOfInterval = MSTK_SINGLE_INTERVAL;
	
	/*	Enable STK Interrupt 			*/
	SET_BIT(MSTK -> CTRL , 1 );

}
void	MSTK_voidSetIntervalPeriodic(u32 Copy_u32Ticks , void (*Copy_PF)(void))
{
	/*	load Ticks to load register		*/
	MSTK -> LOAD	=	Copy_u32Ticks;
	
	/*	Start Timer 					*/
	SET_BIT(MSTK -> CTRL , 0 );
	
	/*	Save Call Back 					*/
	SysTick_CallBack = Copy_PF;
	
	/*	Set mode to Periodic			*/
	MSTK_u8ModeOfInterval = MSTK_PERIOD_INTERVAL;
	
	/*	Enable STK Interrupt 			*/
	SET_BIT(MSTK -> CTRL , 1 );
}
void	MSTK_voidStopInterval		(void)
{
		/*	Disable STK Interrupt 		*/
		CLR_BIT(MSTK -> CTRL , 1 );
	
		/*	Stop timer					*/
		CLR_BIT(MSTK -> CTRL , 0 );
		MSTK -> LOAD	=	0;
		MSTK -> VAL		=	0;	
}
u32		MSTK_u32GetElapsedTime		(void)
{
	u32 Local_u32ElapsedTime;
	
	Local_u32ElapsedTime = ((MSTK -> LOAD) - (MSTK -> VAL));
	
	return	Local_u32ElapsedTime;
}
u32		MSTK_u32GetRemainingTime	(void)
{
	u32 Local_u32RemainingTime;
	
	Local_u32RemainingTime = (MSTK -> VAL);
	
	return	Local_u32RemainingTime;
}

void SysTick_Handler(void)
{
	u8 Local_u8Temp;
	
	if(	MSTK_u8ModeOfInterval == MSTK_SINGLE_INTERVAL)
	{
		/*	Disable STK Interrupt 		*/
		CLR_BIT(MSTK -> CTRL , 1 );
	
		/*	Stop timer					*/
		CLR_BIT(MSTK -> CTRL , 0 );
		MSTK -> LOAD	=	0;
		MSTK -> VAL		=	0;	
	}
	/*	CallBack notification 			*/
	SysTick_CallBack();
	
	/*	Clear Interrupt Flag By reading	*/
	Local_u8Temp = GET_BIT(MSTK -> CTRL , 16);
}


