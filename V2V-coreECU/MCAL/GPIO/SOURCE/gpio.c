/*
=======================================================================================================================
Author       : Mamoun
Module       : GPIO
File Name    : gpio.c
Date Created : Nov 15, 2023
Description  : Source file for the STM32F303 GPIO peripheral driver.
=======================================================================================================================
*/


/*=====================================================================================================================
                                               < Includes >
=====================================================================================================================*/

#include "../../../OTHERS/std_types.h"
#include "../../../OTHERS/common_macros.h"
#include "../INCLUDES/gpio_prv.h"
#include "../INCLUDES/gpio_cfg.h"
#include "../INCLUDES/gpio.h"

/*=====================================================================================================================
                                          < Functions Definitions >
=====================================================================================================================*/

/*=====================================================================================================================
 * [Function Name] : GPIO_init
 * [Description]   : Initialize all the pins with specific static configurations.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ====================================================================================================================*/
void GPIO_init(void)
{
    GPIOx_registersType* LOC_ptr2GPIOx[GPIO_NUM_OF_PORTS] = {GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF,GPIOG,GPIOH};
    GPIO_pinModeType LOC_pinsConfigurations[GPIO_NUM_OF_PORTS][GPIO_NUM_OF_PINS_PER_PORT] = 
    {
        {GPIO_PORTA_PIN00_MODE,GPIO_PORTA_PIN01_MODE,GPIO_PORTA_PIN02_MODE,GPIO_PORTA_PIN03_MODE,GPIO_PORTA_PIN04_MODE,GPIO_PORTA_PIN05_MODE,GPIO_PORTA_PIN06_MODE,GPIO_PORTA_PIN07_MODE,GPIO_PORTA_PIN08_MODE,GPIO_PORTA_PIN09_MODE,GPIO_PORTA_PIN10_MODE,GPIO_PORTA_PIN11_MODE,GPIO_PORTA_PIN12_MODE,GPIO_PORTA_PIN13_MODE,GPIO_PORTA_PIN14_MODE,GPIO_PORTA_PIN15_MODE},
        {GPIO_PORTB_PIN00_MODE,GPIO_PORTB_PIN01_MODE,GPIO_PORTB_PIN02_MODE,GPIO_PORTB_PIN03_MODE,GPIO_PORTB_PIN04_MODE,GPIO_PORTB_PIN05_MODE,GPIO_PORTB_PIN06_MODE,GPIO_PORTB_PIN07_MODE,GPIO_PORTB_PIN08_MODE,GPIO_PORTB_PIN09_MODE,GPIO_PORTB_PIN10_MODE,GPIO_PORTB_PIN11_MODE,GPIO_PORTB_PIN12_MODE,GPIO_PORTB_PIN13_MODE,GPIO_PORTB_PIN14_MODE,GPIO_PORTB_PIN15_MODE},
        {GPIO_PORTC_PIN00_MODE,GPIO_PORTC_PIN01_MODE,GPIO_PORTC_PIN02_MODE,GPIO_PORTC_PIN03_MODE,GPIO_PORTC_PIN04_MODE,GPIO_PORTC_PIN05_MODE,GPIO_PORTC_PIN06_MODE,GPIO_PORTC_PIN07_MODE,GPIO_PORTC_PIN08_MODE,GPIO_PORTC_PIN09_MODE,GPIO_PORTC_PIN10_MODE,GPIO_PORTC_PIN11_MODE,GPIO_PORTC_PIN12_MODE,GPIO_PORTC_PIN13_MODE,GPIO_PORTC_PIN14_MODE,GPIO_PORTC_PIN15_MODE},
        {GPIO_PORTD_PIN00_MODE,GPIO_PORTD_PIN01_MODE,GPIO_PORTD_PIN02_MODE,GPIO_PORTD_PIN03_MODE,GPIO_PORTD_PIN04_MODE,GPIO_PORTD_PIN05_MODE,GPIO_PORTD_PIN06_MODE,GPIO_PORTD_PIN07_MODE,GPIO_PORTD_PIN08_MODE,GPIO_PORTD_PIN09_MODE,GPIO_PORTD_PIN10_MODE,GPIO_PORTD_PIN11_MODE,GPIO_PORTD_PIN12_MODE,GPIO_PORTD_PIN13_MODE,GPIO_PORTD_PIN14_MODE,GPIO_PORTD_PIN15_MODE},
        {GPIO_PORTE_PIN00_MODE,GPIO_PORTE_PIN01_MODE,GPIO_PORTE_PIN02_MODE,GPIO_PORTE_PIN03_MODE,GPIO_PORTE_PIN04_MODE,GPIO_PORTE_PIN05_MODE,GPIO_PORTE_PIN06_MODE,GPIO_PORTE_PIN07_MODE,GPIO_PORTE_PIN08_MODE,GPIO_PORTE_PIN09_MODE,GPIO_PORTE_PIN10_MODE,GPIO_PORTE_PIN11_MODE,GPIO_PORTE_PIN12_MODE,GPIO_PORTE_PIN13_MODE,GPIO_PORTE_PIN14_MODE,GPIO_PORTE_PIN15_MODE},
        {GPIO_PORTF_PIN00_MODE,GPIO_PORTF_PIN01_MODE,GPIO_PORTF_PIN02_MODE,GPIO_PORTF_PIN03_MODE,GPIO_PORTF_PIN04_MODE,GPIO_PORTF_PIN05_MODE,GPIO_PORTF_PIN06_MODE,GPIO_PORTF_PIN07_MODE,GPIO_PORTF_PIN08_MODE,GPIO_PORTF_PIN09_MODE,GPIO_PORTF_PIN10_MODE,GPIO_PORTF_PIN11_MODE,GPIO_PORTF_PIN12_MODE,GPIO_PORTF_PIN13_MODE,GPIO_PORTF_PIN14_MODE,GPIO_PORTF_PIN15_MODE},
        {GPIO_PORTG_PIN00_MODE,GPIO_PORTG_PIN01_MODE,GPIO_PORTG_PIN02_MODE,GPIO_PORTG_PIN03_MODE,GPIO_PORTG_PIN04_MODE,GPIO_PORTG_PIN05_MODE,GPIO_PORTG_PIN06_MODE,GPIO_PORTG_PIN07_MODE,GPIO_PORTG_PIN08_MODE,GPIO_PORTG_PIN09_MODE,GPIO_PORTG_PIN10_MODE,GPIO_PORTG_PIN11_MODE,GPIO_PORTG_PIN12_MODE,GPIO_PORTG_PIN13_MODE,GPIO_PORTG_PIN14_MODE,GPIO_PORTG_PIN15_MODE},
        {GPIO_PORTH_PIN00_MODE,GPIO_PORTH_PIN01_MODE,GPIO_PORTH_PIN02_MODE,GPIO_PORTH_PIN03_MODE,GPIO_PORTH_PIN04_MODE,GPIO_PORTH_PIN05_MODE,GPIO_PORTH_PIN06_MODE,GPIO_PORTH_PIN07_MODE,GPIO_PORTH_PIN08_MODE,GPIO_PORTH_PIN09_MODE,GPIO_PORTH_PIN10_MODE,GPIO_PORTH_PIN11_MODE,GPIO_PORTH_PIN12_MODE,GPIO_PORTH_PIN13_MODE,GPIO_PORTH_PIN14_MODE,GPIO_PORTH_PIN15_MODE},
    };

    for(u8 LOC_portIterator = 0; LOC_portIterator < GPIO_NUM_OF_PORTS; LOC_portIterator++)
    {
        for(u8 LOC_pinIterator = 0; LOC_pinIterator < GPIO_NUM_OF_PINS_PER_PORT; LOC_pinIterator++)
        {
            GPIO_configurationsType LOC_pinConfigurations = {LOC_portIterator,LOC_pinIterator,*(*(LOC_pinsConfigurations + LOC_portIterator) + LOC_pinIterator),GPIO_LOW_SPEED};
            GPIO_configurePin(&LOC_pinConfigurations);
        }
    }
}

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
GPIO_errorStatusType GPIO_configurePin(GPIO_configurationsType* a_ptr2configurations)
{
    GPIO_errorStatusType LOC_errorStatus = GPIO_NO_ERRORS;
    GPIOx_registersType* LOC_ptr2GPIOx[GPIO_NUM_OF_PORTS] = {GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF,GPIOG,GPIOH};

    if(a_ptr2configurations == PTR_NULL)
    {
        LOC_errorStatus = GPIO_NULL_PTR_ERROR;
    }

    else if(a_ptr2configurations->portID >= GPIO_NUM_OF_PORTS)
    {
        LOC_errorStatus = GPIO_PORT_ID_ERROR;
    }

    else if(a_ptr2configurations->pinID >= GPIO_NUM_OF_PINS_PER_PORT)
    {
        LOC_errorStatus = GPIO_PIN_ID_ERROR;
    }

    else if(a_ptr2configurations->pinSpeed > GPIO_HIGH_SPEED)
    {
        LOC_errorStatus = GPIO_PIN_SPEED_ERROR;
    }

    else if((a_ptr2configurations->pinMode > GPIO_ALTERNATE_OPEN_DRAIN_MODE) && (a_ptr2configurations->pinMode != GPIO_INPUT_PULLDOWN_MODE))
    {
        LOC_errorStatus = GPIO_PIN_MODE_ERROR;
    }

    else
    {
        /* Set the I/O mode for the required pin [Input - Output - Alternate Function - Analog]. */
        GPIO_WRITE_TWO_BITS((*(LOC_ptr2GPIOx + a_ptr2configurations->portID))->MODER,a_ptr2configurations->pinID,a_ptr2configurations->pinMode);
			
        switch (a_ptr2configurations->pinMode)
        {
        case GPIO_INPUT_FLOAT_MODE:
        case GPIO_INPUT_PULLUP_MODE:
        case GPIO_INPUT_PULLDOWN_MODE:
            /* In case of input mode, Set the input type for the required pin [Pull-up - Pull-down]. */
            GPIO_WRITE_TWO_BITS((*(LOC_ptr2GPIOx + a_ptr2configurations->portID))->PUPDR,a_ptr2configurations->pinID,(a_ptr2configurations->pinMode >> 2));
            break;
        
        case GPIO_OUTPUT_PUSH_PULL_MODE:
        case GPIO_OUTPUT_OPEN_DRAIN_MODE:
        case GPIO_ALTERNATE_PUSH_PULL_MODE:
        case GPIO_ALTERNATE_OPEN_DRAIN_MODE:
            /* In case of output mode, Set the output speed for the required pin [Low - Medium - High]. */
            GPIO_WRITE_TWO_BITS((*(LOC_ptr2GPIOx + a_ptr2configurations->portID))->OSPEEDR,a_ptr2configurations->pinID,a_ptr2configurations->pinSpeed);
            /* In case of output mode, Set the output type for the required pin [Push-Pull - Open-Drain]. */
            GPIO_WRITE_ONE_BIT((*(LOC_ptr2GPIOx + a_ptr2configurations->portID))->OTYPER,a_ptr2configurations->pinID,(a_ptr2configurations->pinMode >> 2));
            break;
        
        case GPIO_ANALOG_MODE:
            /* Do Nothing. */
            break;
        
        default:
            /* Do Nothing. */
            break;
        }
    }

    return LOC_errorStatus;
}

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
GPIO_errorStatusType GPIO_writePin(GPIO_portIDType a_portID, GPIO_pinIDType a_pinID, GPIO_pinStatusType a_pinStatus)
{
    GPIO_errorStatusType LOC_errorStatus = GPIO_NO_ERRORS;
    GPIOx_registersType* LOC_ptr2GPIOx[GPIO_NUM_OF_PORTS] = {GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF,GPIOG,GPIOH};

    if(a_portID >= GPIO_NUM_OF_PORTS)
    {
        LOC_errorStatus = GPIO_PORT_ID_ERROR;
    }

    else if(a_pinID >= GPIO_NUM_OF_PINS_PER_PORT)
    {
        LOC_errorStatus = GPIO_PIN_ID_ERROR;
    }

    else if((a_pinStatus != GPIO_LOW_PIN) && (a_pinStatus != GPIO_HIGH_PIN))
    {
        LOC_errorStatus = GPIO_PIN_STATUS_ERROR;
    }

    else
    {
        GPIO_WRITE_ONE_BIT((*(LOC_ptr2GPIOx + a_portID))->ODR,a_pinID,a_pinStatus);
    }

    return LOC_errorStatus;
}

/*=====================================================================================================================
 * [Function Name] : GPIO_writePort
 * [Description]   : Write a specific value on a certain port.
 * [Arguments]     : <a_portID>      -> Indicates to the required port ID.
 *                   <a_portValue>   -> Indicates to the value of the port [0 ~ 65535].
 * [return]        : The function returns the error status: - No Errors.
 *                                                          - Port ID Error.
 ====================================================================================================================*/
GPIO_errorStatusType GPIO_writePort(GPIO_portIDType a_portID, u16 a_portValue)
{
    GPIO_errorStatusType LOC_errorStatus = GPIO_NO_ERRORS;
    GPIOx_registersType* LOC_ptr2GPIOx[GPIO_NUM_OF_PORTS] = {GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF,GPIOG,GPIOH};

    if(a_portID >= GPIO_NUM_OF_PORTS)
    {
        LOC_errorStatus = GPIO_PORT_ID_ERROR;
    }

    else
    {
        (*(LOC_ptr2GPIOx + a_portID))->ODR = a_portValue;
    }

    return LOC_errorStatus;
}

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
GPIO_errorStatusType GPIO_readPin(GPIO_portIDType a_portID, GPIO_pinIDType a_pinID, GPIO_pinStatusType* a_ptr2pinStatus)
{
    GPIO_errorStatusType LOC_errorStatus = GPIO_NO_ERRORS;
    GPIOx_registersType* LOC_ptr2GPIOx[GPIO_NUM_OF_PORTS] = {GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF,GPIOG,GPIOH};

    if(a_ptr2pinStatus == PTR_NULL)
    {
        LOC_errorStatus = GPIO_NULL_PTR_ERROR;
    }

    else if(a_portID >= GPIO_NUM_OF_PORTS)
    {
        LOC_errorStatus = GPIO_PORT_ID_ERROR;
    }

    else if(a_pinID >= GPIO_NUM_OF_PINS_PER_PORT)
    {
        LOC_errorStatus = GPIO_PIN_ID_ERROR;
    }

    else
    {
        *a_ptr2pinStatus = GET_BIT((*(LOC_ptr2GPIOx + a_portID))->IDR,a_pinID);
    }

    return LOC_errorStatus;
}

/*=====================================================================================================================
 * [Function Name] : GPIO_readPort
 * [Description]   : Read the value of a specific port.
 * [Arguments]     : <a_portID>          -> Indicates to the required port ID.
 *                   <a_ptr2portStatus>  -> Pointer to variable to store the value of the port.
 * [return]        : The function returns the error status: - No Errors.
 *                                                          - Null Pointer Error.
 *                                                          - Port ID Error.
 ====================================================================================================================*/
GPIO_errorStatusType GPIO_readPort(GPIO_portIDType a_portID, u16* a_ptr2portStatus)
{
    GPIO_errorStatusType LOC_errorStatus = GPIO_NO_ERRORS;
    GPIOx_registersType* LOC_ptr2GPIOx[GPIO_NUM_OF_PORTS] = {GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF,GPIOG,GPIOH};

    if(a_ptr2portStatus == PTR_NULL)
    {
        LOC_errorStatus = GPIO_NULL_PTR_ERROR;
    }

    else if(a_portID >= GPIO_NUM_OF_PORTS)
    {
        LOC_errorStatus = GPIO_PORT_ID_ERROR;
    }

    else
    {
        *a_ptr2portStatus = (*(LOC_ptr2GPIOx + a_portID))->IDR;
    }

    return LOC_errorStatus;
}

/*=====================================================================================================================
 * [Function Name] : GPIO_togglePin
 * [Description]   : Toggle the logic of a specific pin.
 * [Arguments]     : <a_portID>      -> Indicates to the required port ID.
 *                   <a_pinID>       -> Indicates to the required pin ID.
 * [return]        : The function returns the error status: - No Errors.
 *                                                          - Port ID Error.
 *                                                          - Pin ID Error.
 ====================================================================================================================*/
GPIO_errorStatusType GPIO_togglePin(GPIO_portIDType a_portID, GPIO_pinIDType a_pinID)
{
    GPIO_errorStatusType LOC_errorStatus = GPIO_NO_ERRORS;
    GPIOx_registersType* LOC_ptr2GPIOx[GPIO_NUM_OF_PORTS] = {GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF,GPIOG,GPIOH};

    if(a_portID >= GPIO_NUM_OF_PORTS)
    {
        LOC_errorStatus = GPIO_PORT_ID_ERROR;
    }

    else if(a_pinID >= GPIO_NUM_OF_PINS_PER_PORT)
    {
        LOC_errorStatus = GPIO_PIN_ID_ERROR;
    }

    else
    {
        TGL_BIT((*(LOC_ptr2GPIOx + a_portID))->ODR,a_pinID);
    }

    return LOC_errorStatus;
}

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
GPIO_errorStatusType GPIO_setPinFuction(GPIO_portIDType a_portID, GPIO_pinIDType a_pinID, GPIO_alternateFunctionType a_alternateFunction)
{
    GPIO_errorStatusType LOC_errorStatus = GPIO_NO_ERRORS;
    GPIOx_registersType* LOC_ptr2GPIOx[GPIO_NUM_OF_PORTS] = {GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF,GPIOG,GPIOH};

    if(a_portID >= GPIO_NUM_OF_PORTS)
    {
        LOC_errorStatus = GPIO_PORT_ID_ERROR;
    }

    else if(a_pinID >= GPIO_NUM_OF_PINS_PER_PORT)
    {
        LOC_errorStatus = GPIO_PIN_ID_ERROR;
    }

    else if(a_alternateFunction > GPIO_AF15)
    {
        LOC_errorStatus = GPIO_ALTERNATE_FUNCTION_ERROR;
    }

    else if(a_pinID < 8)
    {
        GPIO_WRITE_FOUR_BITS((*(LOC_ptr2GPIOx + a_portID))->AFRL, (a_pinID) ,a_alternateFunction);
    }

    else
    {
        GPIO_WRITE_FOUR_BITS((*(LOC_ptr2GPIOx + a_portID))->AFRH , (a_pinID-8) , a_alternateFunction);
    }

    return LOC_errorStatus;
}

/*=====================================================================================================================
 * [Function Name] : GPIO_lockPin
 * [Description]   : Lock the configurations for a specific pin.
 * [Arguments]     : <a_portID>        -> Indicates to the required port ID.
 *                   <a_pinID>         -> Indicates to the required pin ID.
 * [return]        : The function returns the error status: - No Errors.
 *                                                          - Port ID Error.
 *                                                          - Pin ID Error.
 ====================================================================================================================*/
GPIO_errorStatusType GPIO_lockPin(GPIO_portIDType a_portID, GPIO_pinIDType a_pinID)
{
    GPIO_errorStatusType LOC_errorStatus = GPIO_NO_ERRORS;
    GPIOx_registersType* LOC_ptr2GPIOx[GPIO_NUM_OF_PORTS] = {GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF,GPIOG,GPIOH};

    if(a_portID >= GPIO_NUM_OF_PORTS)
    {
        LOC_errorStatus = GPIO_PORT_ID_ERROR;
    }

    else if(a_pinID >= GPIO_NUM_OF_PINS_PER_PORT)
    {
        LOC_errorStatus = GPIO_PIN_ID_ERROR;
    }

    else
    {
        /* Step 1: WR LCKR = (LCKR[16] = ‘1’) + LCKR[15:0]. */
        (*(LOC_ptr2GPIOx + a_portID))->LCKR = ((1 << 16) | (1 << a_pinID));
        /* Step 2: WR LCKR = (LCKR[16] = ‘0’) + LCKR[15:0]. */
        (*(LOC_ptr2GPIOx + a_portID))->LCKR = (1 << a_pinID);
        /* Step 3: WR LCKR = (LCKR[16] = ‘1’) + LCKR[15:0]. */
        (*(LOC_ptr2GPIOx + a_portID))->LCKR = ((1 << 16) | (1 << a_pinID));
        /* Step 4: RD LCKR. */
        (void)(*(LOC_ptr2GPIOx + a_portID))->LCKR;
    }
}