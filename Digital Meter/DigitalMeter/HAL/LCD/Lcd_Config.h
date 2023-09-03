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

#define LCD_DATA_PORT DIO_u8_PORTA

#define D7 DIO_u8_PIN6 //Because D7 is attached to the pin no.7
#define D6 DIO_u8_PIN5
#define D5 DIO_u8_PIN4
#define D4 DIO_u8_PIN3
// Added in case of eight bit
#define D3 DIO_u8_PIN7
#define D2 DIO_u8_PIN2
#define D1 DIO_u8_PIN1
#define D0 DIO_u8_PIN0

#define LCD_CMD_PORT DIO_u8_PORTB

#define RS DIO_u8_PIN1  //
#define RW DIO_u8_PIN0  //
#define EN DIO_u8_PIN2  //

#endif /* HAL_LCD_LCD_CONFIG_H_ */
