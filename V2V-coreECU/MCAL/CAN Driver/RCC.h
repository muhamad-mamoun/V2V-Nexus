/*
 * RCC.h
 *
 * Created: 11/17/2023 
 *  Author: Ahmed Wael
 */

#ifndef _RCC_H_
#define _RCC_H_

#include "std_types.h"
#include "bit_math.h"

/****************/
#define TIME_OUT 1000000
/****************/

#define SYSCLK_HSE 0
#define SYSCLK_HSI 1
#define SYSCLK_PLL 2   //NOT IMPLEMENTED YET

#define SYS_CLK SYSCLK_HSE

void RCC_voidInitSYSCLK(void);

/*****************************/


#define AHB_BUS  0
#define APB2_BUS 1
#define APB1_BUS 2

/******** AHB ***********/
#define GPIOA_EN 17
#define GPIOB_EN 18
#define GPIOC_EN 19
#define GPIOD_EN 20
#define GPIOE_EN 21
#define GPIOF_EN 22

/******** APB2 ***********/
#define USART1_EN 14    
#define SPI1_EN 12

/******** APB1 ***********/
#define TIM2_EN 0
#define TIM3_EN 1
#define TIM4_EN 2
#define CAN_EN 25


void RCC_voidEnablePeripheral(u8 Copy_u8Bus, u8 Copy_u8Peripheral);

void RCC_voidDisablePeripheral(u8 Copy_u8Bus, u8 Copy_u8Peripheral);

#endif

