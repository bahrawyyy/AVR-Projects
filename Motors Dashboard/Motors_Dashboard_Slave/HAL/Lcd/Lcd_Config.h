/*
 * Lcd_Config.h
 *
 *  Created on: Sep 12, 2022
 *      Author: 10
 */

#ifndef HAL_LCD_LCD_CONFIG_H_
#define HAL_LCD_LCD_CONFIG_H_

//This is a file to define index of pins

// LCD is attached to PORTB

// DIO_U8_PIN_0

#define LCD_MODE FOUR_BIT_MODE

#define EIGHT_BIT_MODE 0
#define FOUR_BIT_MODE 1

#define LCD_DATA_PORT DIO_U8_PORT_A

#define D7 DIO_U8_PIN_6 //Because D7 is attached to the pin no.7
#define D6 DIO_U8_PIN_5
#define D5 DIO_U8_PIN_4
#define D4 DIO_U8_PIN_3
// Added in case of eight bit
#define D3 DIO_U8_PIN_7
#define D2 DIO_U8_PIN_2
#define D1 DIO_U8_PIN_1
#define D0 DIO_U8_PIN_0

#define LCD_CMD_PORT DIO_U8_PORT_B

#define RS DIO_U8_PIN_1  //
#define EN DIO_U8_PIN_0  //

#endif /* HAL_LCD_LCD_CONFIG_H_ */
