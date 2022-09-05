
int red = 9;
int green = 10;
int blue = 11;

void setup() {
  pinMode(red, OUTPUT); // R 빨강
  pinMode(green, OUTPUT); // G 초록
  pinMode(blue, OUTPUT); // B 파랑
}

void loop() {

  for (int i = 0; i < 255; i+=1) {
    analogWrite(blue, 255 - i);
    analogWrite(red, i);
    delay(10);
  }

  for (int i = 0; i < 255; i+=1) {
    analogWrite(red, 255 - i);
    analogWrite(green, i);
    delay(10);
  }

  for (int i = 0; i < 255; i+=1) {
    analogWrite(green, 255 - i);
    analogWrite(blue, i);
    delay(10);
  }
  

}
