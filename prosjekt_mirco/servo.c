#include "servo.h"
#include <avr/interrupt.h>
#include <util/delay.h>

#define F_CPU 16000000UL // 16MHz system clock
#define T1_PRESCALE 8 // Timer 1 clock prescaler

#define SERVO_PERIOD F_CPU/1000000*20000/T1_PRESCALE
#define SERVO_MAX F_CPU/1000000*2000/T1_PRESCALE
#define SERVO_MIN F_CPU/1000000*460/T1_PRESCALE

#define positionMax 180

//Timer initialization


void Timer1_PWM_init(int time){
	
	; // Set ODDRB = (1<<DDB1)C1A/PB1 as output. (pin 9)

	/* Fast PWM non-inverting mode. Clear OC1A on Compare Match, set at TOP=ICR1.

	Pre-scale 16Mhz by 8 -> 2MHz = 0.5us/tick */

	TCCR1A = (1<<COM1A1)|(0<<COM1A0)|(1<<WGM11)|(0<<WGM10);

	TCCR1B = (1<<CS11)|(1<<WGM13)|(1<<WGM12)

	ICR1 = SERVO_PERIOD; // Servo period = 20ms (50Hz)
}



//ADC 
int ADC_Conversion(uint8_t pin){  //conveurtion

	if (pin == 0){
		ADMUX = (1<<REFS0)|(0<<ADLAR); // ADC0 single ended input and result right adjusted.
	}
	else if(pin == 1){
		ADMUX = (1<<REFS0)|(0<<ADLAR)|(1 << MUX0);  // ADC1
	}
	else if (pin == 2)
	{
		ADMUX = (1<<REFS0)|(0<<ADLAR)|(1 << MUX1);  // ADC2
	}
	
	// vent p� start-convertion (vent s� lenge bittet er 1)
	do {} while (ADCSRA & (1<<ADSC)); // ADCSRA & 0b0100 0000

	return ADC;
}

void ADC_Init(void){
	
	DIDR0 |= (1<<ADC0D); // digital input buffer disable, saves power.
	ADCSRA = (1<<ADEN)|(7<<ADPS0)|(1<<ADSC);
}

//kj�rer servoen
void moveServo(int position){
	OCR1A = ((((position)*(SERVO_MAX - SERVO_MIN))/positionMax) + SERVO_MIN);
}

