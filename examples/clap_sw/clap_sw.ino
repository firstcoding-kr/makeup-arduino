int val = 0;

int threshold = 550;
unsigned long t = 0;
unsigned long current = 0;
int count = 0;

void setup() {
  pinMode(13, OUTPUT);
  pinMode(A0, INPUT);
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(7, OUTPUT);
  pinMode(9, OUTPUT);
  digitalWrite(7, LOW);
}

void loop() {
  current = millis();
  val = analogRead(A0);
  
  if (val > threshold) {
    ++count;
    Serial.println("박수 한번 감지!");
    delay(200);

    if (count == 1) {
      t = current;
    }
  }

  if (current - t > 1000) {
    if (count == 2) {
      Serial.println("ON");
    }else if (count == 3) {
      Serial.println("OFF");
    }
    count = 0;
    t = current;
    Serial.println("초기화됨");
  }
}
