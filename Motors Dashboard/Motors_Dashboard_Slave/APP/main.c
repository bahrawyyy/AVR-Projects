/*
 * main.c
 *
 *  Created on: May 4, 2023
 *      Author: Abdallah
 */

#define F_CPU 16000000UL

#include <util/delay.h>
#include "../HAL/KPD/KPD_interface.h"
#include <string.h>
#include "../HAL/DC_Motor/DC_Motor.h"
#include "../HAL/Stepper_Motor/Stepper.h"
#include "../MCAL/EXT_INTERRUPTS/EXT_INTERRUPTS.h"
#include "../HAL/Servo_Motor/Servo.h"
#include "../MCAL/SPI/SPI.h"

volatile u16 countOverflows=0,Copy_counter;
u8 password[] = "1234";
u8 flag=0;
u8 Sign=0;

#define NULL ((void *)0)



#define DC_MOTOR_MOVE		0x03
#define SERVO_MOTOR_MOVE  	0x04
#define STEPPER_MOTOR_MOVE  0x5


#define Not_DC_Motor 	0x06
#define DC_CW 		 	0x07
#define DC_CCW 			0x08


#define ACTION_FAILED  		0x09
#define ACTION_SUCCEEDED 	0x0A

// Build a custom protocol using SPI





// Taking input from user --> Master
// Send instructions to --> slave to control motors


// Define states for the system
typedef enum {
	STATE_NULL_STATE,
	STATE_MAIN_SCREEN,
	STATE_MOTOR_OPTIONS,
	STATE_DC_MOTOR_MOVE,
	STATE_STEPPER_MOVE,
	STATE_SERVO_MOVE,
	STATE_EXIT
} State;



u8 Speed = 0;


u8 gettingMotorOption=0,gettingMovingOption=0,gettingStepperOption=0,gettingSpeedOption=0;
u8 gettingServoOption=0;

State currentState;

// Which_Motor_Move *motor, DC_Motor_Dir *dir, u8 SpeedOrAngle[]


char motor=0,dir=0;
char SpeedOrAngle[4] = {'\0'};

//char SpeedOrAnglee[4];

void SPI_Motors_Dash_Custom_Protocol(char *motor, char *dir, char SpeedOrAngle[])
{

	_delay_ms(1000);


	*motor = SPI_Receive();
	_delay_ms(200);
	*dir = SPI_Receive();
	_delay_ms(200);
	SpeedOrAngle[0] = SPI_Receive();
	_delay_ms(200);
	SpeedOrAngle[1] = SPI_Receive();
	_delay_ms(200);
	if(*motor == DC_MOTOR_MOVE)
		SpeedOrAngle[2] = '\0';
	else
		SpeedOrAngle[2] = SPI_Receive();
	SpeedOrAngle[3] = '\0';


	switch(*motor){
	case DC_MOTOR_MOVE:
		currentState = STATE_DC_MOTOR_MOVE;
		break;
	case SERVO_MOTOR_MOVE:
		currentState = STATE_SERVO_MOVE;
		break;
	case STEPPER_MOTOR_MOVE:
		currentState = STATE_STEPPER_MOVE;
		break;
	}


}

int main()
{
	DIO_ES_tInit();


	Stepper_Init();
	sei();


	SPI_Config_t SPI_Cfg;

	SPI_Cfg.CLK_PHASE = SPI_CLK_PHASE_LEADING_SAMPLE;
	SPI_Cfg.CLK_Polarity = SPI_CLK_Polarity_IDLE_LOW;
	SPI_Cfg.Data_Order = SPI_DATA_ORDER_MSB;

	SPI_Cfg.Device_Mode = SPI_DEVICE_MODE_SLAVE;
	SPI_Cfg.IRQ_Mode = SPI_IRQ_Disable;
	SPI_Cfg.SPI_P_to_Func = NULL;



	SPI_Init(&SPI_Cfg);


	DC_Motor_Init(DC_MOTOR_0);


	u8 stepperAngle=0;
	int ServoAngle=0;




	currentState = STATE_NULL_STATE;


	while(1)
	{
		while((motor == 0) && (dir == 0)){
			SPI_Motors_Dash_Custom_Protocol(&motor,&dir, SpeedOrAngle);
		}


		switch(currentState)
		{
		case STATE_DC_MOTOR_MOVE:
			Speed = (SpeedOrAngle[0] * 10) + SpeedOrAngle[1];
			if (dir == DC_CW) {
				DC_Motor_SetSpeed(DC_MOTOR_0,Speed);
				DC_Motor_Move(DC_MOTOR_0, DC_MOTOR_CW);
				_delay_ms(3000);
				DC_Motor_Stop(DC_MOTOR_0);
				TIMER0_Stop();
				DIO_ES_tSetPinValue(SPI_REG, SS, LOW);
				//SPI_Transmit(ACTION_SUCCEEDED);
				motor = 0;
				dir=0;
				currentState = STATE_MOTOR_OPTIONS;
			} else if (dir == DC_CCW) {
				DC_Motor_SetSpeed(DC_MOTOR_0,Speed);
				DC_Motor_Move(DC_MOTOR_0, DC_MOTOR_CCW);
				_delay_ms(3000);
				DC_Motor_Stop(DC_MOTOR_0);
				TIMER0_Stop();
				DIO_ES_tSetPinValue(SPI_REG, SS, LOW);
				//SPI_Transmit(ACTION_SUCCEEDED);
				motor = 0;
				dir=0;
				currentState = STATE_MOTOR_OPTIONS;
			}
			break;



		case STATE_STEPPER_MOVE:
			stepperAngle = (SpeedOrAngle[0] * 100) + (SpeedOrAngle[1] * 10) + SpeedOrAngle[2];
			Stepper_Rotate(stepperAngle);
			DIO_ES_tSetPinValue(SPI_REG, SS, LOW);
			//SPI_Transmit(ACTION_SUCCEEDED);
			motor = 0;
			dir=0;
			currentState = STATE_MOTOR_OPTIONS;
			break;


		case STATE_SERVO_MOVE:
			Sign = SpeedOrAngle[0];
			if(Sign == '+'){
				ServoAngle = +((SpeedOrAngle[1] * 10) + SpeedOrAngle[2]);
			}else{
				ServoAngle = -((SpeedOrAngle[1] * 10) + SpeedOrAngle[2]);
			}
			Servo_Turn(ServoAngle);
			_delay_ms(1000);
			Servo_Stop();
			DIO_ES_tSetPinValue(SPI_REG, SS, LOW);
			//SPI_Transmit(ACTION_SUCCEEDED);
			motor = 0;
			dir=0;
			currentState = STATE_MOTOR_OPTIONS;
			break;



		case STATE_EXIT:
			_delay_ms(1000);
			return 0;
		}
	}

	return 0;
}
