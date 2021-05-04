#ifndef SERVO_H_INCLUDED
#define SERVO_H_INCLUDED

//Variables
int positionMin;
int positionMax;
int position;

//Functions
void timer_init(void);
int ADC_init(int pin);
void moveServo(int position);
#endif