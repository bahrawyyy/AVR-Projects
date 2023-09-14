/*
 * Stepper.h
 *
 *  Created on: Jul 23, 2023
 *      Author: Abdallah
 */

#ifndef HAL_STEPPER_MOTOR_STEPPER_H_
#define HAL_STEPPER_MOTOR_STEPPER_H_

#include "../../MCAL/Dio/Dio_interface.h"
#include "util/delay.h"

#define F_CPU 16000000UL


void Stepper_Init(void);
void Stepper_Rotate(u8 degree);

#endif /* HAL_STEPPER_MOTOR_STEPPER_H_ */
