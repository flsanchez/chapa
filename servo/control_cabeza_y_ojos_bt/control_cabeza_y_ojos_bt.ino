#include <Servo.h>
#include <SoftwareSerial.h>

#define HEAD_PIN 2
#define EYES_PIN 3
#define BT_TX_PIN 9
#define BT_RX_PIN 10

// declaro los servos
Servo servoHead;
Servo servoEyes;

// declaro la conexion
SoftwareSerial BTSerial(BT_RX_PIN, BT_TX_PIN); // RX, TX

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
char data = 0;
unsigned int button_data = 0;

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);
  serial_time = millis();
  servoHead.attach(HEAD_PIN);
  servoHead.write(min_angle_head);//(min_angle_head+max_angle_head)/2);
  servoEyes.attach(EYES_PIN);
  servoEyes.write(min_angle_eyes);//(min_angle_eyes+max_angle_eyes)/2);
  eyes_cont = 0;
  delay(3000);
}

void loop() {
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

  // buttons poll
  
  if(BTSerial.available() > 0){
    data = BTSerial.read();
    if(data == 'b'){
      delay(10);
      if(BTSerial.available() > 0){
        button_data = BTSerial.read();
        Serial.print("Boton");
        Serial.println(button_data);
        int mask = 1;
        for(int i = 0; i < 4; i++){
          //Serial.println(button_data & mask<<2^i);
          if(button_data & mask<<i) buttons_state[i] = HIGH;
          else buttons_state[i] = LOW;
        }
      }
    }
    else if(data == 's'){
      BTSerial.print(String((int)servoHead.read())+","+String((int)servoEyes.read())+",");
    }
  }
    
}
