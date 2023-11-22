/***********************************************

Description : Header FILE FOR BLE DRIVER                    

Date        : 21-11-2023

Author      : Mohamed Khaled

***********************************************/
/*************************************||INCLUDES||*****************************************/
#include "std_types.h"
#include "BLE.h"
#include "BLE_Cfg.h"
#include "BLE_Prv.h"
#include "gpio.h"
#include "RCC.h"
#include "NVIC.h"
#include "UART_interface.h"


u8 G_Key=NO_REC_KEY;
GPIO_configurationsType UART_PIN_TX = {GPIO_PORTC_ID,GPIO_PIN04_ID,GPIO_ALTERNATE_PUSH_PULL_MODE,GPIO_MEDIUM_SPEED};
GPIO_configurationsType UART_PIN_RX = {GPIO_PORTC_ID,GPIO_PIN05_ID,GPIO_ALTERNATE_PUSH_PULL_MODE,GPIO_MEDIUM_SPEED};
/*
 *Function Name : HBLE_VInit 
 *Description   : Initialization Function Define UART Call Back Function 
 *Parameters    : None 
 *Return Type   : None
 */
 
 MUARTConfig  UART = 
 {
	 OneStart_8Data,
   OV_16 , 
   Parity_Disabled,
	 LSB , 
	 OneStopBit , 
	 9600 , 
	 Interrupt_Enable_RX_Only, 
    	 
 };
 
static void HBLE_VGetChar(u8 Copy_u8Key)
{
	G_Key=Copy_u8Key;
	
}
void HBLE_VInit(void)
{
	RCC_voidEnablePeripheral(AHB_BUS,GPIOC_EN);
	RCC_voidEnablePeripheral(APB2_BUS,USART1_EN);
	GPIO_configurePin(&UART_PIN_TX);
	GPIO_configurePin(&UART_PIN_RX);
	GPIO_setPinFuction(GPIO_PORTC_ID,GPIO_PIN04_ID, GPIO_AF07);
	GPIO_setPinFuction(GPIO_PORTC_ID,GPIO_PIN05_ID, GPIO_AF07);
	MUSART_voidInit(&UART);
	
	//send HBLE_VGetChar to the UART Call Back Function 
	MUSART1_VidSetCallBack(HBLE_VGetChar);
	MNVIC_EnuEnablePerInterrupt(NVIC_REG1,NVIC_REGx_INT5);
}

/*
 *Function Name : HBLE_VGetKey
 *Description   : Function to return the Desired Key 
 *Parameters    : pointer to carry the value of BLE Key
 *Return Type   : None
 */
void HBLE_VGetKey(pu8 ADD_pu8Key)
{
	
	//if the Key has a new value from BLE
	if(G_Key !=NO_REC_KEY)
	{
		switch(G_Key)
		{
			case DESIRED_KEY1:
				*ADD_pu8Key=G_Key;
				break;
			case DESIRED_KEY2:
				*ADD_pu8Key=G_Key;
				break;
			case DESIRED_KEY3:
				*ADD_pu8Key=G_Key;	
			  break;
			case DESIRED_KEY4:
				*ADD_pu8Key=G_Key;
				break;
			case DESIRED_KEY5:
				*ADD_pu8Key=G_Key;
				break;
			case DESIRED_KEY6:
				*ADD_pu8Key=G_Key;
				break;
			case DESIRED_KEY7:
				*ADD_pu8Key=G_Key;
				break;
			case DESIRED_KEY8:
				*ADD_pu8Key=G_Key;
				break;
			default :
				*ADD_pu8Key=NO_REC_KEY;
		}
	  //return G_Key to its initial value 
		G_Key=NO_REC_KEY;
		
	}
	else
	{
		*ADD_pu8Key=NO_REC_KEY;
	}
}


/*
 *Function Name : HBLE_VGetChar
 *Description   : Function to Call when UART Handler Triggered 
 *Parameters    : None 
 *Return Type   : None
 */


