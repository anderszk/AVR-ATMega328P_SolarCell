#ifndef SENSORLOGIC_H_INCLUDED
#define SENSORLOGIC_H_INCLUDED

#include <stdint.h>
#include <stdbool.h>

bool validatePosition(uint8_t position);
int correctPosition(int16_t potValue, int16_t leftSensor, int16_t rightSensor, uint8_t position);
int ADC_Conversion(int8_t pin);
void ADC_Init(void);
void Timer1_PWM_init(void);
void moveServo(uint8_t position);

#endif