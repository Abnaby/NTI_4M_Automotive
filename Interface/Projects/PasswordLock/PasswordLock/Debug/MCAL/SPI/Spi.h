 /*************************************************
 *  File		: Spi.h
 *	Module		: SPI
 *	Target		: ATMEGA32
 *	Author		: mFawzi
 *  Description	:
 **************************************************/
#ifndef SPI_H
#define SPI_H

#include "spi_reg.h"
#include "std_types.h"
#include "bit_math.h"
#include "dio.h"

#define SPI_SCK_FREQ_FCPU_DIV_4			(0<<0)
#define SPI_SCK_FREQ_FCPU_DIV_16		(1<<0)
#define SPI_SCK_FREQ_FCPU_DIV_64		(2<<0)
#define SPI_SCK_FREQ_FCPU_DIV_128		(3<<0)

#define SPI_SPE_BIT_NO           	(6)
#define SPI_MSTR_BIT_NO				(4)
#define SPI_SPIF_BIT_NO				(7)

void spi_masterInit(void (*ptrExchangeInterrupt)(u8 commingData));
void spi_slaveInit(void (*ptrExchangeInterrupt)(u8 commingData));
void spi_masterSendByte(u8 data);
u8 spi_masterReceiveByte(void);
u8 spi_masterTranseveByte(u8 data);

u8 spi_slaveReceiveByte(void);
void spi_SlaveSendByte(u8 data);

void spi_masterSendByteUsingIRQ(u8 data);
u8 spi_masterReceiveByteUsingIRQ(u8 dummyValue);

#endif  /* UART_H */
