#include <Arduino.h>
//#define RAW_BUFFER_LENGTH  750 // 에어컨 사용시
#define MARK_EXCESS_MICROS 20
#define INFO
#include <IRremote.hpp>
#define IR_RECEIVE_PIN 3

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);

  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

  Serial.print(F("Ready to receive IR signals of protocols: "));
  printActiveIRProtocols(&Serial);
  Serial.print(F("at pin "));
  Serial.println(IR_RECEIVE_PIN);
}

void loop() {
  if (IrReceiver.decode()) {  // IR 수신
    // Check if the buffer overflowed
    if (!(IrReceiver.decodedIRData.flags & IRDATA_FLAGS_WAS_OVERFLOW)) {
      Serial.println();
      Serial.println();
      IrReceiver.printIRResultShort(&Serial);
      Serial.println();
      Serial.println(F("Raw result in internal ticks (50 us) - with leading gap"));
      IrReceiver.printIRResultRawFormatted(&Serial, false);
      Serial.println(F("Raw result in microseconds - with leading gap"));
      IrReceiver.printIRResultRawFormatted(&Serial, true);
      Serial.println();
      Serial.print(F("Result as internal ticks (50 us) array - compensated with MARK_EXCESS_MICROS="));
      Serial.println(MARK_EXCESS_MICROS);
      IrReceiver.compensateAndPrintIRResultAsCArray(&Serial, false);
      Serial.print(F("Result as microseconds array - compensated with MARK_EXCESS_MICROS="));
      Serial.println(MARK_EXCESS_MICROS);
      IrReceiver.compensateAndPrintIRResultAsCArray(&Serial, true);
      IrReceiver.printIRResultAsCVariables(&Serial);

      IrReceiver.compensateAndPrintIRResultAsPronto(&Serial);
    }

    IrReceiver.resume();
  }
}
