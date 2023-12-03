/***********************************************

Description : Header FILE FOR BLE DRIVER                    

Date        : 21-11-2023

Author      : Mohamed Khaled

***********************************************/


#ifndef BLE_H //Strat
#define BLE_H //Guard

#include "std_types.h"

#define NO_REC_KEY        (0xFF)


/*
 *Function Name : HBLE_VInit 
 *Description   : Initialization Function Define UART Call Back Function 
 *Parameters    : None 
 *Return Type   : None
 */
void HBLE_VInit(void);

/*
 *Function Name : HBLE_VGetKey
 *Description   : Function to return the Desired Key 
 *Parameters    : pointer to carry the value of BLE Key
 *Return Type   : None
 */
void HBLE_VGetKey(pu8 ADD_pu8Key);



#endif //end Guard
