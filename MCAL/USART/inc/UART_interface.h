#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H

#include "std_types.h"


typedef struct 
{
    volatile u8 WordLength          ;
    /*UART Sampling*/
    volatile u32 OverSampling        ; 

    /*Parity Selection*/
    volatile u32 ParitySelection     ; 
    /*MSB or LSB */
    volatile u32 SBFIRST             ;
    /*# of Stop Bits*/
    volatile u32 StopBits            ; 
    
    /*Baud Rate*/
    volatile u16 BaudRate            ;

 
}MUARTConfig ; 

typedef enum 
{
    UART_EOk               , 
    WordLenghtError        , 
    Wrong_Oversampling     , 
    ParitySelectionError   , 
    WrongStopbitSelection  , 
	   ErrorReceieving 
    

}UART_tenuErrorStatus;

#define OneStart_8Data   0x00000000
#define OneStart_7Data   0x00001000
#define OneStart_9Data   0x10000000


#define OV_16    0 
#define OV_8     1 

//#define Parity_Enabled   1 
#define Parity_Disabled  0 

#define EvenParity    1
#define OddParity     2

#define MSB           2 
#define LSB           3



#define OneStopBit     0 
#define HalfStopBit   1
#define TwoStopBit     2
#define OneAHalfStopBit   3 

#define F_CPU     8000000
/*bits*/
#define OVER_SAM   15 
#define PCE        10 
#define PS          9
#define ABREN       20 
#define MSBFIRST    19
#define STOP0       12
#define STOP1       13
#define TE           3
#define RE           2
#define UE           0


#define THRESHOLD_VALUE 9000000UL 

UART_tenuErrorStatus MUSART_voidInit(MUARTConfig *Add_CnfgStruct);
void MUSART1_VidSendCharSync ( u8 Copy_u8Char);
void MUSART1_VidSendStringSynch ( u8 * Copy_ptrString );
UART_tenuErrorStatus MUSART1_u8RecCharSynch (u32* pData) ;
void UART_Init(void);

#endif