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

u8 Global_u8CANDataIndex;
typedef struct 
{
volatile u8 Global_u8Direction;
volatile u8 Global_u8Speed;
volatile u8  Global_u8BrakeStatus;
}Data_t;

Data_t My_Data = {'S',60,0};
Data_t REC_Data;

u8 Global_u8DataArr[3];

#define CAN_DataID 	0x200

void Motor_SetDirectionT(void* pvParameter)
{
	vTaskDelay(500);
	u8 Local_u8RecData = 0;
	u8 Local_u8PrevDirection = 0;
	while(1)
	{
		HBLE_VGetKey(&Local_u8RecData);
		if (Local_u8RecData == '-' )
		{
			if(My_Data.Global_u8Speed != 0)
			{
				My_Data.Global_u8Speed-=20;
			}
		}
		else if (Local_u8RecData == '+' )
		{
			if(My_Data.Global_u8Speed != 100)
			{
				My_Data.Global_u8Speed+=20;
			}
		}
		else if (Local_u8RecData != NO_REC_KEY)
		{
			My_Data.Global_u8Direction = Local_u8RecData;
		}
		
		/*if(Local_u8PrevDirection != My_Data.Global_u8Direction  || My_Data.Global_u8BrakeStatus == 1 
			           || Local_u8RecData == '+' || Local_u8RecData == '-')
		{*/
		//	Local_u8PrevDirection =  My_Data.Global_u8Direction;
			switch(My_Data.Global_u8Direction)
					{
					case 'F':
						if( My_Data.Global_u8BrakeStatus == 0)
						{
							DCmotor_frontMove(My_Data.Global_u8Speed);
						}
						else
						{
							DCmotor_stop();
						}
						break;
					
					case 'B':
						DCmotor_backMove(My_Data.Global_u8Speed);
						break;
					
					case 'R':
						DCmotor_rightMove(40);
						break;
					
					case 'L':
						DCmotor_leftMove(40);
						break;
					
					case 'S':
						DCmotor_stop();
						My_Data.Global_u8BrakeStatus = 1;
						break;
					}
		/*}
		else
		{
			
		}*/
		
		vTaskDelay(70);
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
			if(Local_Dist < 30)
			{
					My_Data.Global_u8BrakeStatus = 1;
			}
			else if (My_Data.Global_u8Direction != 'S')
			{
				My_Data.Global_u8BrakeStatus = 0;
			}
		}
		vTaskDelay(10); 
	}
}


void CAN_SendDataT(void* pvparam)
{
	vTaskDelay(500);
	CAN_Transmit TConfig = {STD_ID,DataFram,_3Byte_Data,CAN_DataID,Global_u8DataArr};
	while(1)
	{
		Global_u8DataArr[0] = My_Data.Global_u8Direction;
		Global_u8DataArr[1] = My_Data.Global_u8Speed;
		Global_u8DataArr[2] = My_Data.Global_u8BrakeStatus;
		
		CAN_enuTransmit(&TConfig);
		vTaskDelay(1000);
	} 
}

void CAN_RevieveDataT(void* pvparam)
{
	while(1)
	{
		if(CAN_enuRecieve(&Global_u8CANDataIndex) == CAN_NORecievedData)
		{
			
		}
		else
		{
			REC_Data.Global_u8Direction=   ARR_Recieved_Data[Global_u8CANDataIndex][0];
			REC_Data.Global_u8Speed = 		 ARR_Recieved_Data[Global_u8CANDataIndex][1];
			REC_Data.Global_u8BrakeStatus= ARR_Recieved_Data[Global_u8CANDataIndex][2];
		
		}
		vTaskDelay(500);

	}
}



void CAN_voidSysInit()
{
	/*********Pins Configuration*************/
	GPIO_configurationsType CAN_TX  =  {GPIO_PORTB_ID,GPIO_PIN09_ID,GPIO_ALTERNATE_PUSH_PULL_MODE,GPIO_HIGH_SPEED};
	GPIO_configurationsType CAN_RX  =  {GPIO_PORTB_ID,GPIO_PIN08_ID,GPIO_ALTERNATE_PUSH_PULL_MODE,GPIO_HIGH_SPEED};
	
	GPIO_configurePin(&CAN_TX);
	GPIO_configurePin(&CAN_RX);
	
	GPIO_setPinFuction(GPIO_PORTB_ID,GPIO_PIN09_ID,GPIO_AF09);  //sa3at bthng
	GPIO_setPinFuction(GPIO_PORTB_ID,GPIO_PIN08_ID,GPIO_AF09);

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
	xTaskCreate(Motor_SetDirectionT,NULL,configMINIMAL_STACK_SIZE,NULL,1,&Motor_SetDirectionH);
	
	xTaskHandle CAN_SendDataH;
	xTaskCreate(CAN_SendDataT,NULL,configMINIMAL_STACK_SIZE,NULL,1,&CAN_SendDataH);
	
	xTaskHandle CAN_RevieveDataH;
	xTaskCreate(CAN_RevieveDataT,NULL,configMINIMAL_STACK_SIZE,NULL,1,&CAN_RevieveDataH);
	
	
	xTaskHandle US_GetDistanceH;
	xTaskCreate(US_GetDistanceT,NULL,configMINIMAL_STACK_SIZE,NULL,4,&US_GetDistanceH);

	vTaskStartScheduler();
}

