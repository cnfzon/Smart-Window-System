int host;    //pin 7
int servant; //pin 8
int num=0;

void setup() {
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  Serial.begin(19200);
}

void loop() {
  host    = digitalRead(7);
  servant = digitalRead(7);

  //Serial.println("下雨");
  /*digitalWrite(7,LOW);
  if(servant == HIGH)
  {
    Serial.println("接收中");
  }
  if(servant == LOW)
  {
    Serial.println("停止接收");
  }
  delay(200);*/
  if(num%2 == 0) digitalWrite(7,HIGH);
  if(num%2 == 1) digitalWrite(7,LOW);
  if(servant == HIGH)
  {
    Serial.println("接收中");
    num+=1;
  }
  if(servant == LOW)
  {
    Serial.println("停止接收");
    num+=1;
  }
  delay(200);
}
