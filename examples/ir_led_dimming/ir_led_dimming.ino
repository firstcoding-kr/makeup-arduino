#include <IRremote.hpp>
#define DECODE_NEC
#define IR_RECEIVE_PIN 3

int ledStatus = LOW;
int ledBright = 255;
int ledPin = 10;

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, DISABLE_LED_FEEDBACK);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledStatus);
}

void loop() {
  if ( !IrReceiver.decode() ) {
    return;
  }
  
  // 리모컨이 수신되면
  Serial.print("address: ");
  Serial.print(IrReceiver.decodedIRData.address);
  Serial.print(" cmd: ");
  Serial.println(IrReceiver.decodedIRData.command );

  // 전원 ON/OFF
  if (IrReceiver.decodedIRData.command == 70) {
    if (ledStatus == HIGH) {
      digitalWrite(ledPin, LOW);
      ledStatus = LOW;
    } else {
      analogWrite(ledPin, ledBright);
      ledStatus = HIGH;
    }
    delay(300);
  } else if (ledStatus == HIGH and IrReceiver.decodedIRData.command == 21) {
    // 밝아져라
    ledBright += 50;

    if (ledBright > 255) {
      ledBright = 255;
    }
    analogWrite(ledPin, ledBright);
  } else if (ledStatus == HIGH and IrReceiver.decodedIRData.command == 7) {
    // 어두워져라
    ledBright -= 50;
    if (ledBright < 10) {
      ledBright  = 10;
    }    
    analogWrite(ledPin, ledBright);
    delay(300);
  }
  IrReceiver.resume();
}
