/*
 * prosjekt_mirco.c
 *
 * Created: 22.04.2021 16:29:27
 * Author : nixxo
 
 
 test wwwooooowwww
 */ 




/* Quick interactive demo running servo with Tohmer 1 */

// ------- Preamble -------- //
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define PULSE_MIN 1000 /* experiment with these values */
#define PULSE_MAX 2000 /* to match your own servo */
#define PULSE_MID 1500


static inline void initADC0(void) {
	ADMUX |= (1 << REFS0); //reference voltage on AVCC
	ADCSRA |= (1 << ADPS1) | (1 << ADPS0); //ADC clock prescaler /8
	ADCSRA |= (1 << ADEN); //enables the ADC
}


static inline void initTimer1Servo(void) {
	/* Set up Timer1 (16bit) to give a pulse every 20ms */
	/* Use Fast PWM mode, counter max in ICR1 */
	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM12) | (1 << WGM13);
	TCCR1B |= (1 << CS10); /* /1 prescaling -- counting in microseconds */
	ICR1 = 20000; /* TOP value = 20ms */
	DDRB |= (1 << PORTB1); /* set pin for output */
	TCCR1A |= (1 << COM1A1); /* Direct output on PB1 / OC1A */
}


int main(void) {
	
	// -------- Inits --------- //
	
	// adc:
	uint16_t potentiometerValue;
	initADC0();

	//servo:
	OCR1A = PULSE_MID; /* set it to middle position initially */
	_delay_ms(500);
	initTimer1Servo();
	
	
	// ------ Event loop ------ //
	
	while (1) {
		
}
