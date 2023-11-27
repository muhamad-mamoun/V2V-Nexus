/*
=======================================================================================================================
Author       : Mamoun
Module       : 
File Name    : V2V-networkECU.c
Date Created : Nov 24, 2023
Description  : 
=======================================================================================================================
*/


/*=====================================================================================================================
                                               < Includes >
=====================================================================================================================*/

#include "std_types.h"
#include "../MCAL/RCC/inc/RCC_interface.h"
#include "../MCAL/SPI/inc/SPI.h"
#include "../MCAL/GPIO/inc/DIO_interface.h"
#include "../MCAL/NVIC/inc/NVIC_interface.h"

/*=====================================================================================================================
                                           < Global Variables >
=====================================================================================================================*/
u8 gl_buff[10]="HELLOSHAR";


/*=====================================================================================================================
                                      < Private Functions Prototypes >
=====================================================================================================================*/



/*=====================================================================================================================
                                          < Functions Definitions >
=====================================================================================================================*/
void cb(void);
void MASTERCFG(void);
void slave_conf(void);
/*=====================================================================================================================
 * [Function Name] : 
 * [Description]   : 
 * [Arguments]     : <>      -> 
 *                   <>      -> 
 * [return]        : The function returns void.
 ====================================================================================================================*/
int main(void)
{
	MASTERCFG();
	int i = 0;
	int y = 0;
	static int x = 0;
	while (1)
	{
		while (gl_buff[i]!='\0')
		{
			for (y=0;y<100000;y++)
		  {
			
		  }
		SPI_voidSendReceieveCharSynch(gl_buff[i++],&y);	
		y=0;
		}
		i=0;
		MGPIO_voidSetPinValue(GPIOC,PIN13,x^=1);
	}
	return 0;
}

void cb(void)
{
	static u8 x = 0;
	static u8 y = 0;
	y++;
	if(y==100)
	{
		MGPIO_voidSetPinValue(GPIOC,PIN13,x^=1);
		y=0;
	}
	
}

void slave_conf(void)
{
	MRCC_voidPerClock_State(APB2 ,IOPA_PERIPHERAL,PClock_enable);
	MRCC_voidPerClock_State(APB2 ,SPI1_PERIPHERAL,PClock_enable);
	MRCC_voidPerClock_State(APB2 ,IOPC_PERIPHERAL,PClock_enable);
	MRCC_voidPerClock_State(APB2 ,AFIO_PERIPHERAL,PClock_enable);
	MGPIO_voidSetPinDirection(GPIOA,PIN7,INPUT_FLOATING);
	MGPIO_voidSetPinDirection(GPIOA,PIN6,OUTPUT_SPEED_10MHZ_AFPP);
	MGPIO_voidSetPinDirection(GPIOA,PIN5,INPUT_FLOATING);
	MGPIO_voidSetPinDirection(GPIOA,PIN4,INPUT_FLOATING);
	MGPIO_voidSetPinDirection(GPIOC,PIN13,OUTPUT_SPEED_10MHZ_PP);
	SPI_voidsetCallBck(cb);
	SPI_voidInit();
	MNVIC_voidEnableInterrupt(SPI11);
}

void MASTERCFG(void)
{
	MRCC_voidPerClock_State(APB2 ,IOPA_PERIPHERAL,PClock_enable);
	//MRCC_voidPerClock_State(APB2 ,AFIO_PERIPHERAL,PClock_enable);
	MRCC_voidPerClock_State(APB2 ,IOPC_PERIPHERAL,PClock_enable);
	MRCC_voidPerClock_State(APB2 ,SPI1_PERIPHERAL,PClock_enable);
	
	MGPIO_voidSetPinDirection(GPIOA,PIN7,OUTPUT_SPEED_10MHZ_AFPP);
	MGPIO_voidSetPinDirection(GPIOA,PIN6,INPUT_FLOATING);
	MGPIO_voidSetPinDirection(GPIOA,PIN5,OUTPUT_SPEED_10MHZ_AFPP);
	MGPIO_voidSetPinDirection(GPIOA,PIN4,OUTPUT_SPEED_10MHZ_PP);
	MGPIO_voidSetPinValue(GPIOA,PIN4,1);
	MGPIO_voidSetPinDirection(GPIOC,PIN13,OUTPUT_SPEED_10MHZ_PP);
	SPI_voidInit();

	
}