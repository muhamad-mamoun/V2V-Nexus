

#ifndef NVIC_INTERFACE_H_
#define NVIC_INTERFACE_H_

#define GROUP4_SUB_0 0X05FA0300   // 4bits for group  IPR => GROUP
#define GROUP3_SUB_1 0X05FA0400   // 3bits for group  AND ONE BIT FOR SUP
#define GROUP2_SUB_2 0X05FA0500   // 2bits for group  AND 2 BIT FOR SUP
#define GROUP1_SUB_3 0X05FA0600   // 1bits for group  AND 3 BIT FOR SUP
#define GROUP0_SUB_4 0X05FA0700   // 0bits for group  AND 4 BIT FOR SUP


typedef enum
{
    WWDG_ = 0,
    PVD_,
    TAMPER_,
    RTC_,
    FLASH_,
    RCC_,
    EXTI0_,
    EXTI1_,
    EXTI2_,
    EXTI3_,
    EXTI4_,
    DMA1_Channel1_,
    DMA1_Channel2_,
    DMA1_Channel3_,
    DMA1_Channel4_,
    DMA1_Channel5_,
    DMA1_Channel6_,
    DMA1_Channel7_,
    ADC1_2_,
    USB_HP_CAN_TX_,
    USB_LP_CAN_RX0_,
    CAN_RX1,
    CAN_SCE,
    EXTI9_5_,
    TIM1_BRK_,
    TIM1_UP_,
    TIM1_TRG_COM_,
    TIM1_CC_,
    TIMER2_,
    TIMER3_,
    TIMER4_,
    I2C1_EV_,
    I2C1_ER_,
    I2C2_EV_,
    I2C2_ER_,
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
    ADCC3,
    FSMCC,
    SDIOO,
    TIMER5_,
    SPII3,
    UART4_,
    UART5_,
    TIMER6_,
    TIMER7_,
    DMA2_Channel1_,
    DMA2_Channel2_,
    DMA2_Channel3_,
    DMA2_Channel4_5_
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
