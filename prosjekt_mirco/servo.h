#ifndef SERVO_H_INCLUDED
#define SERVO_H_INCLUDED

//Variables


//Functions
void timer_init(void);
void ADC_init(void);
void moveServo(int sens1, int sens2, int potmeter);
#endif