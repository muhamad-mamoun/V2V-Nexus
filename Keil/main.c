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


int main(void)
{
	RCC_voidEnablePeripheral(AHB_BUS,GPIOA_EN);
	RCC_voidEnablePeripheral(AHB_BUS,GPIOC_EN);
	RCC_voidEnablePeripheral(APB1_BUS,TIM2_EN);
	


	 DCmotor_Init();
	
	
	while(1)
	{
		DCmotor_frontMove(100);
		DCmotor_backMove(40);
	 DCmotor_rightMove(80);
		DCmotor_leftMove(40);

		
	}
	
}

