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
#include "NVIC.h"

/*HAL*/
#include "motor.h"
#include "US.h"
#include "BLE.h"
#include "eeprom.h"

#define MAX_DISTANCE 50
#define NUM_OF_CHECK_LOGS 2
#define CAN_DataID 	0x200

/************* LOGS *************/
#define TEMP_OK 0x11
#define TEMP_OVERHEAT 0x5A
#define TEMP_NOTRESPONDING 0xFC

#define US_OK 0x12
//#define US_READINGERROR 0xD7
#define US_NOTRESPONDING 0xFE

#define TEMP_DATA_INDEX 0
#define US_DATA_INDEX   1

#define EEPROM_START_ADDRESS   0x10

/*******************************/



u8 Global_u8LogsArr[NUM_OF_CHECK_LOGS];  //ARR to TEMP STORE LOGS
u8 Global_readEEPROM[NUM_OF_CHECK_LOGS];  //ARR to TEMP STORE LOGS
u8 Global_u8DataArr[3]; 	 							//TEMP ARR FOR CAN DATA

volatile u16 Global_u16Distance; 				//FOR US



typedef struct 
{
volatile u8 Global_u8Direction;
volatile u8 Global_u8Speed;
volatile u8 Global_u8BrakeStatus;
}Data_t;

Data_t My_Data = {'S',60,0}; //INIT VALS FOR CAR
Data_t REC_Data; 						 //REC DATA FROM CAN [NOT USED YET]



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
		else if (Local_u8RecData == '+')
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
						/*MOTORS SET*/
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
			DCmotor_rightMove(30);
			break;
		
		case 'L':
			DCmotor_leftMove(30);
			break;
		
		case 'S':
			DCmotor_stop();
			My_Data.Global_u8BrakeStatus = 1;
			break;
		}
		vTaskDelay(70);
	}
}

void EEPROM_WriteLogsT (void* pvparam) //TASK NOT CREATED YET  
{
	/*TILL EEPROM DRIVER IS FINISHED*/
	      
	while (1)
	{
		EEPROM_WRITE_STRING(EEPROM_START_ADDRESS,Global_u8LogsArr,NUM_OF_CHECK_LOGS);
		EEPROM_READ_STRING(EEPROM_START_ADDRESS,Global_readEEPROM,NUM_OF_CHECK_LOGS);
		vTaskDelay(500);
	}
	
}

void TEMP_GetTempT(void* pvparam)   //TASK NOT CREATED YET  
{
	/*TILL TEMP DRIVER IS FINISHED*/
		/*
				u8 Local_u8Temp;
				u8 ret;
				while (1)
				{
						ret = TEMP_Get(&Local_u8Temp);
						if(ret == 1)
							{
									Global_u8LogsArr[TEMP_DATA_INDEX] = TEMP_NOTRESPONDING;
							}
						else
							{
								if (Local_u8Temp > 100)
								{
									Global_u8LogsArr[TEMP_DATA_INDEX] = TEMP_OVERHEAT;
								}
								else
								{
									Global_u8LogsArr[TEMP_DATA_INDEX] = TEMP_OK;
								}
							}
							vTaskDelay(200);
				}			
		*/
	/******************************/
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
			Global_u8LogsArr[US_DATA_INDEX] = US_OK;
			if(Local_Dist < MAX_DISTANCE)
			{
					My_Data.Global_u8BrakeStatus = 1;
			}
			else if (My_Data.Global_u8Direction != 'S')
			{
				My_Data.Global_u8BrakeStatus = 0;
			}
		}
		else if (Local_Dist == 0xFEFE)
		{
			Global_u8LogsArr[US_DATA_INDEX] = US_NOTRESPONDING;
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
	u8 CAN_u8DataIndex = 0;
	while(1)
	{
		if(CAN_enuRecieve(&CAN_u8DataIndex) == CAN_NORecievedData)
		{
			
		}
		else
		{
			REC_Data.Global_u8Direction 	=  ARR_Recieved_Data[CAN_u8DataIndex][0];
			REC_Data.Global_u8Speed 			=  ARR_Recieved_Data[CAN_u8DataIndex][1];
			REC_Data.Global_u8BrakeStatus =  ARR_Recieved_Data[CAN_u8DataIndex][2];
		}
		vTaskDelay(500);
	}
}

void Button_StateT(void* pvparam)
{
	GPIO_configurationsType LED = {GPIO_PORTA_ID,GPIO_PIN05_ID,GPIO_OUTPUT_PUSH_PULL_MODE,GPIO_MEDIUM_SPEED};
	GPIO_configurationsType BUT = {GPIO_PORTC_ID,GPIO_PIN13_ID,GPIO_INPUT_PULLUP_MODE,GPIO_MEDIUM_SPEED};

	GPIO_configurePin(&LED);
	GPIO_configurePin(&BUT);
	GPIO_pinStatusType state;
	static u16 counter = 0;
	while(1)
	{
		GPIO_readPin(GPIO_PORTC_ID,GPIO_PIN13_ID,&state);
		if (counter == 15)
		{
			GPIO_writePin(GPIO_PORTA_ID,GPIO_PIN05_ID,GPIO_HIGH_PIN);
			/*SWITCH TO MANAGEMENT MODE*/
//			vTaskSuspendAll();
//			MNVIC_VSystemReset();
		  /***************************/
			EEPROM_READ_STRING(EEPROM_START_ADDRESS,Global_readEEPROM,NUM_OF_CHECK_LOGS);
			counter = 0;
		}
		if (state == GPIO_LOW_PIN)
		{
			counter++;
		}
		else
		{
			counter = 0;
		}
		vTaskDelay(200);
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
	EEPROM_init();
	
	/************* TASKS CREATION ***************/
	xTaskHandle Motor_SetDirectionH;
	xTaskCreate(Motor_SetDirectionT,NULL,configMINIMAL_STACK_SIZE,NULL,1,&Motor_SetDirectionH);
	
	xTaskHandle Button_StateH;
	xTaskCreate(Button_StateT,NULL,configMINIMAL_STACK_SIZE,NULL,1,&Button_StateH);
	
	xTaskHandle CAN_SendDataH;
	xTaskCreate(CAN_SendDataT,NULL,configMINIMAL_STACK_SIZE,NULL,1,&CAN_SendDataH);
	
	xTaskHandle CAN_RevieveDataH;
	xTaskCreate(CAN_RevieveDataT,NULL,configMINIMAL_STACK_SIZE,NULL,1,&CAN_RevieveDataH);
	
	
	xTaskHandle US_GetDistanceH;
	xTaskCreate(US_GetDistanceT,NULL,configMINIMAL_STACK_SIZE,NULL,4,&US_GetDistanceH);
	
	xTaskHandle EEPROM_WriteLogsTH;
	xTaskCreate(EEPROM_WriteLogsT,NULL,configMINIMAL_STACK_SIZE,NULL,1,&EEPROM_WriteLogsTH);

	vTaskStartScheduler();
}

