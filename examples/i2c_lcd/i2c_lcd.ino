// LCD를 쉽게 제어하기 위한 라이브러리를 추가.
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// 0x27 I2C 주소를 가지고 있는 16x2 LCD객체를 생성. (0x3F 또는  0x27, LCD마다 다름)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // I2C LCD를 초기화
  lcd.init();
  // I2C LCD의 백라이트를 켬
  lcd.backlight();
}

void loop() {
    lcd.setCursor(0 /* 0번째 셀 */, 0 /* 0번재 줄 */);
    lcd.print(" Hello World!"); // 문구를 출력합니다.
    delay(2000);
    lcd.setCursor(0, 1); // 1번째 줄로 커서 이동
    lcd.print(" How are you?"); // 문구 출력
    delay(2000);
    lcd.clear(); // LCD 내용 삭제
    delay(1000);
}
