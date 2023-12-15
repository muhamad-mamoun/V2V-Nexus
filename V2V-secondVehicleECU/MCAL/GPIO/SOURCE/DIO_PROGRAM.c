/*
 * DIO_program.c
 *
 *  Created on: October 10, 2022
 *      Author: beshoy
 */

#include "std_types.h"
#include "common_macros.h"
#include "DIO_config.h"
#include "DIO_interface.h"
#include "DIO_private.h"


void MGPIO_voidSetPinDirection(u8 copy_u8PORT , u8 copy_u8PIN  , u8 copy_u8Mode)
{

	if(copy_u8PORT<3 && copy_u8PIN<16)
		{
			switch(copy_u8PORT)
			{
				case	GPIOA_driver	:
				/*	Check if Low				*/
				if(copy_u8PIN <8)
				{
					//	#define		CLR(REG,BIT)		REG &=~(1<<BIT)
					/*	CLR The 4 bits Of Direction					*/
					GPIOA_CRL	&=~((0b1111)			<< (copy_u8PIN * 4));
					GPIOA_CRL	|=((copy_u8Mode)	<< (copy_u8PIN * 4));

				}else if(copy_u8PIN <16)
				{
					copy_u8PIN -= 8;
					/*	CLR The 4 bits Of Direction					*/
					GPIOA_CRH	&=~((0b1111)			<< (copy_u8PIN * 4));
					GPIOA_CRH	|=((copy_u8Mode)	<< (copy_u8PIN * 4));
				}else{	/*	Return Error */	}		break;

				case	GPIOB_driver	:
				/*	Check if Low				*/
				if(copy_u8PIN <8)
				{
					//	#define		CLR(REG,BIT)		REG &=~(1<<BIT)
					/*	CLR The 4 bits Of Direction					*/
					GPIOB_CRL	&=~((0b1111)			<< (copy_u8PIN * 4));
					GPIOB_CRL	|=((copy_u8Mode)	<< (copy_u8PIN * 4));

				}else if(copy_u8PIN <16)
				{
					copy_u8PIN -= 8;
					/*	CLR The 4 bits Of Direction					*/
					GPIOB_CRH	&=~((0b1111)			<< (copy_u8PIN * 4));
					GPIOB_CRH	|=((copy_u8Mode)	<< (copy_u8PIN * 4));
				}else{	/*	Return Error */	}		break;

				case	GPIOC_driver	:
				/*	Check if Low				*/
				if(copy_u8PIN <8)
				{
					//	#define		CLR(REG,BIT)		REG &=~(1<<BIT)
					/*	CLR The 4 bits Of Direction					*/
					GPIOC_CRL	&=~((0b1111)			<< (copy_u8PIN * 4));
					GPIOC_CRL	|=((copy_u8Mode)	<< (copy_u8PIN * 4));

				}else if(copy_u8PIN <16)
				{
					copy_u8PIN -= 8;
					/*	CLR The 4 bits Of Direction					*/
					GPIOC_CRH	&=~((0b1111)			<< (copy_u8PIN * 4));
					GPIOC_CRH	|=((copy_u8Mode)	<< (copy_u8PIN * 4));
				}else{	/*	Return Error */	}		break;
			}

		}else{	/*	Return Error		*/	}

	}

void MGPIO_voidSetPinValue(u8 copy_u8PORT , u8 copy_u8PIN , u8 copy_u8Value)
{
	switch(copy_u8PORT)
		{
		case GPIOA_driver :
			        if(copy_u8Value == GPIO_HIGH)
			        {
			        	SET_BIT(   GPIOA_ODR   ,  copy_u8PIN );

			        }
			        else if(copy_u8Value == GPIO_LOW)
			        {
			        	CLR_BIT(  GPIOA_ODR  , copy_u8PIN );

			        }

			        break ;
		case GPIOB_driver :
		     if(copy_u8Value == GPIO_HIGH)
					        {
					        	SET_BIT(  GPIOB_ODR, copy_u8PIN );

					        }
					        else if(copy_u8Value == GPIO_LOW)
					        {
					        	CLR_BIT(  GPIOB_ODR, copy_u8PIN );

					        }

					        break ;


		case GPIOC_driver :
		     if(copy_u8Value == GPIO_HIGH)
					        {
					        	SET_BIT(  GPIOC_ODR, copy_u8PIN );

					        }
					        else if(copy_u8Value == GPIO_LOW)
					        {
					        	CLR_BIT(  GPIOC_ODR, copy_u8PIN );

					        }

					        break ;




		}
	}
u8 MGPIO_u8GetPinValue(u8 copy_u8PORT , u8 copy_u8PIN )
{
	u8 LOC_u8Result =0;

	switch(copy_u8PORT)
	{
	   case GPIOA_driver :  LOC_u8Result = GET_BIT(GPIOA_IDR ,copy_u8PIN );
		             break ;

	   case GPIOB_driver :  LOC_u8Result = GET_BIT(GPIOB_IDR ,copy_u8PIN );
	                 break ;

	   case GPIOC_driver :  LOC_u8Result = GET_BIT(GPIOC_IDR ,copy_u8PIN );
	                 break ;
	}

	return LOC_u8Result ;

}

void MGPIO_voidSetPortDirection  (u8 copy_u8PORT , u32 copy_u32Mode)
{
	switch(copy_u8PORT)
	{
		case GPIOA_driver : GPIOA_CRL = copy_u32Mode;
					 GPIOA_CRH = copy_u32Mode;
					 break;
		case GPIOB_driver : GPIOB_CRL = copy_u32Mode;
					 GPIOB_CRH = copy_u32Mode;
					 break;
		case GPIOC_driver : GPIOC_CRL = copy_u32Mode;
					 GPIOC_CRH = copy_u32Mode;
					 break;

	}
}

void MGPIO_voidSetPortValue      (u8 copy_u8PORT , u16 copy_u16Value)
{
	switch(copy_u8PORT)
	{
		case GPIOA_driver : GPIOA_ODR &= 0x00000000;
					 GPIOA_ODR |= (u32)copy_u16Value;
					 break;
		case GPIOB_driver : GPIOB_ODR &= 0x00000000;
					 GPIOB_ODR |= (u32)copy_u16Value;
					 break;
		case GPIOC_driver : GPIOC_ODR &= 0x00000000;
					 GPIOC_ODR |= (u32)copy_u16Value;
					 break;
	}
}


void MGPIO_voidTglPin      (u8 copy_u8PORT , u8 copy_u8PIN)
{

	switch(copy_u8PORT)
	{
	   case GPIOA_driver :  TGL_BIT(GPIOA_ODR ,copy_u8PIN );
		             break ;

	   case GPIOB_driver :  TGL_BIT(GPIOB_ODR ,copy_u8PIN );
	                 break ;

	   case GPIOC_driver :  TGL_BIT(GPIOC_ODR ,copy_u8PIN );
	                 break ;
	}

}