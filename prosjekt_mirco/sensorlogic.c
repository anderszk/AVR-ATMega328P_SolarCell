// justerer servo basert på sensor og potensometer
#include "sensorlogic.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdbool.h>

//#define F_CPU 16000000UL // 16MHz system clock
#define T1_PRESCALE 8 // Timer 1 clock prescaler
#define SERVO_PERIOD F_CPU/1000000*20000/T1_PRESCALE
#define SERVO_MAX F_CPU/1000000*2500/T1_PRESCALE
#define SERVO_MIN F_CPU/1000000*490/T1_PRESCALE
#define POSITION_MAX 180

//Timer initialization
void Timer1_PWM_init(){
	
	DDRB = (1<<DDB1); // Setter PB1 som output. (pin 9)

	TCCR1A = (1<<COM1A1)|(0<<COM1A0)|(1<<WGM11)|(0<<WGM10);

	TCCR1B = (1<<CS11)|(1<<WGM13)|(1<<WGM12);

	ICR1 = SERVO_PERIOD; // Periodetid på 20ms (50Hz)
}


//ADC
int ADC_Conversion(int8_t pin){

	if (pin == 0){
		ADMUX = (1<<REFS0)|(0<<ADLAR); // ADC0
	}
	else if(pin == 1){
		ADMUX = (1<<REFS0)|(0<<ADLAR)|(1 << MUX0); // ADC1
	}
	else if (pin == 2){
		ADMUX = (1<<REFS0)|(0<<ADLAR)|(1 << MUX1); // ADC2  potensiometer
	}
	else {
		return 0;
		//Flag
	}
	
	ADCSRA |= (1<<ADSC);
	
	// vent på start-convertion (vent så lenge bittet e
	do {} while (ADCSRA & (1<<ADSC)); // ADCSRA & 0b0100 0000
	return ADC;
}

void ADC_Init(void){
	
	DIDR0 |= (1<<ADC0D); // digital input buffer disable, saves power.
	ADCSRA = (1<<ADEN)|(0b111<<ADPS0);
}

//kjører servoen
void moveServo(uint8_t position){
	OCR1A = (((position*(SERVO_MAX - SERVO_MIN))/POSITION_MAX) + SERVO_MIN);
}



bool validatePosition(uint8_t position){     // gjør sånn at posisjonen til servo holder seg mellom 0-180 grader
	if (position <= 1){
		position = 0;
		return false;
	}
	else if(position >= 180){
		position = 181;
		return false;
	}
	else{
		return true;
	}
}

int correctPosition(int16_t potValue, int16_t leftSensor, int16_t rightSensor, uint8_t position){   //returnerer grader til servo
	
	potValue = potValue/200;
	
	if (leftSensor > rightSensor){     //Må finne ut av hvilken vei den skal være
		return (position -= potValue);
	}
	if (leftSensor < rightSensor){
		return (position += potValue);
	}
}