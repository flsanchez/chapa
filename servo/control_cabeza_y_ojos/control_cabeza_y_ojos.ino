#include <Servo.h>

#define HEAD_PIN 2
#define EYES_PIN 3
#define HEAD_CW_PIN 4
#define HEAD_CC_PIN 5
#define EYES_CW_PIN 6
#define EYES_CC_PIN 7

// declaro los servos
Servo servoHead;
Servo servoEyes;

// condiciones de control                               
int del = 10;
int angle_step = 1;
int eyes_divisor = 1;
int eyes_cont;
int min_angle_head = 0;
int max_angle_head = 180;
int min_angle_eyes = 30; // valentin: 0; marta: 30
int max_angle_eyes = 60; // valentin: 40; marta: 60
int min_max_angles[4] = {min_angle_head,max_angle_head,min_angle_eyes,max_angle_eyes};
int buttons[4] = {4,5,6,7};
int buttons_state[4] = {0,0,0,0};
long serial_time = 0;

void setup() {
  Serial.begin(9600);
  serial_time = millis();
  servoHead.attach(HEAD_PIN);
  servoHead.write(min_angle_head);//(min_angle_head+max_angle_head)/2);
  servoEyes.attach(EYES_PIN);
  servoEyes.write(min_angle_eyes);//(min_angle_eyes+max_angle_eyes)/2);
  for(int idx = 0; idx < 4; idx++) pinMode(buttons[idx],INPUT);
  eyes_cont = 0;
  delay(3000);
}
void loop() {
  for(int idx = 0; idx < 4; idx++) buttons_state[idx] = digitalRead(buttons[idx]);
  int angle_head = servoHead.read();
  int angle_eyes = servoEyes.read();
  
  int idx = 0;
  if(buttons_state[idx] == HIGH && (angle_head+angle_step)<=max_angle_head) angle_head = angle_head+angle_step;
  else{
    idx = 1;
    if(buttons_state[idx] == HIGH && (angle_head-angle_step)>=min_angle_head) angle_head = angle_head-angle_step;
  }
  servoHead.write(angle_head);
  
  idx = 2;
  if(buttons_state[idx] == HIGH && (angle_eyes+angle_step)<=max_angle_eyes){
    eyes_cont++;
    if(eyes_cont==eyes_divisor){
      angle_eyes = angle_eyes+angle_step;
      eyes_cont = 0;
    }
  }
  else{
    idx = 3;
    if(buttons_state[idx] == HIGH && (angle_eyes-angle_step)>=min_angle_eyes){
      eyes_cont++;
      if(eyes_cont==eyes_divisor){
        angle_eyes = angle_eyes-angle_step;
        eyes_cont = 0;
      }
    }
  }
  servoEyes.write(angle_eyes);


  if(millis() - serial_time > 500)
  {
    serial_time = millis();
    Serial.print("Cabeza = ");
    Serial.println(servoHead.read());
    Serial.print("Ojos = ");
    Serial.println(servoEyes.read());
  }
  
  delay(del);
    
}
