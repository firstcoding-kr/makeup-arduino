#include <IRremote.hpp>
#define DECODE_NEC // NEC 포맷을 활성화 (대부분의 TV리모컨은 NEC포맷을 사용한다.)
#define IR_RECEIVE_PIN 3 // IR센서 연결 핀을 정의한다.

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
}

void loop() {
  // IR신호가 수신되면 수신 내용을 출력한다.
  if (IrReceiver.decode()) {
    IrReceiver.printIRResultShort(&Serial);
    Serial.println();

    // 다음 명령을 기다리도록 설정한다.
    IrReceiver.resume();

    // 리모컨의 코드값에 맞는 명령을 수행한다.
    if (IrReceiver.decodedIRData.command == 0x10) {
      // do something
    } else if (IrReceiver.decodedIRData.command == 0x11) {
      // do something else
    }
  }
}
