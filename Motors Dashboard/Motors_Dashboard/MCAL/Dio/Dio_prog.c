/*
 * Dio_prog.c
 *
 *  Created on: Apr 30, 2023
 *  Author: Abdallah
 */


#include "Dio_interface.h"
#include "../Registers.h"


#include "Dio_config.h"

// Keypad
// ROWS PB4 --> PB7 OUTPUT
// COLS PD2 --> PD5 INPUT And pull up activated

DIO_U8_Pin_Config Dio_CfgPinsArray[PIN_COUNT] = {
		// LCD Configurations
		{DIO_U8_PORT_A,DIO_U8_PIN_0,OUTPUT,PULLUP_OFF},
		{DIO_U8_PORT_A,DIO_U8_PIN_1,OUTPUT,PULLUP_OFF},
		{DIO_U8_PORT_A,DIO_U8_PIN_2,OUTPUT,PULLUP_OFF},
		{DIO_U8_PORT_A,DIO_U8_PIN_3,OUTPUT,PULLUP_OFF},
		{DIO_U8_PORT_A,DIO_U8_PIN_4,OUTPUT,PULLUP_OFF},
		{DIO_U8_PORT_A,DIO_U8_PIN_5,OUTPUT,PULLUP_OFF},
		{DIO_U8_PORT_A,DIO_U8_PIN_6,OUTPUT,PULLUP_OFF},
		{DIO_U8_PORT_A,DIO_U8_PIN_7,OUTPUT,PULLUP_OFF},
		// LED for testing
		{DIO_U8_PORT_C,DIO_U8_PIN_0,OUTPUT,PULLUP_OFF},
		// EX_INT2
		{DIO_U8_PORT_B,DIO_U8_PIN_2,INPUT,PULLUP_OFF},
		{DIO_U8_PORT_B,DIO_U8_PIN_0,OUTPUT,PULLUP_OFF},
		{DIO_U8_PORT_B,DIO_U8_PIN_1,OUTPUT,PULLUP_OFF},
		{DIO_U8_PORT_B,DIO_U8_PIN_3,OUTPUT,PULLUP_OFF},
		// KEYPAD ROWS
		{DIO_U8_PORT_B,DIO_U8_PIN_4,OUTPUT,PULLUP_OFF},
		{DIO_U8_PORT_B,DIO_U8_PIN_5,OUTPUT,PULLUP_OFF},
		{DIO_U8_PORT_B,DIO_U8_PIN_6,OUTPUT,PULLUP_OFF},
		{DIO_U8_PORT_B,DIO_U8_PIN_7,OUTPUT,PULLUP_OFF},
		// KEYPAD COLS
		{DIO_U8_PORT_D,DIO_U8_PIN_2,INPUT,PULLUP_ON},
		{DIO_U8_PORT_D,DIO_U8_PIN_3,INPUT,PULLUP_ON},
		{DIO_U8_PORT_D,DIO_U8_PIN_4,INPUT,PULLUP_ON},
		{DIO_U8_PORT_D,DIO_U8_PIN_6,INPUT,PULLUP_ON},
		// Motor
		{DIO_U8_PORT_B,DIO_U8_PIN_0,OUTPUT,PULLUP_OFF},
		{DIO_U8_PORT_C,DIO_U8_PIN_4,OUTPUT,PULLUP_OFF},
		{DIO_U8_PORT_D,DIO_U8_PIN_7,OUTPUT,PULLUP_OFF},
		{DIO_U8_PORT_D,DIO_U8_PIN_5,OUTPUT,PULLUP_OFF}

};


/**
 * DIO_ES_tSetPinDirection is used to set pin direction
 * ( INPUT or OUTPUT )
 */

ES_t DIO_ES_tSetPinDirection(DIO_U8_Port_Type copy_u8_PortId, DIO_U8_Pin_Type copy_u8_PinId, DIO_U8_Dir_Type copy_u8_PinDirection)
{
	if(copy_u8_PinId > PIN_LIMIT){
		return ES_NOT_OK;
	}
	if(copy_u8_PortId == DIO_U8_PORT_A){
		if(copy_u8_PinDirection == OUTPUT){
			SET_BIT(DDRA,copy_u8_PinId);
		}else if(copy_u8_PinDirection == INPUT){
			CLR_BIT(DDRA,copy_u8_PinId);
		}else{
			return ES_NOT_OK;
		}
	}else if(copy_u8_PortId == DIO_U8_PORT_B){
		if(copy_u8_PinDirection == OUTPUT){
			SET_BIT(DDRB,copy_u8_PinId);
		}else if(copy_u8_PinDirection == INPUT){
			CLR_BIT(DDRB,copy_u8_PinId);
		}else{
			return ES_NOT_OK;
		}
	}else if(copy_u8_PortId == DIO_U8_PORT_C){
		if(copy_u8_PinDirection == OUTPUT){
			SET_BIT(DDRC,copy_u8_PinId);
		}else if(copy_u8_PinDirection == INPUT){
			CLR_BIT(DDRC,copy_u8_PinId);
		}else{
			return ES_NOT_OK;
		}
	}else if(copy_u8_PortId == DIO_U8_PORT_D){
		if(copy_u8_PinDirection == OUTPUT){
			SET_BIT(DDRD,copy_u8_PinId);
		}else if(copy_u8_PinDirection == INPUT){
			CLR_BIT(DDRD,copy_u8_PinId);
		}else{
			return ES_NOT_OK;
		}
	}else{
		return ES_NOT_OK;
	}
	return ES_OK;
}

/**
 * DIO_ES_tSetPinValue is used to set pin value
 * ( LOW or HIGH )
 */

ES_t DIO_ES_tSetPinValue(DIO_U8_Port_Type copy_u8_PortId, DIO_U8_Pin_Type copy_u8_PinId, DIO_U8_Value_Type copy_u8_PinValue)
{
	if(copy_u8_PinId > PIN_LIMIT){
		return ES_NOT_OK;
	}
	if(copy_u8_PortId == DIO_U8_PORT_A){
		if(copy_u8_PinValue == HIGH){
			SET_BIT(PORTA,copy_u8_PinId);
		}else if(copy_u8_PinValue == LOW){
			CLR_BIT(PORTA,copy_u8_PinId);
		}else{
			return ES_NOT_OK;
		}
	}else if(copy_u8_PortId == DIO_U8_PORT_B){
		if(copy_u8_PinValue == HIGH){
			SET_BIT(PORTB,copy_u8_PinId);
		}else if(copy_u8_PinValue == LOW){
			CLR_BIT(PORTB,copy_u8_PinId);
		}else{
			return ES_NOT_OK;
		}
	}else if(copy_u8_PortId == DIO_U8_PORT_C){
		if(copy_u8_PinValue == HIGH){
			SET_BIT(PORTC,copy_u8_PinId);
		}else if(copy_u8_PinValue == LOW){
			CLR_BIT(PORTC,copy_u8_PinId);
		}else{
			return ES_NOT_OK;
		}
	}else if(copy_u8_PortId == DIO_U8_PORT_D){
		if(copy_u8_PinValue == HIGH){
			SET_BIT(PORTD,copy_u8_PinId);
		}else if(copy_u8_PinValue == LOW){
			CLR_BIT(PORTD,copy_u8_PinId);
		}else{
			return ES_NOT_OK;
		}
	}else{
		return ES_NOT_OK;
	}
	return ES_OK;
}

/**
 * DIO_ES_tGetPinValue is used to read pin value
 * ( LOW or HIGH )
 */


ES_t DIO_ES_tGetPinValue(DIO_U8_Port_Type copy_u8_PortId, DIO_U8_Pin_Type copy_u8_PinId, DIO_U8_Value_Type* copy_pu8_PinValue)
{
	if(copy_u8_PinId > PIN_LIMIT){
		return ES_NOT_OK;
	}
	if(copy_u8_PortId == DIO_U8_PORT_A){
		*copy_pu8_PinValue = GET_BIT(PINA,copy_u8_PinId);
	}else if(copy_u8_PortId == DIO_U8_PORT_B){
		*copy_pu8_PinValue = GET_BIT(PINB,copy_u8_PinId);
	}else if(copy_u8_PortId == DIO_U8_PORT_C){
		*copy_pu8_PinValue = GET_BIT(PINC,copy_u8_PinId);
	}else if(copy_u8_PortId == DIO_U8_PORT_D){
		*copy_pu8_PinValue = GET_BIT(PIND,copy_u8_PinId);
	}else{
		return ES_NOT_OK;
	}
	return ES_OK;
}

/**
 * DIO_ES_tSetPortDirection is used to Set direction
 * of a whole port
 * ( LOW or HIGH )
 */


ES_t DIO_ES_tSetPortDirection(DIO_U8_Port_Type copy_u8_PortId, DIO_U8_Dir_Type copy_u8_PortDirection)
{
	if((copy_u8_PortDirection != OUTPUT) && (copy_u8_PortDirection != OUTPUT)){
		return ES_NOT_OK;
	}
	switch(copy_u8_PortId){
	case DIO_U8_PORT_A:
		if(copy_u8_PortDirection == OUTPUT)
			DDRA = 0xff;
		else
			DDRA = 0x00;
		break;
	case DIO_U8_PORT_B:
		if(copy_u8_PortDirection == OUTPUT)
			DDRB = 0xff;
		else
			DDRB = 0x00;
		break;
	case DIO_U8_PORT_C:
		if(copy_u8_PortDirection == OUTPUT)
			DDRC = 0xff;
		else
			DDRC = 0x00;
		break;
	case DIO_U8_PORT_D:
		if(copy_u8_PortDirection == OUTPUT)
			DDRD = 0xff;
		else
			DDRD = 0x00;
		break;
	default:
		return ES_NOT_OK;
		break;
	}
	return ES_OK;
}



ES_t DIO_ES_tSetPortValue(DIO_U8_Port_Type copy_u8_PortId, u8 copy_u8_PortValue)
{
	if((copy_u8_PortValue != HIGH) && (copy_u8_PortValue != LOW)){
		return ES_NOT_OK;
	}
	switch(copy_u8_PortId){
	case DIO_U8_PORT_A:
		if(copy_u8_PortValue == HIGH)
			PORTA = 0xff;
		else
			PORTA = 0x00;
		break;
	case DIO_U8_PORT_B:
		if(copy_u8_PortValue == HIGH)
			PORTB = 0xff;
		else
			PORTB = 0x00;
		break;
	case DIO_U8_PORT_C:
		if(copy_u8_PortValue == HIGH)
			PORTC = 0xff;
		else
			PORTC = 0x00;
		break;
	case DIO_U8_PORT_D:
		if(copy_u8_PortValue == HIGH)
			PORTD = 0xff;
		else
			PORTD = 0x00;
		break;
	default:
		return ES_NOT_OK;
		break;
	}
	return ES_OK;
}

/*
 * DIO_ES_tTOGPin is used to Toggle a specific pin
 */

ES_t DIO_ES_tTOGPin(DIO_U8_Port_Type copy_u8_PortId, DIO_U8_Pin_Type copy_u8_PinId)
{
	if(copy_u8_PinId > PIN_LIMIT){
		return ES_NOT_OK;
	}
	if(copy_u8_PortId == DIO_U8_PORT_A){
		TOG_BIT(PORTA,copy_u8_PinId);
	}else if(copy_u8_PortId == DIO_U8_PORT_B){
		TOG_BIT(PORTB,copy_u8_PinId);
	}else if(copy_u8_PortId == DIO_U8_PORT_C){
		TOG_BIT(PORTC,copy_u8_PinId);
	}else if(copy_u8_PortId == DIO_U8_PORT_D){
		TOG_BIT(PORTD,copy_u8_PinId);
	}else{
		return ES_NOT_OK;
	}
	return ES_OK;
}


/************************************************************************/
/* To initialize the pins used (output or input)
 Which are stored in an array of structures in configuration.c file  */
/************************************************************************/




ES_t DIO_ES_tInit(void)
{
	int i = 0;
	for(i=0 ; i<PIN_COUNT ; i++){
		if(Dio_CfgPinsArray[i].PinPort == DIO_U8_PORT_A){
			if(Dio_CfgPinsArray[i].dir == OUTPUT){
				SET_BIT(DDRA,Dio_CfgPinsArray[i].Pin);
			}else{
				CLR_BIT(DDRA,Dio_CfgPinsArray[i].Pin);
				if(Dio_CfgPinsArray[i].PullUp == PULLUP_ON){
					SET_BIT(PORTA,Dio_CfgPinsArray[i].Pin);
				}else if(Dio_CfgPinsArray[i].PullUp == PULLUP_OFF){
					CLR_BIT(PORTA,Dio_CfgPinsArray[i].Pin);
				}
			}
		}else if(Dio_CfgPinsArray[i].PinPort == DIO_U8_PORT_B){
			if(Dio_CfgPinsArray[i].dir == OUTPUT){
				SET_BIT(DDRB,Dio_CfgPinsArray[i].Pin);
			}else{
				CLR_BIT(DDRB,Dio_CfgPinsArray[i].Pin);
				if(Dio_CfgPinsArray[i].PullUp == PULLUP_ON){
					SET_BIT(PORTB,Dio_CfgPinsArray[i].Pin);
				}else if(Dio_CfgPinsArray[i].PullUp == PULLUP_OFF){
					CLR_BIT(PORTA,Dio_CfgPinsArray[i].Pin);
				}
			}
		}else if(Dio_CfgPinsArray[i].PinPort == DIO_U8_PORT_C){
			if(Dio_CfgPinsArray[i].dir == OUTPUT){
				SET_BIT(DDRC,Dio_CfgPinsArray[i].Pin);
			}else{
				CLR_BIT(DDRC,Dio_CfgPinsArray[i].Pin);
				if(Dio_CfgPinsArray[i].PullUp == PULLUP_ON){
					SET_BIT(PORTC,Dio_CfgPinsArray[i].Pin);
				}else if(Dio_CfgPinsArray[i].PullUp == PULLUP_OFF){
					CLR_BIT(PORTA,Dio_CfgPinsArray[i].Pin);
				}
			}
		}else if(Dio_CfgPinsArray[i].PinPort == DIO_U8_PORT_D){
			if(Dio_CfgPinsArray[i].dir == OUTPUT){
				SET_BIT(DDRD,Dio_CfgPinsArray[i].Pin);
			}else{
				CLR_BIT(DDRD,Dio_CfgPinsArray[i].Pin);
				if(Dio_CfgPinsArray[i].PullUp == PULLUP_ON){
					SET_BIT(PORTD,Dio_CfgPinsArray[i].Pin);
				}else if(Dio_CfgPinsArray[i].PullUp == PULLUP_OFF){
					CLR_BIT(PORTA,Dio_CfgPinsArray[i].Pin);
				}
			}
		}
	}
	return ES_OK;
}

