#include <Wire.h>
#include <ds3231.h>
#include <Servo.h>
#include <EEPROM.h>

Servo servoHor;
Servo servoVer;
Servo servoDHor;
Servo servoDVer;

struct ts t;
int n = 0;

int vertAngles[45] = {45, 45, 45, 45, 45, 45, 45, 45, 45, 39, 34, 29, 24, 20, 16, 12, 9, 6, 4, 2, 0, 0, 0, 0, 0, 0, 2, 4, 6, 9, 13, 17, 21, 25, 30, 35, 40, 45, 45, 45, 45, 45, 45, 45, 45};
int horzAngles[45] = {-40, -38, -37, -35, -34, -33, -31, -29, -28, -26, -25, -23, -21, -19, -17, -15, -13, -11, -9, -7, -5, -3, 0, 1, 3, 5, 8, 10, 12, 14, 16, 18, 20, 22, 23, 25, 27, 28, 30, 31, 33, 34, 36, 37, 39};
int index = 39;
int vert = 90;
int horz = 90;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  DS3231_init(DS3231_CONTROL_INTCN);
  
  servoDVer.attach(11);
  servoDHor.attach(9);
  servoVer.attach(10);
  servoHor.attach(8);
  vert = vertAngles[index];
  horz = horzAngles[index];
  servoDVer.write(90+vert);
  servoVer.write(100+vert);
  servoDHor.write(98+horz);
  servoHor.write(87+horz);

  t.hour=4; 
  t.min=25;
  t.sec=40;
  t.mday=28;
  t.mon=2;
  t.year=2020;
  DS3231_set(t);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (index < 45) {
    DS3231_get(&t);
    //Serial.print(index);
    if (t.min % 15 == 0 && t.sec == 0)
    {
      Serial.print("\n measuring");
      vert = vertAngles[index];
      horz = horzAngles[index];
      servoDVer.write(90+vert); 
      servoVer.write(100+vert); 
      servoDHor.write(98+horz); 
      servoHor.write(87+horz);
      record();
      delay(1000);
      record();
      index++;
    }
   if (t.sec == 30)
   {  
      Serial.print(index);
      Serial.print("-");
      Serial.print(t.hour);
      Serial.print(":");
      Serial.print(t.min);
      Serial.print(".");
      Serial.print(t.sec);
      Serial.print(" ");
      serialRec();
      Serial.print("\n");
   }
    delay(1000);
  }
  Serial.print(index);
      Serial.print("-");
      Serial.print(t.hour);
      Serial.print(":");
      Serial.print(t.min);
      Serial.print(".");
      Serial.print(t.sec);
      Serial.print(" ");
      serialRec();
      Serial.print("\n");
      delay(1000);
}

void record()
{
  EEPROM.write(n,t.hour);
  n++;
  EEPROM.write(n,t.min);
  n++;
  EEPROM.write(n,t.sec);
  n++;
  EEPROM.write(n,index);
  n++;
  int sensorValue = analogRead(A0);
  float voltage = sensorValue * (5.0 / 1023.0); 
  int v = voltage*100-250;
  EEPROM.write(n,v);
  n++;
  sensorValue = analogRead(A1);
  voltage = sensorValue * (5.0 / 1023.0);
  v = voltage*100-250;
  EEPROM.write(n,v);
  n++;
  sensorValue = analogRead(A2);
  voltage = sensorValue * (5.0 / 1023.0);
  v = voltage*100-250;
  EEPROM.write(n,v);
  n++;
  sensorValue = analogRead(A3);
  voltage = sensorValue * (5.0 / 1023.0);
  v = voltage*100-250;
  EEPROM.write(n,v);
  n++;
}

void serialRec()
{
  int sensorValue = analogRead(A0);
  float voltage = sensorValue * (5.0 / 1023.0); 
  int v = voltage*100-250;
  Serial.print(v);
  Serial.print(" ");
  sensorValue = analogRead(A1);
  voltage = sensorValue * (5.0 / 1023.0);
  v = voltage*100-250;
  Serial.print(v);
  Serial.print(" ");
  sensorValue = analogRead(A2);
  voltage = sensorValue * (5.0 / 1023.0);
  v = voltage*100-250;
  Serial.print(v);
  Serial.print(" ");
  sensorValue = analogRead(A3);
  voltage = sensorValue * (5.0 / 1023.0);
  v = voltage*100-250;
  Serial.print(v);
  Serial.print(" ");
}
