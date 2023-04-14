#include <Wire.h>
#include <VL53L0X.h>
#include <Servo.h>

static const int servoPin1 = 23; //Radar

VL53L0X sensor;
Servo radarBraco;

void setup()
{
  Serial.begin(115200);
  Wire.begin();

  radarBraco.attach(servoPin1);
  sensor.init();
  sensor.setTimeout(500);
}

void loop()
{
  for(int posDegrees = 180; posDegrees >= 0; posDegrees=posDegrees-1) {
    radarBraco.write(posDegrees);
    delay(20);
    int dist = sensor.readRangeSingleMillimeters();
    Serial.print(dist);
    Serial.print(" ");
    Serial.print(posDegrees);
    Serial.print("\n");
  }
  for(int posDegrees = 1; posDegrees <= 180; posDegrees=posDegrees+1) {
    radarBraco.write(posDegrees);
    delay(20);
    int dist = sensor.readRangeSingleMillimeters();
    Serial.print(dist);
    Serial.print(" ");
    Serial.print(posDegrees);
    Serial.print("\n");
  }
}
