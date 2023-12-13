#ifndef EEPROM_H_
#define EEPROM_H_




#define EEPROM_ADDRESS_W   0xA0
#define EEPROM_I2C_INDEX   I2C_2

void EEPROM_init(void);
void EEPROM_WRITE_BYTE(u8 address,u8 byte);
void EEPROM_WRITE_STRING(u8 address,u8 *string,u8 size);
void EEPROM_READ_BYTE(u8 address,u8 *byte);
void EEPROM_READ_STRING(u8 address,u8  *string,u8 size);


#endif



