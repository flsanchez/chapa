#include <SoftwareSerial.h>

char data = 0;                //Variable for storing received data
const int txPin = 9;
const int rxPin = 10;
int st = LOW;
long cont = 0;

SoftwareSerial BTSerial(rxPin, txPin); // RX, TX

void setup() 
{
  Serial.begin(9600);
  BTSerial.begin(9600);         //Sets the data rate in bits per second (baud) for serial data transmission
  pinMode(13, OUTPUT);        //Sets digital pin 13 as output pin
  digitalWrite(13, st);
}
void loop()
{
  if(BTSerial.available() > 0)  // Send data only when you receive data:
  {
    data = BTSerial.read();      //Read the incoming data and store it into variable data
    //BTSerial.print(data);        //Print Value inside data in Serial monitor
    //BTSerial.print("\n");        //New line 
    if(data == '1'){
      st = HIGH;
      digitalWrite(13, st);
    }
    else if(data == '0'){     //Checks whether value of data is equal to 0
      st = LOW;
      digitalWrite(13, st);
      cont++;
      Serial.println(cont);
    }
    else if(data == 'v'){
      if(st == LOW) BTSerial.print("Status: OFF");
      else BTSerial.print("Status: ON");
    }
  }                          
}                 
