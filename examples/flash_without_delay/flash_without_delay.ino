int btn = 3;
int led = 5;
int bzr = 6;

unsigned long prevTime = 0;
unsigned long prevBzrTime = 0;
int ledState = LOW;
int bzrState = LOW;

void setup() {
  pinMode(btn, INPUT);
  pinMode(led, OUTPUT);
  pinMode(bzr, OUTPUT);
}

void loop() {
  if ( millis() - prevTime > 1000 && ledState == HIGH) {
    prevTime = millis();    
    digitalWrite(led, ledState = !ledState);
  } else if ( millis() - prevTime > 2000 && ledState == LOW) {
    prevTime = millis();    
    digitalWrite(led, ledState = !ledState);
  } 

  if ( millis() - prevBzrTime > 100 && bzrState == HIGH) {
    prevBzrTime = millis();    
    digitalWrite(bzr, bzrState = !bzrState);
  } else if ( millis() - prevBzrTime > 1000 && bzrState == LOW) {
    prevBzrTime = millis();    
    digitalWrite(bzr, bzrState = !bzrState);
  } 
}
