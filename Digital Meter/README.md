# Digital Meter
This Digital Meter Project is a versatile and customizable solution for measuring voltage, current, resistance, and frequency. It is designed to display the measurement results on an LCD screen and transmit the data wirelessly to a terminal using the ESP8266 Wi-Fi module. 
## Setup
- Voltage Measurement:  
Connect the voltage source you want to measure to the voltage divider on an analog pin.  
The purpose of this voltage divider to measure a higher range of voltage
- Current Measurement:
Connect the current sensor module to another analog input of the microcontroller.
Connect the current source to the sensor.
- Resistance Measurement:
Connect voltage divider to an analog pin with a known resistance (here 3.3kohm) and the unkown resistance that you want to measure.
- Frequency Measurement:
Connect the signal source whose frequency you want to measure to the ICU input pin (ICP1 on PORTD6).
- ESP8266 Module:
Connect the ESP8266 module to the microcontroller using UART (TX and RX pins).
Connect VCC and GND to the appropriate voltage levels.
## Usage
- Display on LCD:  
The LCD display will show the measured values of voltage, current, resistance, and frequency. Simply power on the circuit to see these values displayed.
- Wireless Terminal Communication:  
Ensure that your wireless terminal (e.g., a computer or smartphone) is connected to the same Wi-Fi network build by the ESP8266 module.  
Open a terminal program (e.g., PuTTY, Arduino Serial Monitor, or a custom application) on your wireless terminal.  
Connect to the ESP8266's IP address and port (specified in Arduino sketch).  
You should now see the measured values being transmitted wirelessly to your terminal in real-time.
