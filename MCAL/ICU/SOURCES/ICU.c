#include "std_types.h"
#include "bit_math.h"

#include "ICU.h"
#include "ICU_prv.h"
#include "ICU_cfg.h"

void ICU_voidInitTimer(u8 Copy_u8Channel, u8 Copy_u8Timer)
{
	/*SET timer on one pulse mode*/
	SET_BIT(Timer[Copy_u8Timer]->CR1,OPM);
	
	#if ICU_INT	== ICU_INTEnable
	SET_BIT(Timer[Copy_u8Timer]->DIER,(CC1IE+Copy_u8Channel));
	#elif ICU_INT	== ICU_INTDisable
	CLEAR_BIT(Timer[Copy_u8Timer]->DIER,(CC1IE+Copy_u8Channel));
	#endif

	#if Timer_INT	== TIMER_INTEnable
	SET_BIT(Timer[Copy_u8Timer]->DIER,UIE);
	#elif Timer_INT	== TIMER_INTDisable
	CLEAR_BIT(Timer[Copy_u8Timer]->DIER,UIE);
	#endif
	ICU_voidSetSensingEdge(Copy_u8Channel, Copy_u8Timer, Falling_Edge);
	switch(Copy_u8Channel)
	{
		case CH1:
			Timer[Copy_u8Timer]->CCMR1 = ((Timer[Copy_u8Timer]->CCMR1&0xFFFFFF00)|0x00000001);
			SET_BIT(Timer[Copy_u8Timer]->CCER, 0);
			break;
		case CH2:
			Timer[Copy_u8Timer]->CCMR1 = ((Timer[Copy_u8Timer]->CCMR1&0xFFFF00FF)|0x00000100);
			SET_BIT(Timer[Copy_u8Timer]->CCER, 4);
			break;
		case CH3:
			Timer[Copy_u8Timer]->CCMR2 = ((Timer[Copy_u8Timer]->CCMR2&0xFFFFFF00)|0x00000001);
			SET_BIT(Timer[Copy_u8Timer]->CCER, 8);
			break;
		case CH4:
			Timer[Copy_u8Timer]->CCMR2 = ((Timer[Copy_u8Timer]->CCMR2&0xFFFF00FF)|0x00000100);
			SET_BIT(Timer[Copy_u8Timer]->CCER, 12);
			break;
	}
	Timer[Copy_u8Timer]->PSC = Timer_Prescaller - 1;
	Timer[Copy_u8Timer]->ARR = ARR_Val - 1;
}
void ICU_voidSetSensingEdge(u8 Copy_u8Channel, u8 Copy_u8Timer, u8 Copy_u8SignalSense)
{
	switch(Copy_u8SignalSense)
	{
		case Falling_Edge:
			SET_BIT(Timer[Copy_u8Timer]->CCER, (1 + (Copy_u8Channel * 4)));
			CLR_BIT(Timer[Copy_u8Timer]->CCER, (3 + (Copy_u8Channel * 4)));
			break;
		case Rising_Edge:
			CLR_BIT(Timer[Copy_u8Timer]->CCER, (1 + (Copy_u8Channel * 4)));
			CLR_BIT(Timer[Copy_u8Timer]->CCER, (3 + (Copy_u8Channel * 4)));
			break;
		case Any_Egdy:
			SET_BIT(Timer[Copy_u8Timer]->CCER, (1 + (Copy_u8Channel * 4)));
			SET_BIT(Timer[Copy_u8Timer]->CCER, (3 + (Copy_u8Channel * 4)));
			break;
	}
}
void ICU_voidSetCountTime(u8 Copy_u8Timer, u32 Copy_u32CountTime)
{
	Timer[Copy_u8Timer]->CNT = Copy_u32CountTime;
}
void ICU_voidEnableTimer(u8 Copy_u8Timer)
{
	SET_BIT(Timer[Copy_u8Timer]->CR1, CEN);  
}
void ICU_voidGetICU_Count(u8 Copy_u8Channel, u8 Copy_u8Timer, u32* Ptr_ICU_Count)
{
	u32 Local_count;
	switch(Copy_u8Channel)
	{
		case CH1:
			Local_count = Timer[Copy_u8Timer]->CCR1;
			break;
		case CH2:
			Local_count = Timer[Copy_u8Timer]->CCR2;
			break;
		case CH3:
			Local_count = Timer[Copy_u8Timer]->CCR3;
			break;
		case CH4:
			Local_count = Timer[Copy_u8Timer]->CCR4;
			break;
	}
	*Ptr_ICU_Count = Local_count;
}
void ICU_voidGetTimerOvStatus(u8 Copy_u8Timer, u8* Ptr_OvStauts)
{
	*Ptr_OvStauts = GET_BIT(Timer[Copy_u8Timer]->SR,UIF);
}
void ICU_voidClrTimerOvFlag(u8 Copy_u8Timer)
{
	CLEAR_BIT(Timer[Copy_u8Timer]->SR,UIF);
}
void ICU_voidGetTimerIcuStatus(u8 Copy_u8Channel, u8 Copy_u8Timer, u8* Ptr_IcuStauts)
{
	*Ptr_IcuStauts = GET_BIT(Timer[Copy_u8Timer]->SR, (CC1IF + Copy_u8Channel));
}
void ICU_voidSetArrTime(u8 Copy_u8Timer, u32 Copy_u32ArrTime)
{
	Timer[Copy_u8Timer]->ARR = Copy_u32ArrTime;
}
void ICU_voidClrTimerIcuFlag(u8 Copy_u8Channel, u8 Copy_u8Timer)
{
	CLEAR_BIT(Timer[Copy_u8Timer]->SR,(CC1IF + Copy_u8Channel));
}
