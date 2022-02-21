int led = 5;
int buzz = 6;
int btn = 3;

void setup() {
  pinMode(buzz, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(btn, INPUT);
}

void sirenOne() {
  for (int hz = 440; hz < 1000; hz += 25) {
    tone(buzz, hz, 50);
    delay(5);
  }

  for (int hz = 1000; hz > 440; hz -= 25) {
    tone(buzz, hz, 50);
    delay(5);
  }

  noTone(buzz);
}

void sirenLong() {
  for (int hz = 440; hz < 2000; hz += 10) {
    tone(buzz, hz, 50);
    delay(10);
  }

  for (int hz = 2000; hz > 440; hz -= 10) {
    tone(buzz, hz, 50);
    delay(10);
  }

  noTone(buzz);
}

void loop() {
  if (digitalRead(btn) == HIGH) {
    sirenOne();
  }
}
