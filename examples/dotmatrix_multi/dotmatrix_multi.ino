#define MAX_LEN 32

int rows[] = {0, 9, 14, 8, 12, 1, 7, 2, 5}; // +핀
int cols[] = {0, 13, 3 , 4 , 10, 6, 11, 15, 16}; // -핀
int arduinoPin[] = {0, 5, 4, 3, 2, A0, A1, A2, A3, 13, 12, 11, 10, 9, 8, 7, 6}; // 총 16핀

unsigned long t = 0;
int xOffset = 0;

// 전광판에 출력할 모양을 2차원 배열로 설정한다.
int shape[8][MAX_LEN] = {
  {1, 1, 0, 0, 0, 1, 1, 0,  0, 1, 1, 1, 1, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 1, 1, 0, 0, 1, 1, 0},
  {1, 1, 0, 0, 0, 1, 1, 0,  0, 0, 1, 1, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  1, 0, 0, 1, 1, 0, 0, 1},
  {1, 1, 0, 0, 0, 1, 1, 0,  0, 0, 1, 1, 0, 0, 0,  0, 0, 1, 1, 0, 0, 0, 0,  1, 0, 0, 0, 0, 0, 0, 1},
  {1, 1, 1, 1, 1, 1, 1, 0,  0, 0, 1, 1, 0, 0, 0,  1, 1, 1, 1, 1, 0, 0, 1,  1, 0, 0, 0, 0, 0, 0, 1},
  {1, 1, 1, 1, 1, 1, 1, 0,  0, 0, 1, 1, 0, 0, 0,  1, 1, 0, 0, 1, 1, 1, 1,  0, 1, 0, 0, 0, 0, 1, 0},
  {1, 1, 0, 0, 0, 1, 1, 0,  0, 0, 1, 1, 0, 0, 0,  0, 0, 0, 0, 0, 1, 1, 0,  0, 1, 0, 0, 0, 0, 1, 0},
  {1, 1, 0, 0, 0, 1, 1, 0,  0, 0, 1, 1, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 1, 0, 0, 1, 0, 0},
  {1, 1, 0, 0, 0, 1, 1, 0,  0, 1, 1, 1, 1, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 1, 1, 0, 0, 0}
};

void resetLeds() {
  for (int i = 1; i <= 8; i++) {
    digitalWrite(arduinoPin[rows[i]], LOW);
    digitalWrite(arduinoPin[cols[i]], HIGH);
  }
}

void printShape() {
  for (int x = 0; x < 8; x++) {
    resetLeds();
    int c = x + xOffset;

    digitalWrite(arduinoPin[cols[x+1]], LOW);

    for (int y = 0; y < 8; y++) {
      if (c < MAX_LEN && c >= 0) {
        digitalWrite(arduinoPin[rows[y + 1]], shape[y][c]);
      }
    }
    delay(1);
  }
}

void setup() {
  for (int i = 1; i <= 16; i++) {
    pinMode(arduinoPin[i], OUTPUT);
  }
  pinMode(A5, INPUT);
  Serial.begin(9600);
}

void loop() {
  if (millis() - t > 100) {
    t = millis();
    if (++xOffset >= MAX_LEN) {
      xOffset = -8;
    }
  }

  printShape();
}
