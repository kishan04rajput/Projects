#include <LiquidCrystal.h>
LiquidCrystal lcd(12, A0, A4, A3, A2, A1);
//0 left
//1 right
//L293D
//Motor A
const int motorPin1  = 4, motorPin2  = 5; // LEFT MOTOR
//Motor B
const int motorPin3  = 2, motorPin4  = 3; // RIGHT MOTOR
//ultrasonic sensor
const int trigPin = 6, echoPin = 7, trigPin0 = 8, echoPin0 = 9, trigPin1 = 10, echoPin1 = 11;
long duration, duration0, duration1;
int distance, distance0, distance1, led = 13, l, s = 0;

//BLUETOOTH
char ch, str[2], i;
int state = A5, k = 3, z = 1;

//BLUETOOTH SYMBOL
byte bluetoothsymbol[] = {
  B00110,
  B10101,
  B01101,
  B00110,
  B01101,
  B10101,
  B00110,
  B00000,
};

byte smily[] = {
  B00000,
  B00000,
  B01010,
  B00000,
  B10001,
  B01110,
  B00000,
  B00000,
};

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
    }

    while (str[i - 1] == 'W')
    {

      if (z == 1) {
        lcd.clear();
        lcd.setCursor(3, 0);
        lcd.print("AUTOMATIC");
        lcd.setCursor(6, 1);
        lcd.print("MODE");
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
        break;
      }

      //ULTRASONIC SENSOR

      sensor();

      //SENSOR 2

      sensor2();

      //SENSOR 3

      sensor3();

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

    if (str[i - 1] == 'F')
    {
      lcd.clear();
      lcd.setCursor(5, 0);
      lcd.print("MANUAL");
      lcd.setCursor(4, 1);
      lcd.print("FORWARD");
      Serial.println("Forward");
      forward();
      i = 0;
    }

    else if (str[i - 1] == 'L')
    {
      lcd.clear();
      lcd.setCursor(5, 0);
      lcd.print("MANUAL");
      lcd.setCursor(6, 1);
      lcd.print("LEFT");
      Serial.println("Left");
      left();
      i = 0;
    }

    else if (str[i - 1] == 'R')
    {
      lcd.clear();
      lcd.setCursor(5, 0);
      lcd.print("MANUAL");
      lcd.setCursor(5, 1);
      lcd.print("RIGHT");
      Serial.println("Right");
      right();
      i = 0;
    }

    else if (str[i - 1] == 'B')
    {
      lcd.clear();
      lcd.setCursor(5, 0);
      lcd.print("MANUAL");
      lcd.setCursor(4, 1);
      lcd.print("BACKWARD");
      Serial.println("Backward");
      backward();
      i = 0;
    }

    else if (str[i - 1] == 'U' || str[i - 1] == 'u')
    {
      lcd.clear();
      lcd.setCursor(5, 0);
      lcd.print("MANUAL");
      lcd.setCursor(6, 1);
      lcd.print("STOP");
      Serial.println("STOP");
      stop();
      i = 0;
    }
  }
}

void forward() {
  ctbt();
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
}

void backward() {
  ctbt();
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
}

void stop() {
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
}

void right() {
  ctbt();
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
}

void left() {
  ctbt();
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
  digitalWrite(motorPin1, HIGH);
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

void sensor() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("distance: ");
  Serial.println(distance);
}

void sensor2() {
  // Clears the trigPin
  digitalWrite(trigPin0, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin0, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin0, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration0 = pulseIn(echoPin0, HIGH);
  // Calculating the distance
  distance0 = duration0 * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("distance0: ");
  Serial.println(distance0);
}

void sensor3() {
  // Clears the trigPin
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration1 = pulseIn(echoPin1, HIGH);
  // Calculating the distance
  distance1 = duration1 * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("distance1: ");
  Serial.println(distance1);
}
