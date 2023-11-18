/***********************************************

Description : SOURCE CODE FILE FOR NVIC DRIVER                    

Date        : 15-11-2023

Author      : Mohamed Khaled

***********************************************/

/*************************************||INCLUDES||*****************************************/
#include "std_types.h"
#include "bit_math.h"
#include "NVIC.h"
#include "NVIC_Prev.h"
#include "NVIC_Config.h"

/*
 *Function Name : NVIC_Init
 *Description   : Function to define Groups and Sub Groups Priority 
 *Parameters    : None
 *Return Type   : None
 */
void NVIC_Init(void)
{
	SCB_AIRCR=NVIC_GROUP_SUBG;
}
/*
 *Function Name : MNVIC__enable_irq
 *Description   : Function to Enable all IRQs 
 *Parameters    : None
 *Return Type   : None
 */

void MNVIC__Venable_irq (void)               // Clears PRIMASK
{
	__asm("CPSIE I") ;
}


/*
 *Function Name : MNVIC__disable_irq
 *Description   : Function to Disable all IRQs 
 *Parameters    : None
 *Return Type   : None
 */
void MNVIC__Vdisable_irq (void)            // Sets PRIMASK
{
		__asm("CPSID I") ;

}


/*
 *Function Name : MNVIC_EnuEnablePerInterrupt
 *Description   : Function to Enable EX peripheral Interrupt
 *Parameters    : Copy_u8RegID ->>Register ID
									Copy_u32PerId ->>Peripheral ID
 *Return Type   : NVIC_ErrorStatu ->>Error Status Enum
 */
NVIC_ErrorStatu MNVIC_EnuEnablePerInterrupt(u8 Copy_u8RegID,u32 Copy_u32PerId)
{
	//Error Status Variable
	u8 ErrorStatus=NVIC_enuOK;
	
	//which Register and Peripheral
	switch(Copy_u8RegID)
	{
		//case Register NVIC_ISER0
		case NVIC_REG0 :
			//Set the Register NVIC_ISER0
		      NVIC_ISER0 |=Copy_u32PerId;
			break;//end case NVIC_REG0
		//case Register NVIC_ISER1
		case NVIC_REG1 :
			//Set the Register NVIC_ISER0
		      NVIC_ISER1 |=Copy_u32PerId;
			break;//end case NVIC_REG1
		//case Register NVIC_ISER2
		case NVIC_REG2 :
			//Set the Register NVIC_ISER0
		      NVIC_ISER2 |=Copy_u32PerId;
			break;//end case NVIC_REG2
		//if an invalid number 
		default :
			//generate Error status 
			ErrorStatus=NVIC_enuErrorRegNum;
			break;//End switch 
	}
	//return Error status 
	return ErrorStatus;
}


/*
 *Function Name : MNVIC_EnuDisablePerInterrupt
 *Description   : Function to Disable EX peripheral Interrupt
 *Parameters    : Copy_u8RegID ->>Register ID
									Copy_u32PerId ->>Peripheral ID
 *Return Type   : NVIC_ErrorStatu ->>Error Status Enum
 */
NVIC_ErrorStatu MNVIC_EnuDisablePerInterrupt(u8 Copy_u8RegID,u32 Copy_u32PerId)
{
	//Error Status Variable
	u8 ErrorStatus=NVIC_enuOK;
	
	//which Register and Peripheral
	switch(Copy_u8RegID)
	{
		//case Register NVIC_ICER0
		case NVIC_REG0 :
			//Set the Register NVIC_ICER0
		      NVIC_ICER0 |=Copy_u32PerId;
			break;//end case NVIC_REG0
		//case Register NVIC_ICER1
		case NVIC_REG1 :
			//Set the Register NVIC_ICER1
		      NVIC_ICER1 |=Copy_u32PerId;
			break;//end case NVIC_REG1
		//case Register NVIC_ICER2
		case NVIC_REG2 :
			//Set the Register NVIC_ICER2
		      NVIC_ICER2 |=Copy_u32PerId;
			break;//end case NVIC_REG2
		//if an invalid number 
		default :
			//generate Error status 
			ErrorStatus=NVIC_enuErrorRegNum;
			break;//End switch 
	}
	//return Error status 
	return ErrorStatus;
}



/*
 *Function Name : MNVIC_EnuSetPendingFlag
 *Description   : Function to Set peripheral Pending Flag
 *Parameters    : Copy_u8RegID ->>Register ID
									Copy_u32PerId ->>Peripheral ID
 *Return Type   : NVIC_ErrorStatu ->>Error Status Enum
 */
NVIC_ErrorStatu MNVIC_EnuSetPendingFlag(u8 Copy_u8RegID,u32 Copy_u32PerId)
{
	//Error Status Variable
	u8 ErrorStatus=NVIC_enuOK;
	
	//which Register and Peripheral
	switch(Copy_u8RegID)
	{
		//case Register NVIC_ISPR0
		case NVIC_REG0 :
			//Set the Register NVIC_ISPR0
		      NVIC_ISPR0 |=Copy_u32PerId;
			break;//end case NVIC_REG0
		//case Register NVIC_ISPR1
		case NVIC_REG1 :
			//Set the Register NVIC_ISPR1
		      NVIC_ISPR1 |=Copy_u32PerId;
			break;//end case NVIC_REG1
		//case Register NVIC_ISPR2
		case NVIC_REG2 :
			//Set the Register NVIC_ISPR2
		      NVIC_ISPR2 |=Copy_u32PerId;
			break;//end case NVIC_REG2
		//if an invalid number 
		default :
			//generate Error status 
			ErrorStatus=NVIC_enuErrorRegNum;
			break;//End switch 
	}
	//return Error status 
	return ErrorStatus;
}

/*
 *Function Name : MNVIC_EnuClearPendingFlag
 *Description   : Function to Clear peripheral Pending Flag
 *Parameters    : Copy_u8RegID ->>Register ID
									Copy_u32PerId ->>Peripheral ID
 *Return Type   : NVIC_ErrorStatu ->>Error Status Enum
 */
NVIC_ErrorStatu MNVIC_EnuClearPendingFlag(u8 Copy_u8RegID,u32 Copy_u32PerId)
{
	//Error Status Variable
	u8 ErrorStatus=NVIC_enuOK;
	
	//which Register and Peripheral
	switch(Copy_u8RegID)
	{
		//case Register NVIC_ICPR0
		case NVIC_REG0 :
			//Set the Register NVIC_ICPR0
		      NVIC_ICPR0 |=Copy_u32PerId;
			break;//end case NVIC_REG0
		//case Register NVIC_ICPR1
		case NVIC_REG1 :
			//Set the Register NVIC_ICPR1
		      NVIC_ICPR1 |=Copy_u32PerId;
			break;//end case NVIC_REG1
		//case Register NVIC_ICPR2
		case NVIC_REG2 :
			//Set the Register NVIC_ICPR2
		      NVIC_ICPR2 |=Copy_u32PerId;
			break;//end case NVIC_REG2
		//if an invalid number 
		default :
			//generate Error status 
			ErrorStatus=NVIC_enuErrorRegNum;
			break;//End switch 
	}
	//return Error status 
	return ErrorStatus;
}


/*
 *Function Name : MNVIC_EnuActiveFlagStatus
 *Description   : Function to GET  peripheral Active Flag Status
 *Parameters    : Copy_u8RegID ->>Register ID
									Copy_u32PerId->>Peripheral ID
									ADD_pu8BitVla->>Pointer to variable that carry Bit Value
 *Return Type   : NVIC_ErrorStatu ->>Error Status Enum
 */
NVIC_ErrorStatu MNVIC_EnuActiveFlagStatus(u8 Copy_u8RegID,u32 Copy_u32PerId,pu8 ADD_pu8BitVla)
{
	//Error Status Variable
	u8 ErrorStatus=NVIC_enuOK;
	
	if(ADD_pu8BitVla==PTR_NULL)
	{
		ErrorStatus=NVIC_enuNullPointer;
	}
	//which Register and Peripheral
	switch(Copy_u8RegID)
	{
		//case Register NVIC_IABR0
		case NVIC_REG0 :
			//GET the PeripheralActive Flag Status
			*ADD_pu8BitVla=GET_BIT(NVIC_IABR0,Copy_u32PerId);
		break;//end case NVIC_REG0
		//case Register NVIC_IABR1
		case NVIC_REG1 :
			//GET the PeripheralActive Flag Status
			*ADD_pu8BitVla=GET_BIT(NVIC_IABR1,Copy_u32PerId);
			break;//end case NVIC_REG1
		//case Register NVIC_IABR2
		case NVIC_REG2 :
			//GET the PeripheralActive Flag Status
			*ADD_pu8BitVla=GET_BIT(NVIC_IABR2,Copy_u32PerId);
			break;//end case NVIC_REG2
		//if an invalid number 
		default :
			//generate Error status 
			ErrorStatus=NVIC_enuErrorRegNum;
			break;//End switch 
	}
	//return Error status 
	return ErrorStatus;
}


NVIC_ErrorStatu MNVIC_EnuSetPriorityGroup(u32 Copy_u32INTID,u8 Copy_u8Group_Prior,u8 Copy_u8SUBg_Prior)
{
	//Error Status Variable
	u8 ErrorStatus=NVIC_enuOK;
	//Calculate the REG ID 
	u8 LOC_u8RegID=Copy_u32INTID/4;
	//Calculate the Per ID Offset
	u8 LOC_u8PerOffset=(Copy_u32INTID%4)*8;
	
	if(Copy_u32INTID >NVIC_MAXIRQS)
	{
		ErrorStatus=NVIC_enuWrongPerID;
	}

//see which NVIC_GROUP_SUBG configuration 	
#if(NVIC_GROUP_SUBG==Groups16_SUB0)
NVIC_IPRx[LOC_u8RegID] =(Copy_u8Group_Prior<<LOC_u8PerOffset);
#elif(NVIC_GROUP_SUBG==Groups8_SUB2)
NVIC_IPRx[LOC_u8RegID] =(Copy_u8Group_Prior<<LOC_u8PerOffset) |(Copy_u8SUBg_Prior<<LOC_u8PerOffset );
#elif(NVIC_GROUP_SUBG==Groups4_SUB4)
NVIC_IPRx[LOC_u8RegID] =(Copy_u8Group_Prior<<LOC_u8PerOffset) |(Copy_u8SUBg_Prior<<LOC_u8PerOffset) ;
#elif(NVIC_GROUP_SUBG==Groups2_SUB8)	
	NVIC_IPRx[LOC_u8RegID] =(Copy_u8Group_Prior<<LOC_u8PerOffset) |(Copy_u8SUBg_Prior<<LOC_u8PerOffset) ;
#elif(NVIC_GROUP_SUBG==Groups0_SUB16)
	NVIC_IPRx[LOC_u8RegID] =(Copy_u8SUBg_Prior<<LOC_u8PerOffset) ;

#endif	
	return ErrorStatus;
}



void MNVIC_VSystemReset(void)
{
		SCB_AIRCR =0x05FA0004;
}