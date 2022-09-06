#include "WiFiEsp.h"
#include "SoftwareSerial.h"
#define LED_PIN 13
SoftwareSerial Serial1(3, 2); // RX, TX

char ssid[] = "FirstCoding";
char pass[] = "first-2498";
int status = WL_IDLE_STATUS;

int ledStatus = LOW;

WiFiEspServer server(80);
RingBuffer buf(8);

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  Serial1.begin(9600);
  WiFi.init(&Serial1);

  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    while (true);
  }

  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
  }

  Serial.println("You're connected to the network");
  printWifiStatus();

  // 웹서버 80포트 시작
  server.begin();
}


void loop()
{
  WiFiEspClient client = server.available();

  if (client) {
    Serial.println("New client");
    buf.init();
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        buf.push(c);

        //Serial.write(c);

        if (buf.endsWith("\r\n\r\n")) {
          sendHttpResponse(client);
          break;
        }

        if (buf.endsWith("GET /H")) {
          Serial.println("Turn led ON");
          ledStatus = HIGH;
          digitalWrite(LED_PIN, HIGH);
        }
        else if (buf.endsWith("GET /L")) {
          Serial.println("Turn led OFF");
          ledStatus = LOW;
          digitalWrite(LED_PIN, LOW);
        }
      }
    }

    client.stop();
    Serial.println("Client disconnected");
  }
}


void sendHttpResponse(WiFiEspClient client)
{
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println();

  client.print("The LED is ");
  client.print(ledStatus);
  client.println("<br>");
  client.println("<br>");

  client.println("Click <a href=\"/H\">LED ON</a><br>");
  client.println("Click <a href=\"/L\">LED OFF</a><br>");

  client.println();
}

void printWifiStatus()
{
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  Serial.println();
  Serial.print("서버주소 http://");
  Serial.println(ip);
  Serial.println();
}
