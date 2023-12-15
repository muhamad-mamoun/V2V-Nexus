/*
 * Temp_sensor.h
 *
 *  Created on: Dec 9, 2023
 *      Author: Ahmed Dwidar
 */

#ifndef TEMP_SENSOR_H_
#define TEMP_SENSOR_H_

#include"ADC.h"

/*
 the voltage output of the LM35 is directly related to the temperature being sensed.
 Specifically, the output voltage of the LM35 increases linearly by 10mV per degree Celsius.
 The typical output range of the LM35 is around 0V to 1V for temperatures ranging from 0°C to 100°C.

 The operating voltage range of the LM35 is one aspect, but when using this sensor,
 you should also consider the voltage levels it generates as a result of temperature changes.
 Ensure that the ADC (Analog to Digital Converter) or any other circuitry you're using to measure the output of the LM35
 can handle the voltage levels within the sensor's specified output range.

If you're using an ADC with a limited input range (for instance, working with a 0-3.3V or 0-5V ADC),
you might need additional circuitry like voltage dividers or amplifiers to scale and adapt the LM35's output voltage
 to fit within the ADC's input range, ensuring accurate temperature measurements.
*/
#define TEMP_SENSOR_CHANNEL_ID         2
#define TEMP_SENSOR_MAX_VOLT_VALUE     1.5
#define TEMP_SENSOR_MAX_TEMPERATURE    150


u16 TEMP_Get(void);


#endif /* TEMP_SENSOR_H_ */
