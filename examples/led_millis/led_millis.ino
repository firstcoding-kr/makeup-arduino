const int ledPin = 13; // LED 핀 번호 상수 정의
const int bzPin = 12;  // Buzzer 핀 번호 상수 정의

unsigned long prevLedMillis = 0; // LED 측정 기준시각 저장할 변수
unsigned long prevBzMillis = 0;  // Buzzer 측정 기준시각 저장할 변수
int ledState = LOW; // LED 상태
int bzState = LOW;  // Buzzer 상태

void setup() {
  pinMode(ledPin, OUTPUT); // Led핀 출력으로 설정
  pinMode(bzPin, OUTPUT); // Buzzer핀 출력으로 설정
}

void blinkPin(int pin,)

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - prevLedMillis >= 500 && ledState == LOW) {
    prevLedMillis = currentMillis;

    ledState = HIGH;
    digitalWrite(ledPin, ledState);
  } else if (currentMillis - prevLedMillis >= 2000 && ledState == HIGH) {
    prevLedMillis = currentMillis;

    ledState = LOW;
    digitalWrite(ledPin, ledState);
  }

  if (currentMillis - prevBzMillis >= 3000 && bzState == LOW) {
    prevBzMillis = currentMillis;

    bzState = HIGH;
    digitalWrite(bzPin, bzState);
  } else if (currentMillis - prevBzMillis >= 1000 && bzState == HIGH) {
    prevBzMillis = currentMillis;

    bzState = LOW;
    digitalWrite(bzPin, bzState);
  }
}
