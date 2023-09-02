/*
 * Stepper.c
 *
 *  Created on: Jul 23, 2023
 *      Author: Abdallah
 */

#include "Stepper.h"
#include "StepperCfg.h"

void Stepper_Init(void)
{
	DIO_ES_tSetPinDirection(Stepper_MOTOR_REG, S1, OUTPUT);
	DIO_ES_tSetPinDirection(Stepper_MOTOR_REG, S2, OUTPUT);
	DIO_ES_tSetPinDirection(Stepper_MOTOR_REG, S3, OUTPUT);
	DIO_ES_tSetPinDirection(Stepper_MOTOR_REG, S4, OUTPUT);
	DIO_ES_tSetPinValue(Stepper_MOTOR_REG, S1, LOW);
	DIO_ES_tSetPinValue(Stepper_MOTOR_REG, S2, LOW);
	DIO_ES_tSetPinValue(Stepper_MOTOR_REG, S3, LOW);
	DIO_ES_tSetPinValue(Stepper_MOTOR_REG, S4, LOW);
}


void Stepper_Rotate(u8 degree)
{
	u16 stepsNum = (degree * 2048UL)/360;
	u16 IterationsNum = stepsNum/4;

	u16 i=0;
	for(i=0;i<IterationsNum;i++)
	{
		DIO_ES_tSetPinValue(Stepper_MOTOR_REG, S1, HIGH);
		DIO_ES_tSetPinValue(Stepper_MOTOR_REG, S2, LOW);
		DIO_ES_tSetPinValue(Stepper_MOTOR_REG, S3, LOW);
		DIO_ES_tSetPinValue(Stepper_MOTOR_REG, S4, LOW);
		_delay_ms(20);
		DIO_ES_tSetPinValue(Stepper_MOTOR_REG, S1, LOW);
		DIO_ES_tSetPinValue(Stepper_MOTOR_REG, S2, HIGH);
		DIO_ES_tSetPinValue(Stepper_MOTOR_REG, S3, LOW);
		DIO_ES_tSetPinValue(Stepper_MOTOR_REG, S4, LOW);
		_delay_ms(20);
		DIO_ES_tSetPinValue(Stepper_MOTOR_REG, S1, LOW);
		DIO_ES_tSetPinValue(Stepper_MOTOR_REG, S2, LOW);
		DIO_ES_tSetPinValue(Stepper_MOTOR_REG, S3, HIGH);
		DIO_ES_tSetPinValue(Stepper_MOTOR_REG, S4, LOW);
		_delay_ms(20);
		DIO_ES_tSetPinValue(Stepper_MOTOR_REG, S1, LOW);
		DIO_ES_tSetPinValue(Stepper_MOTOR_REG, S2, LOW);
		DIO_ES_tSetPinValue(Stepper_MOTOR_REG, S3, LOW);
		DIO_ES_tSetPinValue(Stepper_MOTOR_REG, S4, HIGH);
		_delay_ms(20);
	}



}
