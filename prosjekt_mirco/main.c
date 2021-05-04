/*
 * prosjekt_mirco.c
 *
 * Created: 22.04.2021 16:29:27
 * Author : nixxo

 */ 


// ------- Preamble -------- //
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "sensorlogic.h"
#include "servo.h"

int position = 90;
int potMeter = ADC1;
int lightSensor1 = ADC2;
int lightSensor2 = ADC3;


int main(void) {
	
	// -------- Inits --------- //
	potmeter_init();
	ightsensors_init();
	Timer_PVM_init();
	
	
	// ------ Event loop ------ //
	
	do{

		position = correctPosition(potMeter, lightSensor1, lightSensor2);
		validatePosition(position);

		moveServo(position);

		writeISP(position);

		//interrupts
	} while(1);
		
}


ADMUX = (1 << REFS0 | )