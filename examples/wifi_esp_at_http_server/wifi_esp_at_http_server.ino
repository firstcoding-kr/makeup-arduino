#include <SoftwareSerial.h>
#define DEBUG true

// SoftwareSerial 포트를 통해 esp모듈과 시리얼 통신
SoftwareSerial esp8266(3, 2); // RX, TX

void setup()
{
  Serial.begin(9600);
  esp8266.begin(9600);

  sendData("AT+RST\r\n", 2000, DEBUG); // 모듈 리셋
  sendData("AT+CWMODE=1\r\n", 1000, DEBUG); //AP 모드 - 1:station 2:ap 3:ap+station
  // WiFi AP(공유기)에 접속한다.
  sendData("AT+CWJAP=\"FirstCoding\",\"first-2498\"\r\n", 1000, DEBUG);
  delay(5000);
  sendData("AT+CIFSR\r\n", 1000, DEBUG); // IP주소를 가져온다.
  //sendData("AT+CWSAP=\"esp8266\",\"\",11,0\r\n", 1000, DEBUG);  // soft AP 모드로 설정 name,pass,channel,ecn
  sendData("AT+CIPMUX=1\r\n", 1000, DEBUG);   // multiple connections 설정
  sendData("AT+CIPSERVER=1,80\r\n", 1000, DEBUG); // 80번 포트로 서버 열기
}

void loop()
{
  if (esp8266.available()) // check if the esp is sending a message
  {
      /* // esp 모듈의 응답 내용을 시리얼 모니터에 출력한다.
      while(esp8266.available())
      {
        char c = esp8266.read();
        Serial.write(c);
      } 
      */

    if (esp8266.find("+IPD,"))
    {
      delay(1000);

      int connectionId = esp8266.read() - 48; // subtract 48 because the read() function returns
      // the ASCII decimal value and 0 (the first decimal number) starts at 48

      String webpage = "<h1>Hello World!</h1><button>LED1</button>";

      String cipsend = "AT+CIPSEND=";
      cipsend += connectionId;
      cipsend += ",";
      cipsend += webpage.length();
      cipsend += "\r\n";

      sendData(cipsend, 1000, DEBUG);
      sendData(webpage, 1000, DEBUG);

      String closeCommand = "AT+CIPCLOSE=";
      closeCommand += connectionId; // connection id 추가
      closeCommand += "\r\n";

      sendData(closeCommand, 3000, DEBUG);
    }
  }
}

String sendData(String command, const int timeout, boolean debug)
{
  String response = "";
  esp8266.print(command);

  long int time = millis();
  while ( (time + timeout) > millis())
  {
    while (esp8266.available())
    {
      char c = esp8266.read();
      response += c;
    }
  }

  if (debug)
  {
    Serial.print(response);
  }

  return response;
}
