#ifndef I2C_PRV_H
#define I2C_PRV_H


#define I2C_1_BASE     0x40005400
#define I2C_2_BASE     0x40005800
#define I2C_3_BASE     0x40007800


typedef struct
{
	vu32 I2C_CR1;
	vu32 I2C_CR2;
	vu32 I2C_OAR1;
	vu32 I2C_OAR2;
	vu32 I2C_TIMINGR;
	vu32 I2C_TIMEOUTR;
	vu32 I2C_ISR;
	vu32 I2C_ICR;
	vu32 I2C_PECR;
	vu32 I2C_RXDR;
	vu32 I2C_TXDR;
}I2Cx_REGS_t;

#define I2Cx(BASE) ((volatile I2Cx_REGS_t*)(BASE))


#define I2C_CR1_PE       0x01
#define MASTER_TIMING    0x10420F13



#endif