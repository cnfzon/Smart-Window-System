#include <MQ135.h>

int fc_A0;        //fc-37
int M135_A0;      //MQ-135(室外)
int M135_A1;      //MQ-135(室內)
int M7_A0;        //MQ-7
int M_io = 0;     //indoor=1(HIGH) outdoor=2(LOW)

void setup() {
  pinMode(2, OUTPUT);           //M_io
  pinMode(13, OUTPUT);          //空氣清淨機 red 13
  pinMode(12, OUTPUT);          //除濕機    green 12
  pinMode(11, OUTPUT);          //抽風機    yellow 11
  Serial.begin(9600);  
}

void loop() {
  fc_A0      = analogRead(0);   // 讀fc-37類比訊號
  M135_A0    = analogRead(1);   // 讀MQ-135類比訊號(室外)
  M7_A0      = analogRead(2);   // 讀MQ-7類比訊號
  M135_A1    = analogRead(3);   // 讀MQ-135類比訊號(室內)
  /////////////////////////////////////////////////////////////////fc-37
  //Serial.print("fc-37 : 類比->");
  //Serial.print(fc_A0);    
  Serial.print("  ");                      //在監控視窗印出從A0讀取的值
  if(fc_A0 < 800)                          //讀取fc-37感測器的A0判斷"下雨"
  {
    //Serial.println("下雨");                 //在監控視窗印出"wet"
    digitalWrite(12,HIGH);                 //LED變亮--除濕機
    Serial.write("1");                     //關窗 Close
  }
  else                                     //讀取fc-37感測器的A0判斷"未下雨"
  {
    //Serial.println("未下雨");               //在監控視窗印出"dry"
    digitalWrite(12,LOW);                  //LED變暗
    Serial.write("2");                     //開窗 Open
  }
  /////////////////////////////////////////////////////////////////MQ-135(室內0)
  if (M135_A1 > 500)                       //檢測到有害氣體
  { 
    digitalWrite(13, HIGH);                //LED變亮--空氣清淨機
    digitalWrite(11, HIGH);                //LED變亮--抽風機
    Serial.write("3");                     //開窗 Open
  }
  else
  { 
    digitalWrite(13, LOW);                 //LED變暗--空氣清淨機
    digitalWrite(11, LOW);                 //LED變暗--抽風機
    Serial.write("4");                     //關窗 Close
  }
  /////////////////////////////////////////////////////////////////MQ-135(室外1)
  if (M135_A0 > 500)                       //檢測到有害氣體
  { 
    digitalWrite(13, HIGH);                //LED變亮--空氣清淨機
    Serial.write("E");                     //未下雨 E
    Serial.write("5");                     //關窗 Close
  }
  else
  { 
    digitalWrite(13, LOW);                 //LED變暗--空氣清淨機
    Serial.write("6");                     //開窗 Open
  }
  /////////////////////////////////////////////////////////////////MQ-7
  if (M7_A0 > 180)                         //檢測到有害氣體
  { 
    digitalWrite(13, HIGH);                //LED變亮--空氣清淨機
    digitalWrite(11, HIGH);                //LED變亮--抽風機
    Serial.write("7");                     //開窗 Open
  }  
  else
  { 
    digitalWrite(13, LOW);                 //LED變暗--空氣清淨機
    digitalWrite(11, LOW);                 //LED變暗--抽風機
    Serial.write("8");                     //關窗 Close
  }
  /////////////////////////////////////////////////////////////////序列埠視窗MQ-135(室內1)
  /*Serial.print("MQ-135(indoor) : 氣體數值->");
  Serial.println(M135_A1, DEC);
  /////////////////////////////////////////////////////////////////序列埠視窗MQ-135(室外0)
  Serial.print("MQ-135(outdoor): 氣體數值->");
  Serial.println(M135_A0, DEC);
  /////////////////////////////////////////////////////////////////序列埠視窗MQ-7
  Serial.print("MQ-7           : 氣體數值->");
  Serial.println(M7_A0, DEC);
  Serial.println("　");*/
  /////////////////////////////////////////////////////////////////室內外通知判斷(傳遞訊號給arduino_2)
  /*if(M_io == 1) {digitalWrite(2,HIGH);} //室內
  if(M_io == 2) {digitalWrite(2,LOW);}  //室外*/
  delay(500);
}
/* 
MQ-135
  正常空氣返回約100-200
  瓦斯 450~650
  酒精 400~700
MQ-7
  線香 180~260
*/
