// include the library code:
#include <LiquidCrystal.h>
#include<SoftwareSerial.h>
SoftwareSerial seriall (10, 11); //rx,tx

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 53, en = 51, d4 = 49, d5 = 47, d6 = 45, d7 = 43;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int K, Kk = 1, b2;

//char str[2],i;

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
        lcd.print("BLCN");
        delayy();
        Kk = 0;
      }

      delayy();
      break;
    }

    else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("BTNTCN");
      delayy();
    }

  } while (K == LOW);

  while (Serial.available()) {
    b2 = digitalRead(12);
    if (b2 == HIGH)
      break;

    char k = Serial.read();

    switch (k)
    {
      case 'F':
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("FORWARD");
        delayy();
        break;

      case 'B':
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("BACKWARD");
        delayy();
        //lcd.clear();
        break;

      case 'L':
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("LEFT");
        delayy();
        //lcd.clear();
        break;

      case 'R':
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("RIGHT");
        delayy();
        //lcd.clear();
        break;

      case 'S':
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("STOP");
        delayy();
        //lcd.clear();
        break;

      default:
        break;
    }

  }

  if (b2 == HIGH) {

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

  }

}

void delayy() {
  delay(250);
}
