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
#include "usart.h"

#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)


uint8_t position = 90;
uint16_t potMeter;
uint16_t lightSensor1;
uint16_t lightSensor2;







void readPin(int pin){
	printWord(pin);
	printString("\r\n");
}

ISR(INT0_vect) {
	if (bit_is_clear(PIND, PD2)) {
		printString("Poteniometer value: ");
		readPin(potMeter);
		printString("Lightsensor 1 value: ");
		readPin(lightSensor1);
		printString("Lightsensor 2 value: ");
		readPin(lightSensor2);
		printString("Position: ");
		readPin(position);
		//_delay_ms(1000);
	}
	else{
		
	}
}

void initInterrupt0(void) {
	PORTD |= (1 << PD2);    // pull up
	EIMSK |= (1 << INT0);                                 /* enable INT0 */
	EICRA |= (1 << ISC00);                /* trigger when button changes */
	sei();                          /* set (global) interrupt enable bit */
}

int main(void) {
	
	UBRR0 = BAUD_PRESCALE;
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	
	// ------- Inits -------- //
	initUSART();
	ADC_Init();
	Timer1_PWM_init();
	initInterrupt0();

	 
	 
	
	
	// ------- Handler -------- //
	do{
		
		lightSensor1 = ADC_Conversion(0);
		lightSensor2 = ADC_Conversion(1);
		potMeter = ADC_Conversion(2);

		position = correctPosition(potMeter, lightSensor1, lightSensor2, position);
		
		if (validatePosition(position) && validateTolerance(lightSensor1, lightSensor2)){
			moveServo(position);
		}
		else if (position > 180){
			position = 180;
		}
		else if (position < 5){
			position = 1;
		}
	} while(1);
}

