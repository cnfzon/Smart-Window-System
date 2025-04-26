#include <WiFi.h>  //是用ESP32,要記得修正為WiFi.h
#include <WiFiClient.h>
#include <TridentTD_LineNotify.h> 
#define  LINE_TOKEN "5LBE5L1V9VKbUihaLyCyqRb7wGQWYgkovhJjWsjtqg4"
#define WIFI_SSID "chi"
#define WIFI_PASS "N127059992"

WiFiClient client; //網路連線物件

void setup(){
  Serial.begin(115200);  // 設定速率
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

   LINE.notify("  \n窗戶狀態: \n天氣狀況: \n一氧化碳偵測(室內): \n有害偵測(室內): \n有害偵測(室外): "); //開關窗戶的狀態 if開窗 關窗
   delay(1000);
}
/* LINE.notify("  天氣狀況: \n"); //下雨　未下雨
   LINE.notify("  一氧化碳偵測(室內): \n"); //有無?　ｍｑ７
   LINE.notify("  有害偵測(室內): \n");//有無?　ｍｑ１３５
   LINE.notify("  有害偵測(室外): ");//有無?　ｍｑ１３５*/
