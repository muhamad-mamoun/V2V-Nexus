/*
 * USART_private.h
 *
 *  Created on: december 26, 2022
 *      Author: beshoy
 */

#ifndef USART_PRIVATE_H_
#define USART_PRIVATE_H_

#define USART1_ADDRESS 0x40013800
#define USART2_ADDRESS 0x40004400
#define USART3_ADDRESS 0x40004800

typedef struct
{
	volatile u32 SR;
	volatile u8 DR;
    volatile u8 DR0;
    volatile u8 DR1;
    volatile u8 DR2;
	volatile u32 BRR;
	volatile u32 CR[3];
	volatile u32 GTPR;

}USART_TYPE;
USART_TYPE *USART[3]=
{
	(USART_TYPE *)USART1_ADDRESS,
	(USART_TYPE *)USART2_ADDRESS,
	(USART_TYPE *)USART3_ADDRESS,
};

#define TE 3
#define RE 2
#define UE 13

#define TXE 7
#define TC 	6
#define RXNE 5

#define DMAT 7
#define DMAR 6

#define TXIE 7
#define TCIE 6
#define RXNIE 5

u32 MUSART_voidSetBaudrateRegister(u32 Copy_u32FClock, u32 Copy_u32Baudrate);
void USART1_IRQHandler(void);
#endif
