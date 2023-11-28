#include "Can.h"

//u8 Data[2]={0xFF,0};

int main(void)
{
	u8 x=0;
	u32 Data1;
	CAN_ConfigType Config={FIFO_NOTLOCKED,Automatically_Retransmit,Automatic_WakeUP_Enable,Automatic_BusOff_Enable,Time_Trigger_Disable,CAN_Debug_Working,Request_Order, 0x00050000};
	CAN_enuInit(&Config);
	FilterConfig FConfig={FilterNumber0,_1R,ListMode,Single,FIFO_0,0x070,0};
	CAN_enuCreateFilter(&FConfig);
	//CAN_Transmit TConfig={STD_ID,DataFram,_1Byte_Data,0x070,Data};

	while(1)
	{
		//	CAN_enuTransmit(&TConfig);
//Delay(1000000);

		if(		CAN_enuRecieve(&x)==CAN_NORecievedData)
	{
			
	}
	else
		{
			Data1=ARR_Recieved_Data[x][0];
			
		}
	}
}


