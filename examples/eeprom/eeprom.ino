/*
   EEPROM 쓰기, 읽기 예제
   2번 핀에 연결한 버튼을 누르고 전원을 켜면 EEPROM의 0번지에 1이라는 값을 기록한다.
   0번지 부터 1023번지까지 값을 읽어서 시리얼 모니터에 출력한다.

   EEPROM 크기(용량)은 보드별로 아래와 같다.
    - Arduno Duemilanove: 512b EEPROM storage.
    - Arduino Uno:        1kb EEPROM storage.
    - Arduino Mega:       4kb EEPROM storage.
*/
#include <EEPROM.h>

int writeModePin = 2;
int address = 0;
byte value;

void setup() {
  pinMode(writeModePin, INPUT_PULLUP); // 기록모드 버튼 핀

  // 2번 핀에 연결된 버튼을 누르고 전원을 켜면
  if (digitalRead(writeModePin) == LOW) {
    // EEPROM 0번지에 1이라는 값 기록
    EEPROM.write(0, 1);
  }

  // 시리얼 모니터 설정
  Serial.begin(9600);
  while (!Serial) {
    ; // 시리얼모니터가 연결될 때까지 대기한다.
  }
}

void loop() {
  // EEPROM 각 번지의 값을 읽는다.
  value = EEPROM.read(address);

  Serial.print(address);
  Serial.print("\t");
  Serial.print(value, DEC);
  Serial.println();

  address++;
  if (address == EEPROM.length()) {
    address = 0;
  }

  delay(100);
}
