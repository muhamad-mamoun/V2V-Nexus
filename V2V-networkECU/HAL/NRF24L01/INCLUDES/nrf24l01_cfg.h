/*
=======================================================================================================================
Author       : Mamoun
Module       : NRF24L01
File Name    : nrf24l01_cfg.h
Date Created : Nov 22, 2023
Description  : Configuration file for the NRF24L01 module driver.
=======================================================================================================================
*/


#ifndef HAL_NRF24L01_INCLUDES_NRF24L01_CFG_H_
#define HAL_NRF24L01_INCLUDES_NRF24L01_CFG_H_

/*=====================================================================================================================
                                < Definitions and Static Configurations >
=====================================================================================================================*/

/* The number of the bytes in RX payload. */
#define NRF24L01_PAYLOAD_SIZE                           (32)

/* The 5-byte address of the transmitter [write the LSB first and separate them with comma]. */
#define NRF24L01_TRANSMITTER_ADDRESS                    0XE7,0XE7,0XE7,0XE7,0XE7

/* The 5-byte addresses of the 5 data pipes [write the LSB first and separate them with comma]. */
#define NRF24L01_RECEIVER_PIPE0_ADDRESS                 0X77,0X35,0XF0,0XD3,0XE7
#define NRF24L01_RECEIVER_PIPE1_ADDRESS                 0X77,0X35,0XF0,0XD3,0XE7 /* The 4 MSBs MUST be equal. */
#define NRF24L01_RECEIVER_PIPE2_ADDRESS                 0X77,0X35,0XF0,0XD3,0XE7 /* The 4 MSBs MUST be equal. */
#define NRF24L01_RECEIVER_PIPE3_ADDRESS                 0X77,0X35,0XF0,0XD3,0XE7 /* The 4 MSBs MUST be equal. */
#define NRF24L01_RECEIVER_PIPE4_ADDRESS                 0X77,0X35,0XF0,0XD3,0XE7 /* The 4 MSBs MUST be equal. */
#define NRF24L01_RECEIVER_PIPE5_ADDRESS                 0X77,0X35,0XF0,0XD3,0XE7 /* The 4 MSBs MUST be equal. */

/* SPI MOSI port and pin IDs. */
#define NRF24L01_MOSI_PORT_ID                           (GPIOA)
#define NRF24L01_MOSI_PIN_ID                            (PIN7)

/* SPI MISO port and pin IDs. */
#define NRF24L01_MISO_PORT_ID                           (GPIOA)
#define NRF24L01_MISO_PIN_ID                            (PIN6)

/* SPI SCK port and pin IDs. */
#define NRF24L01_SCK_PORT_ID                            (GPIOA)
#define NRF24L01_SCK_PIN_ID                             (PIN5)

/* SPI NSS port and pin IDs. */
#define NRF24L01_NSS_PORT_ID                            (GPIOA)
#define NRF24L01_NSS_PIN_ID                             (PIN4)

/* Chip enable port and pin IDs. */
#define NRF24L01_CE_PORT_ID                             (GPIOA)
#define NRF24L01_CE_PIN_ID                              (PIN3)

#endif /* HAL_NRF24L01_INCLUDES_NRF24L01_CFG_H_ */
