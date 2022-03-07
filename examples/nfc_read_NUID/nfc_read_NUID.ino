#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN); // MFRC522 객체를 만든다.
MFRC522::MIFARE_Key key; 

byte nuidPICC[4]; // 태그 ID를 저장할 배열

void setup() { 
  Serial.begin(9600);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522 
}
 
void loop() {
  // 태그가 인식되지 않으면 아무 동작 수행 안함
  if ( ! rfid.PICC_IsNewCardPresent())
    return;

  // 카드 ID가 정상적으로 읽히지 않은 경우도 인식 안함
  if ( ! rfid.PICC_ReadCardSerial())
    return;

  if (rfid.uid.uidByte[0] != nuidPICC[0] || 
    rfid.uid.uidByte[1] != nuidPICC[1] || 
    rfid.uid.uidByte[2] != nuidPICC[2] || 
    rfid.uid.uidByte[3] != nuidPICC[3] ) {
    
    // 읽은 태그 id를 nuidPICC 배열에 복사
    for (byte i = 0; i < 4; i++) {
      nuidPICC[i] = rfid.uid.uidByte[i];
    }
   
    Serial.println("태그 인식함:");
    Serial.print("HEX: ");
    printHex(rfid.uid.uidByte, rfid.uid.size);
    Serial.println();
    Serial.print("DEC: ");
    printDec(rfid.uid.uidByte, rfid.uid.size);
    Serial.println();
  }
  else {
    Serial.println("이미 인식한 태그입니다.");
  }

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

/**
 * buffer 배열의 내용을 16진수로 출력하는 함수
 */
void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

/**
 * buffer 배열의 내용을 10진수로 출력하는 함수
 */
void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
  }
}
