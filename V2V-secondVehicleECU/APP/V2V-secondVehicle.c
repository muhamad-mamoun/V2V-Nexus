/*
=======================================================================================================================
Author       : Mamoun & besho
Module       : 
File Name    : V2V-coreECU.c
Date Created : Nov 15, 2023
Description  : 
=======================================================================================================================
*/


/*=====================================================================================================================
                                               < Includes >
=====================================================================================================================*/
/*FreeRTOS*/
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"

#include "common_macros.h"
#include "std_types.h"


#include "RCC_interface.h"
#include "NVIC_interface.h"
#include "DIO_interface.h"
#include "USART_interface.h"
#include "BLE.h"
#include "motor.h"


/*=====================================================================================================================
                                           < Global Variables >
=====================================================================================================================*/

u8 Global_u8Direction = 0xFF;

/*=====================================================================================================================
                                      < Private Functions Prototypes >
=====================================================================================================================*/

void Motor_SetDirectionT(void* pvParameter);

void US_GetDistanceT(void* pvparam);

/*=====================================================================================================================
                                          < Functions Definitions >
=====================================================================================================================*/

/*=====================================================================================================================
 * [Function Name] : 
 * [Description]   : 
 * [Arguments]     : <>      -> 
 *                   <>      -> 
 * [return]        : The function returns void.
 ====================================================================================================================*/
int main(void)
{
		MRCC_voidInit();
		HBLE_VInit();
		xTaskHandle Motor_SetDirectionH;
		xTaskCreate(Motor_SetDirectionT,NULL,configMINIMAL_STACK_SIZE,NULL,1,&Motor_SetDirectionH);
		vTaskStartScheduler();
    while(1)
    {
			
    }
}

void Motor_SetDirectionT(void* pvParameter)
{
	while(1)
	{
			HBLE_VGetKey(&Global_u8Direction) ;
			vTaskDelay(50);
	}
}

