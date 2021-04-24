/*
* prosjekt_mirco.c
*
* Created: 22.04.2021 16:29:27
* Author : nixxo

*/

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int pos = 90;   // initial position
int tolerance = 2;


int main(void) {
	
	DDRC = 0b00000000; // setter A0-A8 til input
	DDRB = (1<<PORTB1); // setter pin9 til output

	while(1){
		
	}

	return (0); /* This line is never reached */
}
