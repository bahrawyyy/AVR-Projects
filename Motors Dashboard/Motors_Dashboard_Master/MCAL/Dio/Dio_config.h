/*
 * Dio_config.h
 *
 *  Created on: Apr 30, 2023
 *      Author: Abdallah
 */


// This file includes configurations for the driver

#ifndef MCAL_DIO_DIO_CONFIG_H_
#define MCAL_DIO_DIO_CONFIG_H_

#include "Dio_interface.h"

#define PIN_COUNT 26

typedef struct{
	DIO_U8_Port_Type PinPort;
	DIO_U8_Pin_Type Pin;
	DIO_U8_Dir_Type dir;
	DIO_U8_PULLUP_Type PullUp;
}DIO_U8_Pin_Config;

extern DIO_U8_Pin_Config Dio_CfgPinsArray[PIN_COUNT];


#endif /* MCAL_DIO_DIO_CONFIG_H_ */
