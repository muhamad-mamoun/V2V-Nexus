/*
/*
=======================================================================================================================
File Name    : V2V-coreECU.c
Date Created : Nov 15, 2023
Description  : The interface file for the Core ECU application.
=======================================================================================================================
*/


#ifndef APP_V2V_COREECU_H_
#define APP_V2V_COREECU_H_

/*=====================================================================================================================
                                               < Includes >
=====================================================================================================================*/



/*=====================================================================================================================
                                < Definitions and Static Configurations >
=====================================================================================================================*/

#define MAX_DISTANCE                            (50)
#define NUM_OF_CHECK_LOGS                       (3)
#define CAN_DataID 	                            (0x200)

/************* LOGS *************/
#define TEMP_OK                                 (0x11)
#define TEMP_OVERHEAT                           (0x5A)
#define TEMP_NOTRESPONDING                      (0xFC)

#define US_OK                                   (0x12)
#define US_NOTRESPONDING                        (0xFE)

#define CAN_OK                                  (0x15)
#define CAN_NOTRESPONDING                       (0xDE)

#define TEMP_DATA_INDEX                         (0)
#define US_DATA_INDEX                           (1)
#define CAN_DATA_INDEX                          (2)

#define EEPROM_START_ADDRESS                    (0x10)

/*=====================================================================================================================
                                       < Shared Global Variables >
=====================================================================================================================*/



/*=====================================================================================================================
                                       < User-defined Data Types >
=====================================================================================================================*/

typedef struct
{
    volatile u8 Global_u8Direction;
    volatile u8 Global_u8Speed;
    volatile u8 Global_u8BrakeStatus;
}Data_t;

/*=====================================================================================================================
                                < Peripheral Registers and Bits Definitions >
=====================================================================================================================*/



/*=====================================================================================================================
                                         < Function-like Macros >
=====================================================================================================================*/



/*=====================================================================================================================
                                         < Function-like Macros >
=====================================================================================================================*/



/*=====================================================================================================================
                                         < Functions Prototypes >
=====================================================================================================================*/

void Suspend_MyTasks();
void Resume_MyTasks();
void SYS_INIT();

void Motor_SetDirectionT(void* pvParameter); 
void EEPROM_WriteLogsT (void* pvparam);
void US_GetDistanceT(void* pvparam);
void CAN_SendDataT(void* pvparam);
void Button_StateT(void* pvparam);

#endif /* APP_V2V_COREECU_H_ */
