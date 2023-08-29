#include<LiquidCrystal.h>
LiquidCrystal lcd(3, 4, 5, 6, 7, 8);
const int in1 = 9, in2 = 10, in3 = 11, in4 = 12;
int xAxis, yAxis;
int k;
char K;
const int trigPinf = 13;
const int echoPinf = 14;
const int trigPinb = 15;
const int echoPinb = 16;
long durationf;
int distancef;
long durationb;
int distanceb;
void setup() {
  // put your setup code here, to run once:
  pinMode(14, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(trigPinf, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPinf, INPUT); // Sets the echoPin as an Input
  pinMode(trigPinb, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPinb, INPUT); // Sets the echoPin as an Input
  pinMode(2, INPUT);
  digitalWrite(14, 1);
  Serial.begin(9600);
  lcd.print("WELCOME");
  delay(1000);
}

void loop() {
  k = digitalRead(2);
  xAxis = analogRead(A0); // Read Joysticks X-axis
  yAxis = analogRead(A1); // Read Joysticks Y-axis
  Serial.print("xAxis: ");
  Serial.println(xAxis/10);// Dividing by 4 for converting from 0 - 1023 to 0 - 256, (1 byte) range
  Serial.print("yAxis: ");
  Serial.println(yAxis / 10);
  xAxis = xAxis / 10;
  yAxis = yAxis / 10;
  if (k == LOW)
  {
    if (yAxis == 69) {
      lcd.clear();
      lcd.setCursor(0, 0);
      ultrasonicf();
      if (distancef >= 30)
      {
        lcd.print("FORWARD");
        forward();
      }
      else
      {
        lcd.print("OBSTACLE");
        STOP();
        delay(10);
        backward();
        delay(100);
        left();
        delay(100);
      }
    }
    if (yAxis == 0) {
      lcd.clear();
      lcd.setCursor(0, 0);
      ultrasonicb();
      if (distanceb >= 30)
      {
        lcd.print("BACKWARD");
        backward();
      }
      else
      {
        lcd.print("OBSTACLE");  
        STOP();
        delay(10);
        forward();
        delay(500);
        right();
        delay(500);
      }
    }
    if (xAxis == 0) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("RIGHT");
      right();
    }
    if (xAxis == 69) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("LEFT");
      left();
    }
    if (xAxis == 34 && yAxis == 34) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("STOP");
      STOP();
    }
    delay(10);
    // put your main code here, to run repeatedly:
  }
  while (Serial.available())
  {
    K = Serial.read();
    if (K == 'F')
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      if (distancef >= 30)
      {
        lcd.print("FORWARD");
        forward();
      }
      else
      {
        lcd.print("OBSTACLE");
        STOP();
        delay(10);
        backward();
        delay(10);
        left();
        delay(10);
      }
    }
    else if (K == 'L')
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("LEFT");
      left();
    }
    else if (K == 'R')
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("RIGHT");
      right();
    }
    else if (K == 'B')
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      if (distanceb >= 30)
      {
        lcd.print("BACKWARD");
        backward();
      }
      else
      {
        lcd.print("OBSTACLE");
        STOP();
        delay(10);
        forward();
        delay(500);
        right();
        delay(500);
      }
    }
    else if (K == 'S')
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("STOP");
      STOP();
    }
  }
  delay(100);
}
void ultrasonicf()
{
  digitalWrite(trigPinf, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPinf, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinf, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  durationf = pulseIn(echoPinf, HIGH);
  // Calculating the distance
  distancef = durationf * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distancef: ");
  Serial.println(distancef);
}
void ultrasonicb()
{
  digitalWrite(trigPinb, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPinb, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinb, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  durationb = pulseIn(echoPinb, HIGH);
  // Calculating the distance
  distanceb = durationb * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distanceb: ");
  Serial.println(distanceb);
}
void STOP()
{
  digitalWrite(in1, 0);
  digitalWrite(in2, 0);
  digitalWrite(in3, 0);
  digitalWrite(in4, 0);
}
void forward()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
void left()
{
  digitalWrite(in1, 0);
  digitalWrite(in2, 1);
  digitalWrite(in3, 1);
  digitalWrite(in4, 0);
}
void right()
{
  digitalWrite(in1, 1);
  digitalWrite(in2, 0);
  digitalWrite(in3, 0);
  digitalWrite(in4, 1);
}
void backward()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, 1);
}
