#define IN1  22
#define IN2  24
#define IN3  26
#define IN4  28

char ser;
int del = 10;
int dir = 1;
int go = 0;

void setup(){
  Serial.begin(9600);
  pinMode(IN1, OUTPUT); 
  pinMode(IN2, OUTPUT); 
  pinMode(IN3, OUTPUT); 
  pinMode(IN4, OUTPUT); 
}

void loop(){

  ser = readData();
  updateVar();
  if(go == 1) doStep(dir,del);
  //for(int i = 0; i<4096;i++) doStep(dir,del);
  
}

void doStep(int dir,int del){
  //dir = 1 CW; dir = 0 CC
  if(dir == 1){
    for(int j = 0; j<8; j++){
      stepper(j);
      delay(del);
    }
  }
  else{
    for(int j = 0; j<8; j++){
      stepper(7-j);
      delay(del);
    }
  }
}

void stepper(int Steps){
  switch(Steps){
       case 0:
         digitalWrite(IN1, LOW); 
         digitalWrite(IN2, LOW);
         digitalWrite(IN3, LOW);
         digitalWrite(IN4, HIGH);
       break; 
       case 1:
         digitalWrite(IN1, LOW); 
         digitalWrite(IN2, LOW);
         digitalWrite(IN3, HIGH);
         digitalWrite(IN4, HIGH);
       break; 
       case 2:
         digitalWrite(IN1, LOW); 
         digitalWrite(IN2, LOW);
         digitalWrite(IN3, HIGH);
         digitalWrite(IN4, LOW);
       break; 
       case 3:
         digitalWrite(IN1, LOW); 
         digitalWrite(IN2, HIGH);
         digitalWrite(IN3, HIGH);
         digitalWrite(IN4, LOW);
       break; 
       case 4:
         digitalWrite(IN1, LOW); 
         digitalWrite(IN2, HIGH);
         digitalWrite(IN3, LOW);
         digitalWrite(IN4, LOW);
       break; 
       case 5:
         digitalWrite(IN1, HIGH); 
         digitalWrite(IN2, HIGH);
         digitalWrite(IN3, LOW);
         digitalWrite(IN4, LOW);
       break; 
         case 6:
         digitalWrite(IN1, HIGH); 
         digitalWrite(IN2, LOW);
         digitalWrite(IN3, LOW);
         digitalWrite(IN4, LOW);
       break; 
       case 7:
         digitalWrite(IN1, HIGH); 
         digitalWrite(IN2, LOW);
         digitalWrite(IN3, LOW);
         digitalWrite(IN4, HIGH);
       break; 
       default:
         digitalWrite(IN1, LOW); 
         digitalWrite(IN2, LOW);
         digitalWrite(IN3, LOW);
         digitalWrite(IN4, LOW);
       break; 
  }
}

char readData(){
  while(Serial.available()) return Serial.read();
}

void updateVar(){
    switch(ser){
      case '0': 
        go = 0;
        break;
      case '1': 
        go = 1;
        break;
      case 'd': 
        dir = !dir;
        break;
      case '+': 
        if(del > 1) del --;
        break;
      case '-': 
        if(del < 10) del ++;
        break;
      default:
        break;
    }
}

