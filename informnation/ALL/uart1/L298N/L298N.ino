// 右馬達控制設定
const byte IN1 = 9;
const byte IN2 = 8;
const byte en_A = 10;
// 左馬達控制設定
const byte IN3 = 12;
const byte IN4 = 13;
const byte en_B = 11;

void setup() {
  Serial.begin(9600);
  pinMode(IN3, OUTPUT);  //pin9
  pinMode(IN4, OUTPUT);  //pin8
  pinMode(en_B, OUTPUT); //pin10
  pinMode(IN1, OUTPUT);  //pin12
  pinMode(IN2, OUTPUT);  //pin13
  pinMode(en_A, OUTPUT); //pin11
  pinMode(M_io, INPUT);
}

void loop() {

  while (!Serial.available()) {}   //直到暫存器出現訊號才跳出迴圈

  Serial.write(Serial.read());  //傳輸讀取的訊號

  //<---window開窗
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);//1H2L 收線
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);//3L4H 放線
  delay(10500); 
  //reset 狀態
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);// L stop
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);// R stop
  delay(2000);

  while (Serial.available()>0)   //如果暫存器有訊號則不斷讀取直到沒有
  { 
    Serial.read();
  }  
}
