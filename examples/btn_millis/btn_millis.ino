const int btnPin = 8;
const int bzPin = 13;
unsigned long prevBtnMillis = 0;
unsigned long prevBzMillis = 0;
int bzState = LOW; // 버저의 상태
int bzCount = 3; // 버저가 울린 횟수를 카운트할 변수
int lastBtnState = HIGH;

void setup() {
  pinMode(bzPin, OUTPUT);
  pinMode(btnPin, INPUT_PULLUP);
}

void loop() {
  // 버튼의 3초 누름을 감지
  if (digitalRead(btnPin) == LOW) {
    if (millis() - prevBtnMillis >= 3000 && lastBtnState == HIGH) {
      bzCount = 0;
      lastBtnState = LOW;
    }
  } else {
    prevBtnMillis = millis();
    lastBtnState = HIGH;
  }

  // 카운트가 3미만이라면 부저 삑삑
  if (bzCount < 3) {
    if (millis() - prevBzMillis >= 600 && bzState == LOW) {
      prevBzMillis = millis();
      bzState = HIGH;
      digitalWrite(bzPin, bzState);
    } else if (millis() - prevBzMillis >= 200 && bzState == HIGH) {
      prevBzMillis = millis();
      bzState = LOW;
      digitalWrite(bzPin, bzState);
      
      bzCount++; // 버저가 울린 횟수 카운트
    }
  }
}
