int trig = 8; // 초음파 송신
int echo = 9; // 수신
int led = 13;

void setup() {
  Serial.begin(9600);

  //초음파 송신부-> OUTPUT, 초음파 수신부 -> INPUT,  LED핀 -> OUTPUT
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  // 초음파 센서 초기화
  digitalWrite(trig, LOW);
  digitalWrite(echo, LOW);
  delayMicroseconds(2);

  // trig핀에 10us 동안 HIGH를 주면 센서가 8번의 초음파를 발사한다.
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  //echo핀이 HIGH신호를 유지하고 있는 동안의 시간을 측정
  unsigned long duration = pulseIn(echo, HIGH);

  // 초음파의 속도는 초당 340미터 = 29마이크로초 당 1센치를 이동.
  // 따라서, 초음파의 이동 거리 = duration(왕복에 걸린시간) / 29 / 2
  float distance = duration / 29.0 / 2.0;

  Serial.print(distance);
  Serial.println("cm");

  delay(500);
}
