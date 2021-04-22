#include <Servo.h>

Servo myservo;
int pos = 90;   // initial position

int tolerance = 2;

void setup()
{
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  myservo.write(pos);
  delay(2000); // a 2 seconds delay while we position the solar panel

}

void loop()
{
  int val1 = analogRead(A0); // read the value of sensor 1
  int val2 = analogRead(A1); // read the value of sensor 2
  
  int potensiometer = analogRead(A2);  // måler fra 0-1025
  potensiometer = potensiometer / 200 ; // gjør om til 0-5

  if ((abs(val1 - val2) <= tolerance) || (abs(val2 - val1) <= tolerance)) {   //do nothing if the difference between values is within the tolerance limit
  }

  else {

    if (val1 > val2)
    {
      pos =  pos - potensiometer;
    }

    if (val1 < val2)
    {
      pos = pos + potensiometer;
    }
  }

  if (pos > 180) {  // reset to 180 if it goes higher
    pos = 180;
  }
  if (pos < 0) {
    pos = 0;  // reset to 0 if it goes lower
  }

  myservo.write(pos); // write the position to servo

  Serial.println(pos);//print it
  delay(50);
}
