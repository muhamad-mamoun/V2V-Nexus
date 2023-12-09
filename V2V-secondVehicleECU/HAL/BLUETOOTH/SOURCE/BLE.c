/***********************************************

Description : Header FILE FOR BLE DRIVER                    

Date        : 21-11-2023

Author      : Mohamed Khaled

***********************************************/
/*************************************||INCLUDES||*****************************************/
#include "std_types.h"
#include "common_macros.h"
#include "DIO_interface.h"
#include "RCC_interface.h"
#include "NVIC_interface.h"
#include "USART_interface.h"
#include "BLE.h"
#include "BLE_Cfg.h"
#include "BLE_Prv.h"

/*
 *Function Name : HBLE_VInit 
 *Description   : Initialization Function Define UART Call Back Function 
 *Parameters    : None 
 *Return Type   : None
 */
void HBLE_VInit(void)
{
	MRCC_voidPerClock_State(APB2 ,IOPA_PERIPHERAL ,PClock_enable );
	MRCC_voidPerClock_State(APB2 ,USART1_PERIPHERAL ,PClock_enable );
	MGPIO_voidSetPinDirection(GPIOA_driver , PIN9  ,  OUTPUT_SPEED_2MHZ_AFPP);
	MGPIO_voidSetPinDirection(GPIOA_driver , PIN10  , INPUT_FLOATING);
	MNVIC_voidEnableInterrupt(USART11);
	MUSART_voidInit(USART1_Driver);
}

/*
 *Function Name : HBLE_VGetKey
 *Description   : Function to return the Desired Key 
 *Parameters    : pointer to carry the value of BLE Key
 *Return Type   : None
 */
void HBLE_VGetKey(pu8 ADD_pu8Key)
{
	MUSART_u8GetRecievedValue(USART1_Driver,ADD_pu8Key);
}