#ifndef I2C_H_
#define I2C_H_

#define SEVEN_BIT_ADDRESS    0
#define TEN_BIT_ADDRESS      1

#define WRITE_REQUEST    0
#define READ_REQUEST     1

typedef enum 
{
	I2C_1,
	I2C_2,
	I2C_3,
	I2C_MAX_INDEX
	
}I2C_enu_index_t;

typedef enum 
{
	I2C_OKAY,
	I2C_INDEX_ERROR,
	
}I2C_enu_Error_t;


I2C_enu_Error_t I2C_init(I2C_enu_index_t Copy_enu_I2C_index);
void I2C_MASTER_init(u8 Address_Size,u16 SlaveAddress,u8 WriteOrRead,u8 bytes);
I2C_enu_Error_t I2C_Start(I2C_enu_index_t Copy_enu_I2C_index);
I2C_enu_Error_t I2C_Stop(I2C_enu_index_t Copy_enu_I2C_index);
void I2C1_Write_byte(u8 data);
void I2C1_Read_byte(u8 *data);

#endif