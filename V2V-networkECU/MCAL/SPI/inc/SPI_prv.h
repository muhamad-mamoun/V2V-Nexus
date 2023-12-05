#ifndef SPI_PRV_H_
#define SPI_PRV_H_

typedef struct
{

    vu32 CR1;
    vu32 CR2;
    vu32 SR;
    vu32 DR;
    vu32 CRCPR;
    vu32 RXCRCR;
    vu32 TXCRCR;
    vu32 I2SCFGR;
    vu32 I2SPR;

} SPI;

#define SPI1 ((volatile SPI *)0x40013000)

#define DFF                         11
#define SSM                         9
#define SSI                         8
#define LSBFIRST                    7
#define SPE                         6
#define BR                          3
#define MSTR                        2
#define CPOL                        1
#define CPHA                        0
#define TXEIE                       7
#define RXNEIE                      6
#define ERRIE                       5

#define BSY                         7


#define SPI_MODE0                   0
#define SPI_MODE1                   1
#define SPI_MODE2                   2
#define SPI_MODE3                   3
#define SPI_MASTER                  0
#define SPI_SLAVE                   1
#define SPI_FPCLK_DIVIDED_BY_2      0b000
#define SPI_FPCLK_DIVIDED_BY_4      0b001
#define SPI_FPCLK_DIVIDED_BY_8      0b010
#define SPI_FPCLK_DIVIDED_BY_16     0b011
#define SPI_FPCLK_DIVIDED_BY_32     0b100
#define SPI_FPCLK_DIVIDED_BY_64     0b101
#define SPI_FPCLK_DIVIDED_BY_128    0b110
#define SPI_FPCLK_DIVIDED_BY_256    0b111
#define SPI_MSB_FIRST               0
#define SPI_LSB_FIRST 				 1
#define HW_SLAVE_MANAGEMENT          0
#define SW_SLAVE_MANAGEMENT          1
#define SPI_8BIT_DATA               0
#define SPI_16BIT_DATA              1

#define SPI_PRE_MASK                0xFFC7
#define MAX_PRE_OPTION              8

#define MAX_QUEUE_SIZE              100
#define EMPTY_POSITOIN              -1

typedef struct
{
	u16 u16_arr_data[MAX_QUEUE_SIZE];
	s8  s16_front_queue;
	s8  s16_rear_queue;
}SPI_QUEUE_t;

#endif /* SPI_PRV_H_ */



