/*
 * KPD_config.h
 *
 *  Created on: May 4, 2023
 *      Author: Abdallah
 */

#ifndef HAL_KPD_KPD_CONFIG_H_
#define HAL_KPD_KPD_CONFIG_H_


/**
 * ROWS PB4 --> PB7 OUTPUT
 * COLS PD2 --> PD5 INPUT
 */


#define KPD_U8_PORTROWS DIO_U8_PORT_A
#define KPD_U8_PORTCOLS DIO_U8_PORT_D

#define KPD_U8_R1 DIO_U8_PIN_0
#define KPD_U8_R2 DIO_U8_PIN_1
#define KPD_U8_R3 DIO_U8_PIN_2
#define KPD_U8_R4 DIO_U8_PIN_7

#define KPD_U8_C1 DIO_U8_PIN_2
#define KPD_U8_C2 DIO_U8_PIN_3
#define KPD_U8_C3 DIO_U8_PIN_4
#define KPD_U8_C4 DIO_U8_PIN_6

#define KPD_KEYS {{'7','8','9','/'},\
				  {'4','5','6','*'},\
		          {'1','2','3','-'},\
		          {'C','0','=','+'}}

#endif /* HAL_KPD_KPD_CONFIG_H_ */
