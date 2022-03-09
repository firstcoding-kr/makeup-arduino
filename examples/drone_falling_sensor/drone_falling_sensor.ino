#include <Wire.h> // i2c 통신 라이브러리 불러들임
#include <math.h> // 수학 계산용 라이브러리 불러들임

boolean checkfalling = false; // 추락상태 여부를 저장하는 변수
long ax = 0, ay = 0, az = 0; // x,y,z 변수선언 및 초기화
long gx = 0, gy = 0, gz = 0;
long asvm = 50000; // 가속도 변화량의 합

const int pinhead = 3; // 핀 번호들
const int led = 5;
const int buzzer = 6;

int ledState = LOW; // led의 켜짐 꺼짐 상태
int buzzerState = LOW; // buzzer의 켜짐 꺼짐 상태

unsigned long prv1 = 0; // led 시간 측정 기준
unsigned long prv2 = 0; // buzzer 시간 측정 기준

int bzLowTime = 500; // buzzer LOW 주기 변수

void initState() { // led, buzzer 상태 초기화 함수
  digitalWrite(led, ledState = LOW);
  digitalWrite(buzzer, buzzerState = LOW);
  checkfalling = false;
  bzLowTime = 500;
}

void setup() {
  Wire.begin();
  Serial.begin(9600);

  Wire.beginTransmission(0x68);
  Wire.write(0x6b);
  Wire.write(0x0);
  Wire.endTransmission();

  pinMode(pinhead, INPUT);
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);

  initState();
}

void loop() {
  getmpudata(); // 센서로부터 데이터를 가져온다.

  // 버튼을 눌렀을 때
  if (digitalRead(pinhead) == HIGH) {
    initState();
  }

  Serial.println(asvm);

  // 투하했을때
  long fallingThresh = 3000;
  if (asvm < fallingThresh) {
    Serial.println("falling!!!!!");
    checkfalling = true;

    delay(3000); // 3초 쉬고
  }

  if (checkfalling == true) {

    unsigned long time1 = millis() - prv1;
    /*
        if (time1 >= 300 && ledState == LOW) {
          digitalWrite(led, ledState = !ledState);
          prv1 = millis();
        } else if (time1 >= 300 && ledState == HIGH) {
          digitalWrite(led, ledState = !ledState);
          prv1 = millis();
        }
        // 이 문장을 줄여서 아래와 같이 쓸 수 있다.

        if ((time1 >= 300 && ledState == LOW)
        || (time1 >= 300 && ledState == HIGH)) {
          digitalWrite(led, ledState = !ledState);
          prv1 = millis();
        }
    */

    // 단순히 동일 시간동안 깜빡이기만 하는 경우 아래와 같이 짧게 짤 수 있다.
    // LED 깜빡 300H-300L...
    if ( time1 >= 300 ) {
      digitalWrite(led, ledState = !ledState);
      prv1 = millis();
    }

    // 부저 컨트롤 부분  200H-100L-200H-500L...
    unsigned long time2 = millis() - prv2;
    if (time2 >= bzLowTime && buzzerState == LOW) {
      digitalWrite(buzzer, buzzerState = !buzzerState);
      prv2 = millis();
    } else if (time2 >= 200 && buzzerState == HIGH) {
      digitalWrite(buzzer, buzzerState = !buzzerState);
      prv2 = millis();

      if (bzLowTime == 100) { 
        bzLowTime = 500; // LOW 시간이 100이었으면 다음 LOW 시간을 500으로 바꾼다.
      }
      else {
        bzLowTime = 100; // LOW 시간이 100이 아니었으면(=500) 다음 LOW 시간을 100으로 바꾼다.
      }
    }
    
  }
}


void getmpudata() {
  Wire.beginTransmission(0x68);
  Wire.write(0x3b);
  Wire.endTransmission();
  Wire.requestFrom(0x68, 14);

  ax = Wire.read() << 8;
  ax |= Wire.read();
  ay = Wire.read() << 8;
  ay |= Wire.read();
  az = Wire.read() << 8;
  az |= Wire.read();
  gx = Wire.read() << 8;
  gx |= Wire.read();
  gy = Wire.read() << 8;
  gy |= Wire.read();
  gz = Wire.read() << 8;
  gz |= Wire.read();

  ax = abs(ax);
  ay = abs(ay);
  az = abs(az);

  Serial.print(" AX = ");
  Serial.print(ax);
  Serial.print(" AY = ");
  Serial.print(ay);
  Serial.print(" AZ = ");
  Serial.print(az);
  Serial.print(" GX = ");
  Serial.print(gx);
  Serial.print(" GY = ");
  Serial.print(gy);
  Serial.print(" GZ = ");
  Serial.print(gz);

  asvm = ax + ay + az;
  Serial.print(" SVM = ");
  Serial.print(asvm);
}
