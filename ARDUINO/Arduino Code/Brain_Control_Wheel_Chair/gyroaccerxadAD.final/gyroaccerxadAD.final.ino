//receiver
// include the library code:
#include <LiquidCrystal.h>
#include<SoftwareSerial.h>
SoftwareSerial seriall (10, 11); //rx,tx//bluetooth mobile wala

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 53, en = 51, d4 = 49, d5 = 47, d6 = 45, d7 = 43;
const int m11 = 22;
const int m12 = 24;
const int m21 = 26;
const int m22 = 28;

//switch
const int kkk = 23;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int K, Kk = 1, b2, kkkk;

char str[2], i;

//ULTRASONIC SENSOR
const int trigPin0 = 52;//front ultrasonic
const int echoPin0 = 50;

const int trigPin1 = 48;//left ultrasonic
const int echoPin1 = 46;

const int trigPin2 = 44;//right ultrasonic
const int echoPin2 = 42;

const int trigPin3 = 40;//back ultrasonic
const int echoPin3 = 38;

long duration0;//front
int distance0;

long duration1;//left
int distance1;

long duration2;//right
int distance2;

long duration3;//back
int distance3;

void setup() {

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  pinMode(14, OUTPUT);//bluetooth gyro wala
  digitalWrite(14, HIGH);

  pinMode(8, OUTPUT);
  analogWrite(8, 255);

  pinMode(9, OUTPUT);
  analogWrite(9, 0);

  pinMode(2, INPUT);
  pinMode(12, INPUT);//Mobile bluetooth state
  pinMode(m11, OUTPUT);
  pinMode(m12, OUTPUT);
  pinMode(m21, OUTPUT);
  pinMode(m22, OUTPUT);

  //switch
  pinMode(kkk, INPUT);

  //BLUETOOTH
  Serial.begin(9600);

  seriall.begin(9600);

  //ULTRASONIC SENSOR
  //front
  pinMode(trigPin0, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin0, INPUT); // Sets the echoPin as an Input

  //left
  pinMode(trigPin1, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin1, INPUT); // Sets the echoPin as an Input

  //right
  pinMode(trigPin2, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin2, INPUT); // Sets the echoPin as an Input

  //back
  pinMode(trigPin3, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin3, INPUT); // Sets the echoPin as an Input

}

void loop() {

  do {
    K = digitalRead(2);

    if (K == HIGH) {
      lcd.clear();
      lcd.setCursor(0, 0);

      if (Kk > 0) {//Kk used as a ending variable to end this loop its default value is 1 when its turns to zero loop ends....
        lcd.print("GYROSCOPE");
        lcd.setCursor(0, 1);
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
      lcd.setCursor(0, 1);
      lcd.print("CONNECTED");
      delayy();
    }

  } while (K == LOW);

  while (Serial.available()) {
    b2 = digitalRead(12);//mobile bluetooth state
    if (b2 == HIGH) {
      lcd.print("MOBILE");
      lcd.setCursor(0, 1);
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
        kkkk = digitalRead(kkk);
        if (kkkk == HIGH)
        {
          //front ultrasonic
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
        }
        if (kkkk == LOW)
          distance0 = 31;
        if (distance0 < 30)
          stop();
        else {
          digitalWrite(m11, HIGH);
          digitalWrite(m12, LOW);
          //delay(100);
          digitalWrite(m21, HIGH);
          digitalWrite(m22, LOW);
          delayy();
        }
        break;

      case 'B':
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("BACKWARD");
        kkkk = digitalRead(kkk);
        if (kkkk == HIGH) {
          //back ultrasonic
          // Clears the trigPin
          digitalWrite(trigPin3, LOW);
          delayMicroseconds(2);

          // Sets the trigPin on HIGH state for 10 micro seconds
          digitalWrite(trigPin3, HIGH);
          delayMicroseconds(10);
          digitalWrite(trigPin3, LOW);

          // Reads the echoPin, returns the sound wave travel time in microseconds
          duration3 = pulseIn(echoPin3, HIGH);

          // Calculating the distance
          distance3 = duration3 * 0.034 / 2;
        }
        if (kkkk == LOW)
          distance3 = 31;
        if (distance3 > 30) {
          digitalWrite(m11, LOW);
          digitalWrite(m12, HIGH);
          digitalWrite(m21, LOW);
          digitalWrite(m22, HIGH);
        }
        else
          stop();
        delayy();
        //lcd.clear();
        break;

      case 'L':
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("LEFT");
        kkkk = digitalRead(kkk);
        if (kkkk == HIGH)
        {
          //left ultrasonic
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
        }
        if (kkkk == LOW)
          distance1 = 29;
        if (distance1 < 30)
        {
          digitalWrite(m11, HIGH);
          digitalWrite(m12, LOW);
          //delay(100);
          digitalWrite(m21, LOW);
          digitalWrite(m22, HIGH);
          delayy();
        }
        else
          stop();
        break;

      case 'R':
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("RIGHT");
        kkkk = digitalRead(kkk);
        if (kkkk == HIGH)
        {
          //right ultrasonic
          // Clears the trigPin
          digitalWrite(trigPin2, LOW);
          delayMicroseconds(2);

          // Sets the trigPin on HIGH state for 10 micro seconds
          digitalWrite(trigPin2, HIGH);
          delayMicroseconds(10);
          digitalWrite(trigPin2, LOW);

          // Reads the echoPin, returns the sound wave travel time in microseconds
          duration2 = pulseIn(echoPin2, HIGH);

          // Calculating the distance
          distance2 = duration2 * 0.034 / 2;
        }
        if (kkkk == LOW)
          distance2 = 31;
        if (distance2 > 30)
        {
          digitalWrite(m11, LOW);
          digitalWrite(m12, HIGH);
          //delay(100);
          digitalWrite(m21, HIGH);
          digitalWrite(m22, LOW);
        }
        else
          stop();
        delayy();
        //lcd.clear();
        break;

      case 'S':
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("STOP");
        stop();
        delayy();
        //lcd.clear();
        break;

      default:
        break;
    }

  }

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
      stop();
      //top;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("MANUAL STOP");
      delay(20);
      i = 0;
    }
  }
}

void delayy() {
  delay(200);
}

void stop() {
  digitalWrite(m11, LOW);
  digitalWrite(m12, LOW);
  digitalWrite(m21, LOW);
  digitalWrite(m22, LOW);
}
