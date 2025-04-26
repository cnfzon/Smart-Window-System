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

   LINE.notify("  這裡的文字會出現在Line上面"); //發送訊息到Line上面
   delay(1000);
  
}
