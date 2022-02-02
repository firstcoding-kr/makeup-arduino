// 해리포터 ost
int melodyData[] = {494, 659, 784, 740, 659, 987, 880, 740, 494, 659, 784, 740, 587, 698, 494, 494, 659, 784, 740, 659, 987, 1175, 1109, 1047, 880, 1047, 987, 880, 494, 784, 659};
int durations[] = {4, 4, 8, 8, 4, 4, 8, 4, 4, 8, 8, 4, 4, 2, 8, 8, 8, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4};
int buzzerPin = 11;

//멜로디 재생 함수
void playMelody()
{
  int len = 0;
  int dur = 0;
  int i = 0;

  len = sizeof(melodyData) / sizeof(int); // melodyData의 데이터 갯수
  for (i = 0; i < len; i++)
  {
    dur = 1000 / durations[i];
    tone(buzzerPin, melodyData[i], dur);
    delay(dur * 1.3); // 적당한 배속으로 delay시킨다.
    noTone(buzzerPin);
  }
}

void setup() {
  pinMode(buzzerPin, OUTPUT);
  playMelody();
}

void loop() {
}
