/*
 * DC_Motor.h
 *
 *  Created on: Jul 23, 2023
 *      Author: Abdallah
 */

#ifndef HAL_DC_MOTOR_DC_MOTOR_H_
#define HAL_DC_MOTOR_DC_MOTOR_H_


// Includes
#include "../../MCAL/Dio/Dio_interface.h"
#include "../../MCAL/Registers.h"
#include "../../MCAL/TIMER/Timer.h"
#include "util/delay.h"

typedef enum{
	DC_MOTOR_CW,
	DC_MOTOR_CCW
}DC_MOTOR_Cfg;

typedef enum{
	DC_MOTOR_0,
	DC_MOTOR_1
}DC_MOTOR_Index;


// APIS supported by DC Motor driver
ES_t DC_Motor_Init(DC_MOTOR_Index Motor);

ES_t DC_Motor_Move(DC_MOTOR_Index Motor,DC_MOTOR_Cfg MotorCfg);
ES_t DC_Motor_Stop(DC_MOTOR_Index Motor);

ES_t DC_Motor_SetSpeed(DC_MOTOR_Index Motor, u8 Speed);


#endif /* HAL_DC_MOTOR_DC_MOTOR_H_ */
