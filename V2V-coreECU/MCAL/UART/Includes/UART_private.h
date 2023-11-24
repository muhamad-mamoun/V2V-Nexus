#ifndef UART_PRIVATE_H
#define UART_PRIVATE_H


#include "Std_types.h"



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

#define MUSART ((volatile USART_t *)0x40013800 )
	

#endif