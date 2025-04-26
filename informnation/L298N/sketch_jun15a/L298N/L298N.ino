// 右馬達控制設定
const byte IN1 = 9;
const byte IN2 = 8;
const byte en_A = 10;
// 左馬達控制設定
const byte IN3 = 12;
const byte IN4 = 13;
const byte en_B = 11;

int M_io=2;   //indoor=1(HIGH) outdoor=2(LOW)


void setup() {
  Serial.begin(9600);
  pinMode(IN3, OUTPUT);  //pin9
  pinMode(IN4, OUTPUT);  //pin8
  pinMode(en_B, OUTPUT); //pin10
  pinMode(IN1, OUTPUT);  //pin12
  pinMode(IN2, OUTPUT);  //pin13
  pinMode(en_A, OUTPUT); //pin11
  pinMode(M_io, INPUT);
  delay(3000);               //剛開機arduino_1輸出低態,先等雜訊跑完
}

void loop() {

  if(M_io==HIGH)              //室內
  {
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
  while(digitalRead(M_io)==HIGH);
  Serial.println("1");
  } 
  if(M_io==LOW)              //室外
  {
  //--->window關窗
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);//1L2H 放線
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);//3H4L 收線
  delay(10500);
  //reset 狀態
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);// L stop
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);// R stop
  delay(2000);
  while(digitalRead(M_io)==LOW);
  Serial.println("2");
  } 
}
