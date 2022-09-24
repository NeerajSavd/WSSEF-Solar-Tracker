#include <Wire.h>
#include <ds3231.h>
#include <Servo.h>
#include <EEPROM.h>

Servo servoVer1;
Servo servoVer2;

struct ts t;
int n = 0;

int vertAngles[48] = {45, 45, 45, 45, 45, 45, 45, 45, 45, 41, 36, 31, 27, 22, 19, 15, 12, 9, 6, 4, 2, 1, 0, 0, 0, 0, 1, 3, 5, 7, 10, 13, 17, 21, 25, 29, 34, 38, 43, 45, 45, 45, 45, 45, 45, 45, 45, 45};
int index = 0;
int vert = 90;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  DS3231_init(DS3231_CONTROL_INTCN);
  
  servoVer1.attach(9);
  servoVer2.attach(10);
  vert = vertAngles[index];
  servoVer1.write(85+vert);
  servoVer2.write(97+vert);

  t.hour=7;
  t.min=22;
  t.sec=20;
  t.mday=12;
  t.mon=3;
  t.year=2020;
  DS3231_set(t);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (index < 48) {
    DS3231_get(&t);
    //Serial.print(index);
    if (t.min % 15 == 0 && t.sec == 0)
    {
      Serial.print("\n measuring");
      vert = vertAngles[index];
      servoVer1.write(85+vert); 
      servoVer2.write(97+vert); 
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
