/*
 * Lcd.h
 *
 *  Created on: Sep 12, 2022
 *      Author: 10
 */

#ifndef HAL_LCD_LCD_H_
#define HAL_LCD_LCD_H_

#define Four_BitMode 0x02
#define Eight_BitMode 0x38
#define CLR_Display 0x01
#define D4_D7 0x28
#define CursorOFF 0x0c
#define CursorON 0x0E
#define IncrCursor 0x06
#define Force1stline 0x80
#define Force2ndline 0xC0
#define ShiftLeft 0x18
#define ShiftRight 0x1C


#include "Lcd_Config.h"
#include "../../MCAL/Dio/Dio_interface.h"

// ES_t DIO_ES_tTOGPin(DIO_U8_Port_Type copy_u8_PortId, DIO_U8_Pin_Type copy_u8_PinId);

ES_t Lcd_ES_tInit();
ES_t Lcd_ES_tsendCmd(u8 cmd);
ES_t Lcd_ES_tsendChar(u8 data);
ES_t Lcd_ES_tsendChar_xy(u8 data,u8 row,u8 col);

ES_t Lcd_ES_tsendString(char *data);
ES_t Lcd_ES_tsendString_xy(char *data,u8 row,u8 col);

ES_t Lcd_ES_tdisplayNum(u16 num);
ES_t Lcd_ES_tdisplayNum_xy(u16 num,u8 row,u8 col);

ES_t LCD_ES_tGoTo(u8 Line, u8 x);
ES_t lcd_ES_tclear();


#endif /* HAL_LCD_LCD_H_ */
