/*
 * USART_program.c
 *
 *  Created on: december 26, 2022
 *      Author: beshoy
 */

#include "std_types.h"
#include "common_macros.h"
#include "DIO_interface.h"
#include "RCC_interface.h"
#include "USART_interface.h"
#include "USART_config.h"
#include "USART_private.h"

u8 GlobalUSART1_u8RecievedValue[BUFFER_SIZE];
s16 GlobalUSART1_s16RecievedFront=-1;
s16 GlobalUSART1_s16RecievedRear=-1;

u8 GlobalUSART2_u8RecievedValue[BUFFER_SIZE];
s16 GlobalUSART2_s16RecievedFront=-1;
s16 GlobalUSART2_s16RecievedRear=-1;

u8 GlobalUSART3_u8RecievedValue[BUFFER_SIZE];
s16 GlobalUSART3_s16RecievedFront=-1;
s16 GlobalUSART3_s16RecievedRear=-1;

static void (* USART1_CallBack)   (u8 data)=PTR_NULL;

void MUSART_voidInit(USART_T USART_NUM)
{
	/*	Baudrate 	9600					*/
	USART[USART_NUM] -> BRR = /*0x341;*/ MUSART_voidSetBaudrateRegister(Fclock, BUADRATE);
	/*	UART EN , TX EN , RX EN 			*/
	SET_BIT((USART[USART_NUM] -> CR[0]),RE);
	SET_BIT((USART[USART_NUM] -> CR[0]),TE);
	
	USART[USART_NUM] -> SR = 0;
	SET_BIT((USART[USART_NUM] -> CR[0]),RXNIE);
	MUSART_voidEnableUSART_RecieveInterrupt(USART_NUM);
	if(USART_NUM == USART1_Driver)
	{
		MGPIO_voidSetPinDirection(GPIOA_driver , PIN9  , OUTPUT_SPEED_2MHZ_AFPP);
		MGPIO_voidSetPinDirection(GPIOA_driver , PIN10  , INPUT_FLOATING);
	}
	else if (USART_NUM == USART2_Driver)
	{
		MRCC_voidPerClock_State(APB1 ,USART2_PERIPHERAL ,PClock_enable );
		MGPIO_voidSetPinDirection(GPIOA_driver , PIN2  , OUTPUT_SPEED_2MHZ_AFPP);
		MGPIO_voidSetPinDirection(GPIOA_driver , PIN3  , INPUT_FLOATING);
	}
	else if(USART_NUM == USART3_Driver)
	{
		MRCC_voidPerClock_State(APB1 ,USART3_PERIPHERAL ,PClock_enable );
		MGPIO_voidSetPinDirection(GPIOB_driver , PIN10  , OUTPUT_SPEED_2MHZ_AFPP);
		MGPIO_voidSetPinDirection(GPIOB_driver , PIN11  , INPUT_FLOATING);
	}
    SET_BIT((USART[USART_NUM] -> CR[0]),UE);
    //USART[0]->DR = 'F';
}
u32 MUSART_voidSetBaudrateRegister(u32 Copy_u32FClock, u32 Copy_u32Baudrate)
{
	u32 Local_u32mentissaa;
	u32 Local_u32DivFrac;
	u32 Local_u32BRRreturn;
	f32 Local_F32mentissaa;
	f32 Local_f32DivFrac;
	
	Local_u32mentissaa=Copy_u32FClock/(Copy_u32Baudrate*16);
	Local_F32mentissaa=Copy_u32FClock/(Copy_u32Baudrate*16);
	Local_u32DivFrac=(Local_u32mentissaa-Local_F32mentissaa)*16;
	Local_f32DivFrac=(Local_u32mentissaa-Local_F32mentissaa)*16;
	if(Local_f32DivFrac>15.5)
	{
		Local_u32mentissaa++;
		Local_u32DivFrac=0;
	}
	else
	{
		if((Local_f32DivFrac-Local_u32DivFrac)> 0.5 )
		{
			Local_u32DivFrac++;
		}
		else
		{/*don't do anything*/}
	}
	Local_u32BRRreturn=(Local_u32mentissaa<<4) | (Local_u32DivFrac);
	return Local_u32BRRreturn;
}
void MUSART_voidTransmitCharacter(USART_T USART_NUM, u8 Copy_u8Character)
{
	u32 TimeOut = 0;
	while(GET_BIT(USART[USART_NUM]->SR,TXE) == 0 && TimeOut<10000000)
	{	
		TimeOut++;
	}
	if(TimeOut<10000000)
	{
		USART[USART_NUM]->DR = Copy_u8Character;
	}
	else
	{
		
	}
}
void MUSART_u8RecieveCharacter(USART_T USART_NUM, u8 *Ptr_u8RecievedChar)
{
	u32 TimeOut = 0;
	while(GET_BIT(USART[USART_NUM]->SR,RXNE) == 0 && TimeOut<10000000)
	{	
		TimeOut++;
	}
	if(TimeOut<10000000)
	{
		*Ptr_u8RecievedChar = USART[USART_NUM]->DR ;
	}
	else
	{
		*Ptr_u8RecievedChar = 255;
	}
}

/*void MUSART_voidTransmitstring(USART_T USART_NUM, u8 arr[])
{
	u8 i = 0;
	while(arr[i] != '\0')
	{
		USART[USART_NUM] -> DR = arr[i];
		while((GET_BIT(USART[USART_NUM] -> SR , TC))== 0);
		i++;
	}
	USART[USART_NUM] -> DR = '\0';
	while(GET_BIT(USART[USART_NUM]->SR,TXE) == 0 );

}*/
void MUSART_SetCallBack(void (*PTR)(u8 data))
{
	USART1_CallBack=PTR;
}
void MUSART_voidTransmitstring(USART_T USART_NUM, u8 arr[])
{
	    int i=0;
		while(arr[i] != '\0')
		{
			USART[USART_NUM] -> DR = arr[i];
			while((GET_BIT(USART[USART_NUM] -> SR , TC))== 0);
			i++;
		}
		USART[USART_NUM] -> DR = '\0';
		while(GET_BIT(USART[USART_NUM]->SR,TXE) == 0 );
}
void MUSART_u8GetRecievedValue(USART_T USART_NUM, u8 *Ptr_u8RecievedChar)
{
	if(MUSART_u8IsRecieveBufferAvailable(USART_NUM)>0)
	{
	if(USART_NUM == USART1_Driver)
	{
		GlobalUSART1_s16RecievedRear=(GlobalUSART1_s16RecievedRear+1)%BUFFER_SIZE;
		*Ptr_u8RecievedChar = GlobalUSART1_u8RecievedValue[GlobalUSART1_s16RecievedRear];
		if(GlobalUSART1_s16RecievedFront == GlobalUSART1_s16RecievedRear)
		{
			GlobalUSART1_s16RecievedFront=-1;
			GlobalUSART1_s16RecievedRear=-1;
		}
	}
	else if(USART_NUM == USART2_Driver)
	{
		GlobalUSART2_s16RecievedRear=(GlobalUSART2_s16RecievedRear+1)%BUFFER_SIZE;
		*Ptr_u8RecievedChar = GlobalUSART2_u8RecievedValue[GlobalUSART2_s16RecievedRear];
		if(GlobalUSART2_s16RecievedFront == GlobalUSART2_s16RecievedRear)
		{
			GlobalUSART2_s16RecievedFront=-1;
			GlobalUSART2_s16RecievedRear=-1;
		}
	}
	else if(USART_NUM == USART3_Driver)
	{
		GlobalUSART3_s16RecievedRear=(GlobalUSART3_s16RecievedRear+1)%BUFFER_SIZE;
		*Ptr_u8RecievedChar = GlobalUSART3_u8RecievedValue[GlobalUSART3_s16RecievedRear];
		if(GlobalUSART3_s16RecievedFront == GlobalUSART3_s16RecievedRear)
		{
			GlobalUSART3_s16RecievedFront=-1;
			GlobalUSART3_s16RecievedRear=-1;
		}
	}
	}
	else 
	{
		*Ptr_u8RecievedChar = 0XFF;
	}
}

u16 MUSART_u8IsRecieveBufferAvailable(USART_T USART_NUM)
{
	u16 Buffer_count;
	if(USART_NUM == USART1_Driver)
	{
		if(GlobalUSART1_s16RecievedFront>GlobalUSART1_s16RecievedRear)
		{
			Buffer_count=GlobalUSART1_s16RecievedFront-GlobalUSART1_s16RecievedRear;
		}
		else if(GlobalUSART1_s16RecievedFront<GlobalUSART1_s16RecievedRear)
		{
			Buffer_count = (BUFFER_SIZE - GlobalUSART1_s16RecievedRear)+ GlobalUSART1_s16RecievedFront;
		}
		else if (GlobalUSART1_s16RecievedFront== -1 && GlobalUSART1_s16RecievedRear == -1)
		{
			Buffer_count=0;
		}
		else 
		{
			Buffer_count = BUFFER_SIZE;
		}
	}
	else if(USART_NUM == USART2_Driver)
	{
		if(GlobalUSART2_s16RecievedFront>GlobalUSART2_s16RecievedRear)
		{
			Buffer_count=GlobalUSART2_s16RecievedFront-GlobalUSART2_s16RecievedRear;
		}
		else if(GlobalUSART2_s16RecievedFront<GlobalUSART2_s16RecievedRear)
		{
			Buffer_count = (BUFFER_SIZE - GlobalUSART2_s16RecievedRear)+ GlobalUSART2_s16RecievedFront;
		}
		else if (GlobalUSART2_s16RecievedFront== -1 && GlobalUSART2_s16RecievedRear == -1)
		{
			Buffer_count=0;
		}
		else 
		{
			Buffer_count = BUFFER_SIZE;
		}
	}
	else if(USART_NUM == USART3_Driver)
	{
		if(GlobalUSART3_s16RecievedFront>GlobalUSART3_s16RecievedRear)
		{
			Buffer_count=GlobalUSART3_s16RecievedFront-GlobalUSART3_s16RecievedRear;
		}
		else if(GlobalUSART3_s16RecievedFront<GlobalUSART3_s16RecievedRear)
		{
			Buffer_count = (BUFFER_SIZE - GlobalUSART3_s16RecievedRear)+ GlobalUSART3_s16RecievedFront;
		}
		else if (GlobalUSART3_s16RecievedFront== -1 && GlobalUSART3_s16RecievedRear == -1)
		{
			Buffer_count=0;
		}
		else 
		{
			Buffer_count = BUFFER_SIZE;
		}
	}
	return Buffer_count;
}
void MUSART_voidTransmitnumber(USART_T USART_NUM, u16 Copy_u8Number)
{
		u8 rest[5] ;
	    int i=-1;
		while(Copy_u8Number != 0)
		{
			i++;
			rest[i]=Copy_u8Number%10;
			Copy_u8Number=Copy_u8Number/10;
		}
		while(GET_BIT(USART[USART_NUM]->SR,TXE) == 0 )
		{
		}
		while(i > -1)
		{
			USART[USART_NUM] -> DR = rest[i] + 48;
			while((GET_BIT(USART[USART_NUM] -> SR , 6))== 0);
			i--;
		}
		USART[USART_NUM] -> DR = '\0';
		while(GET_BIT(USART[USART_NUM]->SR,TXE) == 0 );
}
void MUSART_voidEnableUSART_RecieveInterrupt(USART_T USART_NUM)
{
	SET_BIT(USART[USART_NUM]->CR[0],RXNIE);
}
void MUSART_voidDisableUSART_RecieveInterrupt(USART_T USART_NUM)
{
	CLR_BIT(USART[USART_NUM]->CR[0],RXNIE);
}
void USART1_IRQHandler(void)

{
	if(GET_BIT(USART[0]->SR,RXNE) == 1)
	{
		if(MUSART_u8IsRecieveBufferAvailable(USART1_Driver) < BUFFER_SIZE)
		{
			GlobalUSART1_s16RecievedFront=(GlobalUSART1_s16RecievedFront+1)%BUFFER_SIZE;
			GlobalUSART1_u8RecievedValue[GlobalUSART1_s16RecievedFront] = USART[0]->DR ;
		}
		// u8 returndata = USART[0]->DR ;
		// USART1_CallBack(returndata);
	}
}
void USART2_IRQHandler(void)
{
	if(GET_BIT(USART[1]->SR,RXNE) == 1)
	{
		if(MUSART_u8IsRecieveBufferAvailable(USART2_Driver) <BUFFER_SIZE)
		{
			GlobalUSART2_s16RecievedFront=(GlobalUSART2_s16RecievedFront+1)%BUFFER_SIZE;
			GlobalUSART2_u8RecievedValue[GlobalUSART2_s16RecievedFront] = USART[1]->DR ;
		}
	}
}
void USART3_IRQHandler(void)
{
	if(GET_BIT(USART[2]->SR,RXNE) == 1)
	{
		if(MUSART_u8IsRecieveBufferAvailable(USART3_Driver) <BUFFER_SIZE)
		{
			GlobalUSART3_s16RecievedFront=(GlobalUSART3_s16RecievedFront+1)%BUFFER_SIZE;
			GlobalUSART3_u8RecievedValue[GlobalUSART3_s16RecievedFront] = USART[2]->DR ;
		}
	}
}
