#ifndef SPI_H_
#define SPI_H_


typedef enum 
{
  SPI_OKAY,
  QUEUE_OVERFLOW,
  QUEUE_EMPTY
}SPI_ERROR_STATUS_t;


/*

 NAME  : SPI_voidInit
 DESC  : Initilize Spi peripheral based on selected options in cfg file
 PARAMS: void
 RETURN: void

*/
void SPI_voidInit(void);

/*

 NAME  : SPI_voidSendReceieveCharSynch
 DESC  : Send And Recieve Char From connected Node with Blocking Approach
 PARAMS: Copy_u16_data ----> Data To Be Sent
         ptr_u16_data  ----> Address Variable to store recieved data 
 RETURN: void

*/
void SPI_voidSendReceieveCharSynch(u16 Copy_u16_data,u16 *ptr_u16_data);
/*

 NAME  : SPI_enu_SendDataAsynch
 DESC  : Send Data to connected Node with non-Blocking Approach
 PARAMS: Copy_u16_data ----> Data To Be Sent 
 RETURN: void

*/
void SPI_enu_SendDataAsynch(u16 Copy_u16_data);
/*

 NAME  : SPI_enu_SendStreamAsynch
 DESC  : Send Stream of Data to connected Node with non-Blocking Approach
 PARAMS: ptr_u16_data       ----> Address array of Data To Be Sent 
         Copy_u8_streamSize ----> Size of Data 
 RETURN: void

*/
void SPI_enu_SendStreamAsynch(u16 *ptr_u16_data,u8 Copy_u8_streamSize);

/*

 NAME  : SPI_enu_SendRecieveStreamSynch
 DESC  : Send Stream of Data and Recieve The Same Size Of Data
         to connected Node with Blocking Approach
 PARAMS: ptr_u16_data       ----> Address array of Data To Be Sent 
         ptr_u16_Reception  ----> Address array To Store Receveid Data
         Copy_u8_streamSize ----> Size of Data of Both Sending and Receieving 
                                  MUST BE SAME SIZE
 RETURN: void

*/
void SPI_enu_SendRecieveStreamSynch(u16 *ptr_u16_data,u16 *ptr_u16_Reception,u8 Copy_u8_streamSize);

/*

 NAME  : SPI_enu_GetDataAsynch
 DESC  : Recieve Data Stored In Recieving Buffer with non-Blocking Approach
 PARAMS: ptr_u16_data       ----> Address Variable To Store Receveid Data 
 RETURN: void

*/
void SPI_enu_GetDataAsynch(u16 *ptr_u16_data);

/*

 NAME  : SPI_voidsetCallBck
 DESC  : Set Call Back Function To Execute When Send is Complete Or Reception Is Complete
 PARAMS: ptrFuction       ----> Address Function To Be Executed 
 RETURN: void

*/
void SPI_voidsetCallBck (void(*ptrFuction)(void));


#endif



