// include the library code:
#include <LiquidCrystal.h>
#include<SoftwareSerial.h>
SoftwareSerial seriall (10, 11); //rx,tx

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 53, en = 51, d4 = 49, d5 = 47, d6 = 45, d7 = 43;
const int m11 = A0;
const int m12 = A1;
const int m21 = A2;
const int m22 = A3;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int K, Kk = 1, b2;

char str[2], i;

void setup() {

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  pinMode(14, OUTPUT);
  digitalWrite(14, HIGH);

  pinMode(8, OUTPUT);
  analogWrite(8, 255);

  pinMode(9, OUTPUT);
  analogWrite(9, 0);

  pinMode(2, INPUT);

  pinMode(12, INPUT);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);

  //BLUETOOTH
  Serial.begin(9600);

  seriall.begin(9600);

}

void loop() {

  do {
    K = digitalRead(2);

    if (K == HIGH) {
      lcd.clear();
      lcd.setCursor(0, 0);

      if (Kk > 0) {
        lcd.print("GYROSCOPE");
        lcd.setCursor(0,1);
        lcd.print("CONNECTED");
        delayy();
        Kk = 0;
      }

      delayy();
      break;
    }

    else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("GYROSCOPE NOT");
      lcd.setCursor(0,1);
        lcd.print("CONNECTED");
      delayy();
    }

  } while (K == LOW);

  while (Serial.available()) {
    b2 = digitalRead(12);
    if (b2 == HIGH){
     lcd.print("MOBILE");
  lcd.setCursor(0,1);
  lcd.print("CONNECTED");
  delay(1000);
      break;
    }

    char k = Serial.read();

    switch (k)
    {
      case 'F':
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("FORWARD");
        digitalWrite(m11, HIGH);
      digitalWrite(m12, LOW);
      //delay(100);
      digitalWrite(m21, HIGH);
      digitalWrite(m22, LOW);
        delayy();
        break;

      case 'B':
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("BACKWARD");
        digitalWrite(m11, LOW);
        digitalWrite(m12, HIGH);
        digitalWrite(m21, LOW);
        digitalWrite(m22, HIGH);
        delayy();
        //lcd.clear();
        break;

      case 'L':
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("LEFT");
              digitalWrite(m11, HIGH);
      digitalWrite(m12, LOW);
      //delay(100);
      digitalWrite(m21, LOW);
      digitalWrite(m22, HIGH);
        delayy();
        //lcd.clear();
        break;

      case 'R':
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("RIGHT");
        digitalWrite(m11, LOW);
      digitalWrite(m12, HIGH);
      //delay(100);
      digitalWrite(m21, HIGH);
      digitalWrite(m22, LOW);
        delayy();
        //lcd.clear();
        break;

      case 'S':
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("STOP");
        digitalWrite(m11, LOW);
        digitalWrite(m12, LOW);
        digitalWrite(m21, LOW);
        digitalWrite(m22, LOW);
        delayy();
        //lcd.clear();
        break;

      default:
        break;
    }

  }

  /*if (b2 == HIGH) {

    while (seriall.available())
    {

      char b2d = seriall.read();
      //    str[i++]=b2d;
      switch (b2d)
      {

        case 'F':
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("MANUAL FORWARD");
          delayy();
          //lcd.clear();
          break;

        case 'B':
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("MANUAL BACKWARD");
          delayy();
          //lcd.clear();
          break;

        case 'L':
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("MANUAL LEFT");
          delayy();
          //lcd.clear();
          break;

        case 'R':
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("MANUAL RIGHT");
          delayy();
          //lcd.clear();
          break;

        case 'S':
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("MANUAL STOP");
          delayy();
          //lcd.clear();
          break;

      }

    }

    }*/
    
  while (seriall.available())
  {

    char ch = seriall.read();
    str[i++] = ch;

    if (str[i - 1] == 'F')
    {
     // Serial.println("Forward");
      digitalWrite(m11, HIGH);
      digitalWrite(m12, LOW);
      //delay(100);
      digitalWrite(m21, HIGH);
      digitalWrite(m22, LOW);
      //forward;
      lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("MANUAL FORWARD");
          delay(20);
      i = 0;
    }

    else if (str[i - 1] == 'L')
    {
      Serial.println("Left");
      digitalWrite(m11, HIGH);
      digitalWrite(m12, LOW);
      //delay(100);
      digitalWrite(m21, LOW);
      digitalWrite(m22, HIGH);
      //right;
      lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("MANUAL LEFT");
          delay(20);
      i = 0;
    }

    else if (str[i - 1] == 'R')
    {
      Serial.println("Right");
      digitalWrite(m11, LOW);
      digitalWrite(m12, HIGH);
      //delay(100);
      digitalWrite(m21, HIGH);
      digitalWrite(m22, LOW);
      //left;
      lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("MANUAL RIGHT");
          delay(20);
      i = 0;
    }
      else if (str[i - 1] == 'B')
      {
        Serial.println("Backward");
        digitalWrite(m11, LOW);
        digitalWrite(m12, HIGH);
        digitalWrite(m21, LOW);
        digitalWrite(m22, HIGH);
      //  backward;
      lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("MANUAL BACKWARD");
          delay(20);
        i = 0;
      }

      else if (str[i - 1] == 'S')
      {
        Serial.println("top");
        digitalWrite(m11, LOW);
        digitalWrite(m12, LOW);
        digitalWrite(m21, LOW);
        digitalWrite(m22, LOW);
        //top;
        lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("MANUAL STOP");
          delay(20);
        i = 0;
      }
    //  delay(100);
    }
  }

void delayy() {
  delay(250);
}
