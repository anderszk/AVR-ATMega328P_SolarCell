include "servo.h"
#include <avr/interrupt.h>
#include <util/delay.h>

#define F_CPU 16000000UL // 16MHz system clock
#define T1_PRESCALE 8 // Timer 1 clock prescaler

/* System clock and timer prescaler will give one tick each 0,5us, thus we

need 40000 ticks to get 20 ms period, 1 ms is 2000 and 2 ms is 4000.

Code below automatically calculates values.*/

// servo period = 20ms = 20000us (=50Hz):

#define SERVO_PERIOD F_CPU/1000000*20000/T1_PRESCALE

// maximum servo should be = 2ms = 2000us, but is 2100 after testing servo:

#define SERVO_MAX F_CPU/1000000*2100/T1_PRESCALE

// minimum should be = 1ms = 1000us, but is 460 us after testing:

#define SERVO_MIN F_CPU/1000000*460/T1_PRESCALE

// Include definition file(s)

#include <avr/interrupt.h>
#include <util/delay.h>


int main( void )

{

ADC_Init();

Timer1_PWM_init();

// OCR1A = SERVO_MIN; // Manual setting to 0° for testing

// OCR1A = (SERVO_MAX+SERVO_MIN)/2; // Manual setting to 90° for testing

// OCR1A = SERVO_MAX; // Manual setting to 180° for testing

/* Endless loop. Starts ADC measurement and waits for it to finish

Adjusts servo signal according to ADC measurement. */

do {


ADCSRA |= (1<<ADSC); // Start ADC conversion.

do {} while (ADCSRA & (1<<ADSC)); // wait for it to finish

OCR1A = ADC*(SERVO_MAX-SERVO_MIN)/1024+SERVO_MIN;

// OCR1A = ((ADC*3)+SERVO_MIN); // quick approximation of servo value

} while(1);

}

//Timer initialization
void Timer1_PWM_init(void)

{

DDRB = (1<<DDB1); // Set OC1A/PB1 as output.

/* Fast PWM non-inverting mode. Clear OC1A on Compare Match, set at TOP=ICR1.

Pre-scale 16Mhz by 8 -> 2MHz = 0.5us/tick */

TCCR1A = (1<<COM1A1)|(0<<COM1A0)|(1<<WGM11)|(0<<WGM10);

TCCR1B = (1<<CS11)|(1<<WGM13)|(1<<WGM12);

ICR1 = SERVO_PERIOD; // Servo period = 20ms (50Hz)

}

//ADC initialization
void ADC_Init(void){

// ADCSRB = 0x00; // Free running mode.

ADMUX = (1<<REFS0)|(0<<ADLAR); // ADC0 single ended input and result right adjusted.

DIDR0 |= (1<<ADC0D); // digital input buffer disable, saves power.

ADCSRA = (1<<ADEN)|(7<<ADPS0);

}

//Moves servo to desired position
void moveServo(int position){
    return
}