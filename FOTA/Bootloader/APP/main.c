#include <stdint.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


#include "std_types.h"
#include "common_macros.h"
#include "FPEC_interface.h"
#include "UART_interface.h"
#include "STK_interface.h"
#include "gpio.h"
#include "RCC.h"

#define SCB_VTOR   *((volatile u32*)0xE000ED08)

void Parser_voidParseRecord(u8* Copy_u8BufData);

volatile u8  u8RecBuffer[100]   ;
volatile u8  u8RecCounter    = 0;
volatile u8  u8TimeOutFlag   = 0;
volatile u16 u16TimerCounter = 0;
volatile u8  u8BLWriteReq    = 1;
typedef void (*Function_t)(void);
Function_t addr_to_call = 0;


/* This Function Jumps TO The user Application */
/* In Our Code It will Wait 15 Seconds -> If Nothing Receieved It Will Jump To The User Application */
void BL_jumpFunc(void)
{
	/*Configure The Vector Table Location*/
	SCB_VTOR = 0x08001800;

   	/*Casting The Address To Pointer To Function */
   	/*Then Add The * TO Get What In This Address----> */
	addr_to_call = *(Function_t*)(0x08001804);
	addr_to_call();
}

void BL_initSystem(void)
{
	/* UART Configurations. */
	MUARTConfig UARTconfigurations = {USART0_ID,OneStart_8Data,OV_16,Parity_Disabled,LSB,OneStopBit,9600,Interrupt_Disable};

	/* GPIO Configurations. */
	GPIO_configurationsType UART_PIN_TX = {GPIO_PORTC_ID,GPIO_PIN04_ID,GPIO_ALTERNATE_PUSH_PULL_MODE,GPIO_MEDIUM_SPEED};
	GPIO_configurationsType UART_PIN_RX = {GPIO_PORTC_ID,GPIO_PIN05_ID,GPIO_ALTERNATE_PUSH_PULL_MODE,GPIO_MEDIUM_SPEED};
	GPIO_configurationsType G_debuggingLED = {GPIO_PORTA_ID,GPIO_PIN05_ID,GPIO_OUTPUT_PUSH_PULL_MODE,GPIO_MEDIUM_SPEED};

	/* Enable peripherals clock. */
	RCC_voidInitSYSCLK();
    RCC_voidEnablePeripheral(APB2_BUS,USART1_EN);    		/*USART 1      */
    RCC_voidEnablePeripheral(APB1_BUS,USART3_EN);    		/*USART 3      */
    RCC_voidEnablePeripheral(AHB_BUS,GPIOA_EN); 			/*Enable GPIOA */
    RCC_voidEnablePeripheral(AHB_BUS,GPIOC_EN); 			/*Enable GPIOA */
    RCC_voidEnablePeripheral(AHB_BUS,4);   	    			/*Enable FPEC  */

	/* For debugging. */
	GPIO_configurePin(&G_debuggingLED);
	GPIO_writePin(GPIO_PORTA_ID,GPIO_PIN05_ID,GPIO_HIGH_PIN);

	/* UART pins configurations. */
    GPIO_setPinFuction(GPIO_PORTC_ID,GPIO_PIN04_ID,GPIO_AF07);
    GPIO_setPinFuction(GPIO_PORTC_ID,GPIO_PIN05_ID,GPIO_AF07);
    GPIO_configurePin(&UART_PIN_TX);
    GPIO_configurePin(&UART_PIN_RX);
	
	MUSART_voidInit(&UARTconfigurations);

	MSTK_voidInit();
	MSTK_voidSetIntervalSingle(15000000,BL_jumpFunc);
}

int main(void)
{
	u8 Local_u8RecStatus;

	BL_initSystem();

	MUSART1_VidSendCharSync(USART0_ID,'S');

	while(u8TimeOutFlag == 0)
	{
		Local_u8RecStatus = MUSART1_u8RecCharSynch(USART0_ID,&(u8RecBuffer[u8RecCounter]));
		if (Local_u8RecStatus == 1)
		{
			MSTK_voidStopInterval();

			if(u8RecBuffer[u8RecCounter] == '\n')
			{
				if (u8BLWriteReq == 1)
				{
					FPEC_voidEraseAppArea();
					u8BLWriteReq = 0;
				}

				/* Parse */
				Parser_voidParseRecord(u8RecBuffer);
				MUSART1_VidSendStringSynch(USART0_ID,"ok");
				u8RecCounter = 0;
			}

			else
			{
				u8RecCounter ++ ;
			}

			MSTK_voidSetIntervalSingle(15000000,BL_jumpFunc);
		}

		else
		{
			/* Do Nothing. */
		}
	}
}
