/*
 * RCC.c
 *
 * Created: 11/17/2023 
 *  Author: Ahmed Wael
 */

#include "std_types.h"
#include "common_macros.h"
#include "RCC_prv.h"
#include "RCC.h"

void RCC_voidInitSYSCLK(void)
{
	u32 Time = 0;
	#if SYS_CLK==SYSCLK_HSE
		RCC->RCC_CR = 0x00010000;
		while(GET_BIT(RCC->RCC_CR , 17) == 0 && Time < TIME_OUT)
		 {
			 Time++;
		 }
		 if (Time == TIME_OUT)
		 {
			 //return error
		 }
		 else
		 {
			 RCC->RCC_CFGR = 0x00000001;   //SET SYSTEM CLK
		 }
		
	#elif SYS_CLK==SYSCLK_HSI
		 RCC->RCC_CR = 0x00000001;
		while(GET_BIT(RCC->RCC_CR , 17) == 0 && Time < TIME_OUT)
		 {
			 Time++;
		 }
		 if (GET_BIT(RCC->RCC_CR , 17) == 0)
		 {
			 //return error
		 }
		 else
		 {
			 RCC->RCC_CFGR = 0x00000000;   //SET SYSTEM CLK
		 }
	
	#elif SYS_CLK==SYSCLK_PLL
		#error ("PLL NOT VALID OPTION TILL NOW")
	#endif
}


void RCC_voidEnablePeripheral(u8 Copy_u8Bus, u8 Copy_u8Peripheral)
{
	switch(Copy_u8Bus)
	{
		case AHB_BUS:
			SET_BIT(RCC->RCC_AHBENR,Copy_u8Peripheral);
			break;
		case APB1_BUS:
			SET_BIT(RCC->RCC_APB1ENR,Copy_u8Peripheral);
			break;
		case APB2_BUS:
			SET_BIT(RCC->RCC_APB2ENR,Copy_u8Peripheral);
			break;
	}
}

void RCC_voidDisablePeripheral(u8 Copy_u8Bus, u8 Copy_u8Peripheral)
{
	switch(Copy_u8Bus)
	{
		case AHB_BUS:
			CLR_BIT(RCC->RCC_AHBENR,Copy_u8Peripheral);
			break;
		case APB1_BUS:
			CLR_BIT(RCC->RCC_APB1ENR,Copy_u8Peripheral);
			break;
		case APB2_BUS:
			CLR_BIT(RCC->RCC_APB2ENR,Copy_u8Peripheral);
			break;
	}
}

