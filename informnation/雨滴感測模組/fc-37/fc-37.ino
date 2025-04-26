int DI = 4;      //感測器模組 DO 連接 Arduino pin 4
int AI = A0;     //感測器模組 AO 連接 Arduino pin A0
int led =13;     //LED 長腳連接 Arduino pin 13
int AnalogIn;    //感測器類比輸出訊號值

void setup()
{
  pinMode(DI, INPUT);
  pinMode(AI, INPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
if(digitalRead(DI) == LOW)                  //當感測器上有殘存的雨滴時，感測器數位輸出訊號為 0，序列埠螢幕印出 wet，點亮 LED
  {
    Serial.println("Digital value : wet"); 
    digitalWrite(led, HIGH);
    delay(10); 
  }
else
  {
    Serial.println("Digital value : dry");   //當感測器上面是乾燥的時候，數位輸出訊號為 1，序列埠螢幕印出 dry，熄滅 LED
    delay(10); 
    digitalWrite(led, LOW);
  }
AnalogIn=analogRead(AI); 
 Serial.print("Analog value : ");            //序列埠螢幕印出感測器類比輸出訊號值 
 Serial.println(AnalogIn); 
 Serial.println("");
  delay(1000);                               //每一秒鐘感測一次
}
