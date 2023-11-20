/*Simple Example*/
/* Private*/



/* Interface */
#include "Bit_utils.h"
#include "std_types.h"

#include "UART_interface.h"



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

#define MUSART ((USART_t *)0x40013800 )





UART_tenuErrorStatus MUSART_voidInit(MUARTConfig *Add_CnfgStruct)
{
   UART_tenuErrorStatus ErrorStatus =  UART_EOk   ; 

   switch (Add_CnfgStruct->WordLength)
   {
    case OneStart_8Data:  
                   //MUSART->CR1 |=  OneStart_8Data ;      
										CLR_BIT(MUSART->CR1,28);
										CLR_BIT(MUSART->CR1,12);
    break ;
		/*NOT TESTED*/
    case OneStart_7Data: 
                    MUSART->CR1 |=  OneStart_7Data ;                

    break ; 
		/*NOT TESTED*/
    case OneStart_9Data:
                   MUSART->CR1 |=  OneStart_9Data ;                
    break ;
		
    default :    
                ErrorStatus = WordLenghtError ; 
    break ; 
    

   }

   /*******************************************************************************/
   switch (Add_CnfgStruct->OverSampling)
   {
     case OV_16:
                CLR_BIT(MUSART->CR1 , OVER_SAM) ; 
     break ; 
		 
     case OV_8 :  
                SET_BIT(MUSART->CR1 , OVER_SAM) ; 
     break ;
		 
     default :   ErrorStatus = Wrong_Oversampling ; 
     break ;  
   }

   /**********************************************************************/
   switch (Add_CnfgStruct->ParitySelection)
   {
    case  Parity_Disabled : 
                  CLR_BIT(MUSART->CR1 , PCE) ;                 
    break ; 
		
    case EvenParity : 
                  SET_BIT(MUSART->CR1 , PCE) ;                 
                  CLR_BIT(MUSART->CR1 , PS) ;                 

    break ;
		
    case OddParity:
                    SET_BIT(MUSART->CR1 , PCE) ;                 
                    SET_BIT(MUSART->CR1 , PS) ;                 

    break ; 
		
    default :   ErrorStatus = ParitySelectionError ; 
    break ; 

   }
    
    /* Auto Baud Rate Disable*/
      CLR_BIT (MUSART->CR2 , ABREN) ; 
    


/*************************************************************/
   switch (Add_CnfgStruct->SBFIRST)
   {
    case LSB : 
               CLR_BIT (MUSART->CR2 , MSBFIRST) ;       
    break ; 
		
    case MSB : 
              SET_BIT (MUSART->CR2 , MSBFIRST) ; 
    break ; 

   }

   /***********************************************************************/
      switch (Add_CnfgStruct->StopBits)
      {
        case OneStopBit : 
                       CLR_BIT (MUSART->CR2 , STOP0) ; 
                       CLR_BIT (MUSART->CR2 , STOP1) ; 
        break ;
				
        case HalfStopBit: 
                       SET_BIT (MUSART->CR2 , STOP0) ; 
                       CLR_BIT (MUSART->CR2 , STOP1) ; 
                         
        break ; 
				
        case TwoStopBit  : 
                       CLR_BIT (MUSART->CR2 , STOP0) ; 
                       SET_BIT (MUSART->CR2 , STOP1) ; 
                        
        break ;
				
        case OneAHalfStopBit : 
                       SET_BIT (MUSART->CR2 , STOP0) ; 
                       SET_BIT (MUSART->CR2 , STOP1) ; 
        break ; 
				
        default:  ErrorStatus = WrongStopbitSelection ;
        break ; 
      }


    /*****************************************BAUD_RATE***************************************************8*/
    
				MUSART->BRR = 0x341 /*0x1D4C*/ /*((F_CPU)/(Add_CnfgStruct->BaudRate))*/;
    
         /* Rx Enable*/
         SET_BIT(MUSART->CR1 , RE) ;
 
        /*TX Enable */
         SET_BIT(MUSART->CR1 , TE ) ; 

        /*Enable UART*/
         SET_BIT(MUSART->CR1 , UE ) ; 
			
			return ErrorStatus;

}


void MUSART1_VidSendCharSync ( u8 Copy_u8Char ){

	MUSART -> TDR = Copy_u8Char ;

	while( GET_BIT( MUSART -> ISR , 6 ) == 0) ; 
}


void MUSART1_VidSendStringSynch ( u8 * Copy_ptrString )
	{

	u8 LOC_u8Iterator = 0 ;

	while ( Copy_ptrString[ LOC_u8Iterator ] != '\0' ){

		MUSART1_VidSendCharSync( Copy_ptrString[ LOC_u8Iterator ] );
		LOC_u8Iterator++ ;
	}
}

UART_tenuErrorStatus MUSART1_u8RecCharSynch (u32* pData)
{
 
	UART_tenuErrorStatus ErrorStatus = UART_EOk ; 
	
	u32 LOC_TimeOut = 0 ;

	while((GET_BIT (MUSART->ISR,5) == 0) && ( LOC_TimeOut < 5000 ) )
	{
		LOC_TimeOut++;
	}
	if( LOC_TimeOut >= 5000 )
	{
      ErrorStatus = ErrorReceieving ; 
  }
	else
	{
		*pData = MUSART -> RDR;
	}

		return ErrorStatus;

}


