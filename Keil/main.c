/*FreeRTOS*/


/*Utils*/
#include "common_macros.h"
#include "std_types.h"

/*MCAL*/
#include "RCC.h"
#include "gpio.h"
#include "NVIC.h"
#include "PWM.h"
#include "UART_interface.h"
#include "ICU.h"
#include "EXTI.h"

/*HAL*/
#include "motor.h"
#include "US.h"
#include "BLE.h"

u32 Dist;

int main(void)
{
	RCC_voidEnablePeripheral(AHB_BUS,GPIOA_EN);
	RCC_voidEnablePeripheral(AHB_BUS,GPIOC_EN);
	RCC_voidEnablePeripheral(APB1_BUS,TIM2_EN);
	RCC_voidEnablePeripheral(APB1_BUS,TIM3_EN);
	RCC_voidEnablePeripheral(APB2_BUS,USART1_EN);

	NVIC_Init();

	DCmotor_Init();
	US_voidInit();
	HBLE_VInit();

	
	while(1)
	{
		HBLE_VGetKey(&Dist);
		if(Dist == 'F')
		{
			DCmotor_backMove(100);
		}
		else if (Dist == 'B')
		{
			DCmotor_frontMove(100);
		}
		else
		{
			DCmotor_stop();
		}
	}
	
}

