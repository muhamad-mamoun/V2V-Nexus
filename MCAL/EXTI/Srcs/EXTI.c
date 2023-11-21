/***********************************************

Description : SOURCE CODE FILE FOR EXTI DRIVER                    

Date        : 19-11-2023

Author      : Mohamed Khaled

***********************************************/
/*************************************||INCLUDES||*****************************************/
#include "std_types.h"
#include "common_macros.h"

#include "EXTI.h"
#include "EXTI_Prev.h"
#include "EXTI_Config.h"

void (*Call_Ptr[15])(void);

/*
 *Function Name : EXTI_enuEnableINT
 *Description   : Function to Enable Interrupt on specific PIN
 *Parameters    : Copy_u8ExtiID-->> Register Number from the "Macros For REGx"
									Copy_u8PinID-->>a Specific PIN Number "Macros For PINS"
									Copy_u8EdgeID-->>Raising Edge Or Falling Edge "R or F Edges"
 *Return Type   : EXTI_ErrorStatus enum type of Error Status
 */
EXTI_ErrorStatus EXTI_enuEnableINT(u8 Copy_u8ExtiID,u8 Copy_u8PinID,u8 Copy_u8EdgeID)
{
	//Error Status 
	u8 ErrorStatus=EXTI_enuOK;
	//Calculate the Register Number
	u8 LOC_u8RegID=Copy_u8ExtiID/4;
	//Calculate the Pin Offset
	u8 LOC_u8PINOffset=(Copy_u8ExtiID%4)*4;
	//if the Copy_u8ExtiID is Invalid Input
	if(Copy_u8ExtiID>EXTI15)
	{
		ErrorStatus=	EXTI_WrongReg;
	}
	//if the Copy_u8EdgeID is Invalid Input
	if(Copy_u8EdgeID>EXTI_FALLING)
	{
		ErrorStatus=EXTI_WrongEdge;
	}
	//set the Pin to its Coresponding Bits  
	SYSCFG_EXTIx[LOC_u8RegID]=(Copy_u8PinID<<LOC_u8PINOffset);
  SET_BIT(EXTI_IMR1,Copy_u8ExtiID);
	//if Copy_u8EdgeID is EXTI_RAISING
	if(Copy_u8EdgeID==EXTI_RAISING)
	{
		SET_BIT(EXTI_RTSR1,Copy_u8ExtiID);
	}
		//if Copy_u8EdgeID is EXTI_FALLING
	else if(Copy_u8EdgeID==EXTI_FALLING)
	{
				SET_BIT(EXTI_FTSR1,Copy_u8ExtiID);

	}
	//return ErrorStatus
	return ErrorStatus;
}

/*
 *Function Name : EXTI_enuEnableINT
 *Description   : Function to Enable Interrupt on specific PIN
 *Parameters    : Copy_u8ExtiID-->> Register Number from the "Macros For REGx"
									Copy_u8PinID-->>a Specific PIN Number "Macros For PINS"
									Copy_u8EdgeID-->>Raising Edge Or Falling Edge "R or F Edges"
 *Return Type   : EXTI_ErrorStatus enum type of Error Status
 */
EXTI_ErrorStatus EXTI_enuDisableINT(u8 Copy_u8ExtiID)
{
	//Error Status 
	u8 ErrorStatus=EXTI_enuOK;
	
	//if the Copy_u8ExtiID is Invalid Input
	if(Copy_u8ExtiID>EXTI15)
	{
		ErrorStatus=	EXTI_WrongReg;
	}
	//clear the coresponding bit 
	CLR_BIT(EXTI_IMR1,Copy_u8ExtiID);
	
	//return ErrorStatus
	return ErrorStatus;
}

/*
 *Function Name : EXTI_enuCallBack
 *Description   : Call Back Function to EXTIx
 *Parameters    : void (*Func)(void)-->> Pointer to the CallBack Function 
									Copy_u8FuncIndex-->>Index in the Array 
*Return Type   : 	None
 */
 EXTI_ErrorStatus EXTI_enuCallBack(void (*Func)(void),u8 Copy_u8FuncIndex)
 {
	 //Error Status 
	u8 ErrorStatus=EXTI_enuOK;
	
	if(Func==PTR_NULL)
	{
		ErrorStatus=EXTI_NullPtr;
	}
	
	Call_Ptr[Copy_u8FuncIndex]=Func;
	
	return ErrorStatus;
 }
