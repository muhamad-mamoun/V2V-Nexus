/*
=======================================================================================================================
Author       : Mamoun & Besho
Module       : 
File Name    : V2V-secondVehicle.c
Date Created : Nov 15, 2023
Description  : 
=======================================================================================================================
*/


/*=====================================================================================================================
                                               < Includes >
=====================================================================================================================*/

#include "std_types.h"
#include "common_macros.h"
#include "V2V-secondVehicle.h"
#include "RCC_interface.h"
#include "nrf24l01.h"
#include "motor.h"
#include "BLE.h"

/*=====================================================================================================================
                                           < Global Variables >
=====================================================================================================================*/

V2V_vehicleData G_myVehicle = {'S',0,0};
V2V_vehicleData G_secondVehicle = {'S',0,0};

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
	DCmotor_Init();
	NRF24L01_init();
	NRF24L01_switchToReceiverMode(0X20,NRF24L01_DATA_PIPE_0);
	NRF24L01_bufferStatusType LOC_receiverBufferStatus = NRF24L01_BUFFER_EMPTY;
    
	while (1)
	{
		do
		{
			NRF24L01_checkReceiverBuffer(NRF24L01_DATA_PIPE_0,&LOC_receiverBufferStatus);
		}while(LOC_receiverBufferStatus != NRF24L01_BUFFER_NOT_EMPTY);

		NRF24L01_readData((pu8)&G_myVehicle,3);
		MOTOR_setMotor(G_myVehicle.direction,G_myVehicle.speed);
		LOC_receiverBufferStatus = NRF24L01_BUFFER_EMPTY;
		NRF24L01_flushReceiverBuffer();
	}
}