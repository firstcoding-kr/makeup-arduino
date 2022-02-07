#include<Wire.h> // I2C 통신 라이브러리 추가

int ax, ay, az, tmp, gx, gy, gz;

void get6050() {
  Wire.beginTransmission(0x68);//MPU6050 호출 (0x68: I2C주소)
  Wire.write(0x3B); //ax 레지스터 위치 요청
  Wire.endTransmission(false);
  Wire.requestFrom(0x68, 14, true); //14byte의 데이터를 요청
  
  ax = Wire.read() << 8 | Wire.read(); //두개의 나뉘어진 바이트를 하나로 이어붙임. (2바이트 int형 변수에 저장)
  ay = Wire.read() << 8 | Wire.read();
  az = Wire.read() << 8 | Wire.read();
  tmp = Wire.read() << 8 | Wire.read();
  gx = Wire.read() << 8 | Wire.read();
  gy = Wire.read() << 8 | Wire.read();
  gz = Wire.read() << 8 | Wire.read();
}

void setup()
{
  /*
  Wire.begin();
  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0); // MPU6050 을 동작 대기 모드로 변경
  Wire.endTransmission(true);
  */
  Serial.begin(9600);
}

void loop()
{
  get6050(); // 센서값 갱신

  //받아온 센서값을 시리얼 모니터에 출력
  Serial.print(" ax:");
  Serial.print(ax);
  Serial.print(" ay:");
  Serial.print(ay);
  Serial.print(" az:");
  Serial.print(az);
  Serial.print(" gx:");
  Serial.print(gx);
  Serial.print(" gy:");
  Serial.print(gy);
  Serial.print(" gz:");
  Serial.print(gz);
  Serial.print(" tmp:");
  Serial.print(tmp);
  Serial.println();
  delay(100);
}
