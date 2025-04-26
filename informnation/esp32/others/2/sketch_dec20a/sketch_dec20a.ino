#include <WiFi.h>  //是用ESP32,要記得修正為WiFi.h
#include <WiFiClient.h>
#include <TridentTD_LineNotify.h> 
#define  LINE_TOKEN "5LBE5L1V9VKbUihaLyCyqRb7wGQWYgkovhJjWsjtqg4"
#define WIFI_SSID "chi"
#define WIFI_PASS "N127059992"
#include <hardwareserial.h>

int count=0,d=0;
int da[9]; //8bit data+1bit end
String win="關窗",rain="未下雨",in="無",out="無";

WiFiClient client; //網路連線物件

void setup(){
  Serial.begin(115200);  // 設定速率
  Serial2.begin(115200,SERIAL_8N1,16,17);
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
  Serial.println("9\n");

  da[d]=Serial2.read();
    
    if(da[0]==1) {win="開窗"; Serial.println("1");}
    else         {win="關窗"; Serial.println("2");}
    if(da[1]==1) {rain="下雨"; Serial.println("3");}
    else         {rain="未下雨"; Serial.println("2");}
    if(da[2]==1) {in="有"; Serial.println("5");}
    else         {in="無"; Serial.println("6");}
    if(da[3]==1) {out="有"; Serial.println("7");}
    else         {out="無"; Serial.println("8");}
    
    ++d;
  /*if(Serial1.available()>0)
  {
    da[d]=Serial2.read();
    
    if(da[0]==1) {win="開窗"; Serial.println("1");}
    else         {win="關窗"; Serial.println("2");}
    if(da[1]==1) {rain="下雨"; Serial.println("3");}
    else         {rain="未下雨"; Serial.println("2");}
    if(da[2]==1) {in="有"; Serial.println("5");}
    else         {in="無"; Serial.println("6");}
    if(da[3]==1) {out="有"; Serial.println("7");}
    else         {out="無"; Serial.println("8");}
    
    ++d;
    if(d>=8) 
    {
      LINE.notify("\n窗戶狀態:" +win+ "\n天氣狀況:" +rain+ "\n室內有害氣體偵測:" +in+ "\n室外有害氣體偵測:" +out);
      d=0;
    }*/
  }
}
