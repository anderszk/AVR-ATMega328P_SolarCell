//Includes
#include "sensorlogic.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdbool.h>

//Defines
#define T1_PRESCALE 8 // Timer 1 clock prescaler
#define SERVO_PERIOD F_CPU/1000000*20000/T1_PRESCALE
#define SERVO_MAX F_CPU/1000000*2550/T1_PRESCALE   
#define SERVO_MIN F_CPU/1000000*500/T1_PRESCALE  
#define POSITION_MAX 180

void Timer1_PWM_init(){ //Timer initialization
	
	DDRB = (1<<DDB1); // Sets PB1 as output

	//Settings for servo
	TCCR1A = (1<<COM1A1)|(0<<COM1A0)|(1<<WGM11)|(0<<WGM10);
	TCCR1B = (1<<CS11)|(1<<WGM13)|(1<<WGM12);

	ICR1 = SERVO_PERIOD; // Periodetid på 20ms (50Hz)
}


int ADC_Conversion(int8_t pin){ //Analog to digital converter @param pinnumber to determine MUX(input pin)

	if (pin == 0){ //Sets reference voltage to supply voltage (5V)
		ADMUX = (1<<REFS0)|(0<<ADLAR)|(0 << MUX1)|(0 << MUX0); // ADC0
	}
	else if(pin == 1){
		ADMUX = (1<<REFS0)|(0<<ADLAR)|(0 << MUX1)|(1 << MUX0); // ADC1
	}
	else if (pin == 2){
		ADMUX = (1<<REFS0)|(0<<ADLAR)|(1 << MUX1)|(0 << MUX0); // ADC2  potensiometer
	}
	else {
		return 0;
	}
	
	ADCSRA |= (1<<ADSC); //Starts the conversion
	
	do {} while (ADCSRA & (1<<ADSC)); // vent på start-convertion (vent så lenge bittet er høy)
	return ADC;
}

void ADC_Init(void){ //Initialize the ADC
	ADCSRA = (1<<ADEN)|(0b111<<ADPS0); //Enables ADC with prescale = 8
}


void moveServo(uint8_t position){ //@param desired position, Converts position to period and sends output with the timer
	OCR1A = (((position*(SERVO_MAX - SERVO_MIN))/POSITION_MAX) + SERVO_MIN); //Map-function to convert position to period
}



bool validatePosition(uint8_t position){ //@param desired position, validates the position to prevent invalid outoput to servo
	if (!(position <= 5 || position >= 180)){
		return true;
	}
	else{
		return false;
	}
}


bool validateTolerance(int16_t val1, int16_t val2){ //Checks if the delta is above the tolerance to determine if the servo should move
	int tolleranse = 5; //Delta must be >5 to move
	
	if((abs(val1-val2) <= tolleranse) || (abs(val2-val1) <= tolleranse)){
		return false;
	}
	else{
		return true;
	}
}


int correctPosition(int16_t potValue, int16_t leftSensor, int16_t rightSensor, uint8_t position){   //Gives the determined position of the solarpanel
	
	potValue = (potValue+100)/200; //The rate of which the solarpanel should move (in degrees)
	
	if (leftSensor > rightSensor){     
		return (position -= potValue);
	}
	else if (leftSensor < rightSensor){
		return (position += potValue);
	}
	else{
		return 0;
	}
}