/******************************************************************************
* ESP07TWDWiFiCarTCPDemo.ino
* 
* WiFi 小車測試版
*
* 說明：
*   使用 ESP-07 作為微控制器與 WiFi 模組，TCP 連線方式，由手機控制兩輪小車。
*   ESP07 作為 AP 讓手機連線，之後使用 TCP 協議通訊。
*
* Hardware: 
*   > ESPESP-07 最小系統板 (不加降壓晶片)
*   > TB6612FNG 直流馬達驅動板
*   > 超迷你航模降壓模組 (to 3V5)
*
* APP:
*   > RoboRemo 使用 TCP 協議傳送與接收訊息 (ESP07 as AP Server)
*   
* Compile: 
*   > Arduino IDE V1.6.9
*   > ESP8266 Arduino V2.3.0
*
* Result: Work !
*
******************************************************************************/
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <Streaming.h>
#include "esp6612motordriver.h"

// SSID information to as a AP
#define asApSsid "myESP07"
#define asApPass "1234567"
IPAddress apIP(192, 168, 2, 1);
IPAddress apNetmask(255, 255, 255, 0);

// local port to listen for TCP packets
#define tcpPort  5000

WiFiServer tcpServer( tcpPort ); // tcp server
WiFiClient serverClient;

// variables
char cmd[100]; // stroes the command chars received from RoboRemo
int cmdIndex;
char sendbuf[10];
unsigned long lastCmdTime = 60000;
unsigned long aliveSentTime = 0;

// throttle, steering, trim
static RCCOMMAND lastrc = { 0, 0, 0 };

boolean cmdStartsWith(const char* st) { // checks if cmd starts with st
    for(int i=0; ; i++) {
        if( st[i] == 0 ) return true;
        if( cmd[i] == 0 ) return false;
        if( cmd[i] != st[i] ) return false;;
      }
      return false;
}

void exeCmd() { // executes the command from cmd
    int sw = 0x30;
    int no = 0;
    int sub = 0;

    lastCmdTime = millis();

    //* ** 左右輪差補正 ** */
    if( cmdStartsWith("lr") ) {
        sw = cmd[2] - '0';
        no = (int)( atof( cmd + 4 ) );

        // -1023 ~ -1: 向左加速
        //   1 ~ 1023: 向右加速
        // 接收到的左右偏移量數值再回傳回去顯示在 text field (tr1) 
        switch(sw) {
            case 1: // trim
                // trim < 0: 表示左邊馬達要加速
                // trim > 0: 表示右邊馬達要加速
                sprintf( sendbuf, "tr1 %d\n", no ); // OK
                serverClient.write( (const uint8_t *) &sendbuf[0], sizeof(sendbuf) );

                //* ** DEBUG ** *
                //Serial << sendbuf << ", len: " << sizeof(sendbuf) << endl << "no: " << no << endl;

                // 左右馬達之間只有一個 trim 會大於 0，另一個一定等於 0
                lastrc.trim = no;
            break;
            default:
                Serial << "lr error\n";
        }
        return ; // 儲存 trim 數值不執行
    }

    //* ** ch3: 前進或後退的速度；ch1: 向左或向右的偏轉或旋轉 ** */
    if( cmdStartsWith("ch") ) {
        sw = cmd[2] - '0';
        no = (int)( atof( cmd + 4 ) );

        switch(sw) {
            case 1: // steering
                // -1023 ~ -1：左轉或左偏
                //   1 ~ 1023：右轉或右偏
                lastrc.steering = no;
                Serial << "steering: ";
            break;
            case 3: // throttle
                // -1023 ~ -1: 後退
                //   1 ~ 1023: 前進
                lastrc.throttle = no;
                Serial << "throttle: ";
            break;
            default:
                Serial << "ch error\n";
        }
        Serial << no << endl;
    }
    // DEBUG
    Serial << "lastrc: " << lastrc.throttle << ", " << lastrc.steering << ", " << lastrc.trim << ", ";
    // 執行最新 RC 指令
    Motor_run( lastrc );
}

void setup() {
    delay(1000);

    Serial.begin( 115200 );

    Motor_init();

    Serial << "\n" << "Configurating access point..." << endl;
    WiFi.softAPConfig( apIP, apIP, apNetmask );
    WiFi.softAP( asApSsid, asApPass );

    Serial << "start tcp server..." << endl;
    tcpServer.begin(); // start tcp server

    Serial << "ESP8266 RC receiver for 2WD Car\n"
           << "SSID: " << asApSsid << "  PASS: " << asApPass << endl
           << "RoboRemo app must connect to " 
           << apIP.toString() << ":" << tcpPort << endl;
   delay(3000);
}

void loop() {

    //* - 1. 遙控訊號遺失時的處理 (2000ms)
    // if contact lost for more than half second
    if(millis() - lastCmdTime > 2000) {  
        lastrc.throttle = 0;
        lastrc.steering = 0;
        Motor_run( lastrc );
    }
    //* -- end of 1.

    //* - 2. 沒有客戶端連線時
    if( !serverClient.connected() ){
        serverClient = tcpServer.available();
        return;
    }
    //* -- end of 2.

    //* - 3. 客戶端連線
    // 儲存所有由客戶端傳過來的字元直到 '\n' 換行字元結束
    if( serverClient.available() ) {
        char c = serverClient.read();

        if( c == '\n' ) { // if it is command ending
            cmd[cmdIndex] = 0;
            exeCmd();       // execute the command
            cmdIndex = 0;   // reset the cmdIndex
        } else {
            cmd[cmdIndex] = c;  // add to the cmd buffer
            if( cmdIndex < 99 ) cmdIndex++;
        }
    }
    //* --- end of 3.

    //* - 4. 
    if( millis() - aliveSentTime > 500 ) { // every 500ms
        serverClient.write( "alive 1\n" );

        aliveSentTime = millis();
        }
    //* --- end of 4.

}
