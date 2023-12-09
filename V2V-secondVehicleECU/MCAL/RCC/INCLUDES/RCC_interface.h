/*
 * RCC_interface.h
 *
 *  Created on: septemper 15, 2022
 *      Author: beshoy
 */
 
#ifndef RCC_INTERFACE_H_
#define RCC_INTERFACE_H_

#define HSI 0
#define HSE 1
#define PLL 2

#define NOT_READY 0
#define READY 1

#define HSE_NOT_DIVIDED 1
#define HSE_DIVIDED 2

typedef enum
{
	AHB ,
	APB1 ,
	APB2
}Buses_t;

typedef enum {
	PClock_enable  =1 ,
	PClock_disable =0
}PClock_State_t;


//periphera id bits for AHP
#define DMA1_PERIPHERAL     0
#define DMA2_PERIPHERAL     1
#define SRAM_PERIPHERAL     2
#define FLITF_PERIPHERAL    4
#define CRCE_PERIPHERAL     6
#define FSMC_PERIPHERAL     8
#define SDIO_PERIPHERAL     10

//periphera id bits for APB2
#define AFIO_PERIPHERAL     0
#define IOPA_PERIPHERAL     2
#define IOPB_PERIPHERAL     3
#define IOPC_PERIPHERAL     4
#define IOPD_PERIPHERAL     5
#define IOPE_PERIPHERAL     6
#define IOPF_PERIPHERAL     7
#define IOPG_PERIPHERAL     8
#define ADC1_PERIPHERAL     9
#define ADC2_PERIPHERAL     10
#define TIM1_PERIPHERAL     11
#define SPI1_PERIPHERAL     12
#define TIM8_PERIPHERAL     13
#define USART1_PERIPHERAL   14
#define ADC3_PERIPHERAL     15
#define TIM9_PERIPHERAL     19
#define TIM10_PERIPHERAL    20
#define TIM11_PERIPHERAL    21

//periphera id bits for APB1
#define TIM2_PERIPHERAL     0
#define TIM3_PERIPHERAL     1
#define TIM4_PERIPHERAL     2
#define TIM5_PERIPHERAL     3
#define TIM6_PERIPHERAL     4
#define TIM7_PERIPHERAL     5
#define TIM12_PERIPHERAL    6
#define TIM13_PERIPHERAL    7
#define TIM14_PERIPHERAL    8
#define WWD_PERIPHERAL      11
#define SPI2_PERIPHERAL     14
#define SPI3_PERIPHERAL     15
#define USART2_PERIPHERAL   17
#define USART3_PERIPHERAL   18
#define USART4_PERIPHERAL   19
#define USART5_PERIPHERAL   20
#define I2C1_PERIPHERAL     21
#define I2C2_PERIPHERAL     22
#define USB_PERIPHERAL      23
#define CAN_PERIPHERAL      25
#define BKP_PERIPHERAL      27
#define PWR_PERIPHERAL      28
#define DAC_PERIPHERAL      29

void MRCC_voidInit(void);

void MRCC_voidPerClock_State(Buses_t A_bus ,u8  A_peripheral ,PClock_State_t A_state );

/******************************************************************************/
/*Function: MRCC_voidClkDisable                          			          */
/*I/P Parameters: CLK Source  		            						      */
/*Returns:it returns void                            				          */
/*Desc:This Function Disables the clock  Source							      */
/******************************************************************************/
/* options :- HSI  -  HSE  -  PLL											  */
/******************************************************************************/
void MRCC_voidClkDisable(u8 A_u8ClkSource);
void MRCC_voidClkEnable(u8 A_u8ClkSource);
void MRCC_voidSetClkSource(u8 A_u8ClkSource);
u8   MRCC_u8CheckClockReady(u8 A_u8ClkSource);
void MRCC_voidSetBusesPrescaler(u8 A_u8AHBPrescaler, u8 A_u8APB1Prescaler, u8 A_u8APB2Prescaler);

/* A_u8ClkSource : HSI  -  HSE */
/* A_u8Prescaler : HSE_NOT_DIVIDED  -  HSE_DIVIDED*/
void MRCC_voidSetPLLSource(u8 A_u8ClkSource, u8 A_u8Prescaler);
void MRCC_voidSetPLLMulFactor(u8 A_u8MulFactor);

#endif /* RCC_INTERFACE_H_ */
