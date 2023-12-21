/*
 * ILI9341_STM32_Driver.c
 *
 *  Created on: May 10, 2023
 *      Author: beshoy
 */
#include"../Inc/LIB/STD_TYPES.h"
#include"../Inc/LIB/BIT_MATH.h"
#include "../Inc/HAL/TFT/ILI9341_STM32_Driver.h"
#include "../Inc/MCAL/SPI/SPI_interface.h"
#include "../Inc/MCAL/DIO/DIO_interface.h"
#include	"../Inc/MCAL/SYSTIC/STK_interface.h"

volatile u16 LCD_HEIGHT = ILI9341_SCREEN_HEIGHT;
volatile u16 LCD_WIDTH	 = ILI9341_SCREEN_WIDTH;
static void ILI9341_SPI_Tx(u8 data)
{
	//while(!__HAL_SPI_GET_FLAG(HSPI_INSTANCE, SPI_FLAG_TXE));
	//HAL_SPI_Transmit_DMA(HSPI_INSTANCE, &data, 1);
	//HAL_SPI_Transmit(HSPI_INSTANCE, BurstBuffer, BufferSize, 10);
	//SPI_transmit(HSPI_INSTANCE, &data, 1,10);
	//HAL_SPI_Transmit(HSPI_INSTANCE, &data, 1, 10);
	//SPI_transmit(&data, 1);
	//SPI_voidSendRecSynch(SPI1 , data);
	SPI_transmit(SPI1 , &data, 1);
}

static void ILI9341_SPI_TxBuffer(u8 *buffer, u8 len)
{
	//u16 vounter=0;
	//while(!__HAL_SPI_GET_FLAG(HSPI_INSTANCE, SPI_FLAG_TXE));
	//HAL_SPI_Transmit_DMA(HSPI_INSTANCE, buffer, len);
	//SPI_transmit(HSPI_INSTANCE, buffer, len,10);
	//HAL_SPI_Transmit(HSPI_INSTANCE, buffer, len, 10);
	SPI_transmit(SPI1 , buffer, len);
	/*while(vounter<len)
	{
		SPI_voidSendRecSynch(SPI1 , buffer[vounter]);
		vounter++;
	}*/
}

void ILI9341_WriteCommand(u8 cmd)
{
	// RESET DC PIN    RESET CS PIN
	MGPIO_voidSetPinValue(LCD_DC_PORT, LCD_DC_PIN, GPIO_LOW);	//command
	MGPIO_voidSetPinValue(LCD_CS_PORT, LCD_CS_PIN, GPIO_LOW);	//select
	ILI9341_SPI_Tx(cmd);
	MGPIO_voidSetPinValue    (LCD_CS_PORT , LCD_CS_PIN  , GPIO_HIGH);

	//HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);	//deselect
}

void ILI9341_WriteData(u8 data)
{
	// SET DC PIN    RESET CS PIN
	MGPIO_voidSetPinValue(LCD_DC_PORT, LCD_DC_PIN, GPIO_HIGH);	//data
	MGPIO_voidSetPinValue(LCD_CS_PORT, LCD_CS_PIN, GPIO_LOW);	//select
	ILI9341_SPI_Tx(data);
	MGPIO_voidSetPinValue    (LCD_CS_PORT , LCD_CS_PIN  , GPIO_HIGH);

	//HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);	//deselect
}

void ILI9341_WriteBuffer(u8 *buffer, u16 len)
{
	//u16 counter=0;
	MGPIO_voidSetPinValue(LCD_DC_PORT, LCD_DC_PIN, GPIO_HIGH);	//data
	MGPIO_voidSetPinValue(LCD_CS_PORT, LCD_CS_PIN, GPIO_LOW);	//select
	ILI9341_SPI_TxBuffer(buffer, len);
	MGPIO_voidSetPinValue    (LCD_CS_PORT , LCD_CS_PIN  , GPIO_HIGH);
	/*while(counter<len)
	{
		SPI_voidSendRecSynch (SPI1 , buffer[counter]);
	}
	MGPIO_voidSetPinValue    (LCD_CS_PORT , LCD_CS_PIN  , GPIO_HIGH);*/

	//HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);	//deselect
}

void ILI9341_SetAddress(u16 x1, u16 y1, u16 x2, u16 y2)
{
	u8 buffer[4];
	buffer[0] = x1 >> 8;
	buffer[1] = x1;
	buffer[2] = x2 >> 8;
	buffer[3] = x2;

	ILI9341_WriteCommand(0x2A);
	ILI9341_WriteBuffer(buffer, sizeof(buffer));

	buffer[0] = y1 >> 8;
	buffer[1] = y1;
	buffer[2] = y2 >> 8;
	buffer[3] = y2;

	ILI9341_WriteCommand(0x2B);
	ILI9341_WriteBuffer(buffer, sizeof(buffer));

	ILI9341_WriteCommand(0x2C);
}

void ILI9341_Reset(void)
{
	MGPIO_voidSetPinValue(LCD_RST_PORT, LCD_RST_PIN, GPIO_LOW);	//Disable
	MSTK_voidSetBusyWait 		  (10000);
	MGPIO_voidSetPinValue(LCD_CS_PORT, LCD_CS_PIN, GPIO_LOW);		//Select
	MSTK_voidSetBusyWait 		  (10000);
	MGPIO_voidSetPinValue(LCD_RST_PORT, LCD_RST_PIN, GPIO_HIGH);		//Enable
	MGPIO_voidSetPinValue(LCD_CS_PORT, LCD_CS_PIN, GPIO_HIGH); 		//Deselect
}

void ILI9341_Enable(void)
{
	MGPIO_voidSetPinValue(LCD_RST_PORT, LCD_RST_PIN, GPIO_HIGH);		//Enable
}

void ILI9341_Init(void)
{
	MGPIO_voidSetPinDirection   (LCD_CS_PORT , LCD_CS_PIN  , OUTPUT_SPEED_10MHZ_PP);
	MGPIO_voidSetPinDirection   (LCD_DC_PORT , LCD_DC_PIN  ,  OUTPUT_SPEED_10MHZ_PP);
	MGPIO_voidSetPinDirection   (LCD_RST_PORT , LCD_RST_PIN  ,  OUTPUT_SPEED_10MHZ_PP);
	ILI9341_Enable();
	ILI9341_Reset();

	//SOFTWARE RESET
	ILI9341_WriteCommand(0x01);
	MSTK_voidSetBusyWait 		  (10000);

	//POWER CONTROL A
	ILI9341_WriteCommand(0xCB);
	ILI9341_WriteData(0x39);
	ILI9341_WriteData(0x2C);
	ILI9341_WriteData(0x00);
	ILI9341_WriteData(0x34);
	ILI9341_WriteData(0x02);

	//POWER CONTROL B
	ILI9341_WriteCommand(0xCF);
	ILI9341_WriteData(0x00);
	ILI9341_WriteData(0xC1);
	ILI9341_WriteData(0x30);

	//DRIVER TIMING CONTROL A
	ILI9341_WriteCommand(0xE8);
	ILI9341_WriteData(0x85);
	ILI9341_WriteData(0x00);
	ILI9341_WriteData(0x78);

	//DRIVER TIMING CONTROL B
	ILI9341_WriteCommand(0xEA);
	ILI9341_WriteData(0x00);
	ILI9341_WriteData(0x00);

	//POWER ON SEQUENCE CONTROL
	ILI9341_WriteCommand(0xED);
	ILI9341_WriteData(0x64);
	ILI9341_WriteData(0x03);
	ILI9341_WriteData(0x12);
	ILI9341_WriteData(0x81);

	//PUMP RATIO CONTROL
	ILI9341_WriteCommand(0xF7);
	ILI9341_WriteData(0x20);

	//POWER CONTROL,VRH[5:0]
	ILI9341_WriteCommand(0xC0);
	ILI9341_WriteData(0x23);

	//POWER CONTROL,SAP[2:0];BT[3:0]
	ILI9341_WriteCommand(0xC1);
	ILI9341_WriteData(0x10);

	//VCM CONTROL
	ILI9341_WriteCommand(0xC5);
	ILI9341_WriteData(0x3E);
	ILI9341_WriteData(0x28);

	//VCM CONTROL 2
	ILI9341_WriteCommand(0xC7);
	ILI9341_WriteData(0x86);

	//MEMORY ACCESS CONTROL
	ILI9341_WriteCommand(0x36);
	ILI9341_WriteData(0x48);

	//PIXEL FORMAT
	ILI9341_WriteCommand(0x3A);
	ILI9341_WriteData(0x55);

	//FRAME RATIO CONTROL, STANDARD RGB COLOR
	ILI9341_WriteCommand(0xB1);
	ILI9341_WriteData(0x00);
	ILI9341_WriteData(0x18);

	//DISPLAY FUNCTION CONTROL
	ILI9341_WriteCommand(0xB6);
	ILI9341_WriteData(0x08);
	ILI9341_WriteData(0x82);
	ILI9341_WriteData(0x27);

	//3GAMMA FUNCTION DISABLE
	ILI9341_WriteCommand(0xF2);
	ILI9341_WriteData(0x00);

	//GAMMA CURVE SELECTED
	ILI9341_WriteCommand(0x26);
	ILI9341_WriteData(0x01);

	//POSITIVE GAMMA CORRECTION
	ILI9341_WriteCommand(0xE0);
	ILI9341_WriteData(0x0F);
	ILI9341_WriteData(0x31);
	ILI9341_WriteData(0x2B);
	ILI9341_WriteData(0x0C);
	ILI9341_WriteData(0x0E);
	ILI9341_WriteData(0x08);
	ILI9341_WriteData(0x4E);
	ILI9341_WriteData(0xF1);
	ILI9341_WriteData(0x37);
	ILI9341_WriteData(0x07);
	ILI9341_WriteData(0x10);
	ILI9341_WriteData(0x03);
	ILI9341_WriteData(0x0E);
	ILI9341_WriteData(0x09);
	ILI9341_WriteData(0x00);

	//NEGATIVE GAMMA CORRECTION
	ILI9341_WriteCommand(0xE1);
	ILI9341_WriteData(0x00);
	ILI9341_WriteData(0x0E);
	ILI9341_WriteData(0x14);
	ILI9341_WriteData(0x03);
	ILI9341_WriteData(0x11);
	ILI9341_WriteData(0x07);
	ILI9341_WriteData(0x31);
	ILI9341_WriteData(0xC1);
	ILI9341_WriteData(0x48);
	ILI9341_WriteData(0x08);
	ILI9341_WriteData(0x0F);
	ILI9341_WriteData(0x0C);
	ILI9341_WriteData(0x31);
	ILI9341_WriteData(0x36);
	ILI9341_WriteData(0x0F);

	//EXIT SLEEP
	ILI9341_WriteCommand(0x11);
	MSTK_voidSetBusyWait 		  (100000);

	//TURN ON DISPLAY
	ILI9341_WriteCommand(0x29);

	//STARTING ROTATION
	ILI9341_SetRotation(SCREEN_VERTICAL_2);
}

void ILI9341_SetRotation(u8 rotation)
{
	ILI9341_WriteCommand(0x36);
	MSTK_voidSetBusyWait 		  (1000);

	switch(rotation)
	{
	case SCREEN_VERTICAL_1:
		ILI9341_WriteData(0x40|0x08);
		LCD_WIDTH = 240;
		LCD_HEIGHT = 320;
		break;
	case SCREEN_HORIZONTAL_1:
		ILI9341_WriteData(0x20|0x08);
		LCD_WIDTH  = 320;
		LCD_HEIGHT = 240;
		break;
	case SCREEN_VERTICAL_2:
		ILI9341_WriteData(0x80|0x08);
		LCD_WIDTH  = 240;
		LCD_HEIGHT = 320;
		break;
	case SCREEN_HORIZONTAL_2:
		ILI9341_WriteData(0x40|0x80|0x20|0x08);
		LCD_WIDTH  = 320;
		LCD_HEIGHT = 240;
		break;
	default:
		break;
	}
}

void ILI9341_DrawColor(u16 color)
{
	u8 buffer[2] = {color>>8, color};
	ILI9341_WriteBuffer(buffer, sizeof(buffer));
}

void ILI9341_DrawColorBurst(u16 color, u32 size)
{
	u32 BufferSize = 0;

	if((size*2) < BURST_MAX_SIZE)
	{
		BufferSize = size;
	}
	else
	{
		BufferSize = BURST_MAX_SIZE;
	}

	MGPIO_voidSetPinValue(LCD_DC_PORT, LCD_DC_PIN, GPIO_HIGH);
	MGPIO_voidSetPinValue(LCD_CS_PORT, LCD_CS_PIN, GPIO_LOW);

	u8 chifted = color>>8;
	u8 BurstBuffer[BufferSize];

	for(u32 j = 0; j < BufferSize; j+=2)
	{
		BurstBuffer[j] = chifted;
		BurstBuffer[j+1] = color;
	}

	u32 SendingSize = size * 2;
	u32 SendingInBlock = SendingSize / BufferSize;
	u32 RemainderFromBlock = SendingSize % BufferSize;

	if(SendingInBlock != 0)
	{
		for(u32 j = 0; j < (SendingInBlock); j++)
		{
			ILI9341_WriteBuffer(BurstBuffer, BufferSize);
		}
	}

	ILI9341_WriteBuffer(BurstBuffer, RemainderFromBlock);

	MGPIO_voidSetPinValue(LCD_CS_PORT, LCD_CS_PIN, GPIO_HIGH);
}

void ILI9341_FillScreen(u16 color)
{
	ILI9341_SetAddress(0, 0, LCD_WIDTH, LCD_HEIGHT);
	//ILI9341_DrawColor(color);
	ILI9341_DrawColorBurst(color, LCD_WIDTH*LCD_HEIGHT*2.25);

}

void ILI9341_DrawPixel(u16 x,u16 y,u16 color)
{
	if((x >=LCD_WIDTH) || (y >=LCD_HEIGHT)) return;

	u8 bufferX[4] = {x>>8, x, (x+1)>>8, (x+1)};
	u8 bufferY[4] = {y>>8, y, (y+1)>>8, (y+1)};
	u8 bufferC[2] = {color>>8, color};

	ILI9341_WriteCommand(0x2A); //ADDRESS
	/*ILI9341_WriteData(bufferX[0]);
	ILI9341_WriteData(bufferX[1]);
	ILI9341_WriteData(bufferX[2]);
	ILI9341_WriteData(bufferX[3]);*/

	ILI9341_WriteBuffer(bufferX, sizeof(bufferX));	//XDATA

	ILI9341_WriteCommand(0x2B);	//ADDRESS
	/*ILI9341_WriteData(bufferY[0]);
	ILI9341_WriteData(bufferY[1]);
	ILI9341_WriteData(bufferY[2]);
	ILI9341_WriteData(bufferY[3]);*/
	ILI9341_WriteBuffer(bufferY, sizeof(bufferY));	//YDATA

	ILI9341_WriteCommand(0x2C);						//ADDRESS
	/*ILI9341_WriteData(bufferC[0]);
	ILI9341_WriteData(bufferC[1]);*/
	ILI9341_WriteBuffer(bufferC, sizeof(bufferC));	//COLOR
}

void ILI9341_DrawRectangle(u16 x, u16 y, u16 width, u16 height, u16 color)
{
	if((x >=LCD_WIDTH) || (y >=LCD_HEIGHT)) return;

	if((x+width-1)>=LCD_WIDTH)
	{
		width=LCD_WIDTH-x;
	}

	if((y+height-1)>=LCD_HEIGHT)
	{
		height=LCD_HEIGHT-y;
	}

	ILI9341_SetAddress(x, y, x+width-1, y+height-1);
	ILI9341_DrawColorBurst(color, height*width*2.25);
}

void ILI9341_DrawHLine(u16 x, u16 y, u16 width, u16 color)
{
	if((x >=LCD_WIDTH) || (y >=LCD_HEIGHT)) return;

	if((x+width-1)>=LCD_WIDTH)
	{
		width=LCD_WIDTH-x;
	}

	ILI9341_SetAddress(x, y, x+width-1, y);
	ILI9341_DrawColorBurst(color, width);
}

void ILI9341_DrawVLine(u16 x, u16 y, u16 height, u16 color)
{
	if((x >=LCD_WIDTH) || (y >=LCD_HEIGHT)) return;

	if((y+height-1)>=LCD_HEIGHT)
	{
		height=LCD_HEIGHT-y;
	}

	ILI9341_SetAddress(x, y, x, y+height-1);
	ILI9341_DrawColorBurst(color, height);
}
