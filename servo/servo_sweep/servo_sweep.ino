/*
Creado: Luis del Valle (ldelvalleh@programarfacil.com)
https://programarfacil.com
*/
// Incluímos la librería para poder controlar el servo
#include <Servo.h>

// Declaramos la variable para controlar el servo
Servo servoMotor;
int del = 400;
int angle_step = 10;
int min_angle = 60;
int max_angle = 120;

void setup() {
  // Iniciamos el monitor serie para mostrar el resultado
  Serial.begin(9600);
  // Iniciamos el servo para que empiece a trabajar con el pin 9
  servoMotor.attach(9);
  // Inicializamos al ángulo 0 el servomotor
  servoMotor.write(min_angle);
}
void loop() {
  // Vamos a tener dos bucles uno para mover en sentido positivo y otro en sentido negativo
  // Para el sentido positivo
  for (int i = min_angle/angle_step; i <= max_angle/angle_step; i++)
  {
    // Desplazamos al ángulo correspondiente
    servoMotor.write(angle_step*i);
    Serial.print("Angulo = ");
    Serial.println(angle_step*i);
    // Hacemos una pausa de 25ms
    delay(del);
  }
  // Para el sentido negativo
  for (int i = max_angle/angle_step-1; i > min_angle/angle_step; i--)
  {
    // Desplazamos al ángulo correspondiente
    servoMotor.write(angle_step*i);
    Serial.print("Angulo = ");
    Serial.println(angle_step*i);
    // Hacemos una pausa de 25ms
    delay(del);
  }
}
