#include <LiquidCrystal.h>
LiquidCrystal lcd(12, A0, A4, A3, A2, A1); //RS,EN,D4,D5,D6,D7
//0 left
//1 right
//L293D
//Motor A
const int motorPin1  = 4; // LEFT MOTOR
const int motorPin2  = 5; // LEFT MOTOR
//Motor B
const int motorPin3  = 2; // RIGHT MOTOR
const int motorPin4  = 3; // RIGHT MOTOR
//ultrasonic sensor
const int trigPin = 6; //FRONT SENSOR
const int echoPin = 7;
const int trigPin0 = 8; //LEFT SENSOR
const int echoPin0 = 9;
const int trigPin1 = 10; //RIGHT SENSOR
const int echoPin1 = 11;
long duration; //FRONT SENSOR
long duration0; //LEFT SENSOR
long duration1; //RIGHT SENSOR

int distance; //FRONT SENSOR
int distance0; //LEFT SENSOR
int distance1; //RIGHT SENSOR
int led = 13;
int l;
int s = 0;
//BLUETOOTH
char ch;
char str[2];
char i;
int state = A5;
int k = 3;
int z = 1;
int j = 0;
int a = 0;

void setup() {
  //BLUETOOTH
  pinMode(state, INPUT);

  //MOTOR
  pinMode(motorPin1, OUTPUT); //LEFT MOTOR //4
  pinMode(motorPin2, OUTPUT); //LEFT MOTOR //5
  pinMode(motorPin3, OUTPUT); //RIGHT MOTOR //2
  pinMode(motorPin4, OUTPUT); //RIGHT MOTOR //3

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
  lcd.setCursor(0, 0);
  lcd.print("PLZ...CONNECT   ");
  lcd.setCursor(0, 1);
  lcd.print("TO BLUETOOTH    ");
j=1;
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
        delay(1000);
        k--;

        if (k == 0) {
          lcd.clear();
          lcd.setCursor(7, 0);
          lcd.print("GO");
          delay(1000);
        }
      }
    }
  }

  //BLUETOOTH

s = digitalRead(state);

if( s == LOW){
  lcd.setCursor(14,0);
  lcd.print("CT");
  lcd.setCursor(14,1);
  lcd.print("BT");
}
else{
  lcd.setCursor(14,0);
  lcd.print("  ");
  lcd.setCursor(14,1);
  lcd.print("  ");
}

  while (Serial.available())
  {

    char ch = Serial.read();
    str[i++] = ch;

    if (ch == 'w') {
      //STOP
      stop();
      s = digitalRead(state);
      if ( s == LOW) {
        lcd.clear();
        lcd.print("     MANUAL   CT");
        lcd.setCursor(0, 1);
        lcd.print("      MODE    BT");
      }
      else {
        lcd.clear();
        lcd.setCursor(5, 0);
        lcd.print("MANUAL");
        lcd.setCursor(6, 1);
        lcd.print("MODE");
        z = 1;
      }
    }

    while (str[i - 1] == 'W')
    {

      if (z == 1) {
        s = digitalRead(state);
        if ( s == LOW) {
          lcd.clear();
          lcd.print("   AUTOMATIC  CT");
          lcd.setCursor(0, 1);
          lcd.print("      MODE    BT");
        }
        else {
          lcd.clear();
          lcd.setCursor(3, 0);
          lcd.print("AUTOMATIC");
          lcd.setCursor(6, 1);
          lcd.print("MODE");
          delay(1000);
          z--;
        }
      }

      char ch = Serial.read();

      if (ch == 'w') {
        //STOP
        stop();
        s = digitalRead(state);
        if ( s == LOW) {
          lcd.clear();
          lcd.print("     MANUAL   CT");
          lcd.setCursor(0, 1);
          lcd.print("      MODE    BT");
        }
        else {
          lcd.clear();
          lcd.setCursor(5, 0);
          lcd.print("MANUAL");
          lcd.setCursor(6, 1);
          lcd.print("MODE");
          z = 1;
          break;
        }
      }

      //ULTRASONIC SENSOR

      sensor();

      //SENSOR 2

      sensor2();

      //SENSOR 3

      sensor3();

      s = digitalRead(state);
      if ( s == LOW) {
        lcd.clear();
        lcd.print("GOING         CT");
        lcd.setCursor(0, 1);
        lcd.print("FORWARD       BT");
      }
      else {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("GOING");
        lcd.setCursor(0, 1);
        lcd.print("FORWARD");
      }

      if (distance0 <= 10) {
        //TURNING RIGHT
        s = digitalRead(state);
        if ( s == LOW) {
          lcd.clear();
          lcd.print("TURNING       CT");
          lcd.setCursor(0, 1);
          lcd.print("RIGHT         BT");
          digitalWrite(led, HIGH);
          right();
        }
        else {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("TURNING");
          lcd.setCursor(0, 1);
          lcd.print("RIGHT");
          digitalWrite(led, HIGH);
          right();
          //delay(500);
        }
      }

      else if (distance1 <= 10) {
        //TURNING LEFT
        s = digitalRead(state);
        if ( s == LOW) {
          lcd.clear();
          lcd.print("TURNING       CT");
          lcd.setCursor(0, 1);
          lcd.print("LEFT          BT");
          digitalWrite(led, HIGH);
          left();
        }
        else {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("TURNING");
          lcd.setCursor(0, 1);
          lcd.print("LEFT");
          digitalWrite(led, HIGH);
          left();
          //delay(1000);
        }
      }

      //MAIN

      else if (distance <= 30)
      {

        if (distance0 <= 10) {
          //TURNING RIGHT
          s = digitalRead(state);
          if ( s == LOW) {
            lcd.clear();
            lcd.print("TURNING       CT");
            lcd.setCursor(0, 1);
            lcd.print("RIGHT         BT");
            digitalWrite(led, HIGH);
            right();
          }
          else {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("TURNING");
            lcd.setCursor(0, 1);
            lcd.print("RIGHT");
            digitalWrite(led, HIGH);
            right();
          }
        }

        if (distance0 >= 10) {
          //TURNING LEFT
          s = digitalRead(state);
          if ( s == LOW) {
            lcd.clear();
            lcd.print("TURNING       CT");
            lcd.setCursor(0, 1);
            lcd.print("LEFT          BT");
            digitalWrite(led, HIGH);
            left();
          }
          else {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("TURNING");
            lcd.setCursor(0, 1);
            lcd.print("LEFT");
            digitalWrite(led, HIGH);
            left();
            //delay(1000);
          }
        }

        //LEFT SENSOR
        sensor2();

        //RIGHT SENSOR
        sensor3();

        if (distance0 <= 30) {
          //TURNING RIGHT
          s = digitalRead(state);
          if ( s == LOW) {
            lcd.clear();
            lcd.print("TURNING       CT");
            lcd.setCursor(0, 1);
            lcd.print("RIGHT         BT");
            digitalWrite(led, HIGH);
            right();
          }
          else {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("TURNING");
            lcd.setCursor(0, 1);
            lcd.print("RIGHT");
            right();
            //delay(500);
          }

          if (distance1 <= 30) {

            for (; distance0 <= 30 || distance1 <= 30;)
            {
              //GOING BACKWARD
              s = digitalRead(state);
              if ( s == LOW) {
                lcd.clear();
                lcd.print("GOING         CT");
                lcd.setCursor(0, 1);
                lcd.print("BACKWARD      BT");
                digitalWrite(led, HIGH);
                backward();
                l++;
              }
              else {
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("GOING");
                lcd.setCursor(0, 1);
                lcd.print("BACKWARD");
                backward();
                //  delay(1000);
                l++;
              }

              //SENSOR 2 left

              sensor2();

              //SENSOR 3 right

              sensor3();
            }

            if (l > 0) {
              //  delay(1000);
              l = 0;

              //SENSOR 2 left

              sensor2();

              //SENSOR 3 right

              sensor3();

              if (distance0 < distance1) {
                //TURNING RIGHT
                s = digitalRead(state);
                if ( s == LOW) {
                  lcd.clear();
                  lcd.print("TURNING       CT");
                  lcd.setCursor(0, 1);
                  lcd.print("RIGHT         BT");
                  digitalWrite(led, HIGH);
                  right();
                  delay(500);
                }
                else {
                  lcd.clear();
                  lcd.setCursor(0, 0);
                  lcd.print("TURNING");
                  lcd.setCursor(0, 1);
                  lcd.print("RIGHT");
                  right();
                  delay(500);
                }
              }

              else {
                //LEFT
                s = digitalRead(state);
                if ( s == LOW) {
                  lcd.clear();
                  lcd.print("TURNING       CT");
                  lcd.setCursor(0, 1);
                  lcd.print("LEFT          BT");
                  digitalWrite(led, HIGH);
                  left();
                }
                else {
                  lcd.clear();
                  lcd.setCursor(0, 0);
                  lcd.print("TURNING");
                  lcd.setCursor(0, 1);
                  lcd.print("LEFT");
                  left();
                  //delay(1000);
                }
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
/*s = digitalRead(state);
if(s == LOW){
  lcd.setCursor(15,0);
  lcd.print("BT");
  lcd.setCursor(15,1);
  lcd.print("CT");
}*/
    if (str[i - 1] == 'F')
    {
      //lcd.clear();
      lcd.setCursor(5, 0);
      lcd.print("MANUAL");
      lcd.setCursor(4, 1);
      lcd.print("FORWARD");
      Serial.println("Forward");
      forward();
      i = 0;
      j = 1;
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
      j = 'L';
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
      j = 'R';
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
      j = 'B';
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
      j = 'U';
      a = 'u';
    }

/*s = digitalRead(state);

if(j == 1){
    if ( s == LOW){
      lcd.setCursor(15,0);
      lcd.print("                BT");
      lcd.setCursor(15,1);
      lcd.print("                CT");
      forward();
    }
}*/
  }
}

void forward() {
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
}

void backward() {
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  delay(500);
}

void stop() {
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
}

void right() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  delay(500);
}

void left() {
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  delay(1500);
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
