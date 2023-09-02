/*
 * Servo.c
 *
 *  Created on: Aug 3, 2023
 *      Author: Abdallah
 */


#include "Servo.h"

TIMER1_Config_t Timer1Cfg;


//Position "0" (1.5 ms pulse) is middle, "90" (~2
//ms pulse) is all the way to the left.
//ms pulse) is middle, "90" (~2 ms pulse) is all the way to the right, "
//the left.
//-90" (~1

TIMER1_Config_t Timer1Cfg = {0};


void Servo_Init(void)
{


	Timer1Cfg.mode = TIMER1_FAST_PWM_ICR1_TOP;
	Timer1Cfg.prescalar = TIMER1_PRESCALAR_64;
	Timer1Cfg.OC1A_mode = OCRA_NON_INVERTING;
	Timer1Cfg.OC1B_mode = OCRB_DISCONNECTED;
	TIMER1_Init(&Timer1Cfg);



}






// From 0 to 180
void Servo_Turn(int angle)
{
//	DIO_ES_tSetPinDirection(DIO_U8_PORT_D, DIO_U8_PIN_5, OUTPUT);

	// Calculate the pulse width based on the desired angle
	u16 pulse_width_microseconds = 1500 + ((angle / 180.0) * 1000);
	u16 pulse_width_counts = pulse_width_microseconds / 4; // Timer 1 resolution prescaler is 64
	OCR1A = pulse_width_counts - 1;
	ICR1 = 4999;			// 20 ms in data sheet of servo


	SET_BIT(TCCR1A,COM1A1);
	Servo_Init();



	// Limit the angle to the range -90 to +90 degrees
	if (angle < -90)
		angle = -90;
	else if (angle > 90)
		angle = 90;




}

void Servo_Stop()
{
	// Disable the OC1A interrupt
	TIMER1_Stop();
}


//ISR(TIMER1_CAPT_vect)
//{
//	Servo_Stop();
//}

//ISR(TIMER1_OVF_vect)
//{
//	Servo_Stop();
//}



