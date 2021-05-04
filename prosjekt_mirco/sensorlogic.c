#include "sensorlogic.h"

int position = 90; //Defualt position of the servo when starting the program
int positionMax = 180;
int positionMin = 0;

void potmeter_init(){
    return;
}

void lightsensor_init(){
    return;
}

void validatePosition(int position){ //Checks id the position has exceeded the valid positions
    if (position < 0){
        position = 0;
    }
    else if(position > 180){
        position = 180;
    }
}

int correctPosition(int potValue, int leftSensor, int rightSensor){ //Returns degrees
    if (leftSensor > rightSensor){ //Må finne ut av hvilke vei den skal være
        return (pos -= potValue);
    }
    if (leftSensor < rightSensor){
        return (pos += potValue);
    }
}