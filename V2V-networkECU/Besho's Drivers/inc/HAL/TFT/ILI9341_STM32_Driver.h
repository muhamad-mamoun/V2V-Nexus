/*
 * ILI9341_STM32_Driver.h
 *
 *  Created on: May 10, 2023
 *      Author: beshoy
 */

#ifndef ILI9341_STM32_DRIVER_H
#define ILI9341_STM32_DRIVER_H



#define ILI9341_SCREEN_HEIGHT 	240
#define ILI9341_SCREEN_WIDTH 	320

/* PIN Configuration */

#define LCD_CS_PORT				GPIOB
#define LCD_CS_PIN				PIN10
#define LCD_DC_PORT				GPIOB
#define LCD_DC_PIN				PIN0
#define	LCD_RST_PORT			GPIOB
#define	LCD_RST_PIN				PIN1

#define BURST_MAX_SIZE 			500
#define BLACK      				0x0000
#define NAVY        			0x000F
#define DARKGREEN   			0x03E0
#define DARKCYAN    			0x03EF
#define MAROON      			0x7800
#define PURPLE      			0x780F
#define OLIVE       			0x7BE0
#define LIGHTGREY   			0xC618
#define DARKGREY    			0x7BEF
#define BLUE        			0x001F
#define GREEN       			0x07E0
#define CYAN        			0x07FF
#define RED         			0xF800
#define MAGENTA     			0xF81F
#define YELLOW      			0xFFE0
#define WHITE       			0xFFFF
#define ORANGE      			0xFD20
#define GREENYELLOW 			0xAFE5
#define PINK        			0xF81F

#define SCREEN_VERTICAL_1		0
#define SCREEN_HORIZONTAL_1		1
#define SCREEN_VERTICAL_2		2
#define SCREEN_HORIZONTAL_2		3

void ILI9341_WriteCommand(u8 cmd);
void ILI9341_WriteData(u8 data);
void ILI9341_WriteBuffer(u8 *buffer, u16 len);
void ILI9341_Reset(void);
void ILI9341_Enable(void);
void ILI9341_Init(void);
void ILI9341_SetRotation(u8 rotation);
void ILI9341_SetAddress(u16 x1, u16 y1, u16 x2, u16 y2);
void ILI9341_DrawColor(u16 color);
void ILI9341_DrawColorBurst(u16 color, u32 size);
void ILI9341_FillScreen(u16 color);
void ILI9341_DrawPixel(u16 x,u16 y,u16 color);
void ILI9341_DrawRectangle(u16 x, u16 y, u16 width, u16 height, u16 color);
void ILI9341_DrawHLine(u16 x, u16 y, u16 width, u16 color);
void ILI9341_DrawVLine(u16 x, u16 y, u16 height, u16 color);
#endif
