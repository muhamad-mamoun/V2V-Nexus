/***********************************************

Description : PRIVATE FILE FOR NVIC DRIVER

Date        : 15-11-2023

Author      : Mohamed Khaled

***********************************************/

#ifndef NVIC_PREV_H //-Start 
#define NVIC_PREV_H //-Guard


//NVIC BASE ADDRESS "0xE000E100"

//Interrupt Set Enable Registers
#define NVIC_ISER0     *((vu32*)0xE000E100)
#define NVIC_ISER1     *((vu32*)0xE000E104)
#define NVIC_ISER2     *((vu32*)0xE000E108)

//Interrupt Clear Enable Registers
#define NVIC_ICER0     *((vu32*)0xE000E180)
#define NVIC_ICER1     *((vu32*)0xE000E184)
#define NVIC_ICER2     *((vu32*)0xE000E188)

//Interrupt Set Pending Flag Registers
#define NVIC_ISPR0     *((vu32*)0xE000E200)
#define NVIC_ISPR1     *((vu32*)0xE000E204)
#define NVIC_ISPR2     *((vu32*)0xE000E208)

//Interrupt Clear Pending Flag Registers
#define NVIC_ICPR0     *((vu32*)0xE000E280)
#define NVIC_ICPR1     *((vu32*)0xE000E284)
#define NVIC_ICPR2     *((vu32*)0xE000E288)

//Interrupt Active Bit Registers
#define NVIC_IABR0     *((vu32*)0xE000E300)
#define NVIC_IABR1     *((vu32*)0xE000E304)
#define NVIC_IABR2     *((vu32*)0xE000E308)


//Interrupt priority Register
#define NVIC_IPRx     ((vu32*)0xE000E400)

//Maximum nUmber of Peripheral													 
#define NVIC_MAXIRQS                83


//Configuration For Groups and SubGroups
#define  Groups16_SUB0               0x05FA0000
#define  Groups8_SUB2                0x05FA0400
#define  Groups4_SUB4                0x05FA0500
#define  Groups2_SUB8                0x05FA0600
#define  Groups0_SUB16               0x05FA0700



#define SCB_AIRCR                         *((vu32*)0xE000ED0C) 


#endif //-End Guard        
