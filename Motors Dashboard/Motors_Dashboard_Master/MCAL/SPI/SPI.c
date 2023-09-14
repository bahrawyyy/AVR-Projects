/*
 * SPI.c
 *
 *  Created on: Jul 24, 2023
 *      Author: Abdallah
 */


#include "SPI.h"

#define NULLPTR ((void*)0)   // 0 casted to an address


static void (*GP_SPI_STC)(void);

void SPI_Init(SPI_Config_t * SPI_Cfg)
{
	if(SPI_Cfg->Device_Mode == SPI_DEVICE_MODE_MASTER)
	{
		// SCK, MOSI, SS Output
		DIO_ES_tSetPinDirection(SPI_REG, SCK, OUTPUT);
		DIO_ES_tSetPinDirection(SPI_REG, MOSI, OUTPUT);
		DIO_ES_tSetPinDirection(SPI_REG, SS, OUTPUT);

		// Set MISO pin as INPUT
		DIO_ES_tSetPinDirection(SPI_REG, MISO, INPUT);


		SPCR |= SPI_DEVICE_MODE_MASTER;

		// The master is the one who generates the clock
		if(SPI_Cfg->Prescalar == SPI_Prescalar_4){
			CLR_BIT(SPCR,SPR0);
			CLR_BIT(SPCR,SPR1);
			CLR_BIT(SPSR,SPI2X);
		}else if(SPI_Cfg->Prescalar == SPI_Prescalar_16){
			SET_BIT(SPCR,SPR0);
			CLR_BIT(SPCR,SPR1);
			CLR_BIT(SPSR,SPI2X);
		}else if(SPI_Cfg->Prescalar == SPI_Prescalar_64){
			CLR_BIT(SPCR,SPR0);
			SET_BIT(SPCR,SPR1);
			CLR_BIT(SPSR,SPI2X);
		}else if(SPI_Cfg->Prescalar == SPI_Prescalar_128){
			SET_BIT(SPCR,SPR0);
			SET_BIT(SPCR,SPR1);
			CLR_BIT(SPSR,SPI2X);
		}else if(SPI_Cfg->Prescalar == SPI_Prescalar_2){
			CLR_BIT(SPCR,SPR0);
			CLR_BIT(SPCR,SPR1);
			SET_BIT(SPSR,SPI2X);
		}else if(SPI_Cfg->Prescalar == SPI_Prescalar_8){
			SET_BIT(SPCR,SPR0);
			CLR_BIT(SPCR,SPR1);
			SET_BIT(SPSR,SPI2X);
		}else if(SPI_Cfg->Prescalar == SPI_Prescalar_32){
			CLR_BIT(SPCR,SPR0);
			SET_BIT(SPCR,SPR1);
			SET_BIT(SPSR,SPI2X);
		}

	}else
	{   // Slave

		DIO_ES_tSetPinDirection(SPI_REG, MISO, OUTPUT);
		// Set SCK, MOSI, and SS pins as INPUT (slave mode doesn't need them as output)
		DIO_ES_tSetPinDirection(SPI_REG, SCK, INPUT);
		DIO_ES_tSetPinDirection(SPI_REG, MOSI, INPUT);
		DIO_ES_tSetPinDirection(SPI_REG, SS, INPUT);


		SPCR &= SPI_DEVICE_MODE_SLAVE;
	}



	// Common Configurations
	SPCR |= SPI_Cfg->CLK_Polarity;

	SPCR |= SPI_Cfg->CLK_PHASE;

	SPCR |= SPI_Cfg->Data_Order;


	// If interrupt is enabled
	if(SPI_Cfg->IRQ_Mode != SPI_IRQ_Disable)
	{
		SPCR |= (1<<SPIE);
	}

	GP_SPI_STC = SPI_Cfg->SPI_P_to_Func;

	// Enable SPI
	SET_BIT(SPCR,SPE);
}





u8 SPI_Transmit_Receive(u8 data)
{
	SPDR = data;
	while(!GET_BIT(SPSR,SPIF));
	// Return data received from slave
	return SPDR;
}


ISR(SPI_STC_vect)
{
	if(GP_SPI_STC != NULLPTR){
		GP_SPI_STC();
	}
}


u8 SPI_Receive()
{
    // Wait for data reception to complete
    while (!GET_BIT(SPSR, SPIF));

    // Return data received from slave
    return SPDR;
}


void SPI_Transmit(u8 data)
{
    SPDR = data;
    while (!GET_BIT(SPSR, SPIF));
}



