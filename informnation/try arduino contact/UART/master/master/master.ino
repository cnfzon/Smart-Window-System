void setup() {
  Serial.begin(9600);  //設定通訊速率
}

void loop() {
  Serial.write("TC");  //傳輸讀取的訊號
  delay(500);
}
