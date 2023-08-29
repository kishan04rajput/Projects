#include <LiquidCrystal.h>
LiquidCrystal lcd(12, A0, A4, A3, A2, A1);
//0 left
//1 right
//L293D
//Motor A
const int motorPin1  = 4;  // Pin 14 of L293
const int motorPin2  = 5;  // Pin 10 of L293
//Motor B
const int motorPin3  = 2; // Pin  7 of L293
const int motorPin4  = 3;  // Pin  2 of L293
//ultrasonic sensor
const int trigPin = 6;
const int echoPin = 7;
const int trigPin0 = 8;
const int echoPin0 = 9;
const int trigPin1 = 10;
const int echoPin1 = 11;
long duration;
long duration0;
long duration1;
int distance;
int distance0;
int distance1;
int led = 13;
int l;
//int p = 8;
//int po = 12;
//const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup(){
 
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
    Serial.begin(9600); // Starts the serial communication
    //LED
    pinMode(led, OUTPUT);
//    pinMode(p, OUTPUT);
//     lcd.begin(16, 2);
 
//  lcd.print("stop!");

//LCD
 lcd.begin(16, 2);
  // Print a message to the LCD.
  //lcd.print("hello, world!");
 // pinMode(A1,OUTPUT);
  //pinMode(A2,OUTPUT);
  //pinMode(A3,OUTPUT);
  //pinMode(A4,OUTPUT);
}
void loop(){
//    digitalWrite(p, HIGH);
//    digitalWrite(po, HIGH);
    
    /*/MOTORS
    
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, HIGH);
    */
    //ULTRASONIC SENSOR
    
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
    distance= duration*0.034/2;
    // Prints the distance on the Serial Monitor
    Serial.print("distance: ");
    Serial.println(distance);

    //SENSOR 2
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
    distance0= duration0*0.034/2;
    // Prints the distance on the Serial Monitor
    Serial.print("distance0: ");
    Serial.println(distance0);

    //SENSOR 3
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
    distance1= duration1*0.034/2;
    // Prints the distance on the Serial Monitor
    Serial.print("distance1: ");
    Serial.println(distance1);
    lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("GOING");
      lcd.setCursor(0,1);
      lcd.print("FORWARD");

       if(distance0<=10){
        
        
        //TURNING RIGHT
        lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("TURNING");
      lcd.setCursor(0,1);
      lcd.print("RIGHT");
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, HIGH);
      digitalWrite(motorPin3, HIGH);
      digitalWrite(motorPin4, LOW);
      delay(500);
       }

      else if(distance1<=10){
        //TURNING LEFT
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("TURNING");
      lcd.setCursor(0,1);
      lcd.print("LEFT");
      digitalWrite(led, HIGH);
      digitalWrite(motorPin1, HIGH);
      digitalWrite(motorPin2, LOW);
      digitalWrite(motorPin3, LOW);
      digitalWrite(motorPin4, HIGH);
      delay(1000);
      }

      //MAIN
    else if(distance<=30)
    {
      
      
      //TURNING LEFT
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("TURNING");
      lcd.setCursor(0,1);
      lcd.print("LEFT");
      digitalWrite(led, HIGH);
      digitalWrite(motorPin1, HIGH);
      digitalWrite(motorPin2, LOW);
      digitalWrite(motorPin3, LOW);
      digitalWrite(motorPin4, HIGH);
      delay(1000);
      //do
      //{
      if(distance0<=30){
        
        
        //TURNING RIGHT
        lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("TURNING");
      lcd.setCursor(0,1);
      lcd.print("RIGHT");
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, HIGH);
      digitalWrite(motorPin3, HIGH);
      digitalWrite(motorPin4, LOW);
      delay(500);
      
     // delay(800);
    // do
    // {
     if(distance1<=30){
      //while(distance0 <30 && distance1 <30)
     //{
     for(;distance0 <= 30 || distance1 <= 30;)
     {

      //if(distance0 >30){
        //if(distance1 >30)
          //break;

          
      //GOING BACKWARD
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("GOING");
      lcd.setCursor(0,1);
      lcd.print("BACKWARD");
      digitalWrite(motorPin1, HIGH);
      digitalWrite(motorPin2, LOW);
      digitalWrite(motorPin3, HIGH);
      digitalWrite(motorPin4, LOW);
      delay(1000);
      l++;
      /*if(distance0>30 && distance1>30){
      digitalWrite(motorPin1, HIGH);
      digitalWrite(motorPin2, LOW);
      digitalWrite(motorPin3, LOW);
      digitalWrite(motorPin4, HIGH);
      delay(800);
      }*
      /*if(distance0>30)
      digitalWrite(motorPin1, HIGH);
      digitalWrite(motorPin2, LOW);
      digitalWrite(motorPin3, LOW);
      digitalWrite(motorPin4, HIGH);
      delay(800);*/

          //SENSOR 2 left
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
    distance0= duration0*0.034/2;
    // Prints the distance on the Serial Monitor
    Serial.print("distance0: ");
    Serial.println(distance0);

    
    /*if(distance0>30 && distance1>30){
      digitalWrite(motorPin1, HIGH);
      digitalWrite(motorPin2, LOW);
      digitalWrite(motorPin3, LOW);
      digitalWrite(motorPin4, HIGH);
      delay(800);
    }*/
      

    //SENSOR 3 right
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
    distance1= duration1*0.034/2;
    // Prints the distance on the Serial Monitor
    Serial.print("distance1: ");
    Serial.println(distance1);

    

    
      //if(distance0 >30 || distance1 >30)
        //break;
     }

     if(l>0){

      
      //SENSOR 2 left
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
    distance0= duration0*0.034/2;
    // Prints the distance on the Serial Monitor
    Serial.print("distance0: ");
    Serial.println(distance0);

    //RIGHT
         if(distance0<=30){
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, HIGH);
      digitalWrite(motorPin3, HIGH);
      digitalWrite(motorPin4, LOW);
      delay(500);
      }
      else{
        //LEFT
      digitalWrite(motorPin1, HIGH);
      digitalWrite(motorPin2, LOW);
      //delay(5000);
      digitalWrite(motorPin3, LOW);
      digitalWrite(motorPin4, HIGH);
      delay(1000);
     }
     }
      //}
      //delay(3);
    }
      //if(distance0 >30 /*|| distance1 >30*/)
       // break;
      //}while(distance0 <=30 && distance1<=30);
      }//while(distance0 <=30 && distance1<=30);
    /*else if(distance1<=30){
      digitalWrite(motorPin1, HIGH);
      digitalWrite(motorPin2, LOW);
      digitalWrite(motorPin3, LOW);
      digitalWrite(motorPin4, HIGH);
      //delay(800);
    }*/
   /* else if(distance0&&distance1<=30){
      digitalWrite(motorPin1, HIGH);
      digitalWrite(motorPin2, LOW);
      digitalWrite(motorPin3, HIGH);
      digitalWrite(motorPin4, LOW);
      //delay(800);
    }*/
    }
    else{
        digitalWrite(led, LOW);
        digitalWrite(motorPin1, LOW);
        digitalWrite(motorPin2, HIGH);
        digitalWrite(motorPin3, LOW);
        digitalWrite(motorPin4, HIGH);
    
       }
       // for lcd
//       lcd.setCursor(0, 1);
// lcd.print(millis() / 1000);
 }
