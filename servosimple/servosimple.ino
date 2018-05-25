#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 70;    // variable to store the servo position
int ini = 90;
int fin = 90;
int del = 20;
int st = 1;

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.write(ini);
  delay(3000);
  pinMode(8,INPUT_PULLUP);
}

void loop() {
  
  while(digitalRead(8) == HIGH){
    for (pos = ini; pos <= fin; pos += st){ // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(del);                       // waits 15ms for the servo to reach the position
    }
    for (pos = fin; pos >= ini; pos -= st){ // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(del);                       // waits 15ms for the servo to reach the position
    }
  }
}

