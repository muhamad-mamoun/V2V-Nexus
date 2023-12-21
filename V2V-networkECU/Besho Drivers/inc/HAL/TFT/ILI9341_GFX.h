/*
 * ILI9341_GFX.h
 *
 *  Created on: May 10, 2023
 *      Author: beshoy
 */

#ifndef ILI9341_GFX_H
#define ILI9341_GFX_H

#include "fonts.h"

#define HORIZONTAL_IMAGE	0
#define VERTICAL_IMAGE		1
typedef enum
{
	yeild,
	residential,
	nocycling,
	stop=8

}signs;
void ILI9341_DrawHollowCircle(u16 X, u16 Y, u16 radius, u16 color);
void ILI9341_DrawFilledCircle(u16 X, u16 Y, u16 radius, u16 color);
void ILI9341_DrawHollowRectangleCoord(u16 X0, u16 Y0, u16 X1, u16 Y1, u16 color);
void ILI9341_DrawFilledRectangleCoord(u16 X0, u16 Y0, u16 X1, u16 Y1, u16 color);
void ILI9341_DrawChar(char ch, const u8 font[], u16 X, u16 Y, u16 color, u16 bgcolor);
void ILI9341_DrawText(const char* str, const u8 font[], u16 X, u16 Y, u16 color, u16 bgcolor);
void ILI9341_DrawImage(const u8* image, u8 orientation);
void ILI9341_WelcomingMessage(void);
void ILI9341_ShowParameters(u8 HeartRate, u8 Temperature, u8 Speed);
void ILI9341_ShowParametersV2(u8 HeartRate, u8 Temperature, u8 Speed);
void ILI9341_ShowRoadSigns(signs road);

#endif
