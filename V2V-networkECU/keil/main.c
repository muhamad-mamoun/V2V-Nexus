
#include "common_macros.h"
#include "std_types.h"

#include "RCC_interface.h" 
#include "DIO_interface.h"
#include "Can.h"
#include "SPI.h"
#include "nrf24l01.h"

u8 arr[20] = {0};
u8 x = 0;
u8 Data1 = 0;
u8 Data2 = 0;
u8 Data3 = 0;

int main()
{
	/***RCC Init***/
	MRCC_voidInit();
	MRCC_voidPerClock_State(APB1,CAN_PERIPHERAL,PClock_enable);
	//MRCC_voidPerClock_State(APB2,AFIO_PERIPHERAL,PClock_enable);

	MRCC_voidPerClock_State(APB2,IOPA_PERIPHERAL,PClock_enable);
	MRCC_voidPerClock_State(APB2,IOPC_PERIPHERAL,PClock_enable);


	//SPI 
	
	/***GPIO Init***/

	MGPIO_voidSetPinDirection(GPIOA,PIN12,OUTPUT_SPEED_50MHZ_AFPP); //TX
	MGPIO_voidSetPinDirection(GPIOA,PIN11,INPUT_FLOATING);  //RX
	
	MGPIO_voidSetPinDirection(GPIOC,PIN13,OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinValue(GPIOC,PIN13,GPIO_HIGH);

	/***CAN Init***/
	CAN_ConfigType BasicCFG;
	BasicCFG.LockedMode = FIFO_NOTLOCKED;
	BasicCFG.Retransmission = Automatically_Retransmit;
	BasicCFG.WakeUp = Automatic_WakeUP_Enable;
	BasicCFG.BussOffManag = Automatic_BusOff_Enable;
	BasicCFG.TimeTriggered = Time_Trigger_Disable;
	BasicCFG.DebugFreeze = CAN_Debug_Working;
	BasicCFG.FifoPriority = Message_ID;
	BasicCFG.BuadRate_prescaler = 0x00070000;
	CAN_enuInit(&BasicCFG);
	
	FilterConfig R_Filter = {FilterNumber0,_1R,ListMode,Single,FIFO_0,0x200,0};
	CAN_enuCreateFilter(&R_Filter);
	/***CAN Recieve***/
	
	/***SPI Init***/
	/***NRF Init***/
	/***NRF Send**/
	while(1)
	{
		if(CAN_enuRecieve(&x) == CAN_NORecievedData)
		{
			
		}
		else
		{
			Data1 = ARR_Recieved_Data[x][0];
			Data2 = ARR_Recieved_Data[x][1];
			Data3 = ARR_Recieved_Data[x][2];
			MGPIO_voidSetPinValue(GPIOC,PIN13,GPIO_LOW);
		}	
	}
}



