#include <IRremote.hpp>

#define IR_SEND_PIN 9
#define BTN_ON_PIN 7
#define BTN_OFF_PIN 6

// 에어컨 ON/OFF 신호 데이터
const uint8_t acOnRawTicks[147] = {88, 87, 11, 31, 12, 31, 12, 31, 12, 31, 11, 11, 10, 11, 10, 33, 11, 10, 11, 11, 11, 10, 11, 10, 12, 10, 11, 32, 11, 32, 11, 10, 11, 32, 11, 10, 12, 10, 11, 10, 11, 11, 11, 10, 11, 11, 11, 31, 12, 31, 11, 32, 12, 31, 11, 32, 10, 33, 11, 32, 11, 32, 11, 10, 11, 11, 10, 11, 11, 11, 10, 11, 11, 10, 12, 10, 11, 10, 11, 11, 11, 31, 12, 10, 11, 32, 11, 10, 11, 32, 11, 11, 10, 11, 11, 11, 11, 10, 10, 11, 11, 11, 11, 11, 10, 11, 11, 10, 11, 10, 12, 10, 11, 32, 11, 10, 12, 10, 10, 11, 11, 11, 10, 11, 11, 10, 12, 10, 11, 10, 11, 11, 11, 31, 12, 10, 11, 32, 11, 11, 10, 11, 11, 10, 12, 10, 11};
const uint8_t acOffRawTicks[147] = {91, 83, 12, 31, 12, 31, 12, 31, 12, 30, 12, 10, 12, 9, 11, 32, 12, 10, 11, 10, 12, 10, 12, 9, 12, 10, 11, 31, 14, 29, 11, 11, 11, 31, 12, 10, 12, 10, 11, 10, 12, 9, 12, 10, 11, 10, 12, 31, 12, 31, 12, 31, 12, 31, 11, 31, 12, 32, 11, 31, 12, 31, 12, 10, 11, 10, 11, 10, 12, 10, 12, 9, 12, 10, 11, 10, 12, 9, 12, 10, 12, 31, 11, 10, 12, 31, 12, 10, 14, 28, 12, 10, 12, 9, 12, 10, 12, 9, 11, 10, 12, 10, 12, 9, 11, 11, 12, 9, 12, 31, 12, 31, 12, 31, 11, 10, 12, 10, 12, 9, 12, 10, 11, 10, 12, 9, 12, 10, 12, 10, 11, 10, 11, 31, 12, 10, 12, 31, 12, 9, 12, 31, 12, 31, 11, 10, 12};

void acOn() {
  IrSender.sendRaw(acOnRawTicks, sizeof(acOnRawTicks) / sizeof(acOnRawTicks[0]), NEC_KHZ);
}

void acOff() {
  IrSender.sendRaw(acOffRawTicks, sizeof(acOffRawTicks) / sizeof(acOffRawTicks[0]), NEC_KHZ);
}

void setup() {
  pinMode(BTN_ON_PIN, INPUT_PULLUP);
  pinMode(BTN_OFF_PIN, INPUT_PULLUP);
  pinMode(IR_SEND_PIN, OUTPUT);

  IrSender.begin(IR_SEND_PIN, DISABLE_LED_FEEDBACK);
  delay(100);
}

void loop() {
  if (digitalRead(BTN_ON_PIN) == LOW) {
    acOn();
  } else if (digitalRead(BTN_OFF_PIN) == LOW) {
    acOff();
  }
  delay(150);
}
