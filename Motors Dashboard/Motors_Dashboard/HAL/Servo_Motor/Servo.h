/*
 * Servo.h
 *
 *  Created on: Aug 3, 2023
 *      Author: Abdallah
 */

#ifndef HAL_SERVO_MOTOR_SERVO_H_
#define HAL_SERVO_MOTOR_SERVO_H_

#include "../../MCAL/TIMER/Timer.h"
#include "../../MCAL/Dio/Dio_interface.h"
#include "util/delay.h"
#include "../../MCAL/Registers.h"

#define F_CPU 16000000UL

#define MIN_PULSE_WIDTH 1000   // Minimum pulse width in microseconds
#define MAX_PULSE_WIDTH 2000   // Maximum pulse width in microseconds

void Servo_Init(void);
void Servo_Turn(int angle);
void Servo_Stop();


#endif /* HAL_SERVO_MOTOR_SERVO_H_ */
