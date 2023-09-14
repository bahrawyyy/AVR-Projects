/*
 * Lcd.c
 *
 *  Created on: Sep 12, 2022
 *      Author: 10
 */

#define F_CPU 16000000UL

#include "Lcd.h"
#include <util/delay.h>
#include <string.h>

//ProtoType of static is defined in source file itself(Private declaration)
static ES_t LCD_ES_tTrigger_Enable(void);
static ES_t LCD_ES_tSet_Cursor_Pos(u8 row,u8 column);

//We make it static cuz we won't use it anywhere but here
static ES_t LCD_ES_tTrigger_Enable(void){
	DIO_ES_tSetPinValue(LCD_CMD_PORT, EN, HIGH);
	_delay_us(10);
	DIO_ES_tSetPinValue(LCD_CMD_PORT, EN, LOW);
	_delay_us(2000);
	return ES_OK;
}


ES_t Lcd_ES_tInit(){
#if LCD_MODE == FOUR_BIT_MODE
	Lcd_ES_tsendCmd(Four_BitMode);   /* Go into 4-bit operating mode*/
	Lcd_ES_tsendCmd(D4_D7);  /* 2 Line, 5*7 matrix in 4-bit mode */
	Lcd_ES_tsendCmd(CursorON);  /* Display on cursor off */
	Lcd_ES_tsendCmd(IncrCursor);  /* Increment cursor (shift cursor to right) */
	Lcd_ES_tsendCmd(CLR_Display);  /* Clear display screen */
	return ES_OK;
#elif LCD_MODE == EIGHT_BIT_MODE
	Lcd_ES_tsendCmd(Eight_BitMode);
	Lcd_ES_tsendCmd(CursorON);  /* Display on cursor off */
	Lcd_ES_tsendCmd(IncrCursor);  /* Increment cursor (shift cursor to right) */
	Lcd_ES_tsendCmd(CLR_Display);  /* Clear display screen */
	return ES_OK;
#endif
}

/*
 * RS = 0 // To send command
 * RW = 0 //To write on the LCD
 *  4-bit mode
 * Send higher nibble(1/2 Byte)
 * Send Trigger Enable
 * Send Lower nibble
 * Send Trigger Enable
 * delay
 *
 *
 *	Ex. 0x28 0b 0010 1000  //Read bit by bit and see if it is low or high
 */

ES_t lcd_ES_tclear()
{
	Lcd_ES_tsendCmd(CLR_Display);
	_delay_ms(2);
	return ES_OK;
}

ES_t Lcd_ES_tsendCmd(u8 cmd){
	DIO_ES_tSetPinValue(LCD_CMD_PORT, RS, LOW);
	// DIO_ES_tGetPinValue, DIO_ES_tSetPinValue
	// if(GET_BIT(cmd,7)){Dio_Write(D7,HIGH);}else{Dio_write(D7,LOW);}
	// We use ternary operator instead
#if LCD_MODE == FOUR_BIT_MODE
	(GET_BIT(cmd,7)) ? DIO_ES_tSetPinValue(LCD_DATA_PORT, D7,HIGH) : DIO_ES_tSetPinValue(LCD_DATA_PORT, D7,LOW);
	(GET_BIT(cmd,6)) ? DIO_ES_tSetPinValue(LCD_DATA_PORT, D6,HIGH) : DIO_ES_tSetPinValue(LCD_DATA_PORT, D6,LOW);
	(GET_BIT(cmd,5)) ? DIO_ES_tSetPinValue(LCD_DATA_PORT, D5,HIGH) : DIO_ES_tSetPinValue(LCD_DATA_PORT, D5,LOW);
	(GET_BIT(cmd,4)) ? DIO_ES_tSetPinValue(LCD_DATA_PORT, D4,HIGH) : DIO_ES_tSetPinValue(LCD_DATA_PORT, D4,LOW);
	//Trigger Enable
	LCD_ES_tTrigger_Enable();
	(GET_BIT(cmd,3)) ? DIO_ES_tSetPinValue(LCD_DATA_PORT, D7,HIGH) : DIO_ES_tSetPinValue(LCD_DATA_PORT, D7,LOW);
	(GET_BIT(cmd,2)) ? DIO_ES_tSetPinValue(LCD_DATA_PORT, D6,HIGH) : DIO_ES_tSetPinValue(LCD_DATA_PORT, D6,LOW);
	(GET_BIT(cmd,1)) ? DIO_ES_tSetPinValue(LCD_DATA_PORT, D5,HIGH) : DIO_ES_tSetPinValue(LCD_DATA_PORT, D5,LOW);
	(GET_BIT(cmd,0)) ? DIO_ES_tSetPinValue(LCD_DATA_PORT, D4,HIGH) : DIO_ES_tSetPinValue(LCD_DATA_PORT, D4,LOW);
	//Trigger Enable
	LCD_ES_tTrigger_Enable();
	return ES_OK;
#elif LCD_MODE == EIGHT_BIT_MODE
	(GET_BIT(cmd,7)) ? DIO_ES_tSetPinValue(LCD_DATA_PORT, D7,HIGH) : DIO_ES_tSetPinValue(LCD_DATA_PORT, D7,LOW);
	(GET_BIT(cmd,6)) ? DIO_ES_tSetPinValue(LCD_DATA_PORT, D6,HIGH) : DIO_ES_tSetPinValue(LCD_DATA_PORT, D6,LOW);
	(GET_BIT(cmd,5)) ? DIO_ES_tSetPinValue(LCD_DATA_PORT, D5,HIGH) : DIO_ES_tSetPinValue(LCD_DATA_PORT, D5,LOW);
	(GET_BIT(cmd,4)) ? DIO_ES_tSetPinValue(LCD_DATA_PORT, D4,HIGH) : DIO_ES_tSetPinValue(LCD_DATA_PORT, D4,LOW);
	(GET_BIT(cmd,3)) ? DIO_ES_tSetPinValue(LCD_DATA_PORT, D3,HIGH) : DIO_ES_tSetPinValue(LCD_DATA_PORT, D3,LOW);
	(GET_BIT(cmd,2)) ? DIO_ES_tSetPinValue(LCD_DATA_PORT, D2,HIGH) : DIO_ES_tSetPinValue(LCD_DATA_PORT, D2,LOW);
	(GET_BIT(cmd,1)) ? DIO_ES_tSetPinValue(LCD_DATA_PORT, D1,HIGH) : DIO_ES_tSetPinValue(LCD_DATA_PORT, D1,LOW);
	(GET_BIT(cmd,0)) ? DIO_ES_tSetPinValue(LCD_DATA_PORT, D0,HIGH) : DIO_ES_tSetPinValue(LCD_DATA_PORT, D0,LOW);
	//Trigger Enable
	LCD_ES_tTrigger_Enable();
	return ES_OK;
#endif
}
ES_t Lcd_ES_tsendChar(u8 data){
#if LCD_MODE == FOUR_BIT_MODE
	DIO_ES_tSetPinValue(LCD_CMD_PORT, RS, HIGH);
	(GET_BIT(data,7)) ? DIO_ES_tSetPinValue(LCD_DATA_PORT, D7,HIGH) : DIO_ES_tSetPinValue(LCD_DATA_PORT, D7,LOW);
	(GET_BIT(data,6)) ? DIO_ES_tSetPinValue(LCD_DATA_PORT, D6,HIGH) : DIO_ES_tSetPinValue(LCD_DATA_PORT, D6,LOW);
	(GET_BIT(data,5)) ? DIO_ES_tSetPinValue(LCD_DATA_PORT, D5,HIGH) : DIO_ES_tSetPinValue(LCD_DATA_PORT, D5,LOW);
	(GET_BIT(data,4)) ? DIO_ES_tSetPinValue(LCD_DATA_PORT, D4,HIGH) : DIO_ES_tSetPinValue(LCD_DATA_PORT, D4,LOW);
	//Trigger Enable
	LCD_ES_tTrigger_Enable();
	(GET_BIT(data,3)) ? DIO_ES_tSetPinValue(LCD_DATA_PORT, D7,HIGH) : DIO_ES_tSetPinValue(LCD_DATA_PORT, D7,LOW);
	(GET_BIT(data,2)) ? DIO_ES_tSetPinValue(LCD_DATA_PORT, D6,HIGH) : DIO_ES_tSetPinValue(LCD_DATA_PORT, D6,LOW);
	(GET_BIT(data,1)) ? DIO_ES_tSetPinValue(LCD_DATA_PORT, D5,HIGH) : DIO_ES_tSetPinValue(LCD_DATA_PORT, D5,LOW);
	(GET_BIT(data,0)) ? DIO_ES_tSetPinValue(LCD_DATA_PORT, D4,HIGH) : DIO_ES_tSetPinValue(LCD_DATA_PORT, D4,LOW);
	//Trigger Enable
	LCD_ES_tTrigger_Enable();
	return ES_OK;
#elif LCD_MODE == EIGHT_BIT_MODE
	(GET_BIT(data,7)) ? DIO_ES_tSetPinValue(LCD_DATA_PORT, D7,HIGH) : DIO_ES_tSetPinValue(LCD_DATA_PORT, D7,LOW);
	(GET_BIT(data,6)) ? DIO_ES_tSetPinValue(LCD_DATA_PORT, D6,HIGH) : DIO_ES_tSetPinValue(LCD_DATA_PORT, D6,LOW);
	(GET_BIT(data,5)) ? DIO_ES_tSetPinValue(LCD_DATA_PORT, D5,HIGH) : DIO_ES_tSetPinValue(LCD_DATA_PORT, D5,LOW);
	(GET_BIT(data,4)) ? DIO_ES_tSetPinValue(LCD_DATA_PORT, D4,HIGH) : DIO_ES_tSetPinValue(LCD_DATA_PORT, D4,LOW);
	(GET_BIT(data,3)) ? DIO_ES_tSetPinValue(LCD_DATA_PORT, D3,HIGH) : DIO_ES_tSetPinValue(LCD_DATA_PORT, D3,LOW);
	(GET_BIT(data,2)) ? DIO_ES_tSetPinValue(LCD_DATA_PORT, D2,HIGH) : DIO_ES_tSetPinValue(LCD_DATA_PORT, D2,LOW);
	(GET_BIT(data,1)) ? DIO_ES_tSetPinValue(LCD_DATA_PORT, D1,HIGH) : DIO_ES_tSetPinValue(LCD_DATA_PORT, D1,LOW);
	(GET_BIT(data,0)) ? DIO_ES_tSetPinValue(LCD_DATA_PORT, D0,HIGH) : DIO_ES_tSetPinValue(LCD_DATA_PORT, D0,LOW);
	//Trigger Enable
	LCD_ES_tTrigger_Enable();
	return ES_OK;
#endif

}

ES_t Lcd_ES_tsendString(char *data)
{
	DIO_ES_tSetPinValue(LCD_CMD_PORT, RS, HIGH);

	unsigned char i=0;
	while(data[i]!=0)
	{
		Lcd_ES_tsendChar(data[i]);
		i++;
	}
	return ES_OK;
}

ES_t Lcd_ES_tsendString_xy(char *data,u8 row,u8 col){
	DIO_ES_tSetPinValue(LCD_CMD_PORT, RS, HIGH);


	LCD_ES_tSet_Cursor_Pos(row,col);
	Lcd_ES_tsendString(data);
	return ES_OK;

}


//A function to display Numbers instead of characters
ES_t Lcd_ES_tdisplayNum(u16 num)
{
	DIO_ES_tSetPinValue(LCD_CMD_PORT, RS, HIGH);


	uint8_t ch[10],i=0,j=0;
	if(num == 0)
	{
		Lcd_ES_tsendChar('0');
	}
	else
	{
		while(num)
		{
			ch[i] = num % 10 + '0';  //To convert int to char
			num /= 10;
			i++;
		} //Thus number entered is reversed so, we want to display it correctly
		for(j=i;j>0;j--)
		{
			Lcd_ES_tsendChar(ch[j-1]);
		}
	}
	return ES_OK;
}

ES_t Lcd_ES_tdisplayNum_xy(u16 num,u8 row,u8 col){

	DIO_ES_tSetPinValue(LCD_CMD_PORT, RS, HIGH);


	if(row == 1){
		Lcd_ES_tsendCmd(Force1stline);
		_delay_ms(1);
	}else if(row == 2){
		Lcd_ES_tsendCmd(Force2ndline);
		_delay_ms(10);
	}else{
		return ES_NOT_OK;
	}


	for(int j=1;j<=col;j++){
		Lcd_ES_tsendCmd(ShiftRight);
	}

	Lcd_ES_tdisplayNum(num);
	return ES_OK;

}

ES_t Lcd_ES_tsendChar_xy(u8 data,u8 row,u8 col){
	DIO_ES_tSetPinValue(LCD_CMD_PORT, RS, HIGH);


	if(row == 1){
		Lcd_ES_tsendCmd(Force1stline);
		_delay_ms(1);
	}else if(row == 2){
		Lcd_ES_tsendCmd(Force2ndline);
		_delay_ms(10);
	}else{
		return ES_NOT_OK;
	}

	for(int j=1;j<=col;j++){
		Lcd_ES_tsendCmd(ShiftRight);
	}
	Lcd_ES_tsendChar(data);
	return ES_OK;
}

static ES_t LCD_ES_tSet_Cursor_Pos(u8 row,u8 column){
	column--;
	switch(row){
	case 1:
		Lcd_ES_tsendCmd((0x80 + column));
		break;
	case 2:
		Lcd_ES_tsendCmd((0xc0 + column));
		break;
	default:
		return ES_NOT_OK;
	}
	return ES_OK;
}

/************************************************************************/
ES_t LCD_ES_tGoTo(u8 Line, u8 x){
	if(0 == Line)
	{
		if ( x <=15)
		{
			Lcd_ES_tsendCmd(0x80 + x);
		}
	}
	else if (1 == Line)
	{
		if ( x <=15)
		{
			Lcd_ES_tsendCmd(0xC0 + x);
		}
	}// In case of 16*4 lcd
	else if(2 == Line)
	{
		if ( x <=15)
		{
			Lcd_ES_tsendCmd(0x90 + x);
		}
	}else if(3 == Line)
	{
		if ( x <=15)
		{
			Lcd_ES_tsendCmd(0xD0 + x);
		}
	}
	else{
		return ES_NOT_OK;
	}
	return ES_OK;
}


/************************************************************************/

