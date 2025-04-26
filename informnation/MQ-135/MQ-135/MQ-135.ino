#include <MQ135.h>

int sensorValue;
int digitalValue;

void setup()
{
  Serial.begin(9600); //鮑率9600
  pinMode(13, OUTPUT);
  pinMode(2, INPUT);
}

void loop()
{
  sensorValue = analogRead(1);  // 讀MQ-135類比訊號的值
  digitalValue = digitalRead(4);// 讀MQ-135數位訊號的值
  if (sensorValue > 180) //檢測到非正常氣體
  {
    digitalWrite(13, HIGH);//LED變亮
  }
  else
    digitalWrite(13, LOW);//LED變暗
  Serial.println(sensorValue, DEC); //印出MQ-135類比訊號
  Serial.println(digitalValue, DEC);//印出MQ-135數位訊號
  delay(1000);
}
/*
正常空氣返回約100-200
酒精返回大約 700
較輕的氣體返回約750
 */
