#ifndef SENSORLOGIC_H_INCLUDED
#define SENSORLOGIC_H_INCLUDED

int pos;

void validatePosition(int position);
int correctPosition(int potValue, int leftSensor, int rightSensor);
void moveServo(int position);

#endif