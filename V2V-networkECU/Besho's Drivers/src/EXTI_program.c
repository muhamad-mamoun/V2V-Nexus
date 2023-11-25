/*
 * EXTI_program.c
 *
 *  Created on: january 18, 2023
 *      Author: beshoy
 */
#include "../Inc/LIB/STD_TYPES.h"
#include "../Inc/LIB/BIT_MATH.h"

#include "../Inc/MCAL/EXTI/EXTI_interface.h"
#include "../Inc/MCAL/EXTI/EXTI_private.h"
#include "../Inc/MCAL/EXTI/EXTI_config.h"




#ifndef	NULL
#define NULL	(void *)0
#endif


static void	(* EXTI0_CallBack)	(void) = NULL;
static void (* EXTI1_CallBack)   (void)=NULL;
static void (* EXTI3_CallBack)   (void)=NULL;



void	MEXTI_voidInit			(void)
{/*		Initialize Interrupts (Edges)	and pin Number(A0 or B0 or C0)	*/}
void	MEXTI_voidEnableExti	(u8	Copy_u8ExtiNum)
{
	SET_BIT( EXTI -> IMR , Copy_u8ExtiNum);
}
void	MEXTI_voidSetExtiEdge	(u8 Copy_u8ExtiNum , u8 Copy_u8Edge)
{
	switch(Copy_u8Edge)
	{
		case	MEXTI_RISING_EDGE	:	CLR_BIT( EXTI -> FSTR , Copy_u8ExtiNum);
										SET_BIT( EXTI -> RSTR , Copy_u8ExtiNum);	break;

		case	MEXTI_FALLING_EDGE	:	CLR_BIT( EXTI -> RSTR , Copy_u8ExtiNum);
										SET_BIT( EXTI -> FSTR , Copy_u8ExtiNum);	break;

		case	MEXTI_IOC_EDGE		:	SET_BIT( EXTI -> RSTR , Copy_u8ExtiNum);
										SET_BIT( EXTI -> FSTR , Copy_u8ExtiNum);	break;
	}
	SET_BIT( EXTI -> SWIER , Copy_u8ExtiNum);
}
void 	MEXTI_voidSetEXTILinePin	(u8 Copy_u8ExtiNum, u8 Copy_u8Port)
{
	if(Copy_u8ExtiNum < 4)
	{
		AFIO_EXTICR1 &= ~((0b1111) << (Copy_u8ExtiNum*4));
		AFIO_EXTICR1 |= ((Copy_u8Port) << (Copy_u8ExtiNum*4));
	}
	else if(Copy_u8ExtiNum < 8)
	{
		Copy_u8ExtiNum = Copy_u8ExtiNum - 4;
		AFIO_EXTICR2 &= ~((0b1111) << (Copy_u8ExtiNum*4));
		AFIO_EXTICR2 |= ((Copy_u8Port) << (Copy_u8ExtiNum*4));
	}
	else if(Copy_u8ExtiNum < 12)
	{
		Copy_u8ExtiNum = Copy_u8ExtiNum - 8;
		AFIO_EXTICR3 &= ~((0b1111) << (Copy_u8ExtiNum*4));
		AFIO_EXTICR3 |= ((Copy_u8Port) << (Copy_u8ExtiNum*4));
	}
	else if(Copy_u8ExtiNum < 16)
	{
		Copy_u8ExtiNum = Copy_u8ExtiNum - 12;
		AFIO_EXTICR4 &= ~((0b1111) << (Copy_u8ExtiNum*4));
		AFIO_EXTICR4 |= ((Copy_u8Port) << (Copy_u8ExtiNum*4));
	}
	else {/*error*/}
}
void	MEXTI_voidDisableExti	(u8	Copy_u8ExtiNum)
{
	CLR_BIT( EXTI -> IMR , Copy_u8ExtiNum);
}
void	MEXTI_voidEnableSWI		(u8	Copy_u8ExtiNum)
{
	SET_BIT( EXTI -> SWIER , Copy_u8ExtiNum);
}
void	MEXTI_voidSetCallBack	(void (*ptr) (void))
{
	if(ptr != NULL)
	{
		EXTI3_CallBack  = 	ptr ;
	}
}

void	EXTI0_IRQHandler(void)
{
	EXTI3_CallBack();		
	SET_BIT( EXTI -> PR , 0);

}
void	EXTI1_IRQHandler(void)
{
	EXTI3_CallBack();		
	SET_BIT( EXTI -> PR , 1);

}
void	EXTI3_IRQHandler(void)
{
	EXTI3_CallBack();		
	SET_BIT( EXTI -> PR , 3);
}
void	EXTI4_IRQHandler(void)
{
	EXTI3_CallBack();		
	SET_BIT( EXTI -> PR , 4);
}
void EXTI15_10_IRQHandler(void)
{
	EXTI3_CallBack();		
	SET_BIT( EXTI -> PR , 15);
}

