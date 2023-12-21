
#ifndef HAL_LED_LED_INTERFACE_H_
#define HAL_LED_LED_INTERFACE_H_

#include "../../LIB/STD_TYPES.h"

#define MAX_NUM_OFF_LEDS  3
typedef enum
{
	LED_1,
	LED_2,
	LED_3,


}
tLED;

typedef enum
{
	LED_ON = 1 , LED_OFF = 0

}tLed_State;

typedef struct
{
	u8 port ;
	u8 pin           ;
	tLed_State state ;

}Led_info;

extern Led_info  Leds_data[MAX_NUM_OFF_LEDS];

void HLed_voidInit( tLED  led  ,tLed_State  init_state );

void HLed_voidSetState( tLED  led  ,tLed_State state );

tLed_State  HLed_voidGetState( tLED  led   );

void HLed_voidTogglee( tLED  led  );


#endif /* HAL_LED_LED_INTERFACE_H_ */
