int led=5;
int get_D3 = 3;
int get_A0 = A0;
int sensorValue;
int digitalValue;

void setup() {
  pinMode(led,OUTPUT);  
  pinMode(get_D3, INPUT);
  pinMode(13, OUTPUT);
  pinMode(2, INPUT);
  Serial.begin(9600);  

}

void loop() {
  int value = analogRead(A0);    //從A0讀取感測值
  sensorValue = analogRead(1);  // 讀MQ-135類比訊號的值
  digitalValue = digitalRead(2);// 讀MQ-135數位訊號的值

  Serial.print("fc-37 : 類比->");
  Serial.print(value);    //
  Serial.print("  ");    //在監控視窗印出從A0讀取的值

  if (sensorValue > 400) //檢測到非正常氣體
  {
    digitalWrite(13, HIGH);//LED變亮
  }
  else
  {
    digitalWrite(13, LOW);//LED變暗
  }
  
  if(digitalRead(get_D3) == LOW)//讀取fc-37感測器的D0輸出"低態"
  {
    Serial.println("Digital value : wet"); //在監控視窗印出"wet"
    digitalWrite(led,HIGH);     //LED變亮
  }
  else//讀取fc-37感測器的D0輸出"高態"
  {
    Serial.println("Digital value : dry"); //在監控視窗印出"dry"
    digitalWrite(led,LOW);     //LED變暗
  }
  Serial.print("MQ-135 : 類比->");
  Serial.print(sensorValue, DEC); //印出MQ-135類比訊號
  Serial.print("　數位->");
  Serial.println(digitalValue, DEC);//印出MQ-135數位訊號
  Serial.println("　");
  delay(1000);
}
/*
正常空氣返回約100-200
酒精返回大約 700
較輕的氣體返回約750
 */
