/*=================================================================
													< INCLUDES >
===================================================================*/
/*************FreeRTOS**************/
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"

/*************Utils**************/
#include "common_macros.h"
#include "std_types.h"

/*************MCAL**************/
#include "RCC.h"
#include "gpio.h"
#include "PWM.h"
#include "UART_interface.h"
#include "ICU.h"
#include "Can.h"
#include "gpio_prv.h"
#include "NVIC.h"
#include "ADC.h"

/*************HAL**************/
#include "motor.h"
#include "US.h"
#include "BLE.h"
#include "eeprom.h"



/*=================================================================
													< DEFINES >
===================================================================*/

#define MAX_DISTANCE 50
#define NUM_OF_CHECK_LOGS 3
#define CAN_DataID 	0x200

/************* LOGS *************/
#define TEMP_OK 0x11
#define TEMP_OVERHEAT 0x5A
#define TEMP_NOTRESPONDING 0xFC

#define US_OK 0x12
#define US_NOTRESPONDING 0xFE

#define CAN_OK 0x15
#define CAN_NOTRESPONDING 0xDE

#define TEMP_DATA_INDEX  0
#define US_DATA_INDEX    1
#define CAN_DATA_INDEX   2

#define EEPROM_START_ADDRESS   0x10



/*=================================================================
													< GLOBALS >
===================================================================*/

u8 Global_u8LogsArr[NUM_OF_CHECK_LOGS] = {TEMP_OK,US_OK,CAN_OK};  //ARR to STORE LOGS that sent to EEPROM
u8 Global_readEEPROM[NUM_OF_CHECK_LOGS];  								 //ARR to STORE recieved logs from EEPROM
u8 Global_u8DataArr[3]; 	 															   //ARR FOR CAN DATA
volatile u16 Global_u16Distance; 													 //FOR Ultrasonic
u8 Global_u8ManagmentMode = 0;														 //Initial Management Mode

typedef struct 				//Struct For Data
{
volatile u8 Global_u8Direction;
volatile u8 Global_u8Speed;
volatile u8 Global_u8BrakeStatus;
}Data_t;

Data_t My_Data  = {'S',60,0}; 											//INIT VALS FOR CAR
Data_t REC_Data; 
/*=================================================================
									< Helper Functions PROTOTYPES >
===================================================================*/
void Suspend_MyTasks();
void Resume_MyTasks();
void SYS_INIT();


/*=================================================================
												< TASKS PROTOTYPES >
===================================================================*/
void Motor_SetDirectionT(void* pvParameter); 
void EEPROM_WriteLogsT (void* pvparam);
void US_GetDistanceT(void* pvparam);
void CAN_SendDataT(void* pvparam);
void Button_StateT(void* pvparam);

/*=================================================================
												< TASK HANDLES >
===================================================================*/
xTaskHandle Motor_SetDirectionH;
xTaskHandle Button_StateH;
xTaskHandle CAN_SendDataH;
xTaskHandle US_GetDistanceH;
xTaskHandle EEPROM_WriteLogsTH;
xTaskHandle TEMP_GetTempH;





int main(void)
{	
	/*************INIT******************/	
	SYS_INIT();

	/************* TASKS CREATION ***************/
	xTaskCreate(Motor_SetDirectionT,NULL,configMINIMAL_STACK_SIZE,NULL,1,&Motor_SetDirectionH);

	xTaskCreate(Button_StateT,NULL,configMINIMAL_STACK_SIZE,NULL,1,&Button_StateH);

	xTaskCreate(CAN_SendDataT,NULL,configMINIMAL_STACK_SIZE,NULL,1,&CAN_SendDataH);
	
	xTaskCreate(US_GetDistanceT,NULL,configMINIMAL_STACK_SIZE,NULL,4,&US_GetDistanceH);

	xTaskCreate(EEPROM_WriteLogsT,NULL,configMINIMAL_STACK_SIZE,NULL,1,&EEPROM_WriteLogsTH);

	vTaskStartScheduler();
}






void Suspend_MyTasks()
{
	vTaskSuspend(Motor_SetDirectionH);
	vTaskSuspend(CAN_SendDataH);
	vTaskSuspend(US_GetDistanceH);
	vTaskSuspend(EEPROM_WriteLogsTH);
}
void Resume_MyTasks()
{
	vTaskResume(Motor_SetDirectionH);
	vTaskResume(CAN_SendDataH);
	vTaskResume(US_GetDistanceH);
	vTaskResume(EEPROM_WriteLogsTH);
}
void SYS_INIT()
{
	/********************************** RCC ***********************************/
	RCC_voidEnablePeripheral(AHB_BUS,GPIOA_EN);
	RCC_voidEnablePeripheral(AHB_BUS,GPIOB_EN);
	RCC_voidEnablePeripheral(AHB_BUS,GPIOC_EN);
	RCC_voidEnablePeripheral(AHB_BUS,GPIOD_EN);
	RCC_voidEnablePeripheral(APB1_BUS,TIM2_EN);
	RCC_voidEnablePeripheral(APB1_BUS,TIM3_EN);
	RCC_voidEnablePeripheral(APB1_BUS,TIM4_EN);
	RCC_voidEnablePeripheral(APB2_BUS,USART1_EN);
	RCC_voidEnablePeripheral(APB1_BUS,USART3_EN);
	RCC_voidEnablePeripheral(APB1_BUS,CAN_EN);
	/**************************************************************************/
	
	
	/********************************** CAN ***********************************/
	/**Pins Configuration**/
	GPIO_configurationsType CAN_TX  =  {GPIO_PORTB_ID,GPIO_PIN09_ID,GPIO_ALTERNATE_PUSH_PULL_MODE,GPIO_HIGH_SPEED};
	GPIO_configurationsType CAN_RX  =  {GPIO_PORTB_ID,GPIO_PIN08_ID,GPIO_ALTERNATE_PUSH_PULL_MODE,GPIO_HIGH_SPEED};	
	GPIO_configurePin(&CAN_TX);
	GPIO_configurePin(&CAN_RX);
	GPIO_setPinFuction(GPIO_PORTB_ID,GPIO_PIN09_ID,GPIO_AF09);
	GPIO_setPinFuction(GPIO_PORTB_ID,GPIO_PIN08_ID,GPIO_AF09);
	/**Configuration Struct**/
	CAN_ConfigType BasicCFG;
	BasicCFG.LockedMode = FIFO_NOTLOCKED;
	BasicCFG.Retransmission = Automatically_Retransmit;
	BasicCFG.WakeUp = Automatic_WakeUP_Enable;
	BasicCFG.BussOffManag = Automatic_BusOff_Enable;
	BasicCFG.TimeTriggered = Time_Trigger_Disable;
	BasicCFG.DebugFreeze = CAN_Debug_Working;
	BasicCFG.FifoPriority = Request_Order;
	BasicCFG.BuadRate_prescaler = 0x00070000;
	/**Filter Struct**/
	FilterConfig R_Filter = {FilterNumber0,_1R,ListMode,Single,FIFO_0,0x100,0};
	CAN_enuCreateFilter(&R_Filter);
	/**CAN Init**/
	CAN_enuInit(&BasicCFG);
	/****************************************************************************/
	
	
	/********************************** HAL INITS *******************************/
	DCmotor_Init();
	US_voidInit();
	HBLE_VInit();
	EEPROM_init();
	/**************************************************************************/
}
	

/*||||||||||||||||||||||||||||||||||| MOTOR TASK |||||||||||||||||||||||||||||||||||||||||||*/
void Motor_SetDirectionT(void* pvParameter)
{
	vTaskDelay(500);
	u8 Local_u8RecData = 0;
	while(1)
	{
		HBLE_VGetKey(&Local_u8RecData);
		if (Local_u8RecData == '-' && My_Data.Global_u8Speed != 0)
		{
				My_Data.Global_u8Speed-=20;
		}
		else if (Local_u8RecData == '+' && My_Data.Global_u8Speed != 100)
		{
				My_Data.Global_u8Speed+=20;
		}
		else if (Local_u8RecData != NO_REC_KEY)
		{
			My_Data.Global_u8Direction = Local_u8RecData;
		}
						/*MOTORS SET*/
		if (REC_Data.Global_u8BrakeStatus != My_Data.Global_u8BrakeStatus || REC_Data.Global_u8Direction != My_Data.Global_u8Direction
			   || REC_Data.Global_u8Speed != My_Data.Global_u8Speed)
		{
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
			DCmotor_rightMove(45);
			break;
		
		case 'L':
			DCmotor_leftMove(45);
			break;
		
		case 'S':
			DCmotor_stop();
			My_Data.Global_u8BrakeStatus = 1;
			break;
		}
    REC_Data = My_Data;
			
		}
		vTaskDelay(100);
	}
}

/*||||||||||||||||||||||||||||||||||| EEPROM WRITE TASK |||||||||||||||||||||||||||||||||||||||||||*/

void EEPROM_WriteLogsT (void* pvparam) 
{
	
	vTaskDelay(500);
	while (1)
	{
		EEPROM_WRITE_STRING(EEPROM_START_ADDRESS,Global_u8LogsArr,NUM_OF_CHECK_LOGS);
		vTaskDelay(500);
	}
}
/*||||||||||||||||||||||||||||||||||| ULTRASONIC TASK |||||||||||||||||||||||||||||||||||||||||||*/

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
/*||||||||||||||||||||||||||||||||||| CAN SEND TASK |||||||||||||||||||||||||||||||||||||||||||*/

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
/*||||||||||||||||||||||||||||||||||| Management Switch TASK |||||||||||||||||||||||||||||||||||||||||||*/

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
			if (Global_u8ManagmentMode == 0)
			{
					/*SWITCH TO MANAGEMENT MODE*/
				Global_u8ManagmentMode = 1;
				GPIO_writePin(GPIO_PORTA_ID,GPIO_PIN05_ID,GPIO_HIGH_PIN);
				Suspend_MyTasks();
				EEPROM_READ_STRING(EEPROM_START_ADDRESS,Global_readEEPROM,NUM_OF_CHECK_LOGS);
				
				HBLE_VSendReport("WELCOME TO MANAGMENT MODE");
                
				HBLE_VSendReport("\rMOTOR TEMP STATUS : ");
				if (Global_readEEPROM[TEMP_DATA_INDEX] == TEMP_OVERHEAT)
				{
					HBLE_VSendReport("TEMP_OVERHEAT ");
				}
				else if (Global_readEEPROM[TEMP_DATA_INDEX] == TEMP_NOTRESPONDING)
				{
					HBLE_VSendReport("SENSOR_NOTRESPONDING");
				}
				else
				{
					HBLE_VSendReport("NORMAL");
				}
				
				
				HBLE_VSendReport("\rULTRASONIC STATUS : ");
				if (Global_readEEPROM[US_DATA_INDEX] == US_NOTRESPONDING)
				{
					HBLE_VSendReport("US_NOTRESPONDING");
				}
				else
				{
					HBLE_VSendReport("NORMAL");
				}
				
				
				HBLE_VSendReport("\rCAN STATUS : ");
				if (Global_readEEPROM[CAN_DATA_INDEX] == CAN_NOTRESPONDING)
				{
					HBLE_VSendReport("CAN_NOTRESPONDING");
				}
				else
				{
					HBLE_VSendReport("NORMAL");
				}	

					
			}	
			else
			{
				Global_u8ManagmentMode = 0;
				GPIO_writePin(GPIO_PORTA_ID,GPIO_PIN05_ID,GPIO_LOW_PIN);
				Resume_MyTasks();
			}
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




