#include <IRremote.hpp>

#define IR_SEND_PIN 3 // IR LED 핀
#define BUTTON_PIN 4 // 송신 버튼 핀

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(IR_SEND_PIN, OUTPUT);

  IrSender.begin(IR_SEND_PIN, DISABLE_LED_FEEDBACK);
}

// 보낼 리모컨 신호
uint16_t sAddress = 0x31;
uint8_t sCommand = 0x08F;
uint8_t sRepeats = 2; // 송신 반복 횟수

void loop() {
  // 버튼을 누르면 IR 신호를 송신한다.
  if (digitalRead(BUTTON_PIN) == LOW) {
    IrSender.sendNEC(sAddress, sCommand, sRepeats);
    // IrSender.sendNECRaw(0x708FCE31, sRepeats);

    delay(200);
  }
}
