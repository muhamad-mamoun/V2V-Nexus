/*
 * DIO_interface.h
 *
 *  Created on: October 10, 2022
 *      Author: beshoy
 */



#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

#include "std_types.h"
#include "common_macros.h"

#define GPIO_HIGH   1
#define GPIO_LOW    0



          /* GPIO ports*/
#define GPIOA  0
#define GPIOB  1
#define GPIOC  2

       /* GPIO PINS*/

#define PIN0   0
#define PIN1   1
#define PIN2   2
#define PIN3   3
#define PIN4   4
#define PIN5   5
#define PIN6   6
#define PIN7   7
#define PIN8   8
#define PIN9   9
#define PIN10  10
#define PIN11  11
#define PIN12  12
#define PIN13  13
#define PIN14  14
#define PIN15  15


// pin modes



#define INPUT_ANALOG                  0b0000
#define INPUT_FLOATING                0b0100
#define INPUT_PULL_UP_DOWN            0b1000


#define OUTPUT_SPEED_10MHZ_PP         0X01
#define OUTPUT_SPEED_10MHZ_OD         0b0101
#define OUTPUT_SPEED_10MHZ_AFPP       0b1001
#define OUTPUT_SPEED_10MHZ_AFOD       0b1101


#define OUTPUT_SPEED_2MHZ_PP         0b0010
#define OUTPUT_SPEED_2MHZ_OD         0b0110
#define OUTPUT_SPEED_2MHZ_AFPP       0b1010
#define OUTPUT_SPEED_2MHZ_AFOD       0b1110


#define OUTPUT_SPEED_50MHZ_PP         0b0011
#define OUTPUT_SPEED_50MHZ_OD         0b0111
#define OUTPUT_SPEED_50MHZ_AFPP       0b1011
#define OUTPUT_SPEED_50MHZ_AFOD       0X0F

#define INPUT_ANALOG_PORT                  0x00000000
#define INPUT_FLOATING_PORT                0x44444444
#define INPUT_PULL_UP_DOWN_PORT            0x88888888


#define OUTPUT_SPEED_10MHZ_PP_PORT         0X11111111
#define OUTPUT_SPEED_10MHZ_OD_PORT         0x55555555
#define OUTPUT_SPEED_10MHZ_AFPP_PORT       0x99999999
#define OUTPUT_SPEED_10MHZ_AFOD_PORT       0xDDDDDDDD


#define OUTPUT_SPEED_2MHZ_PP_PORT         0x22222222
#define OUTPUT_SPEED_2MHZ_OD_PORT         0x66666666
#define OUTPUT_SPEED_2MHZ_AFPP_PORT       0xAAAAAAAA
#define OUTPUT_SPEED_2MHZ_AFOD_PORT       0xEEEEEEEE


#define OUTPUT_SPEED_50MHZ_PP_PORT         0x33333333
#define OUTPUT_SPEED_50MHZ_OD_PORT         0x77777777
#define OUTPUT_SPEED_50MHZ_AFPP_PORT       0xBBBBBBBB
#define OUTPUT_SPEED_50MHZ_AFOD_PORT       0XFFFFFFFF



void MGPIO_voidSetPinDirection(u8 copy_u8PORT , u8 copy_u8PIN  , u8 copy_u8Mode);
void MGPIO_voidSetPinValue    (u8 copy_u8PORT , u8 copy_u8PIN  , u8 copy_u8Value);
u8   MGPIO_u8GetPinValue      (u8 copy_u8PORT , u8 copy_u8PIN );
void delay(u32 Copy_DelayTime);
void SEVEN_SEGMENT ( u8 copy_u8PORT, u8 Copy_u8Number  );
void MDIO_voidPingPong(u8 copy_u8PORT);
void MDIO_voidSimultaneously(u8 copy_u8PORT);
void MDIO_voidComingandGoing(u8 copy_u8PORT);
void MGPIO_voidSetPortDirection  (u8 copy_u8PORT , u32 copy_u32Mode);
void MGPIO_voidSetPortValue      (u8 copy_u8PORT , u16 copy_u16Value);




#endif /* DIO_INTERFACE_H_ */
