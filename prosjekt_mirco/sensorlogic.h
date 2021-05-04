#ifndef SENSORLOGIC_H_INCLUDED
#define SENSORLOGIC_H_INCLUDED

int position;
int positionMax;

void validatePosition(int position);
int correctPosition(int potValue, int leftSensor, int rightSensor);
void moveServo(int position);
int ADC_init(int pin);

#endif