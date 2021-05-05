/*
* prosjekt_mirco.c
*
* Created: 22.04.2021 16:29:27
* Author : nixxo

*/

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdbool.h>
#include "sensorlogic.h"



int main(void) {
	
	uint8_t position = 90;
	uint16_t potMeter;
	uint16_t lightSensor1;
	uint16_t lightSensor2;
	
	ADC_Init();
	Timer1_PWM_init();
		
	do{
	
		//potMeter = ADC_Conversion(0);
		// print potMeter to UART
 		lightSensor1 = ADC_Conversion(1);
// 		lightSensor2 = ADC_Conversion(2);
		position = lightSensor1>>3;//correctPosition(potMeter, lightSensor1, lightSensor2, position);
		// print
		if (validatePosition(position) == true){
			moveServo(position);
		} else {
			//return;
		}
		
		//_delay_ms(1000);
		
		/*
		moveServo(1);
		_delay_ms(30000);
		moveServo(179);
		_delay_ms(30000);
		*/
		
		//interrupts

	} while(1);
}

