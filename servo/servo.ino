#include <Servo.h>

static const int servoPin1 = 4; //Garra
static const int servoPin2 = 5; //L - Pulso
static const int servoPin3 = 18; //R - Cutuvelo (Frente e tras)
static const int servoPin4 = 19; //Base

Servo Garra;
Servo Pulso;
Servo Cutuvelo;
Servo Base;

void setup() {
  Serial.begin(115200);
  Garra.attach(servoPin1);
  Pulso.attach(servoPin2);
  Cutuvelo.attach(servoPin3);
  Base.attach(servoPin4);
  
}

void loop() {
//  for(int posDegrees = 0;posDegrees <= 180; posDegrees=posDegrees+5) {
//  }
//  
//  for(int posDegrees = 180; posDegrees >= 0; posDegrees=posDegrees-5) {
//  }

  GarraUpDef();
  delay(10);
  //GarraDownDef();
}

void CutuveloUpDef(){
  for(int posDegrees = 180; posDegrees >= 0; posDegrees=posDegrees-1) {
    Cutuvelo.write(posDegrees);
    delay(20);
  }
}

void GarraUpDef(){
  for(int posDegrees = 180; posDegrees >= 0; posDegrees=posDegrees-1) {
    Garra.write(posDegrees);
    delay(20);
  }
}

void PulsoUpDef(){
  for(int posDegrees = 180; posDegrees >= 0; posDegrees=posDegrees-1) {
    Pulso.write(posDegrees);
    delay(20);
  }
}

void BaseUpDef(){
  for(int posDegrees = 180; posDegrees >= 0; posDegrees=posDegrees-1) {
    Base.write(posDegrees);
    delay(20);
  }
}

void CutuveloDownDef(){
  for(int posDegrees = 0; posDegrees >= 0; posDegrees=posDegrees+1) {
    Cutuvelo.write(posDegrees);
    delay(20);
  }
}

void GarraDownDef(){
  for(int posDegrees = 0; posDegrees >= 0; posDegrees=posDegrees+1) {
    Garra.write(posDegrees);
    delay(20);
  }
}

void PulsoDownDef(){
  for(int posDegrees = 0; posDegrees >= 0; posDegrees=posDegrees+1) {
    Pulso.write(posDegrees);
    delay(20);
  }
}

void BaseDownDef(){
  for(int posDegrees = 0; posDegrees >= 0; posDegrees=posDegrees+1) {
    Base.write(posDegrees);
    delay(20);
  }
}
