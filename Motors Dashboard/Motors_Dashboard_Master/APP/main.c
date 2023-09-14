/*
 * main.c
 *
 *  Created on: May 4, 2023
 *      Author: Abdallah
 */

#define F_CPU 16000000UL

#include "../HAL/Lcd/Lcd.h"
#include <util/delay.h>
#include "../HAL/KPD/KPD_interface.h"
#include <string.h>
#include "../MCAL/EXT_INTERRUPTS/EXT_INTERRUPTS.h"
#include "../MCAL/SPI/SPI.h"

volatile u16 countOverflows=0,Copy_counter;
u8 password[] = "1234";
u8 flag=0;
u8 Sign=0;

#define MAX_WAIT_CYCLES 1000 // timeout to receive ack from slave
int waitCycles = 0;


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


char input[5] = {'\0'}; // Initialize input array
u8 indexz = 0;

char inputSteper[5] = {'\0'}; // Initialize input array
u8 indexStepper = 0;

char inputServo[5] = {'\0'}; // Initialize input array
u8 indexServo = 0;

char inputSpeed[4] = {'\0'}; // Initialize input array
u8 indexSpeed = 0;

char sentSpeed[4] = {'\0'};

u8 Speed = 0;


u8 gettingMotorOption=0,gettingMovingOption=0,gettingStepperOption=0,gettingSpeedOption=0;
u8 gettingServoOption=0;

State currentState;



void Enter_IRQ_CallBack(void)
{
	currentState = STATE_MAIN_SCREEN;
}


#define DC_MOTOR_MOVE		0x03
#define SERVO_MOTOR_MOVE  	0x04
#define STEPPER_MOTOR_MOVE  0x5


#define Not_DC_Motor 	0x06
#define DC_CW 		 	0x07
#define DC_CCW 			0x08


#define ACTION_FAILED  		0x09
#define ACTION_SUCCEEDED 	0x0A

// Build a custom protocol using SPI


u8 state = ACTION_FAILED;

void SPI_Motors_Dash_Custom_Protocol(char motor, char dir, char SpeedOrAngle[])
{

	DIO_ES_tSetPinValue(SPI_REG, SS, LOW);

	// SPI sends and transmitts in hexadecimal
	SPI_Transmit(motor);
	_delay_ms(200);
	DIO_ES_tSetPinValue(SPI_REG, SS, LOW);
	SPI_Transmit(dir);


	u8 i=0;
	for(i=0;SpeedOrAngle[i]!='\0';i++)
	{
		_delay_ms(300);
		DIO_ES_tSetPinValue(SPI_REG, SS, LOW);
		SPI_Transmit(SpeedOrAngle[i]);
	}


}



int main()
{
	DIO_ES_tInit();
	Lcd_ES_tInit();
	sei();

	SPI_Config_t SPI_Cfg;

	SPI_Cfg.CLK_PHASE = SPI_CLK_PHASE_LEADING_SAMPLE;
	SPI_Cfg.CLK_Polarity = SPI_CLK_Polarity_IDLE_LOW;
	SPI_Cfg.Data_Order = SPI_DATA_ORDER_MSB;

	SPI_Cfg.Device_Mode = SPI_DEVICE_MODE_MASTER;
	SPI_Cfg.Prescalar = SPI_Prescalar_16;

	SPI_Init(&SPI_Cfg);




	u8 Value;
	char Option,Option2,Option3,Option4,Option5;
	u8 count=0;
	u8 stepperAngle=0;
	int ServoAngle=0;

	u8 flag=0;

	EXI_TriggerEdge(EX_INT2,RISING_EDGE);
	EXI_ENABLE(EX_INT2);
	EXI_Set_CallBack(EX_INT2,Enter_IRQ_CallBack);


	currentState = STATE_NULL_STATE;


	Lcd_ES_tsendString("Enter Password !");
	LCD_ES_tGoTo(1, 5);

	while(1)
	{
		switch(currentState)
		{
		case STATE_NULL_STATE:
			DIO_ES_tTOGPin(DIO_U8_PORT_D, DIO_U8_PIN_7);
			_delay_ms(500);
			break;


		case STATE_MAIN_SCREEN:
			KPD_ES_tGetKeyPressed(&Value);
			if(Value != KPD_U8_NOT_PRESSED){

				Lcd_ES_tsendChar('*');
				input[indexz] = Value; // Store input in array
				indexz++;
				if (indexz >= 4) { // Check if password entered
					if (strcmp(input, password) == 0) {
						// Password is correct, perform action
						lcd_ES_tclear();
						Lcd_ES_tsendString("Welcome to Motor");
						LCD_ES_tGoTo(1, 0);
						Lcd_ES_tsendString("Dash board");
						_delay_ms(2000);
						currentState = STATE_MOTOR_OPTIONS;
					}
					else {
						// Password is incorrect, reset input
						lcd_ES_tclear();
						Lcd_ES_tsendString("Wrong Password");
						memset(input, '\0', sizeof(input));
						indexz = 0;
						_delay_ms(1500);
						count++;
						lcd_ES_tclear();
						Lcd_ES_tsendString("Try again");
						LCD_ES_tGoTo(1, 5);
						if(count == 3){
							lcd_ES_tclear();
							Lcd_ES_tsendString("Blocked !!!");
							count=0;
						}

					}
				}
			}


			break;


		case STATE_MOTOR_OPTIONS:
			if (!gettingMotorOption) {
				lcd_ES_tclear();
				Lcd_ES_tsendString("1- DC Motor");
				LCD_ES_tGoTo(1, 0);
				Lcd_ES_tsendString("2- Stepper");
				LCD_ES_tGoTo(2, 0);
				Lcd_ES_tsendString("3- Servo Motor");
				gettingMotorOption = 1;
			}

			KPD_ES_tGetKeyPressed(&Option);
			if (Option != KPD_U8_NOT_PRESSED) {
				if (Option == '1') {  // DC Motor
					gettingMotorOption = 0;
					currentState = STATE_DC_MOTOR_MOVE;
				} else if (Option == '2') {  // Stepper Motor
					currentState = STATE_STEPPER_MOVE;
				}else if (Option == '3') {  // Stepper Motor
					currentState = STATE_SERVO_MOVE;
				}else {
					lcd_ES_tclear();
					Lcd_ES_tsendString("Invalid Option");
					_delay_ms(2000);
					gettingMotorOption=0;
					currentState = STATE_MOTOR_OPTIONS;
				}
			}
			break;

		case STATE_DC_MOTOR_MOVE:
			if(!flag)
			{
				if(!gettingSpeedOption){
					lcd_ES_tclear();
					Lcd_ES_tsendString("Speed(0-99): ");
					gettingSpeedOption = 1;
				}
				KPD_ES_tGetKeyPressed(&Option5);
				if(Option5 != KPD_U8_NOT_PRESSED){
					LCD_ES_tGoTo(1, indexSpeed);
					Lcd_ES_tsendChar(Option5);
					inputSpeed[indexSpeed] = Option5 - '0';
					sentSpeed[indexSpeed] = inputSpeed[indexSpeed];
					indexSpeed++;
					if(indexSpeed>=2)
					{
						sentSpeed[indexSpeed] = '\0';
						_delay_ms(2000);
						Speed = (inputSpeed[0] * 10) + inputSpeed[1];
						memset(inputSpeed, '\0', sizeof(inputSteper));
						indexSpeed = 0;
						gettingSpeedOption = 0;
						flag = 1;
					}
				}
			}else
			{


				if (!gettingMovingOption) {
					lcd_ES_tclear();
					Lcd_ES_tsendString("1- Rotate CW");
					LCD_ES_tGoTo(1, 0);
					Lcd_ES_tsendString("2- Rotate CCW");
					Lcd_ES_tsendString(sentSpeed);
					gettingMovingOption = 1;
				}
				KPD_ES_tGetKeyPressed(&Option2);
				if (Option2 != KPD_U8_NOT_PRESSED) {
					if (Option2 == '1') {
						//SPI_Motors_Dash_Custom_Protocol(DC_MOTOR_MOVE, DC_CW, sentSpeed);
						_delay_ms(200);
						SPI_Motors_Dash_Custom_Protocol(DC_MOTOR_MOVE, DC_CW, sentSpeed);
//						while (state != ACTION_SUCCEEDED && waitCycles < MAX_WAIT_CYCLES) {
//							state = SPI_Receive();
//							_delay_ms(1); // Add a small delay to reduce CPU load
//							waitCycles++;
//						}
						_delay_ms(5000);
						waitCycles=0;
						gettingMovingOption = 0;
						gettingMotorOption=0;
						flag = 0; // Reset the flag after direction selection
						currentState = STATE_MOTOR_OPTIONS;
					} else if (Option2 == '2') {
						//SPI_Motors_Dash_Custom_Protocol(DC_MOTOR_MOVE, DC_CCW, sentSpeed);
						_delay_ms(200);
						SPI_Motors_Dash_Custom_Protocol(DC_MOTOR_MOVE, DC_CCW, sentSpeed);
//						while (state != ACTION_SUCCEEDED && waitCycles < MAX_WAIT_CYCLES) {
//							state = SPI_Receive();
//							_delay_ms(1); // Add a small delay to reduce CPU load
//							waitCycles++;
//						}
						_delay_ms(5000);
						gettingMovingOption = 0;
						gettingMotorOption=0;
						waitCycles=0;
						flag = 0; // Reset the flag after direction selection
						currentState = STATE_MOTOR_OPTIONS;
					} else {
						lcd_ES_tclear();
						Lcd_ES_tsendString("Invalid Option");
						_delay_ms(2000);
						flag = 0; // Reset the flag after direction selection
						currentState = STATE_DC_MOTOR_MOVE;
					}
				}
			}
			break;



		case STATE_STEPPER_MOVE:
			if (!gettingStepperOption) {
				lcd_ES_tclear();
				Lcd_ES_tsendString("Angle(3dig) :");
				gettingStepperOption = 1;
			}
			KPD_ES_tGetKeyPressed(&Option3);
			if (Option3 != KPD_U8_NOT_PRESSED) {
				LCD_ES_tGoTo(1, indexStepper);
				Lcd_ES_tsendChar(Option3);
				inputSteper[indexStepper] = Option3 - '0'; // Convert character to integer
				indexStepper++;
				if (indexStepper >= 3) { // Use indexStepper instead of indexz
					stepperAngle = (inputSteper[0] * 100) + (inputSteper[1] * 10) + inputSteper[2];
					_delay_ms(200);
					SPI_Motors_Dash_Custom_Protocol(STEPPER_MOTOR_MOVE, Not_DC_Motor, inputSteper);
//					while (state != ACTION_SUCCEEDED && waitCycles < MAX_WAIT_CYCLES) {
//						state = SPI_Receive();
//						_delay_ms(1); // Add a small delay to reduce CPU load
//						waitCycles++;
//					}
//					waitCycles=0;
					_delay_ms(5000);
					memset(inputSteper, '\0', sizeof(inputSteper));
					indexStepper = 0;
					gettingStepperOption = 0;
					gettingMotorOption=0;
					currentState = STATE_MOTOR_OPTIONS;
				}
			}
			break;


		case STATE_SERVO_MOVE:
			if (!gettingServoOption) {
				lcd_ES_tclear();
				Lcd_ES_tsendString("Signed angle :");
				gettingServoOption = 1;
			}
			KPD_ES_tGetKeyPressed(&Option4);
			if (Option4 != KPD_U8_NOT_PRESSED) {
				LCD_ES_tGoTo(1, indexServo);
				Lcd_ES_tsendChar(Option4);
				if(indexServo == 0)
					Sign = Option4;
				inputServo[indexServo] = Option4 - '0'; // Convert character to integer
				indexServo++;
				if (indexServo >= 3) { // Use indexStepper instead of indexz
					if(Sign == '+'){
						ServoAngle = +((inputServo[1] * 10) + inputServo[2]);
					}else{
						ServoAngle = -((inputServo[1] * 10) + inputServo[2]);
					}
					_delay_ms(200);
					SPI_Motors_Dash_Custom_Protocol(SERVO_MOTOR_MOVE, Not_DC_Motor, inputServo);
//					while (state != ACTION_SUCCEEDED && waitCycles < MAX_WAIT_CYCLES) {
//						state = SPI_Receive();
//						_delay_ms(1); // Add a small delay to reduce CPU load
//						waitCycles++;
//					}
//					waitCycles=0;
					_delay_ms(5000);
					memset(inputServo, '\0', sizeof(inputServo));
					indexServo = 0;
					gettingServoOption = 0;
					gettingMotorOption=0;
					currentState = STATE_MOTOR_OPTIONS;
				}
			}
			break;



		case STATE_EXIT:
			lcd_ES_tclear();
			Lcd_ES_tsendString("Exit System :)");
			_delay_ms(1000);
			return 0;
		}
	}

	return 0;
}
