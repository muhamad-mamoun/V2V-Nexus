#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

void MADC_ON(void);
void MADC_OFF(void);
void MADC_Init(void);
u16 MADC_Read(u8 channel);



#endif
