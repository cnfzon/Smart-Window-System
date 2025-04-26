HardwareSerial uart1(1);

#define TXD_PIN 17
#define RXD_PIN 16

void setup(){
  Serial.begin(115200);  // 設定速率
  uart1.begin(115200,SERIAL_8N1,RXD_PIN,TXD_PIN);
}

void loop() {
  if(uart1.available()>0)
  {
   String mag = uart1.readString();
   Serial.printf("收到資料:%s\n",mag);

   if(mag.substring(0, 1)=="1") {Serial.printf("1");}
   else                       {Serial.printf("2");}
   if(mag.substring(1, 2)=="1") {Serial.printf("3");}
   else                       {Serial.printf("4");}
   if(mag.substring(2, 3)=="1") {Serial.printf("5");}
   else                       {Serial.printf("6");}
   if(mag.substring(3, 4)=="1") {Serial.printf("7");}
   else                       {Serial.printf("8");}
  }
  delay(10);
  }

