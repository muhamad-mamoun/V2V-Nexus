/*Simple Example*/
/* Private*/



/* Common Libraries...*/
#include "std_types.h"
#include "common_macros.h"
#include "UART_interface.h"
#include "UART_Private.h"

/*CallBack Function */
void (*MUSART1_CallBack)(u32);
void (*MUSART2_CallBack)(u32);
void (*MUSART3_CallBack)(u32);

u32 arr_Bases[3]={UART_1_BASE,UART_2_BASE,UART_3_BASE};





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

UART_tenuErrorStatus MUSART_voidInit(MUARTConfig *Add_CnfgStruct)
{
   UART_tenuErrorStatus ErrorStatus =  UART_EOk   ; 
   
	 
/*********************************WordLenght********************************/
   switch (Add_CnfgStruct->WordLength)
   {
    case OneStart_8Data:  
                   //MUSART->CR1 |=  OneStart_8Data ;      
										CLR_BIT(MUSART(arr_Bases[Add_CnfgStruct->UART_Index])->CR1,28);
										CLR_BIT(MUSART(arr_Bases[Add_CnfgStruct->UART_Index])->CR1,12);
    break ;
		/*NOT TESTED*/
    case OneStart_7Data: 
                    MUSART(arr_Bases[Add_CnfgStruct->UART_Index])->CR1 |=  OneStart_7Data ;                

    break ; 
    case OneStart_9Data:
                   MUSART(arr_Bases[Add_CnfgStruct->UART_Index])->CR1 |=  OneStart_9Data ;                
    break ;
		
    default :    
                ErrorStatus = WordLenghtError ; 
    break ; 
    

   }

   /******************************OverSampling*************************************************/
   switch (Add_CnfgStruct->OverSampling)
   {
     case OV_16:
                CLR_BIT(MUSART(arr_Bases[Add_CnfgStruct->UART_Index])->CR1 , OVER_SAM) ; 
               /*Baud Rate For Sampling By 16 */
              MUSART(arr_Bases[Add_CnfgStruct->UART_Index])->BRR =((F_CPU)/(Add_CnfgStruct->BaudRate));
              //MUSART->BRR = 0x341 
             /*0x1D4C*/ 


     break ; 
		 
     case OV_8 :  
                SET_BIT(MUSART(arr_Bases[Add_CnfgStruct->UART_Index])->CR1 , OVER_SAM) ; 
                MUSART(arr_Bases[Add_CnfgStruct->UART_Index])->BRR =(((2)*(F_CPU))/(Add_CnfgStruct->BaudRate));

     break ;
		 
     default :   ErrorStatus = Wrong_Oversampling ; 
     break ;  
   }

   /******************************ParitySelection****************************************/
   switch (Add_CnfgStruct->ParitySelection)
   {
    case  Parity_Disabled : 
                  CLR_BIT(MUSART(arr_Bases[Add_CnfgStruct->UART_Index])->CR1 , PCE) ;                 
    break ; 
		
    case EvenParity : 
                  SET_BIT(MUSART(arr_Bases[Add_CnfgStruct->UART_Index])->CR1 , PCE) ;                 
                  CLR_BIT(MUSART(arr_Bases[Add_CnfgStruct->UART_Index])->CR1 , PS) ;                 

    break ;
		
    case OddParity:
                    SET_BIT(MUSART(arr_Bases[Add_CnfgStruct->UART_Index])->CR1 , PCE) ;                 
                    SET_BIT(MUSART(arr_Bases[Add_CnfgStruct->UART_Index])->CR1 , PS) ;                 

    break ; 
		
    default :   ErrorStatus = ParitySelectionError ; 
    break ; 

   }
    
    /* Auto Baud Rate Disable*/
      CLR_BIT (MUSART(arr_Bases[Add_CnfgStruct->UART_Index])->CR2 , ABREN) ; 
    


/****************************SignificantBit *********************************/
   switch (Add_CnfgStruct->SBFIRST)
   {
    case LSB : 
               CLR_BIT (MUSART(arr_Bases[Add_CnfgStruct->UART_Index])->CR2 , MSBFIRST) ;       
    break ; 
		
    case MSB : 
              SET_BIT (MUSART(arr_Bases[Add_CnfgStruct->UART_Index])->CR2 , MSBFIRST) ; 
    break ; 

   }

   /*********************************STOPBITS**************************************/
      switch (Add_CnfgStruct->StopBits)
      {
        case OneStopBit : 
                       CLR_BIT (MUSART(arr_Bases[Add_CnfgStruct->UART_Index])->CR2 , STOP0) ; 
                       CLR_BIT (MUSART(arr_Bases[Add_CnfgStruct->UART_Index])->CR2 , STOP1) ; 
        break ;
				
        case HalfStopBit: 
                       SET_BIT (MUSART(arr_Bases[Add_CnfgStruct->UART_Index])->CR2 , STOP0) ; 
                       CLR_BIT (MUSART(arr_Bases[Add_CnfgStruct->UART_Index])->CR2 , STOP1) ; 
                         
        break ; 
				
        case TwoStopBit  : 
                       CLR_BIT (MUSART(arr_Bases[Add_CnfgStruct->UART_Index])->CR2 , STOP0) ; 
                       SET_BIT (MUSART(arr_Bases[Add_CnfgStruct->UART_Index])->CR2 , STOP1) ; 
                        
        break ;
				
        case OneAHalfStopBit : 
                       SET_BIT (MUSART(arr_Bases[Add_CnfgStruct->UART_Index])->CR2 , STOP0) ; 
                       SET_BIT (MUSART(arr_Bases[Add_CnfgStruct->UART_Index])->CR2 , STOP1) ; 
        break ; 
				
        default:  ErrorStatus = WrongStopbitSelection ;
        break ; 
      }


      /*********************************Interrupt Choice *********************************************/
            switch (Add_CnfgStruct->Interrupt)
            {
             case Interrupt_Disable:
                                    CLR_BIT(MUSART(arr_Bases[Add_CnfgStruct->UART_Index])->CR1, RXNEIE); // Disable RXNE interrupt
                                    CLR_BIT(MUSART(arr_Bases[Add_CnfgStruct->UART_Index])->CR1, TXEIE);  // Disable TXE interrupt
                                                                 break ; 
             case Interrupt_TX_RX_Enable:
                                    SET_BIT(MUSART(arr_Bases[Add_CnfgStruct->UART_Index])->CR1, RXNEIE); // Enable RXNE interrupt
                                    SET_BIT(MUSART(arr_Bases[Add_CnfgStruct->UART_Index])->CR1, TXEIE);  // Enable TXE interrupt

                                                                break ;
             case Interrupt_Enable_TX_Only : 
                                    SET_BIT(MUSART(arr_Bases[Add_CnfgStruct->UART_Index])->CR1, TXEIE); // Enable RXNE interrupt
                                                                break ;
             case Interrupt_Enable_RX_Only: 
                                    SET_BIT(MUSART(arr_Bases[Add_CnfgStruct->UART_Index])->CR1, RXNEIE); // Enable RXNE interrupt
                                                               break ; 
             default : ErrorStatus = Interrupt_Enable_RX_Only;
             break ; 

            }


    
       /***************************TX_RX_UE -> Enables**********************************************/
         
         /* Rx Enable*/
         SET_BIT(MUSART(arr_Bases[Add_CnfgStruct->UART_Index])->CR1 , RE) ;
 
        /*TX Enable */
         SET_BIT(MUSART(arr_Bases[Add_CnfgStruct->UART_Index])->CR1 , TE ) ; 

        /*Enable UART*/
         SET_BIT(MUSART(arr_Bases[Add_CnfgStruct->UART_Index])->CR1 , UE ) ; 
			



			return ErrorStatus;

}

/**
  ******************************************************************************
  * brief   Sends a character synchronously via USART1.
  * param   Copy_u8Char: The character to be sent.
  * retval  None
  ******************************************************************************
  */
void MUSART1_VidSendCharSync (u8 UART_INDEX, u8 Copy_u8Char)
{
	MUSART(arr_Bases[UART_INDEX]) -> TDR = Copy_u8Char ;

	while( GET_BIT( MUSART(arr_Bases[UART_INDEX]) -> ISR , 6 ) == 0) ; 

       /*Clear FLag*/
      SET_BIT(MUSART(arr_Bases[UART_INDEX])->ICR ,6);



}

/**
  ******************************************************************************
  * brief   Sends a null-terminated string synchronously via USART1.
  * param   Copy_ptrString: Pointer to the string to be sent.
  * retval  None
  ******************************************************************************
  */
void MUSART1_VidSendStringSynch (u8 UART_INDEX, u8 * Copy_ptrString )
	{

	u8 LOC_u8Iterator = 0 ;

	while ( Copy_ptrString[ LOC_u8Iterator ] != '\0' )
  {

		MUSART1_VidSendCharSync(UART_INDEX, Copy_ptrString[ LOC_u8Iterator ] );
		LOC_u8Iterator++ ;
	}
}


/**
  ******************************************************************************
  * brief   Receives a character synchronously via USART1.
  * param   pData: Pointer to a variable to store the received character.
  * retval  UART_tenuErrorStatus: Error status after receiving.
  *             - UART_EOk: No error.
  *             - ErrorReceieving: Error occurred during the receiving process.
  ******************************************************************************
  */
UART_tenuErrorStatus MUSART1_u8RecCharSynch (u8 UART_INDEX,u32* pData)
{
	UART_tenuErrorStatus ErrorStatus = UART_EOk ; 

    /*Clear Flag By Software..*/
   // SET_BIT(MUSART->RQR ,3);

	while((GET_BIT (MUSART(arr_Bases[UART_INDEX])->ISR,5) == 0));
	*pData = MUSART(arr_Bases[UART_INDEX]) -> RDR;
	return ErrorStatus;

}





/**
  *****************************************************************************
  * brief   Sets the callback function for USART1.
  * param   ptr: Pointer to the callback function.
  * retval  None
  *****************************************************************************
  */

void MUSART1_VidSetCallBack(u8 UART_INDEX ,void (*ptr) (u32) )
{
  if (ptr != PTR_NULL)
  {
		if (UART_INDEX == FALSE)
		{
			MUSART1_CallBack = ptr ;
		}
		else if (UART_INDEX == TRUE)
		{
			MUSART2_CallBack = ptr ;
		}
		else
		{
			MUSART3_CallBack = ptr ;
		}
	
  } 
}

/**
  ******************************************************************************
  * brief   Interrupt handler for USART1.
  * param   None
  * retval  None
  ******************************************************************************
  */
void USART1_IRQHandler(void)
{    
	     MUSART1_CallBack(MUSART(UART_1_BASE) -> RDR);
	     /*Clear Flag By Software..*/
	     MUSART(UART_1_BASE) -> ICR |= (1<<3) | (1<<4) | (1<<6); 
	     MUSART(UART_1_BASE) -> RQR |= (1<<4) | (1<<3);

}


void USART2_IRQHandler(void)
{    
	     MUSART1_CallBack(MUSART(UART_2_BASE) -> RDR);
	     /*Clear Flag By Software..*/
	     MUSART(UART_2_BASE) -> ICR |= (1<<3) | (1<<4) | (1<<6); 
	     MUSART(UART_2_BASE) -> RQR |= (1<<4) | (1<<3);

}


void USART3_IRQHandler(void)
{    
	     MUSART1_CallBack(MUSART(UART_3_BASE) -> RDR);
	     /*Clear Flag By Software..*/
	     MUSART(UART_3_BASE) -> ICR |= (1<<3) | (1<<4) | (1<<6); 
	     MUSART(UART_3_BASE) -> RQR |= (1<<4) | (1<<3);

}

