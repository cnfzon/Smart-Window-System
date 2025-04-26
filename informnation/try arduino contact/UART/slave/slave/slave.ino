void setup() {

  Serial.begin(9600);  //設定通訊速率

}

 

void loop() {

  while (!Serial.available()) {}   //直到暫存器出現訊號才跳出迴圈

  Serial.write(Serial.read());  //傳輸讀取的訊號
  Serial.println(" ");
  while (Serial.available()>0) {   //如果暫存器有訊號則不斷讀取直到沒有
    Serial.read();
  }  

}
