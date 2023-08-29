#include <LiquidCrystal.h>
LiquidCrystal lcd(12, A0, A4, A3, A2, A1);    //(rs, en, d4,d5, d6, d7);
int speed = 202, k = 3, s = 0, state = A5, z = 1;

//0 left
//1 right
//L293D
//Motor A
const int motorPin1  = 6, motorPin2  = 9;    // LEFT MOTOR
//Motor B
const int motorPin3  = 3, motorPin4  = 5;    // RIGHT MOTOR

void speedometer() {
  switch (speed) {
    case 0:   lcd.setCursor(15, 1); lcd.print("0"); break;
    case 25:  lcd.setCursor(15, 1); lcd.print("1"); break;
    case 50:  lcd.setCursor(15, 1); lcd.print("2"); break;
    case 75:  lcd.setCursor(15, 1); lcd.print("3"); break;
    case 100: lcd.setCursor(15, 1); lcd.print("4"); break;
    case 125: lcd.setCursor(15, 1); lcd.print("5"); break;
    case 150: lcd.setCursor(15, 1); lcd.print("6"); break;
    case 175: lcd.setCursor(15, 1); lcd.print("7"); break;
    case 200: lcd.setCursor(15, 1); lcd.print("8"); break;
    case 225: lcd.setCursor(15, 1); lcd.print("9"); break;
    case 255: lcd.setCursor(15, 1); lcd.print(" "); break;
    default:  lcd.setCursor(15, 1); lcd.print("8"); break;
  }
}

void stop() {
  lcd.setCursor(15, 1); lcd.print("0");
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
}

void ctbt() {
  if (k == 0) {
    s = digitalRead(state);
    if (s == LOW)
    {
      lcd.setCursor(15, 0);
      lcd.write(byte(0));
      if (z == 1)
      {
        lcd.setCursor(0, 0);
        lcd.print("   BLUETOOTH");
        lcd.setCursor(0, 1);
        lcd.print("  DISCONNECTED");
        stop();
        //      speedcontrol();
        speedometer();
        while (1) {
          s = digitalRead(state);
          if (s == HIGH)
          {
            lcd.setCursor(0, 0);
            lcd.print("   BLUETOOTH");
            lcd.setCursor(0, 1);
            lcd.print("   CONNECTED    ");
            break;
          }
        }
      }
    }
    else {
      if (z == 1) {
        lcd.setCursor(15, 0);
        lcd.write(byte(1));
      }
      else {
        lcd.setCursor(15, 0);
        lcd.print("  ");
      }
    }
  }
}

void forward() {
  ctbt();
  speedometer();
  digitalWrite(motorPin3, LOW);
  analogWrite(motorPin4, speed);
  digitalWrite(motorPin1, LOW);
  analogWrite(motorPin2, speed);
}

void backward() {
  ctbt();
  speedometer();
  analogWrite(motorPin3, speed);
  digitalWrite(motorPin4, LOW);
  analogWrite(motorPin1, speed);
  digitalWrite(motorPin2, LOW);
}

void right() {
  ctbt();
  speedometer();
  digitalWrite(motorPin1, LOW);
  analogWrite(motorPin2, speed);
  analogWrite(motorPin3, speed);
  digitalWrite(motorPin4, LOW);
}

void left() {
  ctbt();
  speedometer();
  digitalWrite(motorPin3, LOW);
  analogWrite(motorPin4, speed);
  analogWrite(motorPin1, speed);
  digitalWrite(motorPin2, LOW);
}
