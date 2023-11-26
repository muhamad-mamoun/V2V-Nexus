/*FreeRTOS*/
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"

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

volatile u32 Global_u32Direction;
volatile u16 Global_u16Distance;
volatile u16 Global_u16Speed;

void Motor_SetDirectionT(void* pvParameter)
{
	vTaskDelay(500);
	while(1)
	{
	
		switch(Global_u32Direction)
		{
		case 'F':
			DCmotor_frontMove(Global_u16Speed);
			break;
		case 'B':
			DCmotor_backMove(Global_u16Speed);
			break;
		case 'R':
			DCmotor_rightMove(Global_u16Speed);
			break;
		case 'L':
			DCmotor_leftMove(Global_u16Speed);
			break;
		case 'S':
			DCmotor_stop();
			break;
		
		}
		vTaskDelay(300);
	}
	
}

void BLE_GetDirectionT(void* pvparam)
{
	while (1)
	{
		HBLE_VGetKey(&Global_u32Direction);
		vTaskDelay(200);
	}
}

void US_GetDistanceT(void* pvparam)
{
	static u16 Local_Dist;
	while(1)
	{
		US_voidUltraSonicStart();
		vTaskDelay(50);
		US_voidGetUSSensorDistanceTask(&Local_Dist);
		if((Local_Dist != 0xDDDD) && (Local_Dist != 0xFEFE))
		{
			Global_u16Distance = Local_Dist;
			/******For Testing********/
			if(Global_u16Distance < 50)
			{
				
					Global_u16Speed = 0;
			}
			else
			{
				Global_u16Speed = 100;
			}
			/************************/
		}
		vTaskDelay(100); 
	}
	
}

xTaskHandle SetDirectionH;

int main(void)
{
	/************* RCC INITS******************/
	RCC_voidEnablePeripheral(AHB_BUS,GPIOA_EN);
	RCC_voidEnablePeripheral(AHB_BUS,GPIOC_EN);
	RCC_voidEnablePeripheral(APB1_BUS,TIM2_EN);
	RCC_voidEnablePeripheral(APB1_BUS,TIM3_EN);
	RCC_voidEnablePeripheral(APB2_BUS,USART1_EN);
	
	/************* MCAL INITS*****************/
	//	NVIC_Init();  Conflict with FreeRTOS Scheduler

	/************* HAL INITS******************/
	DCmotor_Init();
	US_voidInit();
	HBLE_VInit();

	/************* TASKS CREATION ***************/
	xTaskCreate(Motor_SetDirectionT,(const signed char*)"Motor_SetDirectionT",200,NULL,5,&SetDirectionH);

	xTaskHandle GetDirectionH;
	xTaskCreate(BLE_GetDirectionT,(const signed char*)"BLE_GetDirectionT",200,NULL,6,&GetDirectionH);
	
	xTaskHandle GetDistanceH;
	xTaskCreate(US_GetDistanceT,(const signed char*)"US_GetDistanceT",200,NULL,7,&GetDistanceH);

		vTaskStartScheduler();

	while(1)
	{
	}
	
}

