int DI_7;
int sV_7;

void setup() {
  Serial.begin(9600);//鮑率9600
  pinMode(7, OUTPUT);
  pinMode(6, INPUT);
}

void loop() {
  sV_7 = analogRead(2);// 讀MQ-7類比訊號的值
  DI_7 = digitalRead(6);// 讀MQ-7數位訊號的值
  Serial.println(sV_7);//印出MQ-7類比訊號
  Serial.println(DI_7);//印出MQ-7數位訊號
  delay(1000);
}
