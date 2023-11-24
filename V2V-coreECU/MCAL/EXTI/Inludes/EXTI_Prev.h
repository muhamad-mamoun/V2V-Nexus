/***********************************************

Description : Private File for the EXTI Driver                  

Date        : 19-11-2023

Author      : Mohamed Khaled

***********************************************/
#ifndef EXTI_PRV_H //-Start
#define EXTI_PRV_H //-Guard


/*Base Address of SYSCFG 0x40010000 + EXTIx Register Offset 0x08*/
#define SYSCFG_EXTIx       ((vu32*)0x40010008)


/*Base address of EXTI   0x40010400*/
#define EXTI_IMR1          *((vu32*)0x40010400)
#define EXTI_EMR1          *((vu32*)0x40010404)
#define EXTI_RTSR1         *((vu32*)0x40010408)
#define EXTI_FTSR1         *((vu32*)0x4001040C)
#define EXTI_PR1           *((vu32*)0x40010414)


#endif //-End Guard
