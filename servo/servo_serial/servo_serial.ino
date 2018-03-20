/*
Creado: Luis del Valle (ldelvalleh@programarfacil.com)
https://programarfacil.com
*/
// Incluímos la librería para poder controlar el servo
#include <Servo.h>

// Declaramos la variable para controlar el servo
Servo servoMotor;
int angulo;
String inString = "";    // string to hold input
int inChar;
int offset = +90;

void setup() {
  // Iniciamos el monitor serie para mostrar el resultado
  Serial.begin(9600);
  // Iniciamos el servo para que empiece a trabajar con el pin 9
  servoMotor.attach(9);
  // Inicializamos al ángulo 0 el servomotor
  angulo = 90;
}
void loop() {
    // Read serial input:
  while (Serial.available() > 0) {
    inChar = Serial.read();
    if (isDigit(inChar)) {
      // convert the incoming byte to a char and add it to the string:
      inString += (char)inChar;
    }
    // if you get a newline, print the string, then the string's value:
    if (inChar == '\n') {
      Serial.print("Angulo:");
      Serial.println(inString.toInt());
      angulo = inString.toInt();
      // clear the string for new input:
      inString = "";
    }
    servoMotor.write(angulo);
  }
  delay(500);
}
