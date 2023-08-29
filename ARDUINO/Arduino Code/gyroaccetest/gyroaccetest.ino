#include<Wire.h>
#include <SoftwareSerial.h>
SoftwareSerial Seriall (16, 17); //rx,tx
const int MPU = 0x68;
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

void setup() {
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
 // pinMode(20, INPUT);
  digitalWrite(14, HIGH);
  digitalWrite(15, LOW);
  Serial.begin(9600);
  Seriall.begin(9600);
  //Serial1.print("KISHAN");
}
void loop() {
  Seriall.println("KISHAN");
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 12, true);
  AcX = Wire.read() << 8 | Wire.read();
  AcY = Wire.read() << 8 | Wire.read();
  AcZ=Wire.read()<<8|Wire.read();
  // GyX=Wire.read()<<8|Wire.read();
  // GyY=Wire.read()<<8|Wire.read();
  // GyZ=Wire.read()<<8|Wire.read();

 // Serial.print("Accelerometer: ");
  Serial.print("X = "); Serial.print(AcX); //-X=FORWARD
  Serial.print(" | Y = "); Serial.println(AcY); //-Y=LEFT
  Serial.print(" | Z = "); Serial.println(AcZ);
  if (AcX < 0)
    Serial.print("F");
  else
    Serial.print("B");
  if (AcY < 0)
    Serial.println("L");
  else
    Serial.println("R");
    
//    Serial1.println("KISHAN");

  /*  Serial.print("Gyroscope: ");
    Serial.print("X = "); Serial.print(GyX);
    Serial.print(" | Y = "); Serial.print(GyY);
    Serial.print(" | Z = "); Serial.println(GyZ);
    Serial.println(" ");*/
  delay(333);
}
