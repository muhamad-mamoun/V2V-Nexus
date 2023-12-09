

#ifndef NVIC_INTERFACE_H_
#define NVIC_INTERFACE_H_

#define GROUP4_SUB_0 0X05FA0300   // 4bits for group  IPR => GROUP
#define GROUP3_SUB_1 0X05FA0400   // 3bits for group  AND ONE BIT FOR SUP
#define GROUP2_SUB_2 0X05FA0500   // 2bits for group  AND 2 BIT FOR SUP
#define GROUP1_SUB_3 0X05FA0600   // 1bits for group  AND 3 BIT FOR SUP
#define GROUP0_SUB_4 0X05FA0700   // 0bits for group  AND 4 BIT FOR SUP


typedef enum
{
    WWDG = 0,
    PVD,
    TAMPER,
    RTC,
    FLASH,
    RCC,
    EXTI0,
    EXTI1,
    EXTI2,
    EXTI3,
    EXTI4,
    DMA1_Channel1,
    DMA1_Channel2,
    DMA1_Channel3,
    DMA1_Channel4,
    DMA1_Channel5,
    DMA1_Channel6,
    DMA1_Channel7,
    ADC1_2,
    USB_HP_CAN_TX,
    USB_LP_CAN_RX0,
    CAN_RX1,
    CAN_SCE,
    EXTI9_5,
    TIM1_BRK,
    TIM1_UP,
    TIM1_TRG_COM,
    TIM1_CC,
    TIM2,
    TIM3,
    TIM4,
    I2C1_EV,
    I2C1_ER,
    I2C2_EV,
    I2C2_ER,
    SPI11,
    SPI22,
    USART11,
    USART22,
    USART33,
    EXTI15_10,
    RTCAlarm,
    USBWakeup,
    TIM8_BRK,
    TIM8_UP,
    TIM8_TRG_COM,
    TIM8_CC,
    ADC3,
    FSMC,
    SDIO,
    TIM5,
    SPI3,
    UART4,
    UART5,
    TIM6,
    TIM7,
    DMA2_Channel1,
    DMA2_Channel2,
    DMA2_Channel3,
    DMA2_Channel4_5
}NVIC_Per_Position;

void MNVIC_voidInit(void);

void MNVIC_voidSetPriority(NVIC_Per_Position Copy_IntNumber , u8 Copy_u8Prority );

void MNVIC_voidEnableInterrupt(NVIC_Per_Position Copy_IntNumber);

void MNVIC_voidDisableInterrupt(NVIC_Per_Position Copy_IntNumber);

void MNVIC_voidSetPendingFlag(NVIC_Per_Position Copy_IntNumber);

void MNVIC_voidClearPendingFlag(NVIC_Per_Position Copy_IntNumber);

u8 MNVIC_u8GetActiveFlag(NVIC_Per_Position Copy_IntNumber);

void MNVIC_voidSetPriority_2(NVIC_Per_Position Copy_IntNumber  ,u8 copy_u8GroupPriority ,u8 copy_u8SupPriority , u32 copy_u32GroupSubDiv  );

#endif  /* NVIC_INTERFACE_H_ */
