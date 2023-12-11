#include "common_macros.h"
#include "std_types.h"

#include "RCC_interface.h" 
#include "DIO_interface.h"
#include "SPI.h"
#include "nrf24l01.h"

u8 data[3] = {0,0,0};
int main()
{
	MRCC_voidInit();
 
	/**LED for Testing**/
	MRCC_voidPerClock_State(APB2,IOPC_PERIPHERAL,PClock_enable);
	MGPIO_voidSetPinDirection(GPIOC,PIN13,OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinValue(GPIOC,PIN13,GPIO_HIGH);
	/****************/
	
	NRF24L01_init();
	NRF24L01_switchToReceiverMode(0x20,NRF24L01_DATA_PIPE_0);
	NRF24L01_bufferStatusType x;
	while (1)
	{
		NRF24L01_checkReceiverBuffer(NRF24L01_DATA_PIPE_0,&x);
        
		while(x == NRF24L01_BUFFER_EMPTY)
		{
			NRF24L01_checkReceiverBuffer(NRF24L01_DATA_PIPE_0,&x);
		}
		NRF24L01_readData(data,3);
		NRF24L01_flushReceiverBuffer();
		MGPIO_voidTogglePin(GPIOC,PIN13);
	}
	
	
	return 0;
}