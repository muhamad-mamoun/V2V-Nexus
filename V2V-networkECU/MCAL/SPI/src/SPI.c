

#include "../../../OTHERS/std_types.h"
#include "../../../OTHERS/common_macros.h"

#include "../inc/SPI_prv.h"
#include "../inc/SPI_cfg.h"
#include "../inc/SPI.h"


/*insert queue simply insert desired data to be sent in queue*/
static SPI_ERROR_STATUS_t insert_queue(u16 Copy_u16_data);
/*truncate queue simply dequeue desired data to be sent*/
static SPI_ERROR_STATUS_t truncate_queue(void);

/*GLOBAL PTR TO FUNCTION*/
void (*gl_ptr_Function)(void) = PTR_NULL;

/*QUEUE STRUCTURE FOR SENDING DATA*/
SPI_QUEUE_t  gl_SPI_data_queue =
{
	.s16_front_queue = EMPTY_POSITOIN ,
	.s16_rear_queue  = EMPTY_POSITOIN ,
};

/* RECEIEVE BUFFER */
static u16 sgl_arr_Recieve_Buffer[MAX_QUEUE_SIZE] = {};
static u16 sgl_Recieve_Index                      = FALSE;

/*

 NAME  : SPI_voidInit
 DESC  : Initilize Spi peripheral based on selected options in cfg file
 PARAMS: void
 RETURN: void

*/
void SPI_voidInit(void)
{
	 /*Prescaller Selection*/
    #if  SPI1_PRESCALLER < MAX_PRE_OPTION
    SPI1->CR1 &= SPI_PRE_MASK;  // CLR BR BITS 
    SPI1->CR1 |= (SPI1_PRESCALLER<<BR); // SET SELECTED Prescaller
    #else
    #error "SPI1_PRESCALLER ERROR IN CFG"
    #endif
	
	 /*Clock Mode Selection*/
    #if   SPI1_CLOCK_MODE == SPI_MODE0
      CLR_BIT(SPI1->CR1,CPOL);
      CLR_BIT(SPI1->CR1,CPHA);

    #elif SPI1_CLOCK_MODE == SPI_MODE1
      CLR_BIT(SPI1->CR1,CPOL);
      SET_BIT(SPI1->CR1,CPHA);
    #elif SPI1_CLOCK_MODE == SPI_MODE2
      SET_BIT(SPI1->CR1,CPOL);
      CLR_BIT(SPI1->CR1,CPHA);
    #elif SPI1_CLOCK_MODE == SPI_MODE3
      SET_BIT(SPI1->CR1,CPOL);
      SET_BIT(SPI1->CR1,CPHA);    
    #else
    #error "SPI1_CLOCK_MODE ERROR IN CFG"
    #endif
	
    /*Data Size Selection*/
    #if   SPI1_DATA_SIZE == SPI_8BIT_DATA
      CLR_BIT(SPI1->CR1,DFF);
    #elif SPI1_DATA_SIZE == SPI_16BIT_DATA
      SET_BIT(SPI1->CR1,DFF);
    #else
    #error "SPI1_DATA_SIZE ERROR IN CFG"
    #endif
    /*Data Order Selection*/
    #if   SPI1_DATA_ORDER == SPI_MSB_FIRST
      CLR_BIT(SPI1->CR1,LSBFIRST);
    #elif SPI1_DATA_ORDER == SPI_LSB_FIRST
      SET_BIT(SPI1->CR1,LSBFIRST);
    #else
    #error "SPI1_DATA_ORDER ERROR IN CFG"
    #endif
    
    /*SS Manage Selection*/
    #if   SPI1_SS_MANAGE == HW_SLAVE_MANAGEMENT
      CLR_BIT(SPI1->CR1,SSM);
    #elif SPI1_SS_MANAGE == SW_SLAVE_MANAGEMENT
      SET_BIT(SPI1->CR1,SSM);
    #else
    #error "SPI1_SS_MANAGE ERROR IN CFG"
    #endif

    

    /*Master Slave Selection*/
    #if   SPI1_MASTER_SLAVE == SPI_SLAVE
      CLR_BIT(SPI1->CR1,MSTR);
      SET_BIT(SPI1->CR2,RXNEIE); /* ENABLE INTERRUPT FOR RECEPTION */
    #elif SPI1_MASTER_SLAVE == SPI_MASTER
      SET_BIT(SPI1->CR1,MSTR);
      //SET_BIT(SPI1->CR2,TXEIE); /* ENABLE INTERRUPT FOR TRANSIMISSION */

    #else
    #error "SPI1_MASTER_SLAVE ERROR IN CFG"
    #endif

   

    /*Enable SPI1*/
    SET_BIT(SPI1->CR1,SPE);
}

/*

 NAME  : SPI_voidSendReceieveCharSynch
 DESC  : Send And Recieve Char From connected Node with Blocking Approach
 PARAMS: Copy_u16_data ----> Data To Be Sent
         ptr_u16_data  ----> Address Variable to store recieved data 
 RETURN: void

*/
void SPI_voidSendReceieveCharSynch(u8 Copy_u16_data,u8 *ptr_u16_data)
{
    /*WRITE DATA ON SPI DATA REG*/
    *(vu8*)(&SPI1->DR) = (u8)Copy_u16_data;
    /*WAIT UNTILL SPI IS NOT BUSY*/
    while (GET_BIT(SPI1->SR,7) == TRUE);
    while (GET_BIT(SPI1->SR,1) == FALSE);
    /* Return Recieved Data*/
    *ptr_u16_data = *(vu8*)(&SPI1->DR) ;
}

/*

 NAME  : SPI_enu_SendDataAsynch
 DESC  : Send Data to connected Node with non-Blocking Approach
 PARAMS: Copy_u16_data ----> Data To Be Sent 
 RETURN: void

*/
void SPI_enu_SendDataAsynch(u16 Copy_u16_data)
{
    /* SENT DATA TO QUEUE TO BE SENT*/
    insert_queue(Copy_u16_data);
    /* DEQUEUE*/
    truncate_queue();
}

/*

 NAME  : SPI_enu_SendStreamAsynch
 DESC  : Send Stream of Data to connected Node with non-Blocking Approach
 PARAMS: ptr_u16_data       ----> Address array of Data To Be Sent 
         Copy_u8_streamSize ----> Size of Data 
 RETURN: void

*/
void SPI_enu_SendStreamAsynch(u16 *ptr_u16_data,u8 Copy_u8_streamSize)
{
    /*Initilize Local Itrator to Control Buffer Index*/
    u8 loc_buff_index = FALSE;
    /*Loop Until Itrator Reaches Size of Data */
    while (loc_buff_index < Copy_u8_streamSize)
    {
        /* SENT DATA TO QUEUE TO BE SENT THEN INCREAMENT ITRATOR*/
        insert_queue(ptr_u16_data[loc_buff_index++]);
    }
    /*DEQUEUE FRONT DATA FROM QUEUE*/
    truncate_queue(); 
}

/*

 NAME  : SPI_enu_SendRecieveStreamSynch
 DESC  : Send Stream of Data and Recieve The Same Size Of Data
         to connected Node with non-Blocking Approach
 PARAMS: ptr_u16_data       ----> Address array of Data To Be Sent 
         ptr_u16_Reception  ----> Address array To Store Receveid Data
         Copy_u8_streamSize ----> Size of Data of Both Sending and Receieving 
                                  MUST BE SAME SIZE
 RETURN: void

*/
void SPI_enu_SendRecieveStreamSynch(u8 *ptr_u16_data,u8 *ptr_u16_Reception,u8 Copy_u8_streamSize)
{
    /*Initilize Local Itrator to Control Buffer Index*/
    u8 loc_u8_Buff_itrator = FALSE;
     /*Loop Until Itrator Reaches Size of Data */
    while ( loc_u8_Buff_itrator < Copy_u8_streamSize)
    {
        /*SEND DATA AND RECIEVE*/
        SPI_voidSendReceieveCharSynch(ptr_u16_data[loc_u8_Buff_itrator],&ptr_u16_Reception[loc_u8_Buff_itrator]);
        /*Increament Itrator*/
        loc_u8_Buff_itrator++;
    }
}

/*

 NAME  : SPI_enu_GetDataAsynch
 DESC  : Recieve Data Stored In Recieving Buffer with non-Blocking Approach
 PARAMS: ptr_u16_data       ----> Address Variable To Store Receveid Data 
 RETURN: void

*/
void SPI_enu_GetDataAsynch(u16 *ptr_u16_data)
{
    // Check That There's Data Received
    if ( sgl_Recieve_Index > FALSE)
    {
       /* Fetch Data From Buffer and Decremment Index*/
       *ptr_u16_data = sgl_arr_Recieve_Buffer[sgl_Recieve_Index--];
    }
    else
    {
        // NO DATA TO RECEIVE
        *ptr_u16_data = 0xFFFF;
    }
   
}

/*

 NAME  : SPI_voidsetCallBck
 DESC  : Set Call Back Function To Execute When Send is Complete Or Reception Is Complete
 PARAMS: ptrFuction       ----> Address Function To Be Executed 
 RETURN: void

*/
void SPI_voidsetCallBck (void(*ptrFuction)(void))
{
    // Check That Adddress Function Is Valid
    if ( ptrFuction != PTR_NULL)
    {
        /*ASSIGN ADDRESS TO GLOBAL POINTER TO FUNCTION*/
        gl_ptr_Function = ptrFuction;
    }
    else
    {
        // nothing
    }
}


// function to handle enqueue operation
static SPI_ERROR_STATUS_t insert_queue(u16 Copy_u16_data)
{
	//status code
    SPI_ERROR_STATUS_t loc_enu_StatusCode = SPI_OKAY;
	
	//check if queue full
	if( gl_SPI_data_queue.s16_rear_queue >= MAX_QUEUE_SIZE)
	{
		loc_enu_StatusCode = QUEUE_OVERFLOW;
	}
	else
	{
		//check if queue empty
		if( gl_SPI_data_queue.s16_front_queue == EMPTY_POSITOIN)
		{
			gl_SPI_data_queue.s16_front_queue = FALSE;
		}
		
		// increment rear then store byte in queue
		gl_SPI_data_queue.s16_rear_queue++;
		gl_SPI_data_queue.u16_arr_data[gl_SPI_data_queue.s16_rear_queue] = Copy_u16_data;
	}	
	
	return loc_enu_StatusCode;
}


// function to handle dequeue operation
static SPI_ERROR_STATUS_t truncate_queue(void)
{
	
	//status code
    SPI_ERROR_STATUS_t loc_enu_StatusCode = SPI_OKAY;
	
	// check if all bytes has been sent OR queue is empty
	if((gl_SPI_data_queue.s16_front_queue > gl_SPI_data_queue.s16_rear_queue) || (gl_SPI_data_queue.s16_front_queue == EMPTY_POSITOIN))
	{
		// set front and rear to defaults
		gl_SPI_data_queue.s16_front_queue = EMPTY_POSITOIN;
		gl_SPI_data_queue.s16_rear_queue  = EMPTY_POSITOIN;
		
		//status code queue is empty
		loc_enu_StatusCode = QUEUE_EMPTY;
	}
	else
	{
		//send current byte and increment front
		SPI1->DR = gl_SPI_data_queue.u16_arr_data[gl_SPI_data_queue.s16_front_queue];
		gl_SPI_data_queue.s16_front_queue++;
	}
	return loc_enu_StatusCode;
}


void SPI1_IRQHandler(void)
{


    // TODO HANDLE ISR FOR RECEPTION
	#if   SPI1_MASTER_SLAVE == SPI_SLAVE
       sgl_Recieve_Index = (u8)SPI1->DR;
       gl_ptr_Function();
    #elif SPI1_MASTER_SLAVE == SPI_MASTER
      if (truncate_queue() == QUEUE_EMPTY)
      {
        if (gl_ptr_Function != PTR_NULL)
        {
            gl_ptr_Function();
        }
      }
    #endif

}


