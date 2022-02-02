const int btnPin = 8;
const int bzPin = 13;
unsigned long prevBtnMillis = 0;
unsigned long prevBzMillis = 0;
int lastBtnState = HIGH;

void setup() {
  pinMode(bzPin, OUTPUT);
  pinMode(btnPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // 버튼의 3초 누름을 감지
  if (digitalRead(btnPin) == LOW) {
    if (millis() - prevBtnMillis >= 3000 && lastBtnState == HIGH) {
      lastBtnState = LOW;
      
      // 버저를 3번 울린다.
      for (int i = 0; i < 3; i++) {
        digitalWrite(bzPin, HIGH);
        delay(200);
        digitalWrite(bzPin, LOW);
        delay(600);
      }
    }
  } else {
    prevBtnMillis = millis();
    lastBtnState = HIGH;
  }
}
