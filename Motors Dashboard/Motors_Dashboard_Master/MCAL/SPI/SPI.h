/*
 * SPI.h
 *
 *  Created on: Jul 24, 2023
 *      Author: Abdallah
 */

#ifndef MCAL_SPI_SPI_H_
#define MCAL_SPI_SPI_H_

#include "../Dio/Dio_interface.h"
#include "../Registers.h"

/**
 * 	Pins Configurations
 * 	Note: Differs based on Device Mode
 */

#define SPI_REG		DIO_U8_PORT_B
#define SS			DIO_U8_PIN_4
#define MOSI		DIO_U8_PIN_5
#define MISO		DIO_U8_PIN_6
#define SCK			DIO_U8_PIN_7

/** ===========================
 *  Configuration Structure
   ============================ */

typedef struct
{
	u8		Device_Mode;		// Specifies whether you are a master or slave @ref SPI_DEVICE_MODE_Define
	u8		Data_Order;			// Specifies whether LSB or MSB is transmitted first @ref SPI_DATA_ORDER_Define
	u8		CLK_Polarity;		// Specifies which state (LOW or HIGH) is the idle one @ref SPI_CLK_Polarity_Define
	u8 		CLK_PHASE;			// Determine if data is sampled on the leading (first) or trailing (last) edge of SCK @ref SPI_CLK_PHASE_Define
	u8		Prescalar;			// Determine the precsalar of fosc @ref SPI_Prescalar_Define
	u8		IRQ_Mode;			// Determine if the interrupt is enabled or not
	void(*SPI_P_to_Func)(void);	// A pointer to the function
}SPI_Config_t;


/** ===========================
 *  Reference Macros
   ============================ */


// @ref SPI_DEVICE_MODE_Define (MSTR:4 in SPCR)
#define SPI_DEVICE_MODE_SLAVE		(u8)(~(1<<MSTR))
#define SPI_DEVICE_MODE_MASTER		(u8)(1<<MSTR)



// @ref SPI_DATA_ORDER_Define (DORD: 5 in SPCR)
#define SPI_DATA_ORDER_MSB			(u8)(0)
#define SPI_DATA_ORDER_LSB			(u8)(1<<DORD)


// @ref SPI_CLK_Polarity_Define (CPOL: 3 in SPCR)
#define SPI_CLK_Polarity_IDLE_LOW	(u8)(0)
#define SPI_CLK_Polarity_IDLE_HIGH	(u8)(1<<CPOL)


// @ref SPI_CLK_PHASE_Define (CPHA: 2 in SPCR)
#define SPI_CLK_PHASE_LEADING_SAMPLE	(u8)(0)
#define SPI_CLK_PHASE_TRAILING_SAMPLE	(u8)(1<<CPHA)


// @ref SPI_Prescalar_Define
#define SPI_Prescalar_4			0
#define SPI_Prescalar_16		1
#define SPI_Prescalar_64		2
#define SPI_Prescalar_128		3
#define SPI_Prescalar_2			4
#define SPI_Prescalar_8			5
#define SPI_Prescalar_32		6

// @ref SPI_IRQ_Define
#define SPI_IRQ_Disable			0
#define SPI_IRQ_Enable			1


/** ===========================
 *  APIs Supported by SPI driver
   ============================ */


void SPI_Init(SPI_Config_t * SPI_Cfg);

void SPI_Transmit(u8 data);
u8 SPI_Receive();

u8 SPI_Transmit_Receive(u8 data);



#endif /* MCAL_SPI_SPI_H_ */
