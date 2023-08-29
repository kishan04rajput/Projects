#include "A1SpecialCharacters.h"
#include "A2UltrasonicSensors.h"
#include "A3MotorCode.h"

int led = 13, l;

//BLUETOOTH
char ch, str[2], i;

void setup() {
  //BLUETOOTH
  pinMode(state, INPUT);

  //BLUETOOTH SYMBOL
  lcd.createChar(0, bluetoothsymbol);

  //SMILY
  lcd.createChar(1, smily);

  //MOTOR
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);

  //ULTRASONIC SENSOR
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(trigPin0, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin0, INPUT); // Sets the echoPin as an Input
  pinMode(trigPin1, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin1, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600);// Starts the serial communication

  //LED
  pinMode(led, OUTPUT);

  //LCD
  lcd.begin(16, 2);
  lcd.setCursor(3, 0);
  lcd.print("WELCOME TO");
  lcd.setCursor(6, 1);
  lcd.print("AOAR");
  delay(3000);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("PLZ... CONNECT");
  lcd.setCursor(2, 1);
  lcd.print("TO BLUETOOTH");
  s = digitalRead(state);
}

void loop() {

  if (s == LOW) {
    s = digitalRead(state);
  }

  if (k >= 1) {

    if (s == HIGH)
    {

      while (k >= 1) {

        if (k == 3) {
          lcd.clear();
          lcd.setCursor(3, 0);
          lcd.print("BLUETOOTH");
          lcd.setCursor(3, 1);
          lcd.print("CONNECTED");
          delay(1000);
        }

        lcd.clear();
        lcd.setCursor(4, 0);
        lcd.print("READY IN");
        lcd.setCursor(4, 1);
        lcd.print(k);
        k--;
        delay(1000);

        if (k == 0) {
          lcd.clear();
          lcd.setCursor(7, 0);
          lcd.print("GO");
          delay(1000);
          lcd.setCursor(15, 1); lcd.print("0");
          // lcd.setCursor(15, 0); lcd.print(" ");
        }
      }
    }
  }

  ctbt();

  //BLUETOOTH

  while (Serial.available())
  {

    char ch = Serial.read();
    str[i++] = ch;

    if (ch == 'w') {
      //STOP
      stop();
      lcd.clear();
      lcd.setCursor(5, 0);
      lcd.print("MANUAL");
      lcd.setCursor(6, 1);
      lcd.print("MODE");
      z = 1;
      speedometer();
    }

    while (ch == 'W')
    {

      if (z == 1) {
        lcd.clear();
        lcd.setCursor(3, 0);
        lcd.print("AUTOMATIC");
        lcd.setCursor(6, 1);
        lcd.print("MODE");
        speedometer();
        delay(1000);
        z--;
      }

      char ch = Serial.read();

      if (ch == 'w') {
        //STOP
        stop();
        lcd.clear();
        lcd.setCursor(5, 0);
        lcd.print("MANUAL");
        lcd.setCursor(6, 1);
        lcd.print("MODE");
        z = 1;
        speedometer();
        break;
      }

      //ULTRASONIC SENSOR

      sensor();

      //SENSOR 2

      sensor2();

      //SENSOR 3

      sensor3();


      switch (ch) {
        case '0': speed = 0;   break;
        case '1': speed = 25;  break;
        case '2': speed = 50;  break;
        case '3': speed = 75;  break;
        case '4': speed = 100; break;
        case '5': speed = 125; break;
        case '6': speed = 150; break;
        case '7': speed = 175; break;
        case '8': speed = 200; break;
        case '9': speed = 225; break;
        case 'q': speed = 255; break;
      }


      //speedcontrol();

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("GOING");
      lcd.setCursor(0, 1);
      lcd.print("FORWARD");

      if (distance0 <= 10) {
        //TURNING RIGHT
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("TURNING");
        lcd.setCursor(0, 1);
        lcd.print("RIGHT");
        right();
        delay(500);
      }

      else if (distance1 <= 10) {
        //TURNING LEFT
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("TURNING");
        lcd.setCursor(0, 1);
        lcd.print("LEFT");
        digitalWrite(led, HIGH);
        left();
        delay(1000);
      }

      //MAIN

      else if (distance <= 30)
      {
        //TURNING LEFT
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("TURNING");
        lcd.setCursor(0, 1);
        lcd.print("LEFT");
        digitalWrite(led, HIGH);
        left();
        delay(1000);

        if (distance0 <= 30) {
          //TURNING RIGHT
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("TURNING");
          lcd.setCursor(0, 1);
          lcd.print("RIGHT");
          right();
          delay(500);

          if (distance1 <= 30) {

            for (; distance0 <= 30 || distance1 <= 30;)
            {
              //GOING BACKWARD
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("GOING");
              lcd.setCursor(0, 1);
              lcd.print("BACKWARD");
              backward();
              delay(1000);
              l++;

              //SENSOR 2 left

              sensor2();

              //SENSOR 3 right

              sensor3();
            }

            if (l > 0) {
              delay(1000);
              l = 0;

              //SENSOR 2 left

              sensor2();

              //SENSOR 3 right

              sensor3();

              if (distance0 < distance1) {
                //TURNING RIGHT
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("TURNING");
                lcd.setCursor(0, 1);
                lcd.print("RIGHT");
                right();
                delay(1000);
              }

              else {
                //LEFT
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("TURNING");
                lcd.setCursor(0, 1);
                lcd.print("LEFT");
                left();
                delay(1000);
              }
            }
          }
        }
      }

      else {
        //FORWARD
        digitalWrite(led, LOW);
        forward();
      }
    }

    //    manual:

    switch (ch) {
      case 'L':
        lcd.clear();
        lcd.setCursor(5, 0);
        lcd.print("MANUAL");
        lcd.setCursor(6, 1);
        lcd.print("LEFT");
        Serial.println("Left");
        left();
        break;

      case 'F':
        lcd.clear();
        lcd.setCursor(5, 0);
        lcd.print("MANUAL");
        lcd.setCursor(4, 1);
        lcd.print("FORWARD");
        Serial.println("Forward");
        //speedometer();
        forward();
        break;

      case'R':
        lcd.clear();
        lcd.setCursor(5, 0);
        lcd.print("MANUAL");
        lcd.setCursor(5, 1);
        lcd.print("RIGHT");
        Serial.println("Right");
        right();
        break;

      case'B':
        lcd.clear();
        lcd.setCursor(5, 0);
        lcd.print("MANUAL");
        lcd.setCursor(4, 1);
        lcd.print("BACKWARD");
        Serial.println("Backward");
        backward();
        break;

      case'U':
      case'u':
        lcd.clear();
        lcd.setCursor(5, 0);
        lcd.print("MANUAL");
        lcd.setCursor(6, 1);
        lcd.print("STOP");
        Serial.println("STOP");
        stop();
        break;

      case '0': speed = 0;   break;
      case '1': speed = 25;  break;
      case '2': speed = 50;  break;
      case '3': speed = 75;  break;
      case '4': speed = 100; break;
      case '5': speed = 125; break;
      case '6': speed = 150; break;
      case '7': speed = 175; break;
      case '8': speed = 200; break;
      case '9': speed = 225; break;
      case 'q': speed = 255; break;
      default :            ; break;

    }
  }
}
