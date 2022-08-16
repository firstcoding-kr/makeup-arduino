int rows[] = {0, 9, 14, 8, 12, 1, 7, 2, 5}; // +핀
int cols[] = {0, 13, 3 , 4 , 10, 6, 11, 15, 16}; // -핀
int arduinoPin[] = {0, 5, 4, 3, 2, A0, A1, A2, A3, 13, 12, 11, 10, 9, 8, 7, 6}; // 총 16핀

void resetLeds() {
  for (int i = 1; i <= 8; i++) {
    digitalWrite(arduinoPin[rows[i]], LOW);
    digitalWrite(arduinoPin[cols[i]], HIGH);
  }
}

void testLeds() {
  for (int r = 1; r <= 8; r++) {
    for (int c = 1; c <= 8; c++) {
      digitalWrite(arduinoPin[rows[r]], HIGH);
      digitalWrite(arduinoPin[cols[c]], LOW);
      delay(100);
      resetLeds();
    }
  }
}

void testLedsOn() {
  for (int i = 1; i <= 8; i++) {
    digitalWrite(arduinoPin[rows[i]], HIGH);
    digitalWrite(arduinoPin[cols[i]], LOW);
  }
}

void setup() {
  // pinMode 세팅
  for (int i = 1; i <= 16; i++) {
    pinMode(arduinoPin[i], OUTPUT);
  }
}

void loop() {
  resetLeds();
  testLeds();
  delay(1000);
  testLedsOn();
  delay(10000);
}
