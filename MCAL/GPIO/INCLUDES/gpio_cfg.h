/*
=======================================================================================================================
Author       : Mamoun
Module       : GPIO
File Name    : gpio_cfg.h
Date Created : Nov 15, 2023
Description  : Configuration file for the STM32F303 GPIO peripheral driver.
=======================================================================================================================
*/


#ifndef MCAL_GPIO_INCLUDES_GPIO_CFG_H_
#define MCAL_GPIO_INCLUDES_GPIO_CFG_H_

/*=====================================================================================================================
                                < Definitions and Static Configurations >
=====================================================================================================================*/

/*=====================================================================================================================
You can set the mode of any pin with only these values:
1- GPIO_INPUT_FLOAT_MODE
2- GPIO_INPUT_PULLUP_MODE
3- GPIO_INPUT_PULLDOWN_MODE
4- GPIO_OUTPUT_PUSH_PULL_MODE
5- GPIO_OUTPUT_OPEN_DRAIN_MODE
6- GPIO_ALTERNATE_PUSH_PULL_MODE
7- GPIO_ALTERNATE_OPEN_DRAIN_MODE
8- GPIO_ANALOG_MODE
=====================================================================================================================*/

/* PORTA Pins Configurations. */
#define GPIO_PORTA_PIN00_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTA_PIN01_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTA_PIN02_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTA_PIN03_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTA_PIN04_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTA_PIN05_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTA_PIN06_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTA_PIN07_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTA_PIN08_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTA_PIN09_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTA_PIN10_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTA_PIN11_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTA_PIN12_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTA_PIN13_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTA_PIN14_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTA_PIN15_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)

/* PORTB Pins Configurations. */
#define GPIO_PORTB_PIN00_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTB_PIN01_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTB_PIN02_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTB_PIN03_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTB_PIN04_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTB_PIN05_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTB_PIN06_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTB_PIN07_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTB_PIN08_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTB_PIN09_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTB_PIN10_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTB_PIN11_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTB_PIN12_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTB_PIN13_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTB_PIN14_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTB_PIN15_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)

/* PORTC Pins Configurations. */
#define GPIO_PORTC_PIN00_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTC_PIN01_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTC_PIN02_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTC_PIN03_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTC_PIN04_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTC_PIN05_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTC_PIN06_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTC_PIN07_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTC_PIN08_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTC_PIN09_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTC_PIN10_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTC_PIN11_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTC_PIN12_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTC_PIN13_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTC_PIN14_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTC_PIN15_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)

/* PORTD Pins Configurations. */
#define GPIO_PORTD_PIN00_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTD_PIN01_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTD_PIN02_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTD_PIN03_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTD_PIN04_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTD_PIN05_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTD_PIN06_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTD_PIN07_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTD_PIN08_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTD_PIN09_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTD_PIN10_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTD_PIN11_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTD_PIN12_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTD_PIN13_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTD_PIN14_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTD_PIN15_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)

/* PORTE Pins Configurations. */
#define GPIO_PORTE_PIN00_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTE_PIN01_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTE_PIN02_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTE_PIN03_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTE_PIN04_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTE_PIN05_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTE_PIN06_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTE_PIN07_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTE_PIN08_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTE_PIN09_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTE_PIN10_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTE_PIN11_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTE_PIN12_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTE_PIN13_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTE_PIN14_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTE_PIN15_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)

/* PORTF Pins Configurations. */
#define GPIO_PORTF_PIN00_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTF_PIN01_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTF_PIN02_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTF_PIN03_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTF_PIN04_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTF_PIN05_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTF_PIN06_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTF_PIN07_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTF_PIN08_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTF_PIN09_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTF_PIN10_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTF_PIN11_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTF_PIN12_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTF_PIN13_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTF_PIN14_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTF_PIN15_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)

/* PORTG Pins Configurations. */
#define GPIO_PORTG_PIN00_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTG_PIN01_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTG_PIN02_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTG_PIN03_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTG_PIN04_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTG_PIN05_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTG_PIN06_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTG_PIN07_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTG_PIN08_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTG_PIN09_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTG_PIN10_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTG_PIN11_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTG_PIN12_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTG_PIN13_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTG_PIN14_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTG_PIN15_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)

/* PORTH Pins Configurations. */
#define GPIO_PORTH_PIN00_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTH_PIN01_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTH_PIN02_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTH_PIN03_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTH_PIN04_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTH_PIN05_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTH_PIN06_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTH_PIN07_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTH_PIN08_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTH_PIN09_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTH_PIN10_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTH_PIN11_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTH_PIN12_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTH_PIN13_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTH_PIN14_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)
#define GPIO_PORTH_PIN15_MODE                              (GPIO_OUTPUT_PUSH_PULL_MODE)

#endif /* MCAL_GPIO_INCLUDES_GPIO_CFG_H_ */
