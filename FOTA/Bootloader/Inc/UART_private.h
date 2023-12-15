#ifndef UART_PRIVATE_H
#define UART_PRIVATE_H


#include "Std_types.h"

#define UART_1_BASE     0x40013800
#define UART_2_BASE     0x40004400
#define UART_3_BASE     0x40004800 

typedef struct 
{
    volatile u32 CR1   ;
    volatile u32 CR2   ;
    volatile u32 CR3   ;
    volatile u32 BRR   ;
    volatile u32 GTPR  ;
    volatile u32 RTOR  ;
    volatile u32 RQR   ;
    volatile u32 ISR   ;
    volatile u32 ICR   ;
    volatile u32 RDR   ;
    volatile u32 TDR   ;
}USART_t ; 

#define MUSART(BASE) ((volatile USART_t *)BASE )
	

#endif