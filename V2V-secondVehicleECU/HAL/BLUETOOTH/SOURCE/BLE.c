/***********************************************

Description : Header FILE FOR BLE DRIVER                    

Date        : 21-11-2023

Author      : Mohamed Khaled

***********************************************/
/*************************************||INCLUDES||*****************************************/
#include"../../../OTHERS/std_types.h"
#include"../../../OTHERS/common_macros.h"
#include "../../../MCAL/RCC/INCLUDES/RCC_interface.h"
#include "../../../MCAL/NVIC/INCLUDES/NVIC_interface.h"
#include "../../../MCAL/UART/INCLUDES/USART_interface.h"
#include "../INCLUDES/BLE.h"
#include "../INCLUDES/BLE_Cfg.h"
#include "../INCLUDES/BLE_Prv.h"

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
	MNVIC_voidEnableInterrupt(USART11);
	MUSART_voidInit(USART1);
}

/*
 *Function Name : HBLE_VGetKey
 *Description   : Function to return the Desired Key 
 *Parameters    : pointer to carry the value of BLE Key
 *Return Type   : None
 */
void HBLE_VGetKey(pu8 ADD_pu8Key)
{
	MUSART_u8GetRecievedValue(USART1,ADD_pu8Key);
}