#include "APP_Includes.h"


int main(void){
	DIO_voidInit();
	ADC_void_Init();
	LCD_init();
	UART_Init();
	EXTI_voidEnable_GIE();
	/* Global Variables */
	u16 digitalValue;
	u8 UART_Value;
	/* Ohmmeter Variables */
	u16 Vin = 5.0;
	f64 Vout = 0, R1 = 3300.0, R2 = 0;
	u8 OhmDisplayed = 0;

	/* Voltameter Variables */
	f32 voltValue, temp;
	u8 VoltDisplayed = 0;


	/* Ameter Variables */
	u16 currentADC = 0;
	f64 milliVolts = 0;
	u8 sensitivity = 66;
	f64 currentReading = 0;
	u8 ameterDisplayed = 0;

	/* Frequency Variables */
	u32 freq;
	u8 duty;

	// Settings for NodeMCU
	UART_SendString("O:Ohmeter ");
	UART_SendString("V:Voltmeter ");
	UART_SendString("A:Ameter ");
	UART_SendString("F:Frequency meter ");
	UART_SendString("Enter Your Option : ");


	LCD_GoToXY(0, 0);
	LCD_displayString("O:Ohm V:Volt");
	LCD_GoToXY(1, 0);
	LCD_displayString("A:Amp F:Freq");

	while(1){
		UART_u8Recieve1ByteData(&UART_Value);

		if(UART_Value == 'O'){
			ADC_u8_Get_Digital_ValueSynchNonBlocking(0, &digitalValue);
			f32 buffer = digitalValue * Vin;
			Vout = buffer / 1024.0;
			buffer = Vout / (Vin - Vout);
			R2 = R1 * buffer;
			LCD_ClearScreen();
			LCD_GoToXY(0, 0);
			LCD_displayString("Ohmmeter.....");
			LCD_GoToXY(1, 0);
			LCD_DisplayInteger(R2);
			if(!OhmDisplayed){
				UART_DisplayNumber(R2);
				UART_SendString("Ohm ");
				OhmDisplayed = 1;
			}
			else{
				OhmDisplayed = 0;
			}
		}

		else if(UART_Value == 'V'){
			ADC_u8_Get_Digital_ValueSynchNonBlocking(1, &digitalValue);
			temp = (digitalValue * 5.0) / 1023;
			voltValue = temp / (10000.0/(10000.0+90900.0));
			LCD_ClearScreen();
			LCD_GoToXY(0, 0);
			LCD_displayString("Voltmeter.....");
			LCD_GoToXY(1, 0);
			if(voltValue > 0){
				displayFloatOnLCD(voltValue);
				LCD_displayCharacter('V');


				if(!VoltDisplayed){
					UART_displayFloat(voltValue);
					UART_SendString("Volt ");
					VoltDisplayed = 1;
				}
				else{
					VoltDisplayed = 0;
				}

			}
			else{
				LCD_DisplayInteger((u16)(voltValue*1000));
				LCD_displayString("mV");

				if(!VoltDisplayed){
					UART_displayFloat((u16)(voltValue*1000));
					UART_SendString("mV ");
					VoltDisplayed = 1;
				}
				else{
					VoltDisplayed = 0;
				}

			}
		}

		else if(UART_Value == 'A'){
			ADC_u8_Get_Digital_ValueSynchNonBlocking(7, &currentADC);
			milliVolts = (currentADC / 1024.0) * 5000.0;
			currentReading = (milliVolts - 2500)/sensitivity;
			LCD_ClearScreen();
			LCD_GoToXY(0, 0);
			LCD_displayString("Ameter.....");
			LCD_GoToXY(1, 0);
			displayFloatOnLCD(currentReading);

			if(!ameterDisplayed){
				UART_displayFloat(currentReading);
				UART_SendString("Amps ");
				ameterDisplayed = 1;
			}
			else{
				ameterDisplayed = 0;
			}
		}

		else if(UART_Value == 'F'){
			ICU_PWM_Measure(&freq,&duty);
			LCD_ClearScreen();
			LCD_GoToXY(0, 0);
			LCD_displayString("Freq: ");
			UART_Send1ByteData(UART_NewLine);
			if(freq < 1000)
			{
				LCD_DisplayInteger(freq);
				LCD_displayString("Hz");
				UART_DisplayNumber(freq);
				UART_SendString("Hz ");
			}else if(freq > 1000 && freq < 1000000)
			{
				LCD_DisplayInteger(freq/1000);
				LCD_displayString("KHz");
				UART_DisplayNumber(freq/1000);
				UART_SendString("KHz ");

			}else{
				LCD_DisplayInteger(freq/1000000);
				LCD_displayString("MHz");
				UART_DisplayNumber(freq/1000000);
				UART_SendString("MHz ");
			}

			LCD_GoToXY(1, 0);
			LCD_displayString("Duty: ");
			LCD_DisplayInteger(duty);
			LCD_displayCharacter('%');
			UART_Send1ByteData(' ');
		}


	}
	return 0;
}
