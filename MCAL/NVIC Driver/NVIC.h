/***********************************************

Description : HEADER FILE FOR NVIC DRIVER 

Date        : 15-11-2023

Author      : Mohamed Khaled

***********************************************/

#ifndef NVIC_H //-Start 
#define NVIC_H //-Guard

#include "std_types.h"
/******************************************||ERROR STATUS ENUM||**************************************************************************/
typedef enum
{
	NVIC_enuOK,
	NVIC_enuErrorRegNum,
	NVIC_enuNullPointer,
	NVIC_enuWrongPerID
}NVIC_ErrorStatu;
/*******************************************||Macros For registerS||**********************************************************************/
#define NVIC_REG0                       0

#define NVIC_REG1                       1

#define NVIC_REG2                       2


/*******************************************||Macros For peripheral per register||**********************************************************/

#define NVIC_REGx_INT0                 (0X00000001)//1.REG0:  WWDG                   2.REG1: I2C1_ER             3.REG2: COMP1_2_3
																																						         
#define NVIC_REGx_INT1                 (0X00000002)//1.REG0:  PVD                    2.REG1: I2C2_EV             3.REG2: COMP4_5_6
																																						         
#define NVIC_REGx_INT2                 (0X00000004)//1.REG0:  TAMPER_STAMP           2.REG1: I2C2_ER             3.REG2: COMP7
																																						         
#define NVIC_REGx_INT3                 (0X00000008)//1.REG0:  RTC_WKUP               2.REG1: SPI1                3.REG2: Reserved
																																						         
#define NVIC_REGx_INT4                 (0X00000010)//1.REG0:  FLASH                  2.REG1: SPI2                3.REG2: Reserved
																																						         
#define NVIC_REGx_INT5                 (0X00000020)//1.REG0:  RCC                    2.REG1: USART1              3.REG2: Reserved
																																						         
#define NVIC_REGx_INT6                 (0X00000040)//1.REG0:  EXTI0                  2.REG1: USART2              3.REG2: Reserved
																																						         
#define NVIC_REGx_INT7                 (0X00000080)//1.REG0:  EXTI1                  2.REG1: USART3              3.REG2: Reserved
																																						         
#define NVIC_REGx_INT8                 (0X00000100)//1.REG0:  EXTI2_TS               2.REG1: EXTI15_10           3.REG2: I2C3_EV(2)
																																						         
#define NVIC_REGx_INT9                 (0X00000200)//1.REG0:  EXTI3                  2.REG1: RTC_Alarm           3.REG2: I2C3_ER(2)
																																						         
#define NVIC_REGx_INT10                (0X00004000)//1.REG0:  EXTI4                  2.REG1: USBWakeUp           3.REG2: USB_HP
																																						         
#define NVIC_REGx_INT11                (0X00000800)//1.REG0:  DMA1_Channe1           2.REG1: TIM8_BRK            3.REG2: USB_LP
																																						         
#define NVIC_REGx_INT12                (0X00001000)//1.REG0:  DMA1_Channe2           2.REG1: TIM8_UP             3.REG2: USB_WakeUp_RMP
																																						         
#define NVIC_REGx_INT13                (0X00002000)//1.REG0:  DMA1_Channe3           2.REG1: TIM8_TRG_COM        3.REG2: TIM20_BRK(2)
																																						         
#define NVIC_REGx_INT14                (0X00004000)//1.REG0:  DMA1_Channe4           2.REG1: TIM8_CC             3.REG2: TIM20_UP(2)
																																						         
#define NVIC_REGx_INT15                (0X00008000)//1.REG0:  DMA1_Channe5           2.REG1: ADC3                3.REG2: TIM20_TRG_COM(2)
																																						         
#define NVIC_REGx_INT16                (0X00010000)//1.REG0:  DMA1_Channe6           2.REG1: FMC(2)              3.REG2: TIM20_CC(2)
																																						         
#define NVIC_REGx_INT17                (0X00020000)//1.REG0:  DMA1_Channe7           2.REG1: Reserved            3.REG2: FPU
																																						         
#define NVIC_REGx_INT18                (0X00040000)//1.REG0:  ADC1_2                 2.REG1: Reserved            3.REG2: Reserved
																																						         
#define NVIC_REGx_INT19                (0X00080000)//1.REG0:  USB_HP/CAN_TX          2.REG1: SPI3                3.REG2: Reserved
																																						         
#define NVIC_REGx_INT20                (0X00100000)//1.REG0:  USB_LP/CAN_RX0         2.REG1: UART4               3.REG2: SPI4
																																						         
#define NVIC_REGx_INT21                (0X00200000)//1.REG0:  CAN_RX1                2.REG1: UART5               3.REG2: Reserved
																																						         
#define NVIC_REGx_INT22                (0X00400000)//1.REG0:  CAN_SCE                2.REG1: TIM6_DAC            3.REG2: Reserved
																																						         
#define NVIC_REGx_INT23                (0X00800000)//1.REG0:  EXTI9_5                2.REG1: TIM7                3.REG2: Reserved
																																								     
#define NVIC_REGx_INT24                (0X01000000)//1.REG0:  TIM1_BRK/TIM15         2.REG1: DMA2_Channe1        3.REG2: Reserved
																																								     
#define NVIC_REGx_INT25                (0X02000000)//1.REG0:  TIM1_UP/TIM16          2.REG1: DMA2_Channe2        3.REG2: Reserved
								
#define NVIC_REGx_INT26                (0X04000000)//1.REG0:  TIM1_TRG_COM/TIM17     2.REG1: DMA2_Channe3        3.REG2: Reserved
								
#define NVIC_REGx_INT27                (0X08000000)//1.REG0:  TIM1_CC                2.REG1: DMA2_Channe4        3.REG2: Reserved
								
#define NVIC_REGx_INT28                (0X10000000)//1.REG0:  TIM2                   2.REG1: DMA2_Channe5        3.REG2: Reserved
								
#define NVIC_REGx_INT29                (0X20000000)//1.REG0:  TIM3                   2.REG1: ADC4                3.REG2: Reserved
								
#define NVIC_REGx_INT30                (0X40000000)//1.REG0:  TIM4                   2.REG1: Reserved            3.REG2: Reserved
								
#define NVIC_REGx_INT31                (0X80000000)//1.REG0:  I2C1_EV                2.REG1: Reserved            3.REG2: Reserved


/*******************************************||Macros For MNVIC_EnuActiveFlagStatus API||**********************************************************/


#define NVIC_REGx_BIT0                 (0)//1.REG0:  WWDG                   2.REG1: I2C1_ER             3.REG2: COMP1_2_3
																																						         
#define NVIC_REGx_BIT1                 (1)//1.REG0:  PVD                    2.REG1: I2C2_EV             3.REG2: COMP4_5_6
																																				         
#define NVIC_REGx_BIT2                 (2)//1.REG0:  TAMPER_STAMP           2.REG1: I2C2_ER             3.REG2: COMP7
																																				         
#define NVIC_REGx_BIT3                 (3)//1.REG0:  RTC_WKUP               2.REG1: SPI1                3.REG2: Reserved
																																				         
#define NVIC_REGx_BIT4                 (4)//1.REG0:  FLASH                  2.REG1: SPI2                3.REG2: Reserved
																																			         
#define NVIC_REGx_BIT5                 (5)//1.REG0:  RCC                    2.REG1: USART1              3.REG2: Reserved
																																			         
#define NVIC_REGx_BIT6                 (6)//1.REG0:  EXTI0                  2.REG1: USART2              3.REG2: Reserved
																																			         
#define NVIC_REGx_BIT7                 (7)//1.REG0:  EXTI1                  2.REG1: USART3              3.REG2: Reserved
																																				         
#define NVIC_REGx_BIT8                 (8)//1.REG0:  EXTI2_TS               2.REG1: EXTI15_10           3.REG2: I2C3_EV(2)
																																		         
#define NVIC_REGx_BIT9                 (9)//1.REG0:  EXTI3                  2.REG1: RTC_Alarm           3.REG2: I2C3_ER(2)
																																		         
#define NVIC_REGx_BIT10                (10)//1.REG0:  EXTI4                  2.REG1: USBWakeUp           3.REG2: USB_HP
																																			         
#define NVIC_REGx_BIT11                (11)//1.REG0:  DMA1_Channe1           2.REG1: TIM8_BRK            3.REG2: USB_LP
																																		         
#define NVIC_REGx_BIT12                (12)//1.REG0:  DMA1_Channe2           2.REG1: TIM8_UP             3.REG2: USB_WakeUp_RMP
																																		         
#define NVIC_REGx_BIT13                (13)//1.REG0:  DMA1_Channe3           2.REG1: TIM8_TRG_COM        3.REG2: TIM20_BRK(2)
																																	         
#define NVIC_REGx_BIT14                (14)//1.REG0:  DMA1_Channe4           2.REG1: TIM8_CC             3.REG2: TIM20_UP(2)
																																		         
#define NVIC_REGx_BIT15                (15)//1.REG0:  DMA1_Channe5           2.REG1: ADC3                3.REG2: TIM20_TRG_COM(2)
																																	         
#define NVIC_REGx_BIT16                (16)//1.REG0:  DMA1_Channe6           2.REG1: FMC(2)              3.REG2: TIM20_CC(2)
																																		         
#define NVIC_REGx_BIT17                (17)//1.REG0:  DMA1_Channe7           2.REG1: Reserved            3.REG2: FPU
																																		         
#define NVIC_REGx_BIT18                (18)//1.REG0:  ADC1_2                 2.REG1: Reserved            3.REG2: Reserved
																																		         
#define NVIC_REGx_BIT19                (19)//1.REG0:  USB_HP/CAN_TX          2.REG1: SPI3                3.REG2: Reserved
																																		         
#define NVIC_REGx_BIT20                (20)//1.REG0:  USB_LP/CAN_RX0         2.REG1: UART4               3.REG2: SPI4
																																			         
#define NVIC_REGx_BIT21                (21)//1.REG0:  CAN_RX1                2.REG1: UART5               3.REG2: Reserved
																																			         
#define NVIC_REGx_BIT22                (22)//1.REG0:  CAN_SCE                2.REG1: TIM6_DAC            3.REG2: Reserved
																																			         
#define NVIC_REGx_BIT23                (23)//1.REG0:  EXTI9_5                2.REG1: TIM7                3.REG2: Reserved
																																					     
#define NVIC_REGx_BIT24                (24)//1.REG0:  TIM1_BRK/TIM15         2.REG1: DMA2_Channe1        3.REG2: Reserved
																																						     
#define NVIC_REGx_BIT25                (25)//1.REG0:  TIM1_UP/TIM16          2.REG1: DMA2_Channe2        3.REG2: Reserved
								
#define NVIC_REGx_BIT26                (26)//1.REG0:  TIM1_TRG_COM/TIM17     2.REG1: DMA2_Channe3        3.REG2: Reserved
							
#define NVIC_REGx_BIT27                (27)//1.REG0:  TIM1_CC                2.REG1: DMA2_Channe4        3.REG2: Reserved
								
#define NVIC_REGx_BIT28                (28)//1.REG0:  TIM2                   2.REG1: DMA2_Channe5        3.REG2: Reserved
								
#define NVIC_REGx_BIT29                (29)//1.REG0:  TIM3                   2.REG1: ADC4                3.REG2: Reserved
									
#define NVIC_REGx_BIT30                (30)//1.REG0:  TIM4                   2.REG1: Reserved            3.REG2: Reserved
									
#define NVIC_REGx_BIT31                (31)//1.REG0:  I2C1_EV                2.REG1: Reserved            3.REG2: Reserved

/*******************************************||MNVIC_EnuSetPriorityGroup||*************************************************************************/

/*
 * Groups16_SUB0   || --->Copy_u8Group_Prior (0-->>15)    ||--->Copy_u8SUBg_Prior(0)
 * Groups8_SUB2    || --->Copy_u8Group_Prior (0-->>7)     ||--->Copy_u8SUBg_Prior(0 / 1)
 * Groups4_SUB4    || --->Copy_u8Group_Prior (0-->>3)     ||--->Copy_u8SUBg_Prior(0-->>3)
 * Groups2_SUB8    || --->Copy_u8Group_Prior (0 / 1)      ||--->Copy_u8SUBg_Prior(0-->>7)
 * Groups0_SUB16   || --->Copy_u8Group_Prior (0)          ||--->Copy_u8SUBg_Prior(0-->>15)
 */
 //if Group 0 or 2
#define NVIC_GROUP0         (0b00000000)//Group 0 2 4 8 16
#define NVIC_GROUP1         (0b10000000)
//if Group 4
#define NVIC_GROUP2         (0b01000000)
#define NVIC_GROUP3         (0b10000000)
#define NVIC_GROUP4         (0b11000000)
//if Group 8 
#define NVIC_GROUP5         (0b00100000)
#define NVIC_GROUP6         (0b01000000)
#define NVIC_GROUP7         (0b01100000)
#define NVIC_GROUP8         (0b10000000)
#define NVIC_GROUP9         (0b10100000)
#define NVIC_GROUP10        (0b11000000)
#define NVIC_GROUP11        (0b11100000)
//if Group 16 and SUB 0 2 4 8 16
#define NVIC_SUB0_G0         (0b00000000)
#define NVIC_SUB1_G1         (0b00010000)
#define NVIC_SUB2_G2         (0b00100000)
#define NVIC_SUB3_G3         (0b00110000)
#define NVIC_SUB4_G4         (0b01000000)
#define NVIC_SUB5_G5         (0b01010000)
#define NVIC_SUB6_G6         (0b01100000)
#define NVIC_SUB7_G7         (0b01110000)
#define NVIC_SUB8_G8         (0b10000000)
#define NVIC_SUB9_G9         (0b10010000)
#define NVIC_SUB10_G10       (0b10100000)
#define NVIC_SUB11_G11       (0b10110000)
#define NVIC_SUB12_G12       (0b11000000)
#define NVIC_SUB13_G13       (0b11010000)
#define NVIC_SUB14_G14       (0b11100000)
#define NVIC_SUB15_G15       (0b11110000)

/*******************************************||Function Prototypes||*************************************************************************/

/*
 *Function Name : NVIC_Init
 *Description   : Function to define Groups and Sub Groups Priority 
 *Parameters    : None
 *Return Type   : None
 */

void NVIC_Init(void);


/*
 *Function Name : MNVIC__enable_irq
 *Description   : Function to Enable all IRQs 
 *Parameters    : None
 *Return Type   : None
 */

void MNVIC__Venable_irq (void);               // Clears PRIMASK



/*
 *Function Name : MNVIC__disable_irq
 *Description   : Function to Disable all IRQs 
 *Parameters    : None
 *Return Type   : None
 */
void MNVIC__Vdisable_irq (void);              // Sets PRIMASK

/*
 *Function Name : MNVIC_EnuEnablePerInterrupt
 *Description   : Function to Enable EX peripheral Interrupt
 *Parameters    : Copy_u8RegID ->>Register ID
									Copy_u32PerId ->>Peripheral ID
 *Return Type   : NVIC_ErrorStatu ->>Error Status Enum
 */
NVIC_ErrorStatu MNVIC_EnuEnablePerInterrupt(u8 Copy_u8RegID,u32 Copy_u32PerId);


/*
 *Function Name : MNVIC_EnuDisablePerInterrupt
 *Description   : Function to Disable EX peripheral Interrupt
 *Parameters    : Copy_u8RegID ->>Register ID
									Copy_u32PerId ->>Peripheral ID
 *Return Type   : NVIC_ErrorStatu ->>Error Status Enum
 */
NVIC_ErrorStatu MNVIC_EnuDisablePerInterrupt(u8 Copy_u8RegID,u32 Copy_u32PerId);


/*
 *Function Name : MNVIC_EnuSetPendingFlag
 *Description   : Function to Set peripheral Pending Flag
 *Parameters    : Copy_u8RegID ->>Register ID
									Copy_u32PerId ->>Peripheral ID
 *Return Type   : NVIC_ErrorStatu ->>Error Status Enum
 */
NVIC_ErrorStatu MNVIC_EnuSetPendingFlag(u8 Copy_u8RegID,u32 Copy_u32PerId);


/*
 *Function Name : MNVIC_EnuClearPendingFlag
 *Description   : Function to Clear peripheral Pending Flag
 *Parameters    : Copy_u8RegID ->>Register ID
									Copy_u32PerId ->>Peripheral ID
 *Return Type   : NVIC_ErrorStatu ->>Error Status Enum
 */
NVIC_ErrorStatu MNVIC_EnuClearPendingFlag(u8 Copy_u8RegID,u32 Copy_u32PerId);


/*
 *Function Name : MNVIC_EnuActiveFlagStatus
 *Description   : Function to GET  peripheral Active Flag Status
 *Parameters    : Copy_u8RegID ->>Register ID
									Copy_u32PerId->>Peripheral ID
									ADD_pu8BitVla->>Pointer to variable that carry Bit Value
 *Return Type   : NVIC_ErrorStatu ->>Error Status Enum
 */
NVIC_ErrorStatu MNVIC_EnuActiveFlagStatus(u8 Copy_u8RegID,u32 Copy_u32PerId,pu8 ADD_pu8BitVla);


 
//------->>>>>>Use this indexes as a parameter  -----Copy_u32INTID
 
 //0.  WWDG                   32.: I2C1_ER             63.: COMP1_2_3
 															     
 //1.  PVD                    33.: I2C2_EV             64.: COMP4_5_6
 													      
 //2.  TAMPER_STAMP           34.: I2C2_ER             65.: COMP7
 													      
 //3.  RTC_WKUP               35.: SPI1                66.: Reserved
 													      
 //4.  FLASH                  36.: SPI2                67.: Reserved
 												        
 //5.  RCC                    37.: USART1              68.: Reserved
 												        
 //6.  EXTI0                  38.: USART2              69.: Reserved
 												        
 //7.  EXTI1                  39.: USART3              70.: Reserved
 													      
 //8.  EXTI2_TS               40.: EXTI15_10           71.: I2C3_EV(2)
 											         
 //9.  EXTI3                  41.: RTC_Alarm           72.: I2C3_ER(2)
 											         
 //10.  EXTI4                  42.: USBWakeUp           73.: USB_HP
 											         
 //11.  DMA1_Channe1           43.: TIM8_BRK            74.: USB_LP
 										         
 //12.  DMA1_Channe2           44.: TIM8_UP             75.: USB_WakeUp_RMP
 										         
 //13.  DMA1_Channe3           45.: TIM8_TRG_COM        76.: TIM20_BRK(2)
 									         
 //14.  DMA1_Channe4           46.: TIM8_CC             77.: TIM20_UP(2)
 										         
 //15.  DMA1_Channe5           47.: ADC3                78.: TIM20_TRG_COM(2
 									         
 //16.  DMA1_Channe6           48.: FMC(2)              79.: TIM20_CC(2)
 										         
 //17.  DMA1_Channe7           49.: Reserved            80.: FPU
 										         
 //18.  ADC1_2                 50.: Reserved            81.: Reserved
 										         
 //19.  USB_HP/CAN_TX          51.: SPI3                82.: Reserved
 										         
 //20.  USB_LP/CAN_RX0         52.: UART4               83.: SPI4
 											         
 //21.  CAN_RX1                53.: UART5               84.: Reserved
 											         
 //22.  CAN_SCE                54.: TIM6_DAC            85.: Reserved
 											         
 //23.  EXTI9_5                55.: TIM7                86.: Reserved
 													     
 //24.  TIM1_BRK/TIM15         56.: DMA2_Channe1        87.: Reserved
 														    
 //25.  TIM1_UP/TIM16          57.: DMA2_Channe2        88.: Reserved
 
 //26.  TIM1_TRG_COM/TIM17     58.: DMA2_Channe3        89.: Reserved
 
 //27.  TIM1_CC                59.: DMA2_Channe4        90.: Reserved
 
 //28.  TIM2                   60.: DMA2_Channe5        91.: Reserved
 
 //29.  TIM3                   61.: ADC4                92.: Reserved
 
 //30.  TIM4                   61.: Reserved            93.: Reserved
 
 //31.  I2C1_EV                62.: Reserved            94.: Reserved
 
/*
 *Function Name : MNVIC_EnuActiveFlagStatus
 *Description   : Function to GET  peripheral Active Flag Status
 *Parameters    : Copy_u8RegID ->>Register ID
									Copy_u32PerId->>Peripheral ID
									ADD_pu8BitVla->>Pointer to variable that carry Bit Value
 *Return Type   : NVIC_ErrorStatu ->>Error Status Enum
 */
NVIC_ErrorStatu MNVIC_EnuSetPriorityGroup(u32 Copy_u32INTID,u8 Copy_u8Group_Prior,u8 Copy_u8SUBg_Prior);


/*
 *Function Name : MNVIC_VSystemReset
 *Description   : Function to GET  peripheral Active Flag Status
 *Parameters    : None
 *Return Type   : None
 */
 
void MNVIC_VSystemReset(void);


#endif //-End Guard
