/***********************************************

Description : HEADER FILE FOR Can DRIVER 

Date        : 25-11-2023

Author      : Mohamed Khaled

***********************************************/

#ifndef CAN_H
#define CAN_H

#include "std_types.h"

extern u32 ARR_Recieved_Data[14][8];
/**************************************************||ERROR STATUS ENUM ||********************************************************************/
typedef enum
{
	CAN_enuOK,
	CAN_NullPointerError,
	CAN_WrongParam,
	CAN_NORecievedData
}Error_status;


/**************************************************||Initialization Enums ||********************************************************************/

/*
FIFO_NOTLOCKED  : Receive FIFO not locked on overrun. Once a receive FIFO is full the next incoming 
message will overwrite the previous one.

FIFO_LOCKED     : Receive FIFO locked against overrun. Once a receive FIFO is full the next incoming 
message will be discarded.
*/
typedef enum
{
	FIFO_NOTLOCKED,
	FIFO_LOCKED
}FIFO_LockedMoede ;


/*
Automatically_Retransmit : The CAN hardware will automatically retransmit the message until it has been 
successfully transmitted according to the CAN standard.

ONLY_ONCE                : A message will be transmitted only once, independently of the transmission result 
(successful, error or arbitration lost).
*/
typedef enum
{
	Automatically_Retransmit,
	ONLY_ONCE
}AUTO_Retransmission ;

/*
This bit controls the behavior of the CAN hardware on message reception during Sleep 
mode. 
Automatic_WakeUP_Disable: The Sleep mode is left on software request by clearing the SLEEP bit of the CAN_MCR 
register.
Automatic_WakeUP_Enable : The Sleep mode is left automatically by hardware on CAN message detection.
The SLEEP bit of the CAN_MCR register and the SLAK bit of the CAN_MSR register are 
cleared by hardware.
*/
typedef enum
{
	Automatic_WakeUP_Disable,
	Automatic_WakeUP_Enable
}AUTO_WakeUP;

/*
This bit controls the behavior of the CAN hardware on leaving the Bus-Off state. 

Automatic_BusOff_Disable: The Bus-Off state is left on software request, once 128 occurrences of 11 recessive bits 
have been monitored and the software has first set and cleared the INRQ bit of the 
CAN_MCR register.

Automatic_BusOff_Enable : The Bus-Off state is left automatically by hardware once 128 occurrences of 11 recessive 
bits have been monitored.
*/
typedef enum
{
	Automatic_BusOff_Disable,
	Automatic_BusOff_Enable
	
}AUTO_BusOfMangment ;


/*
Time_Trigger_Disable: Time Triggered Communication mode disabled.
Time_Trigger_Enable : Time Triggered Communication mode enabled
*/
typedef enum
{
	Time_Trigger_Disable,
	Time_Trigger_Enable
}Time_TriggerMode ;


/*
CAN_Debug_Working: CAN working during debug

CAN_Debug_Frozen : CAN reception/transmission frozen during debug. Reception FIFOs can still be 
accessed/controlled normally
*/
typedef enum
{
		CAN_Debug_Working,
		CAN_Debug_Frozen
}DEBUG_Freeze ;


/*
This bit controls the transmission order when several mailboxes are pending at the same 
time.
Message_ID   : Priority driven by the identifier of the message

Request_Order: Priority driven by the request order (chronologically)
*/
typedef enum
{
		Message_ID,
		Request_Order
}Transmit_FifoPriority ;

/**************************************************||ConfigType Struct For Init API ||********************************************************************/
typedef struct
{

	FIFO_LockedMoede         LockedMode;

	AUTO_Retransmission      Retransmission;

	AUTO_WakeUP              WakeUp;

	AUTO_BusOfMangment       BussOffManag;

	Time_TriggerMode         TimeTriggered;

	DEBUG_Freeze             DebugFreeze;
	
	Transmit_FifoPriority    FifoPriority;
	
	u32                      BuadRate_prescaler;

}CAN_ConfigType;


/**************************************************||Transmit Enums ||********************************************************************/
//ID
typedef enum
{
	STD_ID, // Standard identifier
	EX_ID // Extended identifier
}CAN_TarnsmitID;	

//RTR
typedef enum
{
	DataFram,
	RemoteFram
}CAN_RemoteFrameRequest;

//DLC
typedef enum
{
	_0Byte_Data,
	_1Byte_Data,
	_2Byte_Data,
	_3Byte_Data,
	_4Byte_Data,
	_5Byte_Data,
	_6Byte_Data,
	_7Byte_Data,
	_8Byte_Data,
}CAN_DataLenthCode;

/**************************************************||CAN_Transmit Struct ||********************************************************************/

typedef struct
{
	CAN_TarnsmitID               TEXID       ;
	CAN_RemoteFrameRequest       RemoteFrame;
	CAN_DataLenthCode            DataLenth  ;
	u32                          ID         ;
	pu8                          Data       ;
}CAN_Transmit;

/**************************************************||Filter Enums ||********************************************************************/
typedef enum
{
		MaskMode,
	  ListMode
}FilterMode;

typedef enum
{
	Dual,
	Single
}FilterScale;

typedef enum
{
	FIFO_0,
	FIFO_1
}FIFOAssignment;
typedef enum
{
	FilterNumber0,
	FilterNumber1,
	FilterNumber2,
	FilterNumber3,
	FilterNumber4,
	FilterNumber5,
	FilterNumber6,
	FilterNumber7,
	FilterNumber8,
	FilterNumber9,
	FilterNumber10,
	FilterNumber11,
	FilterNumber12,
	FilterNumber13,
}FilterNUM;
typedef enum
{
	_1R,
	_2R
}REG_NUM;
/**************************************************||Create Filter Struct ||********************************************************************/
typedef struct
{
	FilterNUM      FilterNumber;
	REG_NUM        RegNumber;  
	FilterMode     Mask;
	FilterScale    Scale;
	FIFOAssignment FIFO_Asign;
	u32            FilterID;
	u32            FilterMask;
}FilterConfig;

/**************************************************||Recieve Data Enums ||********************************************************************/
typedef enum
{
	Index_0,
	Index_1,
	Index_2,
	Index_3,
	Index_4,
	Index_5,
	Index_6,
	Index_7,
	Index_8,
	Index_9,
	Index_10,
	Index_11,
	Index_12,
	Index_13,
}DataIndex;

/**************************************************||Modes change ||********************************************************************/
typedef enum
{
	SLEEP_Mode,
	INIT_Mode,
	NORMAL_Mode
}CAN_Modes;

/**************************************************||Abort Transmit ||********************************************************************/
typedef enum
{
	MailBox0,
	MailBox1,
	MailBox2
}AbortMessage;

/**************************************************||Test Modes ||********************************************************************/
typedef enum
{
	SilentMode,
	LoopBackMode,
	CombinedLoopBackMode
}TestModes;
/**************************************************||Functions Prototype ||********************************************************************/

/*
 *Function Name : CAN_enuInit
 *Description   : Function to Initialize the CAN Peripheral
 *Parameters    : Config_Ptr -> Pointer to CAN_ConfigType configuration struct 
 *Return Type   : Error_status->Error Status Enum
 */
Error_status CAN_enuInit(const CAN_ConfigType* Config_Ptr);


/*
 *Function Name : CAN_enuTransmit
 *Description   : Function to Transmit Data
 *Parameters    : Trans_Ptr -> Pointer to CAN_Transmit Transmit struct 
 *Return Type   : Error_status->Error Status Enum
 */
Error_status CAN_enuTransmit(const CAN_Transmit* Trans_Ptr);

/*
 *Function Name : CAN_enuCreateFilter
 *Description   : Function to create Filter 
 *Parameters    : FilterCFG_Ptr -> Pointer to FilterConfig Filter Configuration struct 
 *Return Type   : Error_status->Error Status Enum
 */
Error_status CAN_enuCreateFilter(const FilterConfig* FilterCFG_Ptr);

/*
 *Function Name : CAN_enuRecieve
 *Description   : Function to Recieve Data 
 *Parameters    : ADD_u8DataIndex -> Pointer to u8 variable that take the data index in ARR_Recieved_Data array
 *Return Type   : Error_status->Error Status Enum
 */
Error_status CAN_enuRecieve(u8* ADD_u8DataIndex);

/*
 *Function Name : CAN_enuChangeMode
 *Description   : Function to change Can Mode
 *Parameters    : Mode -> CAN_Modes Enum type 
 *Return Type   : Error_status->Error Status Enum
 */
Error_status CAN_enuChangeMode(CAN_Modes Mode);

/*
 *Function Name : CAN_enuAbort
 *Description   : Function to Abort Messages
 *Parameters    : mailBox -> mailBox Enum type 
 *Return Type   : Error_status->Error Status Enum
 */
Error_status CAN_enuAbort(AbortMessage mailBox);
/*
 *Function Name : CAN_enuGoTestMode
 *Description   : Function to Go to Test Mode
 *Parameters    : TMode -> TestModes Enum type 
 *Return Type   : Error_status->Error Status Enum
 */
Error_status CAN_enuGoTestMode(TestModes TMode);

#endif
