/*
 * ILI9341_GFX.c
 *
 *  Created on: May 10, 2023
 *      Author: beshoy
 */

#include"../Inc/LIB/STD_TYPES.h"
#include"../Inc/LIB/BIT_MATH.h"
#include "../Inc/HAL/TFT/ILI9341_STM32_Driver.h"
#include "../Inc/HAL/TFT/ILI9341_GFX.h"
#include	"../Inc/MCAL/SYSTIC/STK_interface.h"


/* imprecise small delay */
/*__STATIC_INLINE void DelayUs(volatile u32 us)
{
	us *= (SystemCoreClock / 1000000);
	while (us--);
}*/

void ILI9341_DrawHollowCircle(u16 X, u16 Y, u16 radius, u16 color)
{
	int x = radius-1;
	int y = 0;
	int dx = 1;
	int dy = 1;
	int err = dx - (radius << 1);

	while (x >= y)
	{
		ILI9341_DrawPixel(X + x, Y + y, color);
		ILI9341_DrawPixel(X + y, Y + x, color);
		ILI9341_DrawPixel(X - y, Y + x, color);
		ILI9341_DrawPixel(X - x, Y + y, color);
		ILI9341_DrawPixel(X - x, Y - y, color);
		ILI9341_DrawPixel(X - y, Y - x, color);
		ILI9341_DrawPixel(X + y, Y - x, color);
		ILI9341_DrawPixel(X + x, Y - y, color);

		if (err <= 0)
		{
			y++;
			err += dy;
			dy += 2;
		}

		if (err > 0)
		{
			x--;
			dx += 2;
			err += (-radius << 1) + dx;
		}
	}
}

void ILI9341_DrawFilledCircle(u16 X, u16 Y, u16 radius, u16 color)
{

	int x = radius;
	int y = 0;
	int xChange = 1 - (radius << 1);
	int yChange = 0;
	int radiusError = 0;

	while (x >= y)
	{
		for (int i = X - x; i <= X + x; i++)
		{
			ILI9341_DrawPixel(i, Y + y,color);
			ILI9341_DrawPixel(i, Y - y,color);
		}

		for (int i = X - y; i <= X + y; i++)
		{
			ILI9341_DrawPixel(i, Y + x,color);
			ILI9341_DrawPixel(i, Y - x,color);
		}

		y++;
		radiusError += yChange;
		yChange += 2;

		if (((radiusError << 1) + xChange) > 0)
		{
			x--;
			radiusError += xChange;
			xChange += 2;
		}
	}
}

void ILI9341_DrawHollowRectangleCoord(u16 X0, u16 Y0, u16 X1, u16 Y1, u16 color)
{
	u16 xLen = 0;
	u16 yLen = 0;
	u8 negX = 0;
	u8 negY = 0;
	float negCalc = 0;

	negCalc = X1 - X0;
	if(negCalc < 0) negX = 1;
	negCalc = 0;

	negCalc = Y1 - Y0;
	if(negCalc < 0) negY = 1;

	//DRAW HORIZONTAL!
	if(!negX)
	{
		xLen = X1 - X0;
	}
	else
	{
		xLen = X0 - X1;
	}
	ILI9341_DrawHLine(X0, Y0, xLen, color);
	ILI9341_DrawHLine(X0, Y1, xLen, color);

	//DRAW VERTICAL!
	if(!negY)
	{
		yLen = Y1 - Y0;
	}
	else
	{
		yLen = Y0 - Y1;
	}

	ILI9341_DrawVLine(X0, Y0, yLen, color);
	ILI9341_DrawVLine(X1, Y0, yLen, color);

	if((xLen > 0)||(yLen > 0))
	{
		ILI9341_DrawPixel(X1, Y1, color);
	}
}

void ILI9341_DrawFilledRectangleCoord(u16 X0, u16 Y0, u16 X1, u16 Y1, u16 color)
{
	u16 xLen = 0;
	u16 yLen = 0;
	u8 negX = 0;
	u8 negY = 0;
	int32_t negCalc = 0;
	u16 X0True = 0;
	u16 Y0True = 0;

	negCalc = X1 - X0;
	if(negCalc < 0) negX = 1;
	negCalc = 0;

	negCalc = Y1 - Y0;
	if(negCalc < 0) negY = 1;

	if(!negX)
	{
		xLen = X1 - X0;
		X0True = X0;
	}
	else
	{
		xLen = X0 - X1;
		X0True = X1;
	}

	if(!negY)
	{
		yLen = Y1 - Y0;
		Y0True = Y0;
	}
	else
	{
		yLen = Y0 - Y1;
		Y0True = Y1;
	}

	ILI9341_DrawRectangle(X0True, Y0True, xLen, yLen, color);
}

void ILI9341_DrawChar(char ch, const u8 font[], u16 X, u16 Y, u16 color, u16 bgcolor)
{
	if ((ch < 31) || (ch > 127)) return;

	u8 fOffset, fWidth, fHeight, fBPL;
	u8 *tempChar;

	fOffset = font[0];
	fWidth = font[1];
	fHeight = font[2];
	fBPL = font[3];

	tempChar = (u8*)&font[((ch - 0x20) * fOffset) + 4]; /* Current Character = Meta + (Character Index * Offset) */

	/* Clear background first */
	ILI9341_DrawRectangle(X, Y, fWidth, fHeight, bgcolor);

	for (int j=0; j < fHeight; j++)
	{
		for (int i=0; i < fWidth; i++)
		{
			u8 z =  tempChar[fBPL * i + ((j & 0xF8) >> 3) + 1]; /* (j & 0xF8) >> 3, increase one by 8-bits */
			u8 b = 1 << (j & 0x07);
			if (( z & b ) != 0x00)
			{
				ILI9341_DrawPixel(X+i, Y+j, color);
			}
		}
	}
}

void ILI9341_DrawText(const char* str, const u8 font[], u16 X, u16 Y, u16 color, u16 bgcolor)
{
	u8 charWidth;			/* Width of character */
	u8 fOffset = font[0];	/* Offset of character */
	u8 fWidth = font[1];	/* Width of font */

	while (*str)
	{
		ILI9341_DrawChar(*str, font, X, Y, color, bgcolor);

		/* Check character width and calculate proper position */
		u8 *tempChar = (u8*)&font[((*str - 0x20) * fOffset) + 4];
		charWidth = tempChar[0];

		if(charWidth + 2 < fWidth)
		{
			/* If character width is smaller than font width */
			X += (charWidth + 2);
		}
		else
		{
			X += fWidth;
		}

		str++;
	}
}

void ILI9341_DrawImage(const u8* image, u8 orientation)
{
	if(orientation == SCREEN_HORIZONTAL_1)
	{
		ILI9341_SetRotation(SCREEN_HORIZONTAL_1);
		ILI9341_SetAddress(0,0,ILI9341_SCREEN_WIDTH,ILI9341_SCREEN_HEIGHT);
	}
	else if(orientation == SCREEN_HORIZONTAL_2)
	{
		ILI9341_SetRotation(SCREEN_HORIZONTAL_2);
		ILI9341_SetAddress(0,0,ILI9341_SCREEN_WIDTH,ILI9341_SCREEN_HEIGHT);
	}
	else if(orientation == SCREEN_VERTICAL_2)
	{
		ILI9341_SetRotation(SCREEN_VERTICAL_2);
		ILI9341_SetAddress(0,0,ILI9341_SCREEN_HEIGHT,ILI9341_SCREEN_WIDTH);
	}
	else if(orientation == SCREEN_VERTICAL_1)
	{
		ILI9341_SetRotation(SCREEN_VERTICAL_1);
		ILI9341_SetAddress(0,0,ILI9341_SCREEN_HEIGHT,ILI9341_SCREEN_WIDTH);
	}

	u32 counter = 0;
	for(u32 i = 0; i < ILI9341_SCREEN_WIDTH*ILI9341_SCREEN_HEIGHT*2/BURST_MAX_SIZE; i++)
	{
		ILI9341_WriteBuffer((u8*)(image + counter), BURST_MAX_SIZE);
		counter += BURST_MAX_SIZE;

		/* DMA Tx is too fast, It needs some delay */
		//MSTK_voidSetBusyWait 		  (1);
	}
}
void ILI9341_WelcomingMessage(void)
{
	ILI9341_FillScreen(WHITE);
	//ILI9341_DrawHLine(10, 130, 220, BLACK);
	ILI9341_DrawFilledRectangleCoord(0, 0, 240, 130, BLACK);
	ILI9341_DrawFilledRectangleCoord(0, 190, 240, 320, BLACK);
	ILI9341_DrawHollowRectangleCoord(10, 145, 230, 175, BLACK);
    ILI9341_DrawText("Welcome To City Bikers", FONT4, 20, 155, BLACK, WHITE);
    MSTK_voidSetBusyWait		(100000);

    ILI9341_FillScreen(WHITE);
}
void ILI9341_ShowParameters(u8 HeartRate, u8 Temperature, u8 Speed)
{

	static char BufferText[40];
	sprintf(BufferText, "Temperature : %d C'", Temperature);
    ILI9341_DrawText(BufferText, FONT3, 10, 70, WHITE, BLUE);
	sprintf(BufferText, "Speed       : %d KPH", Speed);
    ILI9341_DrawText(BufferText, FONT3, 10, 110, WHITE, RED);
	sprintf(BufferText, "HeartRate   : %d BPM", HeartRate);
    ILI9341_DrawText(BufferText, FONT3, 10, 150, WHITE, BLACK);
}
void ILI9341_ShowParametersV2(u8 HeartRate, u8 Temperature, u8 Speed)
{
	static char BufferText[40];
	 ILI9341_DrawRectangle(0, 0, 240, 107, ORANGE);
	sprintf(BufferText, "Temperature :", "");
	ILI9341_DrawText(BufferText, FONT4, 75, 33, BLACK, ORANGE);
	sprintf(BufferText, "%d C'",Temperature );
	ILI9341_DrawText(BufferText, FONT4, 75, 70, BLACK, ORANGE);
	ILI9341_DrawRectangle(0, 106, 240, 106, GREEN);
	sprintf(BufferText, "Speed       :", "");
	ILI9341_DrawText(BufferText, FONT4, 75, 139, BLACK, GREEN);
	sprintf(BufferText, "%d KPH", Speed);
	ILI9341_DrawText(BufferText, FONT4, 75, 176, BLACK, GREEN);
	ILI9341_DrawRectangle(0, 213, 240, 106, CYAN);
	sprintf(BufferText, "HeartRate   :", "");
	ILI9341_DrawText(BufferText, FONT4, 75, 246, BLACK, CYAN);
	sprintf(BufferText, "%d BPM", HeartRate);
	ILI9341_DrawText(BufferText, FONT4, 75, 283, BLACK, CYAN);
}

void ILI9341_ShowRoadSigns(signs road)
{

    switch(road)
    {
    case residential:
    	ILI9341_FillScreen(WHITE);
    	ILI9341_DrawHollowRectangleCoord(1, 70, 200, 190, BLACK);
    	ILI9341_DrawHollowRectangleCoord(5, 100, 100, 140, BLUE);
    	ILI9341_DrawFilledRectangleCoord(5, 100, 100, 140, RED);
        ILI9341_DrawText("Road Sign", FONT3, 10, 110, WHITE, RED);
    	ILI9341_DrawText("Residential Area", FONT4, 30, 150, BLACK, WHITE);
    	break;
    case stop:
    	ILI9341_FillScreen(WHITE);
    	ILI9341_DrawHollowRectangleCoord(1, 70, 200, 190, BLACK);
    	ILI9341_DrawHollowRectangleCoord(5, 100, 100, 140, BLUE);
    	ILI9341_DrawFilledRectangleCoord(5, 100, 100, 140, RED);
        ILI9341_DrawText("Road Sign", FONT3, 10, 110, WHITE, RED);
		ILI9341_DrawText("STOP", FONT4, 30, 150, BLACK, WHITE);
		break;
    case nocycling:
    	ILI9341_FillScreen(WHITE);
    	ILI9341_DrawHollowRectangleCoord(1, 70, 200, 190, BLACK);
    	ILI9341_DrawHollowRectangleCoord(5, 100, 100, 140, BLUE);
    	ILI9341_DrawFilledRectangleCoord(5, 100, 100, 140, RED);
        ILI9341_DrawText("Road Sign", FONT3, 10, 110, WHITE, RED);
		ILI9341_DrawText("NO CYCLING", FONT4, 30, 150, BLACK, WHITE);
		break;
    case yeild:
    	ILI9341_FillScreen(WHITE);
    	ILI9341_DrawHollowRectangleCoord(1, 70, 200, 190, BLACK);
    	ILI9341_DrawHollowRectangleCoord(5, 100, 100, 140, BLUE);
    	ILI9341_DrawFilledRectangleCoord(5, 100, 100, 140, RED);
        ILI9341_DrawText("Road Sign", FONT3, 10, 110, WHITE, RED);
		ILI9341_DrawText("ROAD WORKS", FONT4, 30, 150, BLACK, WHITE);
		break;
    default:
    	break;
    }
}

