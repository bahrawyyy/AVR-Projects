/*
 * interface.h
 *
 *  Created on: Apr 30, 2023
 *      Author: Abdallah
 */

// This file includes prototypes of functions
// and Macros used by upper layer

#ifndef MCAL_DIO_DIO_INTERFACE_H_
#define MCAL_DIO_DIO_INTERFACE_H_

#include "../../LIB/STD_Types.h"
#include "../../LIB/ErrorState.h"
#include "../../LIB/Bit_Math.h"


#define PIN_LIMIT 7

typedef enum{
	DIO_U8_PIN_0,
	DIO_U8_PIN_1,
	DIO_U8_PIN_2,
	DIO_U8_PIN_3,
	DIO_U8_PIN_4,
	DIO_U8_PIN_5,
	DIO_U8_PIN_6,
	DIO_U8_PIN_7
}DIO_U8_Pin_Type;

typedef enum{
	DIO_U8_PORT_A,
	DIO_U8_PORT_B,
	DIO_U8_PORT_C,
	DIO_U8_PORT_D
}DIO_U8_Port_Type;

typedef enum{
	INPUT,
	OUTPUT
}DIO_U8_Dir_Type;

typedef enum{
	LOW,
	HIGH
}DIO_U8_Value_Type;

typedef enum{
	PULLUP_OFF,
	PULLUP_ON
}DIO_U8_PULLUP_Type;

ES_t DIO_ES_tSetPinDirection(DIO_U8_Port_Type copy_u8_PortId, DIO_U8_Pin_Type copy_u8_PinId, DIO_U8_Dir_Type copy_u8_PinDirection);
ES_t DIO_ES_tSetPinValue(DIO_U8_Port_Type copy_u8_PortId, DIO_U8_Pin_Type copy_u8_PinId, DIO_U8_Value_Type copy_u8_PinValue);
ES_t DIO_ES_tGetPinValue(DIO_U8_Port_Type copy_u8_PortId, DIO_U8_Pin_Type copy_u8_PinId, DIO_U8_Value_Type* copy_pu8_PinValue);
ES_t DIO_ES_tTOGPin(DIO_U8_Port_Type copy_u8_PortId, DIO_U8_Pin_Type copy_u8_PinId);
ES_t DIO_ES_tSetPortDirection(DIO_U8_Port_Type copy_u8_PortId, DIO_U8_Dir_Type copy_u8_PortDirection);
ES_t DIO_ES_tSetPortValue(DIO_U8_Port_Type copy_u8_PortId, u8 copy_u8_PortValue);
ES_t DIO_ES_tGetPortValue(DIO_U8_Port_Type copy_u8_PortId, u8* copy_pu8_PortValue);
ES_t DIO_ES_tInit(void);


#endif /* MCAL_DIO_DIO_INTERFACE_H_ */
