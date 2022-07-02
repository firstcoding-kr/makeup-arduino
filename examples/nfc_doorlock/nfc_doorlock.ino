#include <SPI.h>
#include <MFRC522.h>
#include <EEPROM.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN); // MFRC522 객체를 만든다.
MFRC522::MIFARE_Key key;

byte nuid[4]; // 태그 ID를 저장할 배열

void setup() {
  Serial.begin(9600);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522
  pinMode(3, OUTPUT);
  pinMode(4, INPUT_PULLUP);
}

void loop() {
  // 태그가 인식되지 않으면 아무 동작 수행 안함
  if ( ! rfid.PICC_IsNewCardPresent()) {
    return; // return 문을 만나 loop 함수가 종료된다.
  }

  // 카드 ID가 정상적으로 읽히지 않은 경우도 인식 안함
  if ( ! rfid.PICC_ReadCardSerial()) {
    return; // return 문을 만나 loop 함수가 종료된다.
  }

  tone(3, 4000, 200);

  // 등록기능 - 버튼을 누르면
  if (digitalRead(4) ==  LOW) {
    // 읽은 태그 id를 nuidPICC 배열에 복사
    for (byte i = 0; i < 4; i++) {
      // nuid[i] = rfid.uid.uidByte[i];
      EEPROM.write(i, rfid.uid.uidByte[i]);
    }
    okMelody();
    return;
  }

  int a = rfid.uid.uidByte[0];
  int b = rfid.uid.uidByte[1];
  int c = rfid.uid.uidByte[2];
  int d = rfid.uid.uidByte[3];

  // 카드 인식
  if ( a == EEPROM.read(0) && b == EEPROM.read(1)
       && c == EEPROM.read(2) && d == EEPROM.read(3) ) {
    Serial.println("등록된 카드입니다");
    okMelody();
  } else {
    Serial.println("미등록 카드입니다");
    denyMelody();
  }


  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

/**
   buffer 배열의 내용을 16진수로 출력하는 함수
*/
void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}


void okMelody() {
  tone(3, 1046);
  delay(300);
  tone(3, 1318);
  delay(300);
  tone(3, 1567);
  delay(500);
  noTone(3);
}

void denyMelody() {
  tone(3, 2000);
  delay(300);
  noTone(3);
  tone(3, 2000);
  delay(300);
  noTone(3);
  tone(3, 2000);
  delay(300);
  noTone(3);
}
