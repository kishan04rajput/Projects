#include <LiquidCrystal.h>
#include<SoftwareSerial.h>
SoftwareSerial serial(A0, A1);
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int led = 8, motor = 9, buzzer = 10, led1 = 11, state, b2state;
void setup() {
  lcd.begin(16, 2);
  pinMode(8, OUTPUT);
  pinMode(A2, INPUT);//connet state pin of 2nd bluetooth here
  Serial.begin(9600);
  serial.begin(9600);
  lcd.print("LED ON");
  // put your setup code here, to run once:

}

void loop() {
  b2state = digitalRead(A2);
  if (b2state == LOW)
  {
    if (Serial.available() > 0) {
      state = Serial.read();
    }
    if (state == '1')
    {
      //if(state!='1')
      lcd.clear();
      digitalWrite(led, HIGH);
      digitalWrite(motor, LOW);
      digitalWrite(buzzer, LOW);
      digitalWrite(led1, LOW);
      lcd.print("LED ON");
      //  delay(1000);
    }
    if (state == '2')
    {
      //if(state!='2')
      lcd.clear();
      digitalWrite(led, LOW);
      digitalWrite(motor, HIGH);
      digitalWrite(buzzer, LOW);
      digitalWrite(led1, LOW);
      lcd.print("MOTOR ON");
      //delay(1000);
    }
    if (state == '3')
    {
      //if(state!='3')
      lcd.clear();
      digitalWrite(led, LOW);
      digitalWrite(motor, LOW);
      digitalWrite(led1, LOW);
      digitalWrite(buzzer, HIGH);
      lcd.print("BUZZER ON");
      //delay(1000);
    }
    if (state == '4')
    {
      //if(state!='4')
      lcd.clear();
      digitalWrite(led, LOW);
      digitalWrite(motor, LOW);
      digitalWrite(buzzer, LOW);
      digitalWrite(led1, HIGH);
      lcd.print("LED1 ON");
      //delay(1000);
    }
  }
  else {
    while (serial.available())
    {
      char k = serial.read();
      if (k == 'F')
      {
        lcd.clear();
        digitalWrite(led, HIGH);
        digitalWrite(motor, LOW);
        digitalWrite(buzzer, LOW);
        digitalWrite(led1, LOW);
        lcd.print("LED ON");
      }
      else if (k == 'B')
      {
        lcd.clear();
        digitalWrite(led, LOW);
        digitalWrite(motor, HIGH);
        digitalWrite(buzzer, LOW);
        digitalWrite(led1, LOW);
        lcd.print("MOTOR ON");
      }
      else if (k == 'L')
      {
        lcd.clear();
        digitalWrite(led, LOW);
        digitalWrite(motor, LOW);
        digitalWrite(led1, LOW);
        digitalWrite(buzzer, HIGH);
        lcd.print("BUZZER ON");
      }
      else if (k == 'R')
      {
        lcd.clear();
        digitalWrite(led, LOW);
        digitalWrite(motor, LOW);
        digitalWrite(buzzer, LOW);
        digitalWrite(led1, HIGH);
        lcd.print("LED1 ON");
      }
    }
  }
}
