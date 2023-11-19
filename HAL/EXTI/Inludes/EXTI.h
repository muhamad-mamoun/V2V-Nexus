/***********************************************

Description : Header File for the EXTI Driver                  

Date        : 19-11-2023

Author      : Mohamed Khaled

***********************************************/
#ifndef EXTI_H //-Start
#define EXTI_H //-Guard
#include "std_types.h"
/******************************************||ERROR STATUS ENUM||**************************************************************************/
typedef enum
{
	EXTI_enuOK,
	EXTI_WrongReg,
	EXTI_WrongEdge,
	EXTI_NullPtr
}EXTI_ErrorStatus;	

/*******************************************||Macros For REGx and Indexes for CallBack||**********************************************************************/
#define EXTI0             0
#define EXTI1             1
#define EXTI2             2
#define EXTI3             3
#define EXTI4             4
#define EXTI5             5
#define EXTI6             6
#define EXTI7             7
#define EXTI8             8
#define EXTI9             9
#define EXTI10            10
#define EXTI11            11
#define EXTI12            12
#define EXTI13            13
#define EXTI14            14
#define EXTI15            15

/*******************************************||Macros For PINS||**********************************************************************/
//PINx0        Reg EXTI0
#define PINA0             0x0
#define PINB0             0x1 
#define PINC0             0x2
#define PIND0             0x3
#define PINE0             0x4
#define PINF0             0x5
#define PING0             0x5
#define PINH0             0x6
//PINx1        Reg EXTI1
#define PINA1             0x0
#define PINB1             0x1 
#define PINC1             0x2
#define PIND1             0x3
#define PINE1             0x4
#define PINF1             0x5
#define PING1             0x5
#define PINH1             0x6
//PINx2        Reg EXTI2
#define PINA2             0x0
#define PINB2             0x1 
#define PINC2             0x2
#define PIND2             0x3
#define PINE2             0x4
#define PINF2             0x5
#define PING2             0x5
#define PINH2             0x6
//PINx3        Reg EXTI3
#define PINA3             0x0
#define PINB3             0x1 
#define PINC3             0x2
#define PIND3             0x3
#define PINE3             0x4
#define PINF3             0x5
#define PING3             0x5
#define PINH3             0x6
//PINx4        Reg EXTI4
#define PINA4             0x0
#define PINB4             0x1 
#define PINC4             0x2
#define PIND4             0x3
#define PINE4             0x4
#define PINF4             0x5
#define PING4             0x5
#define PINH4             0x6
//PINx5        Reg EXTI5
#define PINA5             0x0
#define PINB5             0x1 
#define PINC5             0x2
#define PIND5             0x3
#define PINE5             0x4
#define PINF5             0x5
#define PING5             0x5
#define PINH5             0x6
//PINx6        Reg EXTI6
#define PINA6             0x0
#define PINB6             0x1 
#define PINC6             0x2
#define PIND6             0x3
#define PINE6             0x4
#define PINF6             0x5
#define PING6             0x5
#define PINH6             0x6
//PINx7        Reg EXTI7
#define PINA7             0x0
#define PINB7             0x1 
#define PINC7             0x2
#define PIND7             0x3
#define PINE7             0x4
#define PINF7             0x5
#define PING7             0x5
#define PINH7             0x6
//PINx8        Reg EXTI8
#define PINA8             0x0
#define PINB8             0x1 
#define PINC8             0x2
#define PIND8             0x3
#define PINE8             0x4
#define PINF8             0x5
#define PING8             0x5
#define PINH8             0x6
//PINx9        Reg EXTI9
#define PINA9             0x0
#define PINB9             0x1 
#define PINC9             0x2
#define PIND9             0x3
#define PINE9             0x4
#define PINF9             0x5
#define PING9             0x5
#define PINH9             0x6
//PINx10        Reg EXTI10
#define PINA10           0x0
#define PINB10           0x1 
#define PINC10           0x2
#define PIND10           0x3
#define PINE10           0x4
#define PINF10           0x5
#define PING10           0x5
#define PINH10           0x6
//PINx11        Reg EXTI11
#define PINA11           0x0
#define PINB11           0x1 
#define PINC11           0x2
#define PIND11           0x3
#define PINE11           0x4
#define PINF11           0x5
#define PING11           0x5
#define PINH11           0x6
//PINx12        Reg EXTI12
#define PINA12           0x0
#define PINB12           0x1 
#define PINC12           0x2
#define PIND12           0x3
#define PINE12           0x4
#define PINF12           0x5
#define PING12           0x5
#define PINH12           0x6
//PINx13        Reg EXTI13
#define PINA13           0x0
#define PINB13           0x1 
#define PINC13           0x2
#define PIND13           0x3
#define PINE13           0x4
#define PINF13           0x5
#define PING13           0x5
#define PINH13           0x6
//PINx14        Reg EXTI14
#define PINA14           0x0
#define PINB14           0x1 
#define PINC14           0x2
#define PIND14           0x3
#define PINE14           0x4
#define PINF14           0x5
#define PING14           0x5
#define PINH14           0x6
//PINx15        Reg EXTI15
#define PINA15           0x0
#define PINB15           0x1 
#define PINC15           0x2
#define PIND15           0x3
#define PINE15           0x4
#define PINF15           0x5
#define PING15           0x5
#define PINH15           0x6
/*******************************************||R or F Edges||**********************************************************************/
#define EXTI_RAISING     0               

#define EXTI_FALLING     1

/*******************************************||Function Prototypes||**********************************************************************/
/*
 *Function Name : EXTI_enuEnableINT
 *Description   : Function to Enable Interrupt on specific PIN
 *Parameters    : Copy_u8ExtiID-->> Register Number from the "Macros For REGx"
									Copy_u8PinID-->>a Specific PIN Number "Macros For PINS"
									Copy_u8EdgeID-->>Raising Edge Or Falling Edge "R or F Edges"
 *Return Type   : EXTI_ErrorStatus enum type of Error Status
 */
EXTI_ErrorStatus EXTI_enuEnableINT(u8 Copy_u8ExtiID,u8 Copy_u8PinID,u8 Copy_u8EdgeID);

/*
 *Function Name : EXTI_enuEnableINT
 *Description   : Function to Enable Interrupt on specific PIN
 *Parameters    : Copy_u8ExtiID-->> Register Number from the "Macros For REGx"
									Copy_u8PinID-->>a Specific PIN Number "Macros For PINS"
									Copy_u8EdgeID-->>Raising Edge Or Falling Edge "R or F Edges"
 *Return Type   : EXTI_ErrorStatus enum type of Error Status
 */
EXTI_ErrorStatus EXTI_enuDisableINT(u8 Copy_u8ExtiID);

/*
 *Function Name : EXTI_enuCallBack
 *Description   : Call Back Function to EXTIx
 *Parameters    : void (*Func)(void)-->> Pointer to the CallBack Function 
									Copy_u8FuncIndex-->>Index in the Array 
*Return Type   : 	None
 */
 EXTI_ErrorStatus EXTI_enuCallBack(void (*Func)(void),u8 Copy_u8FuncIndex);

#endif //-End Guard
