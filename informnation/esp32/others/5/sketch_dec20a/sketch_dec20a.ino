#include <WiFi.h>  //是用ESP32,要記得修正為WiFi.h
#include <WiFiClient.h>
#include <TridentTD_LineNotify.h> 
#define  LINE_TOKEN "5LBE5L1V9VKbUihaLyCyqRb7wGQWYgkovhJjWsjtqg4"
#define WIFI_SSID "chi"
#define WIFI_PASS "N127059992"

HardwareSerial uart1(1);

#define TXD_PIN 17
#define RXD_PIN 16
String win="關窗",rain="未下雨",in="無",out="無";

WiFiClient client; //網路連線物件

void setup(){
  Serial.begin(115200);  // 設定速率
  uart1.begin(115200,SERIAL_8N1,RXD_PIN,TXD_PIN);
  WiFi.mode(WIFI_STA);   // 進行無線網路連接
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  //等待無線網路連接
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
  LINE.setToken(LINE_TOKEN); //設定Line Token權杖
}

void loop() {
  if(uart1.available()>0)
  {
   String mag = uart1.readString();
   Serial.printf("收到資料:%s\n",mag);

   if(mag.substring(0, 1)=="1") {win="開窗";}
   else                         {win="關窗";}
   if(mag.substring(1, 2)=="1") {rain="下雨";}
   else                         {rain="未下雨";}
   if(mag.substring(2, 3)=="1") {in="有";}
   else                         {in="無";}
   if(mag.substring(3, 4)=="1") {out="有";}
   else                         {out="無";}
  }
  delay(10);
  LINE.notify("\n窗戶狀態:" +win+ "\n天氣狀況:" +rain+ "\n室內有害氣體偵測:" +in+ "\n室外有害氣體偵測:" +out);
  }

