#include "common_macros.h"
#include "std_types.h"

#include "RCC_interface.h" 
#include "DIO_interface.h"
#include "Can.h"
#include "SPI.h"
#include "nrf24l01.h"

#define Network_CH 0x20

u8 CAN_DataIndex;
u8 Global_NetworkDataArr[3];;


void CANSys_INIT()
{
		MRCC_voidPerClock_State(APB1,CAN_PERIPHERAL,PClock_enable);
		MRCC_voidPerClock_State(APB2,IOPA_PERIPHERAL,PClock_enable);
	
		MGPIO_voidSetPinDirection(GPIOA,PIN12,OUTPUT_SPEED_50MHZ_AFPP); //TX
		MGPIO_voidSetPinDirection(GPIOA,PIN11,INPUT_FLOATING);  //RX
	
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
}

int main()
{
	
	MRCC_voidInit();
 
	/**LED for Testing**/
	MRCC_voidPerClock_State(APB2,IOPC_PERIPHERAL,PClock_enable);
	MGPIO_voidSetPinDirection(GPIOC,PIN13,OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinValue(GPIOC,PIN13,GPIO_HIGH);
	/****************/
	
	NRF24L01_init();
	CANSys_INIT();
	NRF24L01_switchToTransmitterMode(Network_CH);
	
	while(1)
	{
		if(CAN_enuRecieve(&CAN_DataIndex) == CAN_NORecievedData)
		{
			
		}
		else
		{
			Global_NetworkDataArr[0] = ARR_Recieved_Data[CAN_DataIndex][0];
			Global_NetworkDataArr[1] = ARR_Recieved_Data[CAN_DataIndex][1];
			Global_NetworkDataArr[2] = ARR_Recieved_Data[CAN_DataIndex][2];
			NRF24L01_sendData(Global_NetworkDataArr,3);
			MGPIO_voidTogglePin(GPIOC,PIN13);
		}
     
   //		
	}
}


