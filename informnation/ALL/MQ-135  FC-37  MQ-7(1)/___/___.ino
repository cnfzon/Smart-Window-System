int led=5;        //fc-37
int get_D3 = 3;   //fc-37
int get_A0 = A0;  //fc-37
int sensorValue;  //MQ-135
int digitalValue; //MQ-135
int DI_7;         //MQ-7
int sV_7;         //MQ-7

void setup() {
  pinMode(led,OUTPUT);   //fc-37 pin5
  pinMode(get_D3, INPUT);//fc-37 pin3
  pinMode(4, OUTPUT);    //MQ-135
  pinMode(2, INPUT);     //MQ-135
  pinMode(7, OUTPUT);    //MQ-7
  pinMode(6, INPUT);     //MQ-7
  Serial.begin(9600);  

}

void loop() {
  int value = analogRead(0);    //讀fc-37類比訊號的值
  sensorValue = analogRead(1);  // 讀MQ-135類比訊號的值
  sV_7 = analogRead(2);         // 讀MQ-7類比訊號的值
  digitalValue = digitalRead(2);// 讀MQ-135數位訊號的值
  DI_7 = digitalRead(6);        // 讀MQ-7數位訊號的值

  Serial.print("fc-37 : 類比->");
  Serial.print(value);    
  Serial.print("  ");    //在監控視窗印出從A0讀取的值

  if (sensorValue > 50) //檢測到非正常氣體 MQ-135
  { digitalWrite(4, HIGH);} //LED變亮 
  else
  { digitalWrite(4, LOW);} //LED變暗

  if (sV_7 > 50) //檢測到非正常氣體 MQ-7
  { digitalWrite(7, HIGH);} //LED變亮 
  else
  { digitalWrite(7, LOW);} //LED變暗
  
  if(digitalRead(get_D3) == LOW)//讀取fc-37感測器的D0輸出"低態"
  {
    Serial.println("Digital value : wet"); //在監控視窗印出"wet"
    digitalWrite(led,HIGH);     //LED變亮
  }
  else                          //讀取fc-37感測器的D0輸出"高態"
  {
    Serial.println("Digital value : dry"); //在監控視窗印出"dry"
    digitalWrite(led,LOW);     //LED變暗
  }
  Serial.print("MQ-135 : 類比->");
  Serial.print(sensorValue, DEC); //印出MQ-135類比訊號
  Serial.print("　數位->");
  Serial.println(digitalValue, DEC);//印出MQ-135數位訊號
  Serial.print("MQ-7 : 類比->");
  Serial.print(sV_7, DEC); //印出MQ-135類比訊號
  Serial.print("　數位->");
  Serial.println(DI_7, DEC);//印出MQ-135數位訊號
  Serial.println("　");
  delay(1000);
}
/* MQ-135
正常空氣返回約100-200
酒精返回大約 700
較輕的氣體返回約750 */
