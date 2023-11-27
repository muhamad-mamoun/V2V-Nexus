/*
 * DIO_program.c
 *
 *  Created on: October 10, 2022
 *      Author: beshoy
 */

#include "std_types.h"
#include "common_macros.h"

#include "../inc/DIO_config.h"
#include "../inc/DIO_interface.h"
#include "../inc/DIO_private.h"


void MGPIO_voidSetPinDirection(u8 copy_u8PORT , u8 copy_u8PIN  , u8 copy_u8Mode)
{

	if(copy_u8PORT<3 && copy_u8PIN<16)
		{
			switch(copy_u8PORT)
			{
				case	GPIOA	:
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

				case	GPIOB	:
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

				case	GPIOC	:
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
		case GPIOA :
			        if(copy_u8Value == GPIO_HIGH)
			        {
			        	SET_BIT(   GPIOA_ODR   ,  copy_u8PIN );

			        }
			        else if(copy_u8Value == GPIO_LOW)
			        {
			        	CLR_BIT(  GPIOA_ODR  , copy_u8PIN );

			        }

			        break ;
		case GPIOB :
		     if(copy_u8Value == GPIO_HIGH)
					        {
					        	SET_BIT(  GPIOB_ODR, copy_u8PIN );

					        }
					        else if(copy_u8Value == GPIO_LOW)
					        {
					        	CLR_BIT(  GPIOB_ODR, copy_u8PIN );

					        }

					        break ;


		case GPIOC :
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
	   case GPIOA :  LOC_u8Result = GET_BIT(GPIOA_IDR ,copy_u8PIN );
		             break ;

	   case GPIOB :  LOC_u8Result = GET_BIT(GPIOB_IDR ,copy_u8PIN );
	                 break ;

	   case GPIOC :  LOC_u8Result = GET_BIT(GPIOC_IDR ,copy_u8PIN );
	                 break ;
	}

	return LOC_u8Result ;

}
void delay(u32 Copy_DelayTime)
{
	for (u32 i =0 ;  i < Copy_DelayTime ; i++)
	{
		//asm ("NOP");
	}
}
void SEVEN_SEGMENT ( u8 copy_u8PORT, u8 Copy_u8Number  )
{
	switch (copy_u8PORT )
	{
	case GPIOA:
		if (Copy_u8Number == 0)
		{
			MGPIO_voidSetPinValue(GPIOA , PIN0 , GPIO_HIGH);
			MGPIO_voidSetPinValue(GPIOA , PIN1 , GPIO_HIGH);
			MGPIO_voidSetPinValue(GPIOA , PIN2 , GPIO_HIGH);
			MGPIO_voidSetPinValue(GPIOA , PIN3 , GPIO_HIGH);
			MGPIO_voidSetPinValue(GPIOA , PIN4 , GPIO_HIGH);
			MGPIO_voidSetPinValue(GPIOA , PIN5 , GPIO_HIGH);
			MGPIO_voidSetPinValue(GPIOA , PIN6 , GPIO_LOW);
		}
		else if (Copy_u8Number == 1)
		{
			MGPIO_voidSetPinValue(GPIOA , PIN0 , GPIO_LOW);
			MGPIO_voidSetPinValue(GPIOA , PIN1 , GPIO_HIGH);
			MGPIO_voidSetPinValue(GPIOA , PIN2 , GPIO_HIGH);
			MGPIO_voidSetPinValue(GPIOA , PIN3 , GPIO_LOW);
			MGPIO_voidSetPinValue(GPIOA , PIN4 , GPIO_LOW);
			MGPIO_voidSetPinValue(GPIOA , PIN5 , GPIO_LOW);
			MGPIO_voidSetPinValue(GPIOA , PIN6 , GPIO_LOW);
		}
		else if (Copy_u8Number == 2)
		{
			MGPIO_voidSetPinValue(GPIOA , PIN0 , GPIO_HIGH);
	     	MGPIO_voidSetPinValue(GPIOA , PIN1 , GPIO_HIGH);
			MGPIO_voidSetPinValue(GPIOA , PIN2 , GPIO_LOW);
			MGPIO_voidSetPinValue(GPIOA , PIN3 , GPIO_HIGH);
			MGPIO_voidSetPinValue(GPIOA , PIN4 , GPIO_HIGH);
			MGPIO_voidSetPinValue(GPIOA , PIN5 , GPIO_LOW);
			MGPIO_voidSetPinValue(GPIOA , PIN6 , GPIO_HIGH);
		}
		else if (Copy_u8Number == 3)
	   	{
			MGPIO_voidSetPinValue(GPIOA , PIN0 , GPIO_HIGH);
			MGPIO_voidSetPinValue(GPIOA , PIN1 , GPIO_HIGH);
			MGPIO_voidSetPinValue(GPIOA , PIN2 , GPIO_HIGH);
			MGPIO_voidSetPinValue(GPIOA , PIN3 , GPIO_HIGH);
			MGPIO_voidSetPinValue(GPIOA , PIN4 , GPIO_LOW);
			MGPIO_voidSetPinValue(GPIOA , PIN5 , GPIO_LOW);
			MGPIO_voidSetPinValue(GPIOA , PIN6 , GPIO_HIGH);
		}
		else if (Copy_u8Number == 4)
		{
			MGPIO_voidSetPinValue(GPIOA , PIN0 , GPIO_LOW);
			MGPIO_voidSetPinValue(GPIOA , PIN1 , GPIO_HIGH);
			MGPIO_voidSetPinValue(GPIOA , PIN2 , GPIO_HIGH);
			MGPIO_voidSetPinValue(GPIOA , PIN3 , GPIO_LOW);
			MGPIO_voidSetPinValue(GPIOA , PIN4 , GPIO_LOW);
			MGPIO_voidSetPinValue(GPIOA , PIN5 , GPIO_HIGH);
			MGPIO_voidSetPinValue(GPIOA , PIN6 , GPIO_HIGH);
		}
		else if (Copy_u8Number == 5)
		{
		    MGPIO_voidSetPinValue(GPIOA , PIN0 , GPIO_HIGH);
		    MGPIO_voidSetPinValue(GPIOA , PIN1 , GPIO_LOW);
			MGPIO_voidSetPinValue(GPIOA , PIN2 , GPIO_HIGH);
			MGPIO_voidSetPinValue(GPIOA , PIN3 , GPIO_HIGH);
			MGPIO_voidSetPinValue(GPIOA , PIN4 , GPIO_LOW);
			MGPIO_voidSetPinValue(GPIOA , PIN5 , GPIO_HIGH);
			MGPIO_voidSetPinValue(GPIOA , PIN6 , GPIO_HIGH);
		}
		else if (Copy_u8Number == 6)
		{
			MGPIO_voidSetPinValue(GPIOA , PIN0 , GPIO_HIGH);
	        MGPIO_voidSetPinValue(GPIOA , PIN1 , GPIO_LOW);
			MGPIO_voidSetPinValue(GPIOA , PIN2 , GPIO_HIGH);
			MGPIO_voidSetPinValue(GPIOA , PIN3 , GPIO_HIGH);
			MGPIO_voidSetPinValue(GPIOA , PIN4 , GPIO_HIGH);
			MGPIO_voidSetPinValue(GPIOA , PIN5 , GPIO_HIGH);
			MGPIO_voidSetPinValue(GPIOA , PIN6 , GPIO_HIGH);
		}
		else if (Copy_u8Number == 7)
		{
			MGPIO_voidSetPinValue(GPIOA , PIN0 , GPIO_HIGH);
			MGPIO_voidSetPinValue(GPIOA , PIN1 , GPIO_HIGH);
			MGPIO_voidSetPinValue(GPIOA , PIN2 , GPIO_HIGH);
			MGPIO_voidSetPinValue(GPIOA , PIN3 , GPIO_LOW);
			MGPIO_voidSetPinValue(GPIOA , PIN4 , GPIO_LOW);
			MGPIO_voidSetPinValue(GPIOA , PIN5 , GPIO_LOW);
			MGPIO_voidSetPinValue(GPIOA , PIN6 , GPIO_LOW);
		}
		else if (Copy_u8Number == 8)
		{
			MGPIO_voidSetPinValue(GPIOA , PIN0 , GPIO_HIGH);
			MGPIO_voidSetPinValue(GPIOA , PIN1 , GPIO_HIGH);
			MGPIO_voidSetPinValue(GPIOA , PIN2 , GPIO_HIGH);
			MGPIO_voidSetPinValue(GPIOA , PIN3 , GPIO_HIGH);
			MGPIO_voidSetPinValue(GPIOA , PIN4 , GPIO_HIGH);
			MGPIO_voidSetPinValue(GPIOA , PIN5 , GPIO_HIGH);
			MGPIO_voidSetPinValue(GPIOA , PIN6 , GPIO_HIGH);
		}
		else if (Copy_u8Number == 9)
		{
			MGPIO_voidSetPinValue(GPIOA , PIN0 , GPIO_HIGH);

			MGPIO_voidSetPinValue(GPIOA , PIN1 , GPIO_HIGH);
			MGPIO_voidSetPinValue(GPIOA , PIN2 , GPIO_HIGH);
			MGPIO_voidSetPinValue(GPIOA , PIN3 , GPIO_HIGH);
			MGPIO_voidSetPinValue(GPIOA , PIN4 , GPIO_LOW);
			MGPIO_voidSetPinValue(GPIOA , PIN5 , GPIO_HIGH);
			MGPIO_voidSetPinValue(GPIOA , PIN6 , GPIO_HIGH);
		}
		break;
	case GPIOB:
		if (Copy_u8Number == 0)
				{
					MGPIO_voidSetPinValue(GPIOB , PIN0 , GPIO_HIGH);
					MGPIO_voidSetPinValue(GPIOB , PIN1 , GPIO_HIGH);
					MGPIO_voidSetPinValue(GPIOB , PIN2 , GPIO_HIGH);
					MGPIO_voidSetPinValue(GPIOB , PIN3 , GPIO_HIGH);
					MGPIO_voidSetPinValue(GPIOB , PIN4 , GPIO_HIGH);
					MGPIO_voidSetPinValue(GPIOB , PIN5 , GPIO_HIGH);
					MGPIO_voidSetPinValue(GPIOB , PIN6 , GPIO_LOW);
				}
				else if (Copy_u8Number == 1)
				{
					MGPIO_voidSetPinValue(GPIOB , PIN0 , GPIO_LOW);
					MGPIO_voidSetPinValue(GPIOB , PIN1 , GPIO_HIGH);
					MGPIO_voidSetPinValue(GPIOB , PIN2 , GPIO_HIGH);
					MGPIO_voidSetPinValue(GPIOB , PIN3 , GPIO_LOW);
					MGPIO_voidSetPinValue(GPIOB , PIN4 , GPIO_LOW);
					MGPIO_voidSetPinValue(GPIOB , PIN5 , GPIO_LOW);
					MGPIO_voidSetPinValue(GPIOB , PIN6 , GPIO_LOW);
				}
				else if (Copy_u8Number == 2)
				{
					MGPIO_voidSetPinValue(GPIOB , PIN0 , GPIO_HIGH);
			     	MGPIO_voidSetPinValue(GPIOB , PIN1 , GPIO_HIGH);
					MGPIO_voidSetPinValue(GPIOB , PIN2 , GPIO_LOW);
					MGPIO_voidSetPinValue(GPIOB , PIN3 , GPIO_HIGH);
					MGPIO_voidSetPinValue(GPIOB , PIN4 , GPIO_HIGH);
					MGPIO_voidSetPinValue(GPIOB , PIN5 , GPIO_LOW);
					MGPIO_voidSetPinValue(GPIOB , PIN6 , GPIO_HIGH);
				}
				else if (Copy_u8Number == 3)
			   	{
					MGPIO_voidSetPinValue(GPIOB , PIN0 , GPIO_HIGH);
					MGPIO_voidSetPinValue(GPIOB , PIN1 , GPIO_HIGH);
					MGPIO_voidSetPinValue(GPIOB , PIN2 , GPIO_HIGH);
					MGPIO_voidSetPinValue(GPIOB , PIN3 , GPIO_HIGH);
					MGPIO_voidSetPinValue(GPIOB , PIN4 , GPIO_LOW);
					MGPIO_voidSetPinValue(GPIOB , PIN5 , GPIO_LOW);
					MGPIO_voidSetPinValue(GPIOB , PIN6 , GPIO_HIGH);
				}
				else if (Copy_u8Number == 4)
				{
					MGPIO_voidSetPinValue(GPIOB , PIN0 , GPIO_LOW);
					MGPIO_voidSetPinValue(GPIOB , PIN1 , GPIO_HIGH);
					MGPIO_voidSetPinValue(GPIOB , PIN2 , GPIO_HIGH);
					MGPIO_voidSetPinValue(GPIOB , PIN3 , GPIO_LOW);
					MGPIO_voidSetPinValue(GPIOB , PIN4 , GPIO_LOW);
					MGPIO_voidSetPinValue(GPIOB , PIN5 , GPIO_HIGH);
					MGPIO_voidSetPinValue(GPIOB , PIN6 , GPIO_HIGH);
				}
				else if (Copy_u8Number == 5)
				{
				    MGPIO_voidSetPinValue(GPIOB , PIN0 , GPIO_HIGH);
				    MGPIO_voidSetPinValue(GPIOB , PIN1 , GPIO_LOW);
					MGPIO_voidSetPinValue(GPIOB , PIN2 , GPIO_HIGH);
					MGPIO_voidSetPinValue(GPIOB , PIN3 , GPIO_HIGH);
					MGPIO_voidSetPinValue(GPIOB , PIN4 , GPIO_LOW);
					MGPIO_voidSetPinValue(GPIOB , PIN5 , GPIO_HIGH);
					MGPIO_voidSetPinValue(GPIOB , PIN6 , GPIO_HIGH);
				}
				else if (Copy_u8Number == 6)
				{
					MGPIO_voidSetPinValue(GPIOB , PIN0 , GPIO_HIGH);
			        MGPIO_voidSetPinValue(GPIOB , PIN1 , GPIO_LOW);
					MGPIO_voidSetPinValue(GPIOB , PIN2 , GPIO_HIGH);
					MGPIO_voidSetPinValue(GPIOB , PIN3 , GPIO_HIGH);
					MGPIO_voidSetPinValue(GPIOB , PIN4 , GPIO_HIGH);
					MGPIO_voidSetPinValue(GPIOB , PIN5 , GPIO_HIGH);
					MGPIO_voidSetPinValue(GPIOB , PIN6 , GPIO_HIGH);
				}
				else if (Copy_u8Number == 7)
				{
					MGPIO_voidSetPinValue(GPIOB , PIN0 , GPIO_HIGH);
					MGPIO_voidSetPinValue(GPIOB , PIN1 , GPIO_HIGH);
					MGPIO_voidSetPinValue(GPIOB , PIN2 , GPIO_HIGH);
					MGPIO_voidSetPinValue(GPIOB , PIN3 , GPIO_LOW);
					MGPIO_voidSetPinValue(GPIOB , PIN4 , GPIO_LOW);
					MGPIO_voidSetPinValue(GPIOB , PIN5 , GPIO_LOW);
					MGPIO_voidSetPinValue(GPIOB , PIN6 , GPIO_LOW);
				}
				else if (Copy_u8Number == 8)
				{
					MGPIO_voidSetPinValue(GPIOB , PIN0 , GPIO_HIGH);
					MGPIO_voidSetPinValue(GPIOB , PIN1 , GPIO_HIGH);
					MGPIO_voidSetPinValue(GPIOB , PIN2 , GPIO_HIGH);
					MGPIO_voidSetPinValue(GPIOB , PIN3 , GPIO_HIGH);
					MGPIO_voidSetPinValue(GPIOB , PIN4 , GPIO_HIGH);
					MGPIO_voidSetPinValue(GPIOB , PIN5 , GPIO_HIGH);
					MGPIO_voidSetPinValue(GPIOB , PIN6 , GPIO_HIGH);
				}
				else if (Copy_u8Number == 9)
				{
					MGPIO_voidSetPinValue(GPIOB , PIN0 , GPIO_HIGH);
					MGPIO_voidSetPinValue(GPIOB , PIN1 , GPIO_HIGH);
					MGPIO_voidSetPinValue(GPIOB , PIN2 , GPIO_HIGH);
					MGPIO_voidSetPinValue(GPIOB , PIN3 , GPIO_HIGH);
					MGPIO_voidSetPinValue(GPIOB , PIN4 , GPIO_LOW);
					MGPIO_voidSetPinValue(GPIOB , PIN5 , GPIO_HIGH);
					MGPIO_voidSetPinValue(GPIOB , PIN6 , GPIO_HIGH);
				}
				break;
	case GPIOC:
				if (Copy_u8Number == 0)
						{
							MGPIO_voidSetPinValue(GPIOC , PIN0 , GPIO_HIGH);
							MGPIO_voidSetPinValue(GPIOC , PIN1 , GPIO_HIGH);
							MGPIO_voidSetPinValue(GPIOC , PIN2 , GPIO_HIGH);
							MGPIO_voidSetPinValue(GPIOC , PIN3 , GPIO_HIGH);
							MGPIO_voidSetPinValue(GPIOC , PIN4 , GPIO_HIGH);
							MGPIO_voidSetPinValue(GPIOC , PIN5 , GPIO_HIGH);
							MGPIO_voidSetPinValue(GPIOC , PIN6 , GPIO_LOW);
						}
						else if (Copy_u8Number == 1)
						{
							MGPIO_voidSetPinValue(GPIOC , PIN0 , GPIO_LOW);
							MGPIO_voidSetPinValue(GPIOC , PIN1 , GPIO_HIGH);
							MGPIO_voidSetPinValue(GPIOC , PIN2 , GPIO_HIGH);
							MGPIO_voidSetPinValue(GPIOC , PIN3 , GPIO_LOW);
							MGPIO_voidSetPinValue(GPIOC , PIN4 , GPIO_LOW);
							MGPIO_voidSetPinValue(GPIOC , PIN5 , GPIO_LOW);
							MGPIO_voidSetPinValue(GPIOC , PIN6 , GPIO_LOW);
						}
						else if (Copy_u8Number == 2)
						{
							MGPIO_voidSetPinValue(GPIOC , PIN0 , GPIO_HIGH);
					     	MGPIO_voidSetPinValue(GPIOC , PIN1 , GPIO_HIGH);
							MGPIO_voidSetPinValue(GPIOC , PIN2 , GPIO_LOW);
							MGPIO_voidSetPinValue(GPIOC , PIN3 , GPIO_HIGH);
							MGPIO_voidSetPinValue(GPIOC , PIN4 , GPIO_HIGH);
							MGPIO_voidSetPinValue(GPIOC , PIN5 , GPIO_LOW);
							MGPIO_voidSetPinValue(GPIOC , PIN6 , GPIO_HIGH);
						}
						else if (Copy_u8Number == 3)
					   	{
							MGPIO_voidSetPinValue(GPIOC , PIN0 , GPIO_HIGH);
							MGPIO_voidSetPinValue(GPIOC , PIN1 , GPIO_HIGH);
							MGPIO_voidSetPinValue(GPIOC , PIN2 , GPIO_HIGH);
							MGPIO_voidSetPinValue(GPIOC , PIN3 , GPIO_HIGH);
							MGPIO_voidSetPinValue(GPIOC , PIN4 , GPIO_LOW);
							MGPIO_voidSetPinValue(GPIOC , PIN5 , GPIO_LOW);
							MGPIO_voidSetPinValue(GPIOC , PIN6 , GPIO_HIGH);
						}
						else if (Copy_u8Number == 4)
						{
							MGPIO_voidSetPinValue(GPIOC , PIN0 , GPIO_LOW);
							MGPIO_voidSetPinValue(GPIOC , PIN1 , GPIO_HIGH);
							MGPIO_voidSetPinValue(GPIOC , PIN2 , GPIO_HIGH);
							MGPIO_voidSetPinValue(GPIOC , PIN3 , GPIO_LOW);
							MGPIO_voidSetPinValue(GPIOC , PIN4 , GPIO_LOW);
							MGPIO_voidSetPinValue(GPIOC , PIN5 , GPIO_HIGH);
							MGPIO_voidSetPinValue(GPIOC , PIN6 , GPIO_HIGH);
						}
						else if (Copy_u8Number == 5)
						{
						    MGPIO_voidSetPinValue(GPIOC , PIN0 , GPIO_HIGH);
						    MGPIO_voidSetPinValue(GPIOC , PIN1 , GPIO_LOW);
							MGPIO_voidSetPinValue(GPIOC , PIN2 , GPIO_HIGH);
							MGPIO_voidSetPinValue(GPIOC , PIN3 , GPIO_HIGH);
							MGPIO_voidSetPinValue(GPIOC , PIN4 , GPIO_LOW);
							MGPIO_voidSetPinValue(GPIOC , PIN5 , GPIO_HIGH);
							MGPIO_voidSetPinValue(GPIOC , PIN6 , GPIO_HIGH);
						}
						else if (Copy_u8Number == 6)
						{
							MGPIO_voidSetPinValue(GPIOC , PIN0 , GPIO_HIGH);
					        MGPIO_voidSetPinValue(GPIOC , PIN1 , GPIO_LOW);
							MGPIO_voidSetPinValue(GPIOC , PIN2 , GPIO_HIGH);
							MGPIO_voidSetPinValue(GPIOC , PIN3 , GPIO_HIGH);
							MGPIO_voidSetPinValue(GPIOC , PIN4 , GPIO_HIGH);
							MGPIO_voidSetPinValue(GPIOC , PIN5 , GPIO_HIGH);
							MGPIO_voidSetPinValue(GPIOC , PIN6 , GPIO_HIGH);
						}
						else if (Copy_u8Number == 7)
						{
							MGPIO_voidSetPinValue(GPIOC , PIN0 , GPIO_HIGH);
							MGPIO_voidSetPinValue(GPIOC , PIN1 , GPIO_HIGH);
							MGPIO_voidSetPinValue(GPIOC , PIN2 , GPIO_HIGH);
							MGPIO_voidSetPinValue(GPIOC , PIN3 , GPIO_LOW);
							MGPIO_voidSetPinValue(GPIOC , PIN4 , GPIO_LOW);
							MGPIO_voidSetPinValue(GPIOC , PIN5 , GPIO_LOW);
							MGPIO_voidSetPinValue(GPIOC , PIN6 , GPIO_LOW);
						}
						else if (Copy_u8Number == 8)
						{
							MGPIO_voidSetPinValue(GPIOC , PIN0 , GPIO_HIGH);
							MGPIO_voidSetPinValue(GPIOC , PIN1 , GPIO_HIGH);
							MGPIO_voidSetPinValue(GPIOC , PIN2 , GPIO_HIGH);
							MGPIO_voidSetPinValue(GPIOC , PIN3 , GPIO_HIGH);
							MGPIO_voidSetPinValue(GPIOC , PIN4 , GPIO_HIGH);
							MGPIO_voidSetPinValue(GPIOC , PIN5 , GPIO_HIGH);
							MGPIO_voidSetPinValue(GPIOC , PIN6 , GPIO_HIGH);
						}
						else if (Copy_u8Number == 9)
						{
							MGPIO_voidSetPinValue(GPIOC , PIN0 , GPIO_HIGH);
							MGPIO_voidSetPinValue(GPIOC , PIN1 , GPIO_HIGH);
							MGPIO_voidSetPinValue(GPIOC , PIN2 , GPIO_HIGH);
							MGPIO_voidSetPinValue(GPIOC , PIN3 , GPIO_HIGH);
							MGPIO_voidSetPinValue(GPIOC , PIN4 , GPIO_LOW);
							MGPIO_voidSetPinValue(GPIOC , PIN5 , GPIO_HIGH);
							MGPIO_voidSetPinValue(GPIOC , PIN6 , GPIO_HIGH);
						}
						break;
			}


}
void MGPIO_voidSetPortDirection  (u8 copy_u8PORT , u32 copy_u32Mode)
{
	switch(copy_u8PORT)
	{
		case GPIOA : GPIOA_CRL = copy_u32Mode;
					 GPIOA_CRH = copy_u32Mode;
					 break;
		case GPIOB : GPIOB_CRL = copy_u32Mode;
					 GPIOB_CRH = copy_u32Mode;
					 break;
		case GPIOC : GPIOC_CRL = copy_u32Mode;
					 GPIOC_CRH = copy_u32Mode;
					 break;

	}
}
void MGPIO_voidSetPortValue      (u8 copy_u8PORT , u16 copy_u16Value)
{
	switch(copy_u8PORT)
	{
		case GPIOA : GPIOA_ODR &= 0x00000000;
					 GPIOA_ODR |= (u32)copy_u16Value;
					 break;
		case GPIOB : GPIOB_ODR &= 0x00000000;
					 GPIOB_ODR |= (u32)copy_u16Value;
					 break;
		case GPIOC : GPIOC_ODR &= 0x00000000;
					 GPIOC_ODR |= (u32)copy_u16Value;
					 break;
	}
}
void MDIO_voidPingPong(u8 copy_u8PORT)
{
switch (copy_u8PORT)
{
case GPIOA:
	for (u8 i=0;i<=4;i++)
				{
					MGPIO_voidSetPinValue(GPIOA,i,GPIO_HIGH );
					MGPIO_voidSetPinValue(GPIOA,7-i,GPIO_HIGH );
					delay(10000);
					MGPIO_voidSetPinValue(GPIOA,i,GPIO_LOW );
					MGPIO_voidSetPinValue(GPIOA,7-i,GPIO_LOW );
				}
			for (u8 j=4;j--;)
			{
				MGPIO_voidSetPinValue(GPIOA,j,GPIO_HIGH );
				MGPIO_voidSetPinValue(GPIOA,7-j,GPIO_HIGH );
				delay(10000);
				MGPIO_voidSetPinValue(GPIOA,j,GPIO_LOW );
				MGPIO_voidSetPinValue(GPIOA,7-j,GPIO_LOW );
			}
break;
case GPIOB:
	for (u8 i=0;i<=4;i++)
				{
					MGPIO_voidSetPinValue(GPIOB,i,GPIO_HIGH );
					MGPIO_voidSetPinValue(GPIOB,7-i,GPIO_HIGH );
					delay(10000);
					MGPIO_voidSetPinValue(GPIOB,i,GPIO_LOW );
					MGPIO_voidSetPinValue(GPIOB,7-i,GPIO_LOW );
				}
			for (u8 j=4;j--;)
			{
				MGPIO_voidSetPinValue(GPIOB,j,GPIO_HIGH );
				MGPIO_voidSetPinValue(GPIOB,7-j,GPIO_HIGH );
				delay(10000);
				MGPIO_voidSetPinValue(GPIOB,j,GPIO_LOW );
				MGPIO_voidSetPinValue(GPIOB,7-j,GPIO_LOW );
			}
break;
case GPIOC:
	for (u8 i=0;i<=4;i++)
				{
					MGPIO_voidSetPinValue(GPIOC,i,GPIO_HIGH );
					MGPIO_voidSetPinValue(GPIOC,7-i,GPIO_HIGH );
					delay(10000);
					MGPIO_voidSetPinValue(GPIOC,i,GPIO_LOW );
					MGPIO_voidSetPinValue(GPIOC,7-i,GPIO_LOW );
				}
			for (u8 j=4;j--;)
			{
				MGPIO_voidSetPinValue(GPIOC,j,GPIO_HIGH );
				MGPIO_voidSetPinValue(GPIOC,7-j,GPIO_HIGH );
				delay(10000);
				MGPIO_voidSetPinValue(GPIOC,j,GPIO_LOW );
				MGPIO_voidSetPinValue(GPIOC,7-j,GPIO_LOW );
			}
}
}
void MDIO_voidSimultaneously(u8 copy_u8PORT)
{
switch (copy_u8PORT)
{
case GPIOA:
for (u8 i=0;i<=7;i++)
						{
							MGPIO_voidSetPinValue(GPIOA,i,GPIO_HIGH );
							delay(10000);
							MGPIO_voidSetPinValue(GPIOA,i,GPIO_LOW );
						}
break;
case GPIOB:
for (u8 i=0;i<=7;i++)
						{
							MGPIO_voidSetPinValue(GPIOB,i,GPIO_HIGH );
							delay(10000);
							MGPIO_voidSetPinValue(GPIOB,i,GPIO_LOW );
						}
break;
case GPIOC:
for (u8 i=0;i<=7;i++)
						{
							MGPIO_voidSetPinValue(GPIOC,i,GPIO_HIGH );
							delay(10000);
							MGPIO_voidSetPinValue(GPIOC,i,GPIO_LOW );
						}
break;
}
}
void MDIO_voidComingandGoing(u8 copy_u8PORT)
{
switch (copy_u8PORT)
{
case GPIOA:
for (u8 i=0;i<=7;i++)
						{
							MGPIO_voidSetPinValue(GPIOA,i,GPIO_HIGH );
							delay(10000);
							MGPIO_voidSetPinValue(GPIOA,i,GPIO_LOW );
						}
					for (u8 j=7;j--;)
					{
						MGPIO_voidSetPinValue(GPIOA,j,GPIO_HIGH );
						delay(10000);
						MGPIO_voidSetPinValue(GPIOA,j,GPIO_LOW );
					}
					break;
case GPIOB:
for (u8 i=0;i<=7;i++)
						{
							MGPIO_voidSetPinValue(GPIOB,i,GPIO_HIGH );
							delay(10000);
							MGPIO_voidSetPinValue(GPIOB,i,GPIO_LOW );
						}
					for (u8 j=7;j--;)
					{
						MGPIO_voidSetPinValue(GPIOB,j,GPIO_HIGH );
						delay(10000);
						MGPIO_voidSetPinValue(GPIOB,j,GPIO_LOW );
					}
					break;
case GPIOC:
for (u8 i=0;i<=7;i++)
						{
							MGPIO_voidSetPinValue(GPIOC,i,GPIO_HIGH );
							delay(10000);

							MGPIO_voidSetPinValue(GPIOC,i,GPIO_LOW );
						}
					for (u8 j=7;j--;)
					{
						MGPIO_voidSetPinValue(GPIOC,j,GPIO_HIGH );
						delay(10000);
						MGPIO_voidSetPinValue(GPIOC,j,GPIO_LOW );
					}
					break;
}
}
