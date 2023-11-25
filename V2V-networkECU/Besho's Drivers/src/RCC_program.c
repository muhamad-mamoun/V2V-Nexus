/*
 * RCC_program.c
 *
 *  Created on: septemper 15, 2022
 *      Author: beshoy
 */
#include "../Inc/LIB/STD_TYPES.h"
#include "../Inc/LIB/BIT_MATH.h"

#include "../Inc/MCAL/RCC/RCC_interface.h"
#include "../Inc/MCAL/RCC/RCC_private.h"
#include "../Inc/MCAL/RCC/RCC_configuration.h"

void MRCC_voidInit(void)
{
#if CLK_SOURCE == HSI
	// Turn on HSI
	MRCC_voidClkEnable(HSI);
	// Check HSI Ready
	while (MRCC_u8CheckClockReady(HSI) == NOT_READY);
	// Set Buses Prescaler
	MRCC_voidSetBusesPrescaler(AHB_PRESCALER, ABP1_PRESCALER, ABP2_PRESCALER);
	// Switch to HSI Clock
	MRCC_voidSetClkSource(HSI);
	// Turn off HSE and PLL
	MRCC_voidClkDisable(HSE);
	MRCC_voidClkDisable(PLL);
#elif CLK_SOURCE == HSE
	// Turn on HSE
	MRCC_voidClkEnable(HSE);
	// Check HSE Ready
	while (MRCC_u8CheckClockReady(HSE) == NOT_READY)
		;
	// Set Buses Prescaler
	MRCC_voidSetBusesPrescaler(AHB_PRESCALER, ABP1_PRESCALER, ABP2_PRESCALER);
	// Switch to HSE Clock
	MRCC_voidSetClkSource(HSE);
	// Turn off HSE and PLL
	MRCC_voidClkDisable(HSI);
	MRCC_voidClkDisable(PLL);

#elif CLK_SOURCE == PLL
	#if PLL_SOURCE == HSE
		MRCC_voidSetPLLSource(PLL_SOURCE, PLL_HSE_FACTOR);
		// Turn on HSE
		MRCC_voidClkEnable(HSE);
		// Check HSE Ready
		while (MRCC_u8CheckClockReady(HSE) == NOT_READY);
		MRCC_voidClkDisable(HSI);
	#elif PLL_SOURCE == HSI
		MRCC_voidSetPLLSource(PLL_SOURCE, HSE_NOT_DIVIDED);
		// Turn on HSE
		MRCC_voidClkEnable(HSI);
		// Check HSE Ready
		while (MRCC_u8CheckClockReady(HSI) == NOT_READY);
		MRCC_voidClkDisable(HSE);
	#else
		#error Wrong PLL Configurations
	#endif
		// Set Pll Multiplication Factor
		MRCC_voidSetPLLMulFactor(PLL_MULTIPLICATION_FACTOR);
		// Set Buses Prescaler
		MRCC_voidSetBusesPrescaler(AHB_PRESCALER, ABP1_PRESCALER, ABP2_PRESCALER);
		// Turn on PLL
		MRCC_voidClkEnable(PLL);
		// Check PLL Ready
		while (MRCC_u8CheckClockReady(PLL) == NOT_READY);
		// Switch to PLL Clock
		MRCC_voidSetClkSource(PLL);


#else
#error CLOCK Source isn not configured in the right way
#endif

}

void MRCC_voidPerClock_State(Buses_t A_bus ,u8  A_peripheral ,PClock_State_t A_state )
{
	  switch (A_bus) {
	        case AHB  :
	        	if(A_state == PClock_enable)
	        	{
	        		SET_BIT (RCC->AHBENR  , A_peripheral );
	        	}
	        	else if(A_state == PClock_disable)
	        	{
		        	CLR_BIT (RCC->AHBENR  , A_peripheral );

	        	}
	        	break;
	        case APB1 :
	        	if(A_state == PClock_enable)
	        	{
	        		SET_BIT (RCC->APB1ENR  , A_peripheral );
	        	}
	        	else if(A_state == PClock_disable)
	        	{
	        		CLR_BIT (RCC->APB1ENR  , A_peripheral );
	        	}
	        	break;
	        case APB2 :
	        	if(A_state == PClock_enable)
	        	{
	        		SET_BIT (RCC->APB2ENR  , A_peripheral );
	        	}
	        	else if(A_state == PClock_disable)
	        	{
	        		CLR_BIT (RCC->APB2ENR  , A_peripheral );
	        	}
	        	break;

	        default       : break;
	      }
}

void MRCC_voidSetPLLMulFactor(u8 A_u8MulFactor)
{
	RCC->CFGR &= ~(MULTIPLICATION_FACTOR_RESET_MASK);
	RCC->CFGR |= (A_u8MulFactor << PLL_MUL_FBIT);
}

/* A_u8ClkSource : HSI  -  HSE */
/* A_u8Prescaler : HSE_NOT_DIVIDED  -  HSE_DIVIDED*/

void MRCC_voidSetPLLSource(u8 A_u8ClkSource, u8 A_u8Prescaler)
{
	switch (A_u8ClkSource)
	{
	case HSI:
		CLR_BIT(RCC->CFGR, PLLSRC_BIT);
		break;
	case HSE:
		SET_BIT(RCC->CFGR, PLLSRC_BIT);
		switch (A_u8Prescaler)
		{
		case HSE_NOT_DIVIDED:
			CLR_BIT(RCC->CFGR, PLLXTPRE_BIT);
			break;
		case HSE_DIVIDED:
			SET_BIT(RCC->CFGR, PLLXTPRE_BIT);
			break;
		default:
			break;
		}
		break;
	}
}

void MRCC_voidClkEnable(u8 A_u8ClkSource)
{
	switch (A_u8ClkSource)
	{
	case HSI:
		SET_BIT(RCC->CR, HSI_ON_BIT);
		break;
	case HSE:
		SET_BIT(RCC->CR, HSE_ON_BIT);
		break;
	case PLL:
		SET_BIT(RCC->CR, PLL_ON_BIT);
		break;
	}
}

void MRCC_voidClkDisable(u8 A_u8ClkSource)
{
	switch (A_u8ClkSource)
	{
	case HSI:
		CLR_BIT(RCC->CR, HSI_ON_BIT);
		break;
	case HSE:
		CLR_BIT(RCC->CR, HSE_ON_BIT);
		break;
	case PLL:
		CLR_BIT(RCC->CR, PLL_ON_BIT);
		break;
	}
}

u8 MRCC_u8CheckClockReady(u8 A_u8ClkSource)
{
	u8 local_u8ReadyFlag = 0;
	switch (A_u8ClkSource)
	{
	case HSI:
		local_u8ReadyFlag = GET_BIT(RCC->CR, HSI_RDY_BIT);
		break;
	case HSE:
		local_u8ReadyFlag = GET_BIT(RCC->CR, HSE_RDY_BIT);
		break;
	case PLL:
		local_u8ReadyFlag = GET_BIT(RCC->CR, PLL_RDY_BIT);
		break;
	}
	return local_u8ReadyFlag;
}

void MRCC_voidSetClkSource(u8 A_u8ClkSource)
{
	switch (A_u8ClkSource)
	{
	case HSI:
		CLR_BIT(RCC->CFGR, SYSTEM_CLOCK_BIT0);
		CLR_BIT(RCC->CFGR, SYSTEM_CLOCK_BIT1);
		break;
	case HSE:
		SET_BIT(RCC->CFGR, SYSTEM_CLOCK_BIT0);
		CLR_BIT(RCC->CFGR, SYSTEM_CLOCK_BIT1);
		break;
	case PLL:
		CLR_BIT(RCC->CFGR, SYSTEM_CLOCK_BIT0);
		SET_BIT(RCC->CFGR, SYSTEM_CLOCK_BIT1);
		break;
	}
}

void MRCC_voidSetBusesPrescaler(u8 A_u8AHBPrescaler, u8 A_u8APB1Prescaler, u8 A_u8APB2Prescaler)
{
	RCC->CFGR &= ~(BUSES_PRESCALER_RESET_MASK << AHB_PRESCALER_FBIT);
	RCC->CFGR |= (A_u8AHBPrescaler << AHB_PRESCALER_FBIT);
	RCC->CFGR |= (A_u8APB1Prescaler << APB1_PRESCALER_FBIT);
	RCC->CFGR |= (A_u8APB2Prescaler << APB2_PRESCALER_FBIT);
}
