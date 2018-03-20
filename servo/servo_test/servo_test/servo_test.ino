/*
Creado: Luis del Valle (ldelvalleh@programarfacil.com)
https://programarfacil.com
*/
// Incluímos la librería para poder controlar el servo
#include <Servo.h>

// Declaramos la variable para controlar el servo
Servo servoMotor;
int del = 500;

void setup() {
  // Iniciamos el monitor serie para mostrar el resultado
  Serial.begin(9600);
  // Iniciamos el servo para que empiece a trabajar con el pin 9
  servoMotor.attach(9);
  // Inicializamos al ángulo 0 el servomotor
  servoMotor.write(0);
}
void loop() {
  // Vamos a tener dos bucles uno para mover en sentido positivo y otro en sentido negativo
  // Para el sentido positivo
  for (int i = 0; i <= 20; i++)
  {
    // Desplazamos al ángulo correspondiente
    servoMotor.write(9*i);
    Serial.print("Angulo = ");
    Serial.println(9*i);
    // Hacemos una pausa de 25ms
    delay(del);
  }
  // Para el sentido negativo
  for (int i = 19; i > 0; i--)
  {
    // Desplazamos al ángulo correspondiente
    servoMotor.write(9*i);
    Serial.print("Angulo = ");
    Serial.println(9*i);
    // Hacemos una pausa de 25ms
    delay(del);
  }
}
