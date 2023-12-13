#include "std_types.h"
#include "gpio.h"
#include "RCC.h"
#include "I2C.h"
#include "eeprom.h"


GPIO_configurationsType SCL = 
{
	GPIO_PORTA_ID,
	GPIO_PIN09_ID,
	GPIO_ALTERNATE_OPEN_DRAIN_MODE,
	GPIO_LOW_SPEED
};


GPIO_configurationsType SDA = 
{
	GPIO_PORTA_ID,
	GPIO_PIN10_ID,
	GPIO_ALTERNATE_OPEN_DRAIN_MODE,
	GPIO_LOW_SPEED
};


void EEPROM_init(void)
{
	RCC_voidEnablePeripheral(AHB_BUS,GPIOA_EN);
	RCC_voidEnablePeripheral(APB1_BUS,I2C2_EN);
	GPIO_configurePin(&SDA);
	GPIO_configurePin(&SCL);
	GPIO_setPinFuction(GPIO_PORTA_ID,GPIO_PIN09_ID,GPIO_AF04);
	GPIO_setPinFuction(GPIO_PORTA_ID,GPIO_PIN10_ID,GPIO_AF04);
	I2C_init(EEPROM_I2C_INDEX);
}


void EEPROM_WRITE_BYTE(u8 address,u8 byte)
{
	I2C_MASTER_init(EEPROM_I2C_INDEX,SEVEN_BIT_ADDRESS,(u16)EEPROM_ADDRESS_W,WRITE_REQUEST,2);
	I2C_Start(EEPROM_I2C_INDEX);
	I2C1_Write_byte(EEPROM_I2C_INDEX,address);
	I2C1_Write_byte(EEPROM_I2C_INDEX,byte);
	I2C_Stop(EEPROM_I2C_INDEX);
}
void EEPROM_WRITE_STRING(u8 address,u8 *string,u8 size)
{
	u8   loc_u8_itrator  = FALSE;
	vu32 loc_u32_timeOut = FALSE;
	while (loc_u8_itrator < size)
	{
		EEPROM_WRITE_BYTE(address,string[loc_u8_itrator]);
		for(loc_u32_timeOut = FALSE ; loc_u32_timeOut<10000;loc_u32_timeOut++);
		address++;
		loc_u8_itrator++;
	}
}
void EEPROM_READ_BYTE(u8 address,u8 *byte)
{
	  I2C_MASTER_init(EEPROM_I2C_INDEX,SEVEN_BIT_ADDRESS,(u16)EEPROM_ADDRESS_W,WRITE_REQUEST,1);
	  I2C_Start(EEPROM_I2C_INDEX);
	  I2C1_Write_byte(EEPROM_I2C_INDEX,address);
		I2C_MASTER_init(EEPROM_I2C_INDEX,SEVEN_BIT_ADDRESS,(u16)EEPROM_ADDRESS_W,READ_REQUEST,1);
		I2C_Start(EEPROM_I2C_INDEX);
	  I2C1_Read_byte(EEPROM_I2C_INDEX,byte);
	  I2C_Stop(EEPROM_I2C_INDEX);
}
void EEPROM_READ_STRING(u8 address,u8 *string,u8 size)
{
	u8   loc_u8_itrator  = FALSE;
	vu32 loc_u32_timeOut = FALSE;
	while (loc_u8_itrator < size)
	{
		EEPROM_READ_BYTE(address,string);
		for(loc_u32_timeOut = FALSE ; loc_u32_timeOut<10000;loc_u32_timeOut++);
		loc_u8_itrator++;
		address++;
		string++;
	}
}
