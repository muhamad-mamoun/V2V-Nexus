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
#include "PWM.h"
#include "UART_interface.h"
#include "ICU.h"
#include "Can.h"
#include "gpio_prv.h"

/*HAL*/
#include "motor.h"
#include "US.h"
#include "BLE.h"

volatile u16 Global_u16Distance;
/*MakeSure of u8 pointer*/

volatile u8 Global_u8Direction;
volatile u8 Global_u8Speed = 70;
volatile u8  Global_u8BrakeStatus;

u8 Global_u8DataArr[3];

#define CAN_DataID 	0x200

void Motor_SetDirectionT(void* pvParameter)
{
	vTaskDelay(500);
	while(1)
	{
		switch(Global_u8Direction)
		{
		case 'F':
			DCmotor_frontMove(Global_u8Speed);
		  Global_u8BrakeStatus = 0;
			break;
		
		case 'B':
			DCmotor_backMove(Global_u8Speed);
			Global_u8BrakeStatus = 0;
			break;
		
		case 'R':
			DCmotor_rightMove(40);
			Global_u8BrakeStatus = 0;
			break;
		
		case 'L':
			DCmotor_leftMove(40);
			Global_u8BrakeStatus = 0;
			break;
		
		case 'S':
			DCmotor_stop();
		  Global_u8BrakeStatus = 1;
			break;
		}
		vTaskDelay(100);
	}
}

void BLE_GetDirectionT(void* pvparam)
{
	while (1)
	{
		HBLE_VGetKey(&Global_u8Direction);
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
			
			/******Speed Handling********/
			if(Global_u16Distance < 20)
			{
					Global_u8Speed = 0;
					Global_u8BrakeStatus = 1;
			}
			else
			{
				Global_u8Speed = 80;
				Global_u8BrakeStatus = 0;
			}
			/************************/
			
		}
		vTaskDelay(100); 
	}
}


void CAN_SendDataT(void* pvparam)
{
	vTaskDelay(500);
	CAN_Transmit TConfig={STD_ID,DataFram,_3Byte_Data,0x200,Global_u8DataArr};
	while(1)
	{
			Global_u8DataArr[0] = 5/* Global_u8Direction*/;
			Global_u8DataArr[1] = 6/*Global_u8Speed*/;
			Global_u8DataArr[2] = 7/*Global_u8BrakeStatus*/;
			CAN_enuTransmit(&TConfig);
			vTaskDelay(1000);
	}
}




void CAN_voidSysInit()
{
	/*********Pins Configuration*************/
	GPIO_configurationsType CAN_TX  =  {GPIO_PORTB_ID,GPIO_PIN09_ID,GPIO_ALTERNATE_PUSH_PULL_MODE,GPIO_HIGH_SPEED};
	GPIO_configurationsType CAN_RX  =  {GPIO_PORTB_ID,GPIO_PIN08_ID,GPIO_ALTERNATE_PUSH_PULL_MODE,GPIO_HIGH_SPEED};
	GPIO_configurePin(&CAN_TX);
	GPIO_configurePin(&CAN_RX);

  GPIOB->AFRH |=(GPIO_AF09<<0);
  GPIOB->AFRH |=(GPIO_AF09<<4);

	/*********Configuration Struct***********/
	CAN_ConfigType BasicCFG;
	BasicCFG.LockedMode = FIFO_NOTLOCKED;
	BasicCFG.Retransmission = Automatically_Retransmit;
	BasicCFG.WakeUp = Automatic_WakeUP_Enable;
	BasicCFG.BussOffManag = Automatic_BusOff_Enable;
	BasicCFG.TimeTriggered = Time_Trigger_Disable;
	BasicCFG.DebugFreeze = CAN_Debug_Working;
	BasicCFG.FifoPriority = Request_Order;
	BasicCFG.BuadRate_prescaler = 0x00070000;
	
	/***********Filter Struct**************/
	FilterConfig R_Filter = {FilterNumber0,_1R,ListMode,Single,FIFO_0,0x100,0};
	CAN_enuCreateFilter(&R_Filter);
	
	/***********CAN Init******************/
	CAN_enuInit(&BasicCFG);
}

int main(void)
{	
	/************* RCC INITS******************/
	RCC_voidEnablePeripheral(AHB_BUS,GPIOA_EN);
	RCC_voidEnablePeripheral(AHB_BUS,GPIOB_EN);
	RCC_voidEnablePeripheral(AHB_BUS,GPIOC_EN);
	RCC_voidEnablePeripheral(APB1_BUS,TIM2_EN);
	RCC_voidEnablePeripheral(APB1_BUS,TIM3_EN);
	RCC_voidEnablePeripheral(APB2_BUS,USART1_EN);
	RCC_voidEnablePeripheral(APB1_BUS,CAN_EN);
	
	/************* MCAL INITS *****************/
	CAN_voidSysInit();
	
	/************* HAL INITS ******************/
	DCmotor_Init();
	US_voidInit();
	HBLE_VInit();
	
	/************* TASKS CREATION ***************/
	xTaskHandle Motor_SetDirectionH;
	xTaskCreate(Motor_SetDirectionT,(const signed char*)"Motor_SetDirectionT",200,NULL,5,&Motor_SetDirectionH);
	
	xTaskHandle CAN_SendDataH;
	xTaskCreate(CAN_SendDataT,(const signed char*)"CAN_SendDataT",200,NULL,5,&CAN_SendDataH);
		
	xTaskHandle BLE_GetDirectionH;
	xTaskCreate(BLE_GetDirectionT,(const signed char*)"BLE_GetDirectionT",200,NULL,6,&BLE_GetDirectionH);
	
	xTaskHandle US_GetDistanceH;
	xTaskCreate(US_GetDistanceT,(const signed char*)"US_GetDistanceT",200,NULL,7,&US_GetDistanceH);

	vTaskStartScheduler();
}

