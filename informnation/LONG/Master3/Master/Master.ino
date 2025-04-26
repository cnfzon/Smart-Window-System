#include <MQ135.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10,11);//建立軟體串列埠腳位 (RX, TX)

int fc_A0;              //fc-37
int M135_A0;            //MQ-135(室外)
int M135_A1;            //MQ-135(室內)
int M7_A0;              //MQ-7
int M_io = 0;           //indoor=1(HIGH) outdoor=2(LOW)
int Open1_Close0=0;     //開關


void setup() {
  pinMode(2, OUTPUT);           //M_io
  pinMode(9, OUTPUT);          //空氣清淨機 red 13->9
  pinMode(8, OUTPUT);          //除濕機    green 12->8
  pinMode(7, OUTPUT);          //抽風機    yellow 11->7
  Serial.begin(115200); 
  mySerial.begin(115200);
}


void loop() {
  
  fc_A0      = analogRead(0);   // 讀fc-37類比訊號
  M135_A0    = analogRead(1);   // 讀MQ-135類比訊號(室外)
  M7_A0      = analogRead(2);   // 讀MQ-7類比訊號
  M135_A1    = analogRead(3);   // 讀MQ-135類比訊號(室內)
  digitalWrite(7, LOW);                 //LED變暗--抽風機
  digitalWrite(8, LOW);                 //LED變暗--除濕機
  digitalWrite(9, LOW);                 //LED變暗--空氣清淨機
  
  ////fc-37
  if(fc_A0 > 800)                          //讀取fc-37感測器的A0判斷"下雨"
  {
    digitalWrite(12,HIGH);                 //LED變亮--除濕機
    Open1_Close0=0;                        //關窗Close
  }
  else                                     //讀取fc-37感測器的A0判斷"未下雨"
  {
    digitalWrite(12,LOW);                  //LED變暗
    ////MQ-135(室內0)
    if (M135_A1 > 500)                       //檢測到有害氣體
    { 
      digitalWrite(13, HIGH);                //LED變亮--空氣清淨機
      digitalWrite(11, HIGH);                //LED變亮--抽風機
      Open1_Close0=1;                        //開窗Open
    }
    else
    { 
      digitalWrite(13, LOW);                   //LED變暗--空氣清淨機
      digitalWrite(11, LOW);                   //LED變暗--抽風機
      ////MQ-7(室內0)
      if (M7_A0 > 180)                         //檢測到有害氣體
      { 
        digitalWrite(13, HIGH);                //LED變亮--空氣清淨機
        digitalWrite(11, HIGH);                //LED變亮--抽風機
        Open1_Close0=1;                        //開窗Open
      } 
      else
      { 
        digitalWrite(13, LOW);                 //LED變暗--空氣清淨機
        digitalWrite(11, LOW);                 //LED變暗--抽風機
        ////MQ-135(室外1)
        if (M135_A0 > 500)                     //檢測到有害氣體
        { 
          digitalWrite(13, HIGH);              //LED變亮--空氣清淨機
          Open1_Close0=0;                      //關窗Close
        }
       else
        { 
          digitalWrite(13, LOW);               //LED變暗--空氣清淨機
          Open1_Close0=1;                      //開窗Open
        }
      }
    }
  }

  if(Open1_Close0==1)                       //開關窗狀態
  {
    Serial.write('1');
    mySerial.write('1');
  }
  else if(Open1_Close0==0)
  {
    Serial.write('0');
    mySerial.write('0');
  }

  if(fc_A0 > 800)                           //'1'有下雨，'0'沒下雨
    {
      Serial.write('1');
      mySerial.write('1');
    }
  else
    {
      Serial.write('0');
      mySerial.write('0');
    }

  if (M135_A1 > 500||M7_A0 > 180)           //'1'室內有有害氣體，'0'室內無有害氣體
    {
      Serial.write('1');
      mySerial.write('1');
    }
  else
    {
      Serial.write('0');
      mySerial.write('0');
    }
 
  if (M135_A0 > 500)                       //'1'室外有有害氣體，'0'室外無有害氣體
    { 
      Serial.write("1\n");
      mySerial.write('1');
    }
  else
    {
      Serial.write("0\n");
      mySerial.write('0');
    }
    delay(12500);
}
