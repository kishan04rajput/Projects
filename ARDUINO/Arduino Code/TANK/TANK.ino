//pin connection
//lcd: 1: gnd; 2: vcc; 3:gnd; 4:2; 5:gnd; 6:3; 7,8,9,10:not connected; 11:4; 12:5; 13:6; 14:7; 15:vcc; 16:gnd;
//motor driver: in1 = 10, in2 = 11, in3 = 12, in4 = 13;
//sensors: temp = A0, gas = A1, pir = A2;
//servo: horizontal:9; vertical:8;
#include<LiquidCrystal.h>
#include<Servo.h>
LiquidCrystal lcd (2, 3, 4, 5, 6, 7); //rs,en,d4,d5,d6,d7
Servo servov, servoh;
int anglev, angleh, in1 = 10, in2 = 11, in3 = 12, in4 = 13, temp = A0, gas = A1, pir = A2;
char b1;
void setup() {
  // put your setup code here, to run once:
  servov.attach(8);
  servoh.attach(9);
  Serial.begin(9600);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(temp, INPUT);
  pinMode(gas, INPUT);
  pinMode(pir, INPUT);
  digitalWrite(in1, 0);
  digitalWrite(in2, 0);
  digitalWrite(in3, 0);
  digitalWrite(in4, 0);
  servoh.write(0);
  servov.write(0);
  lcd.setCursor(0, 0);
  lcd.begin(16, 2);
  lcd.print("   CONNECT TO");
  lcd.setCursor(0, 1);
  lcd.print("    BLUETOOTH");
}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available())
  {
    b1 = Serial.read();
    if (b1 == 'W')
    {
      lcd.clear();
      lcd.print("GUN ACTIVATED");
      while (b1 != 'w')
      {
        b1 = Serial.read();
        if (b1 == 'F' && anglev <= 179)
        {
          lcd.setCursor(0, 1);
          lcd.print("UP               ");
          servov.write(anglev);
          anglev++;
        }
        else if (b1 == 'B' && anglev >= 1)
        {
          lcd.setCursor(0, 1);
          lcd.print("DOWN             ");
          servov.write(anglev);
          anglev--;
        }
        else if (b1 == 'L' && angleh <= 179)
        {
          lcd.setCursor(0, 1);
          lcd.print("LEFT             ");
          servoh.write(angleh);
          angleh++;
        }
        else if (b1 == 'R' && angleh >= 1)
        {
          lcd.setCursor(0, 1);
          lcd.print("RIGHT            ");
          servoh.write(angleh);
          angleh--;
        }
        else if (b1 == 'S')
        {
          lcd.setCursor(0, 1);
          lcd.print("                 ");
        }
        Serial.println(b1);
      }
    }
    if (b1 == 'F')
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("FORWARD");
      digitalWrite(in1, 1);
      digitalWrite(in2, 0);
      digitalWrite(in3, 1);
      digitalWrite(in4, 0);
    }
    else if (b1 == 'L')
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("LEFT");
      digitalWrite(in1, 0);
      digitalWrite(in2, 1);
      digitalWrite(in3, 1);
      digitalWrite(in4, 0);
    }
    else if (b1 == 'R')
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("RIGHT");
      digitalWrite(in1, 1);
      digitalWrite(in2, 0);
      digitalWrite(in3, 0);
      digitalWrite(in4, 1);
    }
    else if (b1 == 'B')
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("BACKWARD");
      digitalWrite(in1, 0);
      digitalWrite(in2, 1);
      digitalWrite(in3, 0);
      digitalWrite(in4, 1);
    }
    else if (b1 == 'S')
    {
      int  LM35 = analogRead(A0);
      LM35 = LM35 * 0.48828125;//5V
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("STOP");
      lcd.setCursor(0, 1);
      lcd.print(LM35);
      digitalWrite(in1, 0);
      digitalWrite(in2, 0);
      digitalWrite(in3, 0);
      digitalWrite(in4, 0);
      if (digitalRead(A1) == LOW)
      {
        lcd.setCursor(5, 1);
        lcd.print("GAS");
      }
      if (digitalRead(A2) == LOW)
      {
        lcd.setCursor(9, 1);
        lcd.print(" MOTION");
      }
      //delay(40);
    }
  }
}
