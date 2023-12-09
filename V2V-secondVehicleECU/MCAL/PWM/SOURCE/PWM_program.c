/*
 * PWM_program.c
 *
 *  Created on: April 7, 2023
 *      Author: beshoy
 */

#include "std_types.h"
#include "common_macros.h"
#include "RCC_interface.h"
#include "DIO_interface.h"
#include "PWM_interface.h"
#include "PWM_config.h"
#include "PWM_private.h"

void MPWM_voidInit(TIM_T Timer, CH_T CHANNEL, u16 AutoReload_Val)
{
	MRCC_voidPerClock_State(APB1 , Timer , PClock_enable );
	/*auto reload preload*/
	SET_BIT(TIM[Timer]->CR1,ARPE);
	/*Edge Aligned*/
	CLR_BIT(TIM[Timer]->CR1,CMS1);
	CLR_BIT(TIM[Timer]->CR1,CMS0);
	/*upcounting DIR ARR is the destination*/
	CLR_BIT(TIM[Timer]->CR1,DIR);
	/*set prescaler*/
	TIM[Timer]->PSC = TIMER_PRESCALLER-1;
	TIM[Timer]->ARR = AutoReload_Val-1;
	switch(CHANNEL)
	{
		case CH1:
		if(Timer == TIMER2)
		{
			MGPIO_voidSetPinDirection(GPIOA_driver , PIN0  , OUTPUT_SPEED_10MHZ_AFPP);
		}
		else if(Timer == TIMER3)
		{
			MGPIO_voidSetPinDirection(GPIOA_driver , PIN6  , OUTPUT_SPEED_10MHZ_AFPP);
		}
		else if(Timer == TIMER4)
		{
			MGPIO_voidSetPinDirection(GPIOB_driver , PIN6  , OUTPUT_SPEED_10MHZ_AFPP);
		}
		else if(Timer == TIMER5)
		{
		}
		else
		{	
		}
		SET_BIT(TIM[Timer]->CCER,CC1E);
		SET_BIT(TIM[Timer]->CCMR1,OC1PE);
		TIM[Timer]->CCMR1 &= ~(0b111<<OC1M);
		TIM[Timer]->CCMR1 |=  (PWM_MODE<<OC1M);
		TIM[Timer]->CCR1 = AutoReload_Val;
		break;
		case CH2:
		if(Timer == TIMER2)
		{
			MGPIO_voidSetPinDirection(GPIOA_driver , PIN1  , OUTPUT_SPEED_10MHZ_AFPP);
		}
		else if(Timer == TIMER3)
		{
			MGPIO_voidSetPinDirection(GPIOA_driver , PIN7  , OUTPUT_SPEED_10MHZ_AFPP);
		}
		else if(Timer == TIMER4)
		{
			MGPIO_voidSetPinDirection(GPIOB_driver , PIN7  , OUTPUT_SPEED_10MHZ_AFPP);
		}
		else if(Timer == TIMER5)
		{
		}
		else
		{
		}
		SET_BIT(TIM[Timer]->CCMR1,OC2PE);
		TIM[Timer]->CCMR1 &= ~(0b111<<OC2M);
		TIM[Timer]->CCMR1 |=  (PWM_MODE<<OC2M);
		TIM[Timer]->CCR2 = AutoReload_Val;
		break;
		case CH3:
		if(Timer == TIMER2)
		{
			MGPIO_voidSetPinDirection(GPIOA_driver , PIN2  , OUTPUT_SPEED_10MHZ_AFPP);
		}
		else if(Timer == TIMER3)
		{
			MGPIO_voidSetPinDirection(GPIOB_driver , PIN0  , OUTPUT_SPEED_10MHZ_AFPP);
		}
		else if(Timer == TIMER4)
		{
			MGPIO_voidSetPinDirection(GPIOB_driver , PIN8  , OUTPUT_SPEED_10MHZ_AFPP);
		}
		else if(Timer == TIMER5)
		{
		}
		else
		{
		}
		SET_BIT(TIM[Timer]->CCMR2,OC3PE);
		TIM[Timer]->CCMR2 &= ~(0b111<<OC3M);
		TIM[Timer]->CCMR2 |=  (PWM_MODE<<OC3M);
		TIM[Timer]->CCR3 = AutoReload_Val;
		break;
		case CH4:
		if(Timer == TIMER2)
		{
			MGPIO_voidSetPinDirection(GPIOA_driver , PIN3  , OUTPUT_SPEED_10MHZ_AFPP);
		}
		else if(Timer == TIMER3)
		{
			MGPIO_voidSetPinDirection(GPIOB_driver , PIN1  , OUTPUT_SPEED_10MHZ_AFPP);
		}
		else if(Timer == TIMER4)
		{
			MGPIO_voidSetPinDirection(GPIOB_driver , PIN9  , OUTPUT_SPEED_10MHZ_AFPP);
		}
		else if(Timer == TIMER5)
		{
			MGPIO_voidSetPinDirection(GPIOA_driver , PIN3  , OUTPUT_SPEED_10MHZ_AFPP);
		}
		else
		{
		}
		SET_BIT(TIM[Timer]->CCMR2,OC4PE);
		TIM[Timer]->CCMR2 &= ~(0b111<<OC4M);
		TIM[Timer]->CCMR2 |=  (PWM_MODE<<OC4M);
		TIM[Timer]->CCR4 = AutoReload_Val;
		break;
		default:
		break;
	}
	SET_BIT(TIM[Timer]->EGR, UG);
	SET_BIT(TIM[Timer]->CR1, CEN);
}
void MPWM_SETValuesOfPWM(TIM_T Timer, CH_T CHANNEL, u16  MCopy_u16CompareVal)
{
	switch(CHANNEL)
	{
		case CH1:
		TIM[Timer]->CCR1 = MCopy_u16CompareVal;
		break;
		case CH2:
		TIM[Timer]->CCR2 = MCopy_u16CompareVal;
		break;
		case CH3:
		TIM[Timer]->CCR3 = MCopy_u16CompareVal;
		break;
		case CH4:
		TIM[Timer]->CCR4 = MCopy_u16CompareVal;
		break;
		default:
			break;
	}
	SET_BIT(TIM[Timer]->EGR, UG);
}
