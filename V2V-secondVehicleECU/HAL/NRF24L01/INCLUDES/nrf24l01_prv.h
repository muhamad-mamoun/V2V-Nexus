/*
=======================================================================================================================
Author       : Mamoun
Module       : NRF24L01
File Name    : nrf24l01_prv.h
Date Created : Nov 22, 2023
Description  : Private file for the NRF24L01 module driver.
=======================================================================================================================
*/


#ifndef HAL_NRF24L01_INCLUDES_NRF24L01_PRV_H_
#define HAL_NRF24L01_INCLUDES_NRF24L01_PRV_H_

/*=====================================================================================================================
                                < Definitions and Static Configurations >
=====================================================================================================================*/

#define NRF24L01_MAX_CHANNEL_NUMBER                           (125U)
#define NRF24L01_TX_RX_ADDRESS_SIZE                           (5)

/* nRF24L01 Commmands. */
#define NRF24L01_R_REGISTER_COMMAND                           (0b00000000)
#define NRF24L01_W_REGISTER_COMMAND                           (0b00100000)
#define NRF24L01_R_RX_PAYLOAD_COMMAND                         (0b01100001)
#define NRF24L01_W_TX_PAYLOAD_COMMAND                         (0b10100000)
#define NRF24L01_FLUSH_TX_COMMAND                             (0b11100001)
#define NRF24L01_FLUSH_RX_COMMAND                             (0b11100010)
#define NRF24L01_REUSE_TX_PL_COMMAND                          (0b11100011)
#define NRF24L01_R_RX_PL_WID_COMMAND                          (0b01100000)
#define NRF24L01_W_ACK_PAYLOAD_COMMAND                        (0b10101000)
#define NRF24L01_W_TX_PAYLOAD_NACK_COMMAND                    (0b10110000)
#define NRF24L01_NOP_COMMAND                                  (0b11111111)

/*=====================================================================================================================
                                < Peripheral Registers and Bits Definitions >
=====================================================================================================================*/

/* nRF24L01 Registers. */
#define NRF24L01_CONFIG_REG                                   (0X00)
#define NRF24L01_EN_AA_REG                                    (0X01)
#define NRF24L01_EN_RXADDR_REG                                (0X02)
#define NRF24L01_SETUP_AW_REG                                 (0X03)
#define NRF24L01_SETUP_RETR_REG                               (0X04)
#define NRF24L01_RF_CH_REG                                    (0X05)
#define NRF24L01_RF_SETUP_REG                                 (0X06)
#define NRF24L01_STATUS_REG                                   (0X07)
#define NRF24L01_OBSERVE_TX_REG                               (0X08)
#define NRF24L01_RPD_REG                                      (0X09)
#define NRF24L01_RX_ADDR_P0_REG                               (0X0A)
#define NRF24L01_RX_ADDR_P1_REG                               (0X0B)
#define NRF24L01_RX_ADDR_P2_REG                               (0X0C)
#define NRF24L01_RX_ADDR_P3_REG                               (0X0D)
#define NRF24L01_RX_ADDR_P4_REG                               (0X0E)
#define NRF24L01_RX_ADDR_P5_REG                               (0X0F)
#define NRF24L01_TX_ADDR_REG                                  (0X10)
#define NRF24L01_RX_PW_P0_REG                                 (0X11)
#define NRF24L01_RX_PW_P1_REG                                 (0X12)
#define NRF24L01_RX_PW_P2_REG                                 (0X13)
#define NRF24L01_RX_PW_P3_REG                                 (0X14)
#define NRF24L01_RX_PW_P4_REG                                 (0X15)
#define NRF24L01_RX_PW_P5_REG                                 (0X16)
#define NRF24L01_FIFO_STATUS_REG                              (0X17)
#define NRF24L01_DYNPD_REG                                    (0X1C) 
#define NRF24L01_FEATURE_REG                                  (0X1D)

/*=====================================================================================================================
                                      < Private Functions Prototypes >
=====================================================================================================================*/

/*=====================================================================================================================
 * [Function Name] : NRF24L01_sendCommand
 * [Description]   : Send a specific command to the NRF24L01 module.
 * [Arguments]     : <a_command>      -> Indicates to the required command.
 * [return]        : The function returns void.
 ====================================================================================================================*/
static void NRF24L01_sendCommand(u8 a_command);

/*=====================================================================================================================
 * [Function Name] : NRF24L01_readRegister
 * [Description]   : Read the value of a specific register in the NRF24L01 module.
 * [Arguments]     : <a_registerAddress>   -> Indicates to the address of the required register.
 *                   <a_ptr2value>         -> Pointer to variable to store the register value.
 * [return]        : The function returns void.
 ====================================================================================================================*/
static void NRF24L01_readRegister(u8 a_registerAddress, u8* a_ptr2value);

/*=====================================================================================================================
 * [Function Name] : NRF24L01_writeRegister
 * [Description]   : Write a specific value in a specific register in the NRF24L01 module.
 * [Arguments]     : <a_registerAddress>   -> Indicates to the address of the required register.
 *                   <a_value>             -> Indicates to the required value to be written.
 * [return]        : The function returns void.
 ====================================================================================================================*/
static void NRF24L01_writeRegister(u8 a_registerAddress, u8 a_value);

/*=====================================================================================================================
 * [Function Name] : NRF24L01_writeRegisterMulti
 * [Description]   : Write a specific value [multiple bytes] in a specific register in the NRF24L01 module.
 * [Arguments]     : <a_registerAddress>   -> Indicates to the address of the required register.
 *                   <a_ptr2value>         -> Pointer to the required value to be written.
 *                   <a_size>              -> Indicates to the size of the data.
 * [return]        : The function returns void.
 ====================================================================================================================*/
static void NRF24L01_writeRegisterMulti(u8 a_registerAddress, u8* a_ptr2value, u8 a_size);

#endif /* HAL_NRF24L01_INCLUDES_NRF24L01_PRV_H_ */
