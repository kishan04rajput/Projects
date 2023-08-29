#include<LiquidCrystal.h>
LiquidCrystal lcd(3, 4, 5, 6, 7, 8);
const int in1 = 9, in2 = 10, in3 = 11, in4 = 12;
int xAxis, yAxis;
int k;
char K;
void setup() {
  // put your setup code here, to run once:
  pinMode(14, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(2, INPUT);
  digitalWrite(14, 1);
  Serial.begin(9600);
  lcd.print("WELCOME");
  delay(4000);
}

void loop() {
  k = digitalRead(2);
  xAxis = analogRead(A0); // Read Joysticks X-axis
  yAxis = analogRead(A1); // Read Joysticks Y-axis
  Serial.print(xAxis / 100); // Dividing by 4 for converting from 0 - 1023 to 0 - 256, (1 byte) range
  Serial.println(yAxis / 100);
  xAxis = xAxis / 100;
  yAxis = yAxis / 100;
  if (k == LOW)
  {
    if (yAxis == 10) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("FORWARD");
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
    }
    if (yAxis == 0) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("BACKWARD");
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, LOW);
      digitalWrite(in4, 1);
    }
    if (xAxis == 0) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("RIGHT");
      digitalWrite(in1, 1);
      digitalWrite(in2, 0);
      digitalWrite(in3, 0);
      digitalWrite(in4, 1);
    }
    if (xAxis == 10) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("LEFT");
      digitalWrite(in1, 0);
      digitalWrite(in2, 1);
      digitalWrite(in3, 1);
      digitalWrite(in4, 0);
    }
    if (xAxis == 5 && yAxis == 5) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("STOP");
      digitalWrite(in1, 0);
      digitalWrite(in2, 0);
      digitalWrite(in3, 0);
      digitalWrite(in4, 0);
    }
    delay(100);
    // put your main code here, to run repeatedly:
  }
  while (Serial.available())
  {
    K=Serial.read();
    if (K == 'F')
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("FORWARD");
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
    }
    else if (K == 'L')
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("LEFT");
      digitalWrite(in1, 0);
      digitalWrite(in2, 1);
      digitalWrite(in3, 1);
      digitalWrite(in4, 0);
    }
    else if (K == 'R')
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("RIGHT");
      digitalWrite(in1, 1);
      digitalWrite(in2, 0);
      digitalWrite(in3, 0);
      digitalWrite(in4, 1);
    }
    else if (K == 'B')
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("BACKWARD");
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, LOW);
      digitalWrite(in4, 1);
    }
    else if (K == 'S')
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("STOP");
      digitalWrite(in1, 0);
      digitalWrite(in2, 0);
      digitalWrite(in3, 0);
      digitalWrite(in4, 0);
    }
  }
}
