/*
  가속도 센서(ax, ay, ax)로 각도 구하기
*/
#include<Wire.h>

const int MPU_ADDR = 0x68;
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

double angleAcX, angleAcY, angleAcZ;

// (360도 = 2*파이라디안) = (180도 = 파이라디안) => 라디안 각을 도로 바꾸기 위해 180/파이를 곱해준다.
const double RADIAN_TO_DEGREE = 180 / 3.14159; 

void setup() {
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  
  Serial.begin(9600);

  pinMode(6, OUTPUT);
}

void loop() {
  getData();
  angleAcY = atan(AcX / sqrt(pow(AcY, 2) + pow(AcZ, 2)));
  angleAcY *= RADIAN_TO_DEGREE;
  
  angleAcX = atan(AcY / sqrt(pow(AcX, 2) + pow(AcZ, 2)));
  angleAcX = atan2(AcY, sqrt(pow(AcX, 2) + pow(AcZ, 2)));
  angleAcX *= RADIAN_TO_DEGREE;

  Serial.print(" x: ");
  Serial.print(angleAcX);
  Serial.print(" y: ");
  Serial.print(angleAcY);
  Serial.print(" z: ");
  Serial.print(angleAcZ);
  Serial.println();
  
  delay(100);
}

void getData() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 14, true);

  AcX = Wire.read() << 8 | Wire.read();
  AcY = Wire.read() << 8 | Wire.read();
  AcZ = Wire.read() << 8 | Wire.read();
  Tmp = Wire.read() << 8 | Wire.read();
  GyX = Wire.read() << 8 | Wire.read();
  GyY = Wire.read() << 8 | Wire.read();
  GyZ = Wire.read() << 8 | Wire.read();
}
