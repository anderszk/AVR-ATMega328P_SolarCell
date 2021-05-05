#include "sensorlogic.h"


void validatePosition(int position){ //Checks id the position has exceeded the valid positions
    if (position < 0){
        position = 0;
    }
    else if(position > 180){
        position = 180;
    }
}

int correctPosition(int potValue, int leftSensor, int rightSensor){ //Returns degrees
	
	 potValue = potValue/200;
	 
    if (leftSensor > rightSensor){ //Må finne ut av hvilke vei den skal være
        return (position -= potValue);
    }
    if (leftSensor < rightSensor){
        return (position += potValue);
    }
}