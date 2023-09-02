/*
 * KPD_program.c
 *
 *  Created on: May 4, 2023
 *      Author: Abdallah
 */

#include "../../LIB/Bit_Math.h"
#include "../../LIB/STD_Types.h"
#include "../../LIB/ErrorState.h"

#include "../../MCAL/Dio/Dio_interface.h"

#include "KPD_interface.h"
#include "KPD_private.h"
#include "KPD_config.h"

#define F_CPU 16000000UL
#include <util/delay.h>

#define NULL ((void *)0)


/* Steps of driver */

/** COLS and ROWS can be reversed
 *  1- SET COLS to be input and activate pull up to avoid floating
 	2- SET ROWS to be output and initially high
 	3- Activate a specific ROW and read the 4 COLS
 */

/* Activation steps */
/* DIO_ES_tSetPinValue(DIO_U8_PORT_B, DIO_U8_PIN_7, LOW);
 * if conditions to read the four columns
 * if all are high then activate the next row by
 * changing the pin only
 * Don't forget to activate only a row at a time
 * to avoid multiple options for switches and get confused
 *
 *
 */

/**
 * ROWS PB4 --> PB7 OUTPUT
 * COLS PD2 --> PD5 INPUT
 */

#define ROWS_NUM 4
#define COLS_NUM 4
#define INIT 0

const u8 KPD_Au8Keys[ROWS_NUM][COLS_NUM] = KPD_KEYS;

// To avoid the unarrangement and uncontiguous
const u8 KPD_Au8RowsPins[4] = {KPD_U8_R1,KPD_U8_R2,KPD_U8_R3,KPD_U8_R4};
const u8 KPD_Au8ColsPins[4] = {KPD_U8_C1,KPD_U8_C2,KPD_U8_C3,KPD_U8_C4};

ES_t KPD_ES_tGetKeyPressed(u8 *copy_pu8ReturnedKey)
{
	*copy_pu8ReturnedKey = KPD_U8_NOT_PRESSED;
	u8 Local_u8RowsCounter,Local_u8ColsCounter,Local_u8PinVal,Local_u8Flag = LOW;
	if(copy_pu8ReturnedKey != NULL)
	{
		/* Activation of each row "for loop" */
		for(Local_u8RowsCounter=INIT;Local_u8RowsCounter<ROWS_NUM;Local_u8RowsCounter++)
		{
			// Activate row
			DIO_ES_tSetPinValue(KPD_U8_PORTROWS,KPD_Au8RowsPins[Local_u8RowsCounter],LOW);
			// Check which input pin has zero "pressed"
			// by reading 4 pins input "columns"
			for(Local_u8ColsCounter=INIT;Local_u8ColsCounter<COLS_NUM;Local_u8ColsCounter++)
			{
				DIO_ES_tGetPinValue(KPD_U8_PORTCOLS,KPD_Au8ColsPins[Local_u8ColsCounter],&Local_u8PinVal);
				if(Local_u8PinVal == LOW){ /* Switch is pressed */
					/* The switch which reaches between the activated
					 * Column and the pressed key */
					_delay_ms(20);   // Debouncing
					// Check if the pin is still low "problem of multiple display"
					DIO_ES_tGetPinValue(KPD_U8_PORTCOLS,KPD_Au8ColsPins[Local_u8ColsCounter],&Local_u8PinVal);  // Update the PinVal
					// will not get out of the while until he raised his hand "Value = HIGH"
					// You want to let stuck the code here until the value equals high
					while(Local_u8PinVal == LOW){
						// Continues reading until the value equals high
						DIO_ES_tGetPinValue(KPD_U8_PORTCOLS,KPD_Au8ColsPins[Local_u8ColsCounter],&Local_u8PinVal);  // Update the PinVal
					}
					*copy_pu8ReturnedKey = KPD_Au8Keys[Local_u8RowsCounter][Local_u8ColsCounter];
					Local_u8Flag = HIGH;
					break;
				}
			}
			// Deactivate ROW
			DIO_ES_tSetPinValue(KPD_U8_PORTROWS,KPD_Au8RowsPins[Local_u8RowsCounter],HIGH);
			if(Local_u8Flag == HIGH)
				break;
		}


	}else{
		return ES_NOT_OK;
	}
	return ES_OK;
}
