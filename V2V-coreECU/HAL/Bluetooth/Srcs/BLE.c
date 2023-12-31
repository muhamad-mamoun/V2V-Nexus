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

GPIO_configurationsType UART_PIN_TX1 = {GPIO_PORTB_ID,GPIO_PIN10_ID,GPIO_ALTERNATE_PUSH_PULL_MODE,GPIO_MEDIUM_SPEED};
GPIO_configurationsType UART_PIN_RX1 = {GPIO_PORTB_ID,GPIO_PIN11_ID,GPIO_ALTERNATE_PUSH_PULL_MODE,GPIO_MEDIUM_SPEED};
/*
 *Function Name : HBLE_VInit 
 *Description   : Initialization Function Define UART Call Back Function 
 *Parameters    : None 
 *Return Type   : None
 */
 
 MUARTConfig  UART = 
 {
	 FALSE,
	 OneStart_8Data,
   OV_16 , 
   Parity_Disabled,
	 LSB , 
	 OneStopBit , 
	 9600 , 
	 Interrupt_Enable_RX_Only, 
    	 
 };
 
 MUARTConfig  UART1 = 
 {
	 2,
	 OneStart_8Data,
   OV_16 , 
   Parity_Disabled,
	 LSB , 
	 OneStopBit , 
	 9600 , 
   Interrupt_Disable, 
    	 
 };
 
static void HBLE_VGetChar(u32 Copy_u8Key)
{
	G_Key=Copy_u8Key;
	
}
void HBLE_VInit(void)
{
	GPIO_configurePin(&UART_PIN_TX);
	GPIO_configurePin(&UART_PIN_RX);
	GPIO_setPinFuction(GPIO_PORTC_ID,GPIO_PIN04_ID, GPIO_AF07);
	GPIO_setPinFuction(GPIO_PORTC_ID,GPIO_PIN05_ID, GPIO_AF07);
	GPIO_configurePin(&UART_PIN_TX1);
	GPIO_configurePin(&UART_PIN_RX1);
	GPIO_setPinFuction(GPIO_PORTB_ID,GPIO_PIN10_ID, GPIO_AF07);
	GPIO_setPinFuction(GPIO_PORTB_ID,GPIO_PIN11_ID, GPIO_AF07);
	MUSART_voidInit(&UART);
	MUSART_voidInit(&UART1);
	
	//send HBLE_VGetChar to the UART Call Back Function 
	MUSART1_VidSetCallBack(FALSE,HBLE_VGetChar);
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
		
	  //return G_Key to its initial value 
		*ADD_pu8Key=G_Key;
		G_Key = NO_REC_KEY;
		
	}
	else
	{
		*ADD_pu8Key=NO_REC_KEY;
	}
}




void HBLE_VSendReport(pu8 records)
{
	MUSART1_VidSendStringSynch (2, records);
}


