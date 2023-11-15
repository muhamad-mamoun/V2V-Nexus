/*
=======================================================================================================================
Author       : Mamoun
Module       : GPIO
File Name    : gpio.h
Date Created : Nov 15, 2023
Description  : Interface file for the STM32F303 GPIO peripheral driver.
=======================================================================================================================
*/


#ifndef MCAL_GPIO_INCLUDES_GPIO_H_
#define MCAL_GPIO_INCLUDES_GPIO_H_

/*=====================================================================================================================
                                       < User-defined Data Types >
=====================================================================================================================*/

typedef enum
{
    GPIO_NO_ERRORS,
    GPIO_NULL_PTR_ERROR,
    GPIO_PORT_ID_ERROR,
    GPIO_PIN_ID_ERROR,
    GPIO_PIN_MODE_ERROR,
    GPIO_PIN_SPEED_ERROR,
    GPIO_PIN_STATUS_ERROR,
    GPIO_ALTERNATE_FUNCTION_ERROR,
}GPIO_errorStatusType;

typedef enum
{
    GPIO_PORTA_ID,
    GPIO_PORTB_ID,
    GPIO_PORTC_ID,
    GPIO_PORTD_ID,
    GPIO_PORTE_ID,
    GPIO_PORTF_ID,
    GPIO_PORTG_ID,
    GPIO_PORTH_ID,
}GPIO_portIDType;

typedef enum
{
    GPIO_PIN00_ID,
    GPIO_PIN01_ID,
    GPIO_PIN02_ID,
    GPIO_PIN03_ID,
    GPIO_PIN04_ID,
    GPIO_PIN05_ID,
    GPIO_PIN06_ID,
    GPIO_PIN07_ID,
    GPIO_PIN08_ID,
    GPIO_PIN09_ID,
    GPIO_PIN10_ID,
    GPIO_PIN11_ID,
    GPIO_PIN12_ID,
    GPIO_PIN13_ID,
    GPIO_PIN14_ID,
    GPIO_PIN15_ID,
}GPIO_pinIDType;

typedef enum
{
    GPIO_LOW_PIN,
    GPIO_HIGH_PIN,
}GPIO_pinStatusType;

typedef enum
{
    GPIO_INPUT_FLOAT_MODE,
    GPIO_OUTPUT_PUSH_PULL_MODE,
    GPIO_ALTERNATE_PUSH_PULL_MODE,
    GPIO_ANALOG_MODE,
    GPIO_INPUT_PULLUP_MODE,
    GPIO_OUTPUT_OPEN_DRAIN_MODE,
    GPIO_ALTERNATE_OPEN_DRAIN_MODE,
    GPIO_INPUT_PULLDOWN_MODE = 0X08,
}GPIO_pinModeType;

typedef enum
{
    GPIO_LOW_SPEED,
    GPIO_MEDIUM_SPEED,
    GPIO_HIGH_SPEED = 0X03,
}GPIO_pinSpeedType;

typedef enum
{
    GPIO_AF00,
    GPIO_AF01,
    GPIO_AF02,
    GPIO_AF03,
    GPIO_AF04,
    GPIO_AF05,
    GPIO_AF06,
    GPIO_AF07,
    GPIO_AF08,
    GPIO_AF09,
    GPIO_AF10,
    GPIO_AF11,
    GPIO_AF12,
    GPIO_AF13,
    GPIO_AF14,
    GPIO_AF15,
}GPIO_alternateFunctionType;

typedef struct
{
    GPIO_portIDType portID;
    GPIO_pinIDType pinID;
    GPIO_pinModeType pinMode;
    GPIO_pinSpeedType pinSpeed;
}GPIO_configurationsType;

/*=====================================================================================================================
                                         < Functions Prototypes >
=====================================================================================================================*/

/*=====================================================================================================================
 * [Function Name] : GPIO_init
 * [Description]   : Initialize all the pins with specific static configurations.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ====================================================================================================================*/
void GPIO_init(void);

/*=====================================================================================================================
 * [Function Name] : GPIO_configurePin
 * [Description]   : Configure a specific GPIO pin with specific configurations.
 * [Arguments]     : <a_ptr2configurations>      -> Pointer to a structure that holds the configurations.
 * [return]        : The function returns the error status: - No Errors.
 *                                                          - Null Pointer Error.
 *                                                          - Port ID Error.
 *                                                          - Pin ID Error.
 *                                                          - Speed Error.
 *                                                          - Mode Error.
 ====================================================================================================================*/
GPIO_errorStatusType GPIO_configurePin(GPIO_configurationsType* a_ptr2configurations);

/*=====================================================================================================================
 * [Function Name] : GPIO_writePin
 * [Description]   : Write a specific logic [High or Low] on a specific pin.
 * [Arguments]     : <a_portID>      -> Indicates to the required port ID.
 *                   <a_pinID>       -> Indicates to the required pin ID.
 *                   <a_pinStatus>   -> Indicates to the value [High - Low].
 * [return]        : The function returns the error status: - No Errors.
 *                                                          - Port ID Error.
 *                                                          - Pin ID Error.
 *                                                          - Pin Status Error.
 ====================================================================================================================*/
GPIO_errorStatusType GPIO_writePin(GPIO_portIDType a_portID, GPIO_pinIDType a_pinID, GPIO_pinStatusType a_pinStatus);

/*=====================================================================================================================
 * [Function Name] : GPIO_writePort
 * [Description]   : Write a specific value on a certain port.
 * [Arguments]     : <a_portID>      -> Indicates to the required port ID.
 *                   <a_portValue>   -> Indicates to the value of the port [0 ~ 65535].
 * [return]        : The function returns the error status: - No Errors.
 *                                                          - Port ID Error.
 ====================================================================================================================*/
GPIO_errorStatusType GPIO_writePort(GPIO_portIDType a_portID, u16 a_portValue);

/*=====================================================================================================================
 * [Function Name] : GPIO_readPin
 * [Description]   : Read the logic of a specific pin [High - LOW].
 * [Arguments]     : <a_portID>         -> Indicates to the required port ID.
 *                   <a_pinID>          -> Indicates to the required pin ID.
 *                   <a_ptr2pinStatus>  -> Pointer to variable to store the value of the pin.
 * [return]        : The function returns the error status: - No Errors.
 *                                                          - Null Pointer Error.
 *                                                          - Port ID Error.
 *                                                          - Pin ID Error.
 ====================================================================================================================*/
GPIO_errorStatusType GPIO_readPin(GPIO_portIDType a_portID, GPIO_pinIDType a_pinID, GPIO_pinStatusType* a_ptr2pinStatus);

/*=====================================================================================================================
 * [Function Name] : GPIO_readPort
 * [Description]   : Read the value of a specific port.
 * [Arguments]     : <a_portID>          -> Indicates to the required port ID.
 *                   <a_ptr2portStatus>  -> Pointer to variable to store the value of the port.
 * [return]        : The function returns the error status: - No Errors.
 *                                                          - Null Pointer Error.
 *                                                          - Port ID Error.
 ====================================================================================================================*/
GPIO_errorStatusType GPIO_readPort(GPIO_portIDType a_portID, u16* a_ptr2portStatus);

/*=====================================================================================================================
 * [Function Name] : GPIO_togglePin
 * [Description]   : Toggle the logic of a specific pin.
 * [Arguments]     : <a_portID>      -> Indicates to the required port ID.
 *                   <a_pinID>       -> Indicates to the required pin ID.
 * [return]        : The function returns the error status: - No Errors.
 *                                                          - Port ID Error.
 *                                                          - Pin ID Error.
 ====================================================================================================================*/
GPIO_errorStatusType GPIO_togglePin(GPIO_portIDType a_portID, GPIO_pinIDType a_pinID);

/*=====================================================================================================================
 * [Function Name] : GPIO_setPinFuction
 * [Description]   : Select the alternate function for a specific pin.
 * [Arguments]     : <a_portID>             -> Indicates to the required port ID.
 *                   <a_pinID>              -> Indicates to the required pin ID.
 *                   <a_alternateFunction>  -> Indicates to the required alternate function.
 * [return]        : The function returns the error status: - No Errors.
 *                                                          - Port ID Error.
 *                                                          - Pin ID Error.
 *                                                          - Pin Function Error.
 ====================================================================================================================*/
GPIO_errorStatusType GPIO_setPinFuction(GPIO_portIDType a_portID, GPIO_pinIDType a_pinID, GPIO_alternateFunctionType a_alternateFunction);

/*=====================================================================================================================
 * [Function Name] : GPIO_lockPin
 * [Description]   : Lock the configurations for a specific pin.
 * [Arguments]     : <a_portID>        -> Indicates to the required port ID.
 *                   <a_pinID>         -> Indicates to the required pin ID.
 * [return]        : The function returns the error status: - No Errors.
 *                                                          - Port ID Error.
 *                                                          - Pin ID Error.
 ====================================================================================================================*/
GPIO_errorStatusType GPIO_lockPin(GPIO_portIDType a_portID, GPIO_pinIDType a_pinID);

#endif /* MCAL_GPIO_INCLUDES_GPIO_H_ */
