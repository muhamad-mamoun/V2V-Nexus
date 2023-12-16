#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H

#include "std_types.h"

#define USART1_ID        (0)
#define USART2_ID        (1)
#define USART3_ID        (2)

typedef struct 
{
	  volatile u8 UART_Index          ;
    volatile u8 WordLength          ;
    /*UART Sampling*/
    volatile u8 OverSampling        ; 

    /*Parity Selection*/
    volatile u8 ParitySelection     ; 
    /*MSB or LSB */
    volatile u8 SBFIRST             ;
    /*# of Stop Bits*/
    volatile u8 StopBits            ; 
    
    /*Baud Rate*/
    volatile u16 BaudRate           ;

   /*Interrupt Enable / Disable*/
    volatile u8 Interrupt   ;



}MUARTConfig ; 

typedef enum 
{
    UART_EOk               , 
    WordLenghtError        , 
    Wrong_Oversampling     , 
    ParitySelectionError   , 
    WrongStopbitSelection  , 
	ErrorReceieving        ,
    WrongInterruptChoice    

    

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


/*MSB / LSB */
#define MSB           2 
#define LSB           3



/*# of Stop Bits*/
#define OneStopBit        0  
#define HalfStopBit       1
#define TwoStopBit        2
#define OneAHalfStopBit   3 

/*CPU To Control Baud_Rate */
#define F_CPU     8000000

/*Threshold Value For Time Out In Receieve_Synchoronus_Function*/
#define THRESHOLD_VALUE 5000UL 



/*Interrupt States*/
#define Interrupt_Disable           0
#define Interrupt_TX_RX_Enable      1
#define Interrupt_Enable_TX_Only    2
#define Interrupt_Enable_RX_Only    3

/****************************UART REGISTERS -> Bits************************/

/*Oversampling Bit */
#define OVER_SAM   15 
#define PCE        10
/*Parity Selection Bit*/ 
#define PS          9
/*Auto Baud Rate Bit */
#define ABREN       20 
/*MSB & LSB Selection Bit */
#define MSBFIRST    19
/*Stop Bits For Selection */
#define STOP0       12
#define STOP1       13
/*Enable Transmission */
#define TE           3
/*Enable Receieving*/
#define RE           2
/*Enable UART Bit*/
#define UE           0
/* Interrupt Bits */
#define TXEIE        7
#define TCIE         6
#define RXNEIE       5


/*WordLenghtBits */
#define M1      28 
#define M0      12






/**
  ******************************************************************************
  * brief  : Initializes the USART module with the provided configuration.
  * param  : Add_CnfgStruct: Pointer to a structure containing USART configuration.
  * retval : UART_tenuErrorStatus: Error status after initialization.
  *             - UART_EOk: No error.
  *             - WordLenghtError: Invalid word length.
  *             - Wrong_Oversampling: Invalid oversampling value.
  *             - ParitySelectionError: Invalid parity selection.
  *             - WrongStopbitSelection: Invalid stop bit configuration.
  ******************************************************************************
  */

UART_tenuErrorStatus MUSART_voidInit(MUARTConfig *Add_CnfgStruct);



/**
  ******************************************************************************
  * brief   Sends a character synchronously via USART1.
  * param   Copy_u8Char: The character to be sent.
  * retval  None
  ******************************************************************************
  */

void MUSART1_VidSendCharSync (u8 UART_INDEX, u8 Copy_u8Char);

/**
  ******************************************************************************
  * brief   Sends a null-terminated string synchronously via USART1.
  * param   Copy_ptrString: Pointer to the string to be sent.
  * retval  None
  ******************************************************************************
  */
void MUSART1_VidSendStringSynch (u8 UART_INDEX, u8 * Copy_ptrString );

/**
  ******************************************************************************
  * brief   Receives a character synchronously via USART1.
  * param   pData: Pointer to a variable to store the received character.
  * retval  UART_tenuErrorStatus: Error status after receiving.
  *             - UART_EOk: No error.
  *             - ErrorReceieving: Error occurred during the receiving process.
  ******************************************************************************
  */
UART_tenuErrorStatus MUSART1_u8RecCharSynch (u8 UART_INDEX,u32* pData) ;



void MUSART1_VidSetCallBack(u8 UART_INDEX, void (*ptr) (u32)) ; 


#endif
