int led=5;
//int buzz=4;
int get_D3 = 3;
int get_A0 = A0;

void setup(){
  pinMode(led,OUTPUT);  
  //pinMode(buzz, OUTPUT);  
  pinMode(get_D3, INPUT);
  Serial.begin(9600);  
}
void loop(){

  int value = analogRead(A0);    //從A0讀取感測值

  Serial.print(value);    //
  Serial.print("   ");    //在監控視窗印出從A0讀取的值

  if(digitalRead(get_D3) == LOW)//讀取fc-37感測器的D0輸出"低態"
  {
    Serial.println("Digital value : wet"); //在監控視窗印出"wet"
    digitalWrite(led,HIGH);     //LED變亮
  }
  else//讀取fc-37感測器的D0輸出"高態"
  {
    Serial.println("Digital value : dry"); //在監控視窗印出"dry"
    digitalWrite(led,LOW);     //LED變暗
  }
  delay(1000);
}
