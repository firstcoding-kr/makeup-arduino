#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ArduinoOTA.h>
#include <ESP8266WebServer.h>

#define LED_PIN 0

const String hostName = "FC-ESP-01"; // 장치 이름
const char* ssid = "FirstCoding"; // WiFi SSID
const char* password = "first-2498"; // WiFi PW

const String formHtml = "<!DOCTYPE html>\
<html lang=\"ko\" class=\"h-100\">\
<head>\
    <meta charset=\"UTF-8\">\
    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\
    <title>WIFI 모듈 원격제어</title>\
    <link href=\"https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css\" rel=\"stylesheet\"\
        integrity=\"sha384-1BmE4kWBq78iYhFldvKuhfTAU6auU8tT94WrHftjDbrCEXSU1oBoqyl2QvZ6jIW3\" crossorigin=\"anonymous\">\
    <link rel=\"icon\" href=\"data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAIAAAACACAYAAADDPmHLAAAAAXNSR0IArs4c6QAADhxJREFUeF7tnXtwVNUdx7+/c+/e3c0+8gIVRAhgIYpoKw+1qICVgDqtOphawsMAlhmt0KoVrPVBdcaOr1GsOuq0an2C1SpKSUhVoqgoxAcoT8FgglQEVCAhu8nuPZ0bjIaYTe65j2XvenaGP5j8Huf3PZ/93XPvObtLyMJXKedKUX28iBEGcR2DQRgMoIhA+Rw8BCAE8DyAwus3NPhIAWdESYUhQUQJxhBjKn2pMNqsMHpPVdmKBn945b+GUHO2yUXZUNDcXTzCY/EzSMcYTnwMgU4E4DdT27oNDWbMQETQNGr0a2ydoipLCoP08IKh4Z2mnDPYyLMAzPssPoSTPgmcnQXiIwCoVnQ2C0DH2IZw/gDb71dpjV9T7nx0RHSxlfyH28dTAFxZzwt8evwiEKYBGOWEeFYB6Jhb01g8GFBeUyl57eOnFqx1YmzpiOEZAObWxe4HMMvqOz2VmE4B0BbfEDQcVj5eOCp/aDom0G4OzwAwry52FQfusltwR3+nATDi5+b6Fj99au4FTo/VjXieAeAPtTxPU+LbD67gnXs5DQAxIJQfPnbR8MBW50bpXiTPAGBIMLc+9hB462VA9NUMjloi1INjr07USOAHQNhbtz0+mnM9yjn5oesBnVMwmeDhlhZd46JZWtu/b8OiUbnHW3A9LC6eAmBefXwo57ybBRbtIfA3OPAWJ2xQgM2BPv5t84kSIgqX1/KAsmvvqDjx0/UEhiUSGBaLJ3slk+hSs4Ie/olPDIv8WyTX4bT1FACtXaAuVg1gdDvRjIl9BRzLuMKqQ0f71s4n0t0Qdf5yrn4a3Tsx0UKTWuL6qKZYskf7LhEIKN88Pzo/343cbsX0HADX1McnEufPEbCec3qc6y3/vKN/+Au3BOoq7sU1sYFqoml+PM5/1RTTo/l56h1PnpI393CMxWpOzwEwn3O1ob65+M6+/o+tFu2GX3lN4wUozKl8rD/F3IjvVkzPAeCWED/WuBKAH+vMf1u3BEACkL0KXLetsVeSKSdyjsGcMIiAQeDoCUIUaP0XWr+xIagQ6UxhSSKeYAod8CnYwVRlk8LwAZKJJV56ti86m1nVAYzNIpU3jyPwMZwwhjiKuxPEzJNAY6NH02iLpqj/bVZ993nlKV93tRt/9zwAxuGPfnXxsYzRNHB+EYCgmcLbbMwA0D4eEZATVHdqGj0dPRC98YGxZO5Agcig0mjreQDm1sXWAzjOqmaiALTPY3SGF8YWBKzmzgQ/zwMwr67pFg663qqYdgCIhJUVC0fln2k1dyb4eR6AuXWNvQFlGwCfFUGtAmAI1yPfN/KxkbmrreTNFB/PA2AIOa8+9iznKLUiqlUAQiFW/+zpBX2t5Mwkn+wAoK7pTA56vRthW8DxKRg+AehrcN7YfjsYnAJcR6ilRc83sxVcWKjMeXx4/t8yaTKtjCUrADAKn1sXWwPAOA3c9qrjoGpAX64yett/tP9Ts1vCxlYw37v3TD2Gi+NJjI7HkkWJBFfaAmsaxV4YWyh0t2FlctLhkz0AfBabBeJ/BdFzpOtP3NYv500nBZy+et/5TQl+bVNjYmQ4zJ566tR842Cq519ZA8CsGu7rPQzc7Lvc6swZ3WHPHrCXh9MBqzEyyS9rAMgkUb00FgmAl2bLhbFKAFwQ1UshJQBemi0XxpqVAIyfMquXzuMDoLP+DBgA4v11TkVEFCEgwsGDxieDAR6pr92oEmOcMUUnQCdSWoihmTFlD2NUrzBlE4eylivKypqKl4xbTVcOnLowt6ZCeh6Ac8tm9ktyfooOPpIRTuHAz0Q+PFJfu9GUUIaR8Qlhn8+/T1F9WxSmrGAKf+7dykpHbzdND8YhQ88BMK6s/KfE2QQCP40zjATHUXa0EAGgszxG5/Bp/l1MVdYwRX2spnLpIi91iYwH4LTS0mDUFxnFwX8J4EIAx9iZ8I6+dgHoGK8VCH9gm6qqi32aetfKJUs+d3K8TsfKSADOLp2Vq/hapnKi88D5GACu7bk7DUD7CTr4pRL+3YrPv5yR/+rVVYvrnZ5Au/EyEoAJU8rH6Dott1ucGX83AWifPxTNu7JmWcU9ZsaUThsJgMAi0M7ESAAE1JMdQEAsm6ayA8gOYBMhF9xlB3BB1BQhZQeQHSB9tJnNJDuAWaXs28kOIDuAfYqcjiA7gNOKpo4nO4DsAOmjzWwmOx2g6Ji+mHrxpJSpnlj0DLbV13339/ZPAov6/wTTZ/4+pe+j/1iAbbWfmC3jEDv5IEhANjsAHDeoGDdek/prem6+43Zs2Pz9FnB7AIaccDL+ckvqo/433TAb6z5+X6CS700lAAKySQAExLJpmnVrANkBxIiQALRbBMpLgBg8rlnLS4Br0v4gsOwAsgOkjzazmex0AHkbaFblg3ZZ1wHEygfkiSBRxdJgb6cDiA5PAiCqWBrsJQBpEPnbFPISIPcC0keb2UyyA5hVyr6d7ACyA9inyOkIsgM4rWjqeFnXAeRzADF4sg4AuRkkAZDnAQQYkB1A7gUI4JImUzuLQHkJEJsk2QFkBxAjJh3WsgOkQ+Us3Q2Ut4Fi8GTdJUCsfLkdLAGQj4JF3zPu29tZA4iOTp4HEFUsDfYSgDSILM8DHFRAdoD0wWY6k+wApqWybSgXgXIRaBsixwPY6QDyOYDYdGRdB5B7ARIAuR0swIDsAHIzSACXNJnaWQPIS4DYJMkOIDuAGDHpsJYdIB0qy+3gHzwJlF8SlT7wusxkpwOIliAfBYsqlgZ7CUAaRJabQXIzyFAg6+4CRN878hIgqlga7OUlIA0iy0uAvATIS4A8EPLjWwP4C3si9/iT4O95JHzRXOxM9ACPN6Blz+fYveJF7Nts/Dyw8y/5XcECmrqxBggfW4zeE85HTp+iQ0aybkPDIf/XKI6vq5/BzuXPC4y4e1MJQPcafWfhJADMp+GYi6Yg/6QRnY6gIwBtRr74bmy9dw4SjfsFRp7aVAIgIKNTACjBEAZeOhs5R/dLmT0VAIaDxppRu+B3iO/5QmD0nZtKAAQkdAIAUhgGzJiNyMDiLjN3BUArBLwRm26dBt7SLFDBD00lAALyOQHAUb84F0eNM35wvOtXdwC03ir9bw22PnR9d6G6/LsEQEA+uwCo4TCOv+ZmMH+w26xmAGAM2PHgFTiw47Nu46UykAAISGcXgCPPOhe9Srp/9xtDMgNAaxf44iNsffA6gSoONZUACEhnF4DBc/6EYO++pjKaBcDHmrHpxommYnZmJAEQkM4OAIrfj6Hz7wbI3D6XWQCM4dfdNRWJ/d8IVPK9qQRAQDY7ABhP+I67er7pbCIA7F54E/ZtlL8aZlpcq4YlZTPPBPTXrfjn9OuPQZel/tm4jjFFANhf9QB2vV1hZViI5BXMWVXxn9S/SWcpqn0nc33Sfh6hCCVllwwDWI2Q07fGgZ5HotilDrDnmRuwd9OHVoaFSDR/8qplS5+25OyiU0YCMGHKjMG6zr//dUcBATJ1DZCXW3j2ysolrwqUkhbTjATgvLKy/Bb4v7KqwKArrkVOn9SPf9vHNXsJ0KgZG2+yfhcQjhzRd3XV4nqrNbnll5EAGMWWlE3/EkBPK4W78xxgLbY++GcrwwFTFH3dm28qlpxddspcACZNfwOEM6zU7/STQIUB9fdfjthOa29gzR/4Zk318nwrtbjtk7EAjJ80/TZOML+c76CU2S5g5hLAdnyILQ/fYHkuQjmRlTWvVv3ccgAXHTMYgPIJnMjaPZchGGMYMO0yRItP6FK+7gDQ9EZsvnUq9ESL5WmIRPPmrVpWcbvlAC46ZiwAJVOnhpBUdwIIWa2/9TzAzCt+cArI7CLQWPh9uuByNH9lDMPai4hxioR7rFu2zPKi1lpmc14ZC8DBhWD5kwBNNldK51bGiaA+F05GwckjOzVIfSJoF7beMxuJpkY76REIhrZ+8Norx9oK4qJzZgMwqXwciKqcqD88cBB6jb8Aob79DwnX2ZnAb5Y/iS+qX3QiLcJ5edesrqi405FgLgTJaACMXdiSsunGMd2hTtWuGaeCi4cicMRRUI1Twcke4LH9SOz+9lTwlo+cSgWfqjWtXfF6GIDuWFCHA2U6ABg/ubyMc3rK4bq/C+fmR8NCkdy7a6oqr3Jr7E7EzXgASktLlb2+8CoAJztRcMcYbgGgav7GQkJedXV1wo1xOxUz4wEwCp0wuXyEzukd4+bOqcLb4rgBABEhEs6d+W5VxSNOj9fpeJ4AoPWOYPKMe8H5bKcFcAOAYE7k/fdfrRrm9FjdiOcZAM45Z7Y/md/wttOXAqcB8PkCBwoYP7K6uvrQjxy5MXsOxPQMAEat51x8ycCkwlZa3STqTC8nAWBM0XNC0bGrq5a+4cDcpCWEpwAwFBn3mxnDifHlAIzbK9svpwAgYgjn5f521dKlf7c9qDQG8BwAhjbjy2aM5eDGk5qoXa2cAIAxxoPh6FU1yyrusTuedPt7EoDWReHBY2PGZpGlMwNO3QUYbT8Ujk7NxONeZmDyLACta4LJl/ZJcn0hwEeZKdbpNYBxr58TDEx4t7LyTav5D7efpwEwxBs2a5avcH/LX0D4IwCfqKBWLgHGfb4/FH6LBfwl77388gHRnJlk73kA2sQcP+mSITrYfUQYIyKwKACa5v86mBO85J2KipdF8mSqbdYA8B0IBxeIxvGdsWZENwuATwt8rQUCN3txodeVDlkHQFuxJZPKiwGaBsKvAQxMJUJXACiqr0XTAqsVf+CW1UtfqjQDlNdsshaA9hNRMvXS/kjqZ4FwEjg3vjHC+KKgAgCR7bWbNFKYzoglFVXdR0zdrqrK+4z4I15e3JkF8f/dE1HqObaluQAAAABJRU5ErkJggg==\" sizes=\"128x128\" />\
</head>\
<body class=\"text-center text-white bg-dark h-100\">\
    <div class=\"h-100 row align-items-center\">\
        <form action=\"/send-on\" method=\"post\">\
            <button style=\"padding:20px;\" class=\"btn btn-light\">LED ON</button>\
        </form>\
        <form action=\"/send-off\" method=\"post\">\
            <button style=\"padding:20px;\" class=\"btn btn-light\">LED OFF</button>\
        </form>\
    </div>\
</body>\
</html>";

const String postResp = "<!DOCTYPE html>\
<html lang=\"ko\">\
<head>\
    <meta charset=\"UTF-8\">\
    <title>WIFI 모듈 원격제어</title>\
    <script>alert('신호를 전송했습니다.');location.replace('/');</script>\
</head>\
</html>";

ESP8266WebServer server(80);

void handleOn() {
  if (server.method() != HTTP_POST) {
    server.send(405, "text/plain", "Method Not Allowed");
    return;
  }

  digitalWrite(LED_PIN, HIGH);
  responseServer();
}

void handleOff() {
  if (server.method() != HTTP_POST) {
    server.send(405, "text/plain", "Method Not Allowed");
    return;
  }

  digitalWrite(LED_PIN, LOW);
  responseServer();
}

void responseServer() {
  String message = "POST form was:\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  Serial.print("Http Message: ");
  Serial.println(message);
  server.send(200, "text/html", postResp);
}

void handleRoot() {
  server.send(200, "text/html", formHtml);
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  WiFi.mode(WIFI_STA);
  WiFi.hostname(hostName);
  WiFi.begin(ssid, password);

  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Connect Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  ArduinoOTA.setHostname((const char *)hostName.c_str());
  ArduinoOTA.begin();

  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.on("/off", handleOff);
  server.begin();

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  ArduinoOTA.handle();
  server.handleClient();

  delay(10);
}
