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

u32 Global_u32Direction = 'F';
u16 Global_u16Distance;

void Motor_SetDirectionT(void* pvParameter)
{
	u8 Speed = 0;
	vTaskDelay(500);
	while(1)
	{
		if( Global_u16Distance > 50)
		{
			Speed = 100;
		}
		else if (Global_u16Distance > 5 && Global_u16Distance <= 50)
		{
			Speed =  Global_u16Distance + 10;
		}
		else 
		{
			Speed = 0;
		}
		switch(Global_u32Direction)
		{
		case 'F':
			DCmotor_frontMove(Speed);
			break;
		case 'B':
			DCmotor_backMove(Speed);
			break;
		case 'R':
			DCmotor_rightMove(Speed);
			break;
		case 'L':
			DCmotor_leftMove(Speed);
			break;
		default:
			DCmotor_stop();
		break;
		}
		vTaskDelay(100);
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
					GPIO_writePin(H_BRIDGE_INPUT2_PORT,H_BRIDGE_INPUT2_PIN,GPIO_HIGH_PIN);
			}
			else
			{
					GPIO_writePin(H_BRIDGE_INPUT2_PORT,H_BRIDGE_INPUT2_PIN,GPIO_LOW_PIN);
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

//	xTaskHandle GetDirectionH;
//	xTaskCreate(BLE_GetDirectionT,(const signed char*)"BLE_GetDirectionT",200,NULL,6,&GetDirectionH);
//	
	xTaskHandle GetDistanceH;
	xTaskCreate(US_GetDistanceT,(const signed char*)"US_GetDistanceT",200,NULL,7,&GetDistanceH);

		vTaskStartScheduler();

	while(1)
	{
	}
	
}

