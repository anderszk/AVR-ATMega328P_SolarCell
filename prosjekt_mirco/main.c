/*
 * prosjekt_mirco.c
 *
 * Created: 22.04.2021 16:29:27
 * Author : nixxo

 */ 


// ------- Preamble -------- //


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "sensorlogic.h"
#include "servo.h"

int position = 90;

int potMeter;
int lightSensor1;
int lightSensor2;


int main(void) {
	
	
	
	
	
	do{
		
		potMeter = ADC_Init(1);
		lightSensor1 = ADC_Init(2);
		lightSensor2 = ADC_Init(3);

		position = correctPosition(potMeter, lightSensor1, lightSensor2);
		validatePosition(position);

		moveServo(position);

		

		//interrupts
	} while(1);
		
}

