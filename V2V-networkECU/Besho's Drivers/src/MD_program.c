/*
 * MD_program.c
 *
 *  Created on: May 15, 2023
 *      Author: beshoy
 */

#include "../Inc/LIB/STD_TYPES.h"
#include "../Inc/LIB/BIT_MATH.h"
#include "../Inc/MCAL/DIO/DIO_interface.h"
#include "../Inc/MCAL/PWM/PWM_interface.h"
#include "../Inc/MCAL/ADC/ADC_interface.h"
#include	"../Inc/MCAL/SYSTIC/STK_interface.h"
#include "../Inc/HAL/MD/MD_interface.h"
#include "../Inc/HAL/MD/MD_config.h"
#include "../Inc/HAL/MD/MD_private.h"

void HMD_voidInit(void)
{
	MADC_Init();
	MPWM_voidInit(TIMER2, CH1,8000);
	MPWM_SETValuesOfPWM(TIMER2, CH1, 0);
	MGPIO_voidSetPinDirection(GPIOA , PIN2  , OUTPUT_SPEED_10MHZ_PP);
	MGPIO_voidSetPinDirection(GPIOA , PIN3  , OUTPUT_SPEED_10MHZ_PP);
}


void HMD_voidForward(void)
{

	static s16 new=0,old=1000;
		new=MADC_Read(1);
		for(u32 i=0;i<5;i++);
		//MSTK_voidSetBusyWait 		  (500000);
		if(new-old>5)
		{
			MPWM_SETValuesOfPWM(TIMER2, CH1, (new*1.9+2150));
		}
		else if(old-new>40)
		{
			MPWM_SETValuesOfPWM(TIMER2, CH1, (new*1.4));
		}
		else if(old-new>90)
		{
			MPWM_SETValuesOfPWM(TIMER2, CH1, (new*1.3));
		}
		else if(old-new>120)
		{
			MPWM_SETValuesOfPWM(TIMER2, CH1, (new*1.2));
		}
		else if(old-new>150)
		{
			MPWM_SETValuesOfPWM(TIMER2, CH1, (new*1.1));
		}
		else if(old-new>190)
		{
			MPWM_SETValuesOfPWM(TIMER2, CH1, (new*.95));
		}
		else if(old-new>350)
		{
			MPWM_SETValuesOfPWM(TIMER2, CH1, (new*.44));
		}
		if(new<1090)
		{
			MPWM_SETValuesOfPWM(TIMER2, CH1, 0);
		}
		old=new;
}

