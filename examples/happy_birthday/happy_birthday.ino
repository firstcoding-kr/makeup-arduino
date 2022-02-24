int btnPin = 3;
int buzzerPin = 6;
char* song[] = {"솔", "솔", "라", "솔", "도", "도", "시", "솔", "솔", "라", "솔", "레", "레", "도", "솔", "솔", "쏠", "미", "도", "시", "라", "파", "파", "미", "도", "레", "레", "도"};

int getHz(char* name) {
  if (!strcmp("도", name)) return 523;
  else if (!strcmp("레", name)) return 587;
  else if (!strcmp("미", name)) return 659;
  else if (!strcmp("파", name)) return 699;
  else if (!strcmp("솔", name)) return 784;
  else if (!strcmp("라", name)) return 880;
  else if (!strcmp("시", name)) return 988;
  else if (!strcmp("쏠", name)) return 1568;

  return 0;
}

void playMelody()
{
  int len = sizeof(song) / sizeof(char*);

  for (int i = 0; i < len; i++)
  {
    tone(buzzerPin, getHz(song[i]), 500);
    delay(300);
    noTone(buzzerPin);
  }
}

void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(btnPin, INPUT);
}

void loop () {
  if (digitalRead(btnPin) == HIGH) {
    playMelody();
  }
}
