#include "EXTI_Prev.h"
#include "common_macros.h"
#include "std_types.h"
extern void (*Call_Ptr[15])(void);

void EXTI0_IRQHandler(void)
{
	Call_Ptr[0]();
}

void EXTI1_IRQHandler(void)
{
	Call_Ptr[1]();
}

void EXTI2_TSC_IRQHandler(void)
{
	Call_Ptr[2]();
}

void EXTI3_IRQHandler(void)
{
	Call_Ptr[3]();
}


void EXTI4_IRQHandler(void)
{
	Call_Ptr[4]();
}


void EXTI9_5_IRQHandler(void)
{
	if(GET_BIT(EXTI_PR1,5)==1)
	{
			Call_Ptr[5]();
		SET_BIT(EXTI_PR1,5);
	}
	else if(GET_BIT(EXTI_PR1,6)==1)
	{
			Call_Ptr[6]();
				SET_BIT(EXTI_PR1,6);
	}
	else if(GET_BIT(EXTI_PR1,7)==1)
	{
			Call_Ptr[7]();
				SET_BIT(EXTI_PR1,7);

	}
	else if(GET_BIT(EXTI_PR1,8)==1)
	{
			Call_Ptr[8]();
				SET_BIT(EXTI_PR1,8);

	}
	else if(GET_BIT(EXTI_PR1,9)==1)
	{
			Call_Ptr[9]();
				SET_BIT(EXTI_PR1,9);

	}
	else
		{
			
		}
}


void EXTI15_10_IRQHandler(void)
{
	if(GET_BIT(EXTI_PR1,10)==1)
	{
			Call_Ptr[10]();
		SET_BIT(EXTI_PR1,10);
	}
	else if(GET_BIT(EXTI_PR1,11)==1)
	{
			Call_Ptr[11]();
				SET_BIT(EXTI_PR1,11);
	}
	else if(GET_BIT(EXTI_PR1,12)==1)
	{
			Call_Ptr[12]();
				SET_BIT(EXTI_PR1,12);

	}
	else if(GET_BIT(EXTI_PR1,13)==1)
	{
			Call_Ptr[13]();
				SET_BIT(EXTI_PR1,13);

	}
	else if(GET_BIT(EXTI_PR1,14)==1)
	{
			Call_Ptr[14]();
				SET_BIT(EXTI_PR1,14);

	}
	else if(GET_BIT(EXTI_PR1,15)==1)
	{
			Call_Ptr[15]();
				SET_BIT(EXTI_PR1,15);

	}
	else 
	{
		
	}
}
