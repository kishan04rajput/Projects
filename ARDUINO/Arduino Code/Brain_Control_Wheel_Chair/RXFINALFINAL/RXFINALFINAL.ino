#include<LiquidCrystal.h>
#include<SoftwareSerial.h>
SoftwareSerial serial(A0, A1); //RX,TX
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); //rs,en,d4,d5,d6,d7
int in1 = 8, in2 = 9, in3 = 10, in4 = 11, trigf = 12, echof = 13, trigb = 14, echob = 15, durationf, distancef, durationb, distanceb, stateb2, s; //stateb2=18
char b1, b2;
void setup() {
  // put your setup code here, to run once:
  pinMode(trigf, OUTPUT);
  pinMode(echof, INPUT);
  pinMode(trigb, OUTPUT);
  pinMode(echob, INPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("WELCOME");
}

void loop() {
  // put your main code here, to run repeatedly:
  serial.print(b2);
  stateb2 = digitalRead(18);
    if (stateb2 == HIGH)
    {
      serial.print(b2);
      b2 = serial.read();
      //switch(b2)
      //{
      motor();
    }
  while (Serial.available())
  {
    b1 = Serial.read();
    if (stateb2 == LOW)
    {
      //switch (b1)
      //{
      motor();
      //}
    }
  }
}
void motor()
{
  if (stateb2 == HIGH)
    s = b2;
  else
    s = b1;
  switch (s)
  {
    case 'F':
      digitalWrite(trigf, LOW);
      delayMicroseconds(2);
      // Sets the trigf on HIGH state for 10 micro seconds
      digitalWrite(trigf, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigf, LOW);
      // Reads the echof, returns the sound wave travel time in microseconds
      durationf = pulseIn(echof, HIGH);
      // Calculating the distance
      distancef = durationf * 0.034 / 2;
      // Prints the distance on the Serial Monitor
      Serial.print("Distancef: ");
      Serial.println(distancef);
      if (distancef > 30)
      {
        forward();
      }
      else
      {
        STOP();
        delay(100);
        left();
        delay(500);
      }
      break;
    case 'L':
      left();
      break;
    case 'R':
      right();
      break;
    case 'B':
      digitalWrite(trigb, LOW);
      delayMicroseconds(2);
      // Sets the trigf on HIGH state for 10 micro seconds
      digitalWrite(trigb, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigb, LOW);
      // Reads the echof, returns the sound wave travel time in microseconds
      durationb = pulseIn(echob, HIGH);
      // Calculating the distance
      distanceb = durationb * 0.034 / 2;
      // Prints the distance on the Serial Monitor
      Serial.print("Distanceb: ");
      Serial.println(distanceb);
      if (distanceb > 30)
      {
        backward();
      }
      else
      {
        STOP();
        delay(100);
        left();
        delay(500);
      }
      break;
    case 'S':
      STOP();
      break;
  }
}
void forward()
{
  digitalWrite(in1, 1);
  digitalWrite(in2, 0);
  digitalWrite(in3, 1);
  digitalWrite(in4, 0);
  lcd.clear();
  lcd.print("FORWARD");
}
void left()
{
  digitalWrite(in1, 1);
  digitalWrite(in2, 0);
  digitalWrite(in3, 0);
  digitalWrite(in4, 1);
  lcd.clear();
  lcd.print("LEFT");
}
void right()
{
  digitalWrite(in1, 0);
  digitalWrite(in2, 1);
  digitalWrite(in3, 1);
  digitalWrite(in4, 0);
  lcd.clear();
  lcd.print("RIGHT");
}
void backward()
{
  digitalWrite(in1, 0);
  digitalWrite(in2, 1);
  digitalWrite(in3, 0);
  digitalWrite(in4, 1);
  lcd.clear();
  lcd.print("BACKWARD");
}
void STOP()
{
  digitalWrite(in1, 0);
  digitalWrite(in2, 0);
  digitalWrite(in3, 0);
  digitalWrite(in4, 0);
  lcd.clear();
  lcd.print("STOP");
}
