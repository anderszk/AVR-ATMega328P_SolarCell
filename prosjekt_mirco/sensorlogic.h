#ifndef SENSORLOGIC_H_INCLUDED
#define SENSORLOGIC_H_INCLUDED

//Includes
#include <stdint.h>
#include <stdbool.h>

//Function that can be used in main
bool validatePosition(uint8_t position);
bool validateTolerance(int16_t val1, int16_t val2);
int correctPosition(int16_t potValue, int16_t leftSensor, int16_t rightSensor, uint8_t position);
int ADC_Conversion(int8_t pin);
void ADC_Init(void);
void Timer1_PWM_init(void);
void moveServo(uint8_t position);

#endif