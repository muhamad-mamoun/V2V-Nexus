/*
=======================================================================================================================
Author       : Mamoun
Module       : GPIO
File Name    : gpio_prv.h
Date Created : Nov 15, 2023
Description  : Private file for the STM32F303 GPIO peripheral driver.
=======================================================================================================================
*/


#ifndef MCAL_GPIO_INCLUDES_GPIO_PRV_H_
#define MCAL_GPIO_INCLUDES_GPIO_PRV_H_

/*=====================================================================================================================
                                < Definitions and Static Configurations >
=====================================================================================================================*/

#define GPIO_NUM_OF_PORTS                            (8U)
#define GPIO_NUM_OF_PINS_PER_PORT                    (16U)

/*=====================================================================================================================
                                       < User-defined Data Types >
=====================================================================================================================*/

typedef struct
{
    volatile u32 MODER;
    volatile u32 OTYPER;
    volatile u32 OSPEEDR;
    volatile u32 PUPDR;
    volatile u32 IDR;
    volatile u32 ODR;
    volatile u32 BSRR;
    volatile u32 LCKR;
    volatile u32 AFRL;
    volatile u32 AFRH;
    volatile u32 BRR;
}GPIOx_registersType;

/*=====================================================================================================================
                                < Peripheral Registers and Bits Definitions >
=====================================================================================================================*/

#define GPIOA                              ((volatile GPIOx_registersType*)(0X48000000))
#define GPIOB                              ((volatile GPIOx_registersType*)(0X48000400))
#define GPIOC                              ((volatile GPIOx_registersType*)(0X48000800))
#define GPIOD                              ((volatile GPIOx_registersType*)(0X48000C00))
#define GPIOE                              ((volatile GPIOx_registersType*)(0X48001000))
#define GPIOF                              ((volatile GPIOx_registersType*)(0X48001400))
#define GPIOG                              ((volatile GPIOx_registersType*)(0X48001800))
#define GPIOH                              ((volatile GPIOx_registersType*)(0X48001C00))

/*=====================================================================================================================
                                         < Function-like Macros >
=====================================================================================================================*/

#define GPIO_WRITE_ONE_BIT(REG,PIN,VALUE)   (REG = (REG & (~(0X01 << (PIN * 1)))) | ((VALUE & 0X01) << (PIN * 1)))
#define GPIO_WRITE_TWO_BITS(REG,PIN,VALUE)  (REG = (REG & (~(0X03 << (PIN * 2)))) | ((VALUE & 0X03) << (PIN * 2)))
#define GPIO_WRITE_FOUR_BITS(REG,PIN,VALUE) (REG = (REG & (~(0X0F << (PIN * 4)))) | ((VALUE & 0X0F) << (PIN * 4)))

#endif /* MCAL_GPIO_INCLUDES_GPIO_PRV_H_ */
