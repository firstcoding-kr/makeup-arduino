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
    Serial.println("박수 감지!");
    ++count;
    delay(200);

    t = current;
  }

  if (count > 0 && current - t > 1000) {
    
    if (count == 2) {
      // 박수 2회
      Serial.println("ON");
    }else if (count == 3) {
      // 박수 3회
      Serial.println("OFF");
    }
    
    count = 0;
    t = current;
    Serial.println("초기화됨");
  }
}
