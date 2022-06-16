#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// 0x27 I2C 주소를 가지고 있는 16x2 LCD객체를 생성. (0x3F 또는  0x27, LCD마다 다름)
LiquidCrystal_I2C lcd(0x27, 16, 2);

unsigned long now = 0;
unsigned long prev = 0;

char buff[16];

int h = 0;
int m = 0;
int s = 0;

void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);

  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
}

void loop() {
  now = millis(); // 현재의 밀리초

  delay(100);

  if (digitalRead(3) == LOW) {
    h++;
    s = 0;
    print_lcd();
  }

  if (digitalRead(2) == LOW) {
    m++;
    s = 0;

    if (m >= 60) {
      m = 0;
    }

    print_lcd();
  }

  if  (now - prev >= 1000) {
    prev = now;
    // 매 1초마다 실행되는 부분
    ++s;

    // 60초가 되면 1분 증가
    if (s >= 60) {
      ++m;
      s = 0;
    }

    // 60분이 되면 1시간 증가
    if (m >= 60) {
      ++h;
      m = 0;
    }

    if (h >= 24) {
      h = 0;
    }

    print_lcd();
  }
}

char* ampm;

void print_lcd() {
  lcd.setCursor(0, 0);

  if (h > 12) {
    ampm = "PM";
  } else {
    ampm = "AM";
  }

  if (h % 12 == 0) {
    sprintf(buff, "%s 12:%02d:%02d", ampm, m, s);
  } else {
    sprintf(buff, "%s %02d:%02d:%02d", ampm, h % 12, m, s);
  }

  lcd.print(buff);
}
