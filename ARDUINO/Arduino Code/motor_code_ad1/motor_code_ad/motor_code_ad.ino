#include <LiquidCrystal.h>
LiquidCrystal lcd(12, A0, A4, A3, A2, A1);
//0 left
//1 right
//L293D
//Motor A
const int motorPin1  = 4;  // Pin 14 of L293 LEFT MOTOR
const int motorPin2  = 5;  // Pin 10 of L293 LEFT MOTOR
//Motor B
const int motorPin3  = 2; // Pin  7 of L293 RIGHT MOTOR
const int motorPin4  = 3;  // Pin  2 of L293 RIGHT MOTOR
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
int s=0;

//BLUETOOTH
char ch;
char str[2],i;
int state=A5;
int k=3;
int z=1;

void setup(){
  //BLUETOOTH
  pinMode(state,INPUT);
 
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
  lcd.setCursor(3,0);
  lcd.print("WELCOME TO");
  lcd.setCursor(6,1);
  lcd.print("AOAR");
  delay(3000);
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("PLZ... CONNECT");
  lcd.setCursor(2,1);
  lcd.print("TO BLUETOOTH");
  s=digitalRead(state);
}
void loop(){
  if(s==LOW){
  s=digitalRead(state);
  }
  if(k>=1){
  if(s==HIGH)
  {
    while(k>=1){
      if(k==3){
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("BLUETOOTH");
  lcd.setCursor(3,1);
  lcd.print("CONNECTED");
  delay(1000);
      }
      
    lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("READY IN");
  lcd.setCursor(4,1);
  lcd.print(k);
  k--;
  delay(1000);
  if(k==0){
    lcd.clear();
  lcd.setCursor(7,0);
  lcd.print("GO");
  delay(1000);
  }
    }
  }
  }
  //BLUETOOTH
    while(Serial.available())
    {
        char ch=Serial.read();
        str[i++]=ch;
        if(ch=='w'){
        digitalWrite(motorPin3, LOW);
        digitalWrite(motorPin4, LOW);
        digitalWrite(motorPin1, LOW);
        digitalWrite(motorPin2, LOW);
        lcd.clear();
        lcd.setCursor(5,0);
        lcd.print("MANUAL");
        lcd.setCursor(6,1);
        lcd.print("MODE");
        z=1;
        }
        while(str[i-1]=='W')
        { 
          if(z==1){
        lcd.clear();
        lcd.setCursor(3,0);
        lcd.print("AUTOMATIC");
        lcd.setCursor(6,1);
        lcd.print("MODE");
        delay(1000);
        z--;
          }
        char ch=Serial.read();
        if(ch=='w'){
        digitalWrite(motorPin3, LOW);
        digitalWrite(motorPin4, LOW);
        digitalWrite(motorPin1, LOW);
        digitalWrite(motorPin2, LOW);
        lcd.clear();
        lcd.setCursor(5,0);
        lcd.print("MANUAL");
        lcd.setCursor(6,1);
        lcd.print("MODE");
        z=1;
        break;
        }
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
      delay(1000);
      l=0;

      
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


    //SENSOR 3 right
    //RIGHT
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


    //RIGHT
         if(distance0<distance1){
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
      delay(1000);
      }
      else{
        //LEFT
        lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("TURNING");
      lcd.setCursor(0,1);
      lcd.print("LEFT");
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
    //str[i++]=ch;
       }
       // for lcd
//       lcd.setCursor(0, 1);
// lcd.print(millis() / 1000);
//str[i=i+1]=ch;
        }
        

    //    manual:
        if(str[i-1]=='F')
        {
          lcd.clear();
          lcd.setCursor(5,0);
      lcd.print("MANUAL");
      lcd.setCursor(4,1);
      lcd.print("FORWARD");
   Serial.println("Forward");
   digitalWrite(motorPin3, LOW);
   digitalWrite(motorPin4, HIGH);
   //delay(100);
   digitalWrite(motorPin1, LOW);
   digitalWrite(motorPin2, HIGH);
//     forward;
     i=0;
     }

        else if(str[i-1]=='L')
    {
      lcd.clear();
      lcd.setCursor(5,0);
      lcd.print("MANUAL");
      lcd.setCursor(6,1);
      lcd.print("LEFT");
     Serial.println("Left");
     digitalWrite(motorPin3, LOW);
   digitalWrite(motorPin4, HIGH);
   //delay(100);
   digitalWrite(motorPin1, HIGH);
   digitalWrite(motorPin2, LOW);
//     right;
     i=0;
    }

    else if(str[i-1]=='R')
    {
      lcd.clear();
      lcd.setCursor(5,0);
      lcd.print("MANUAL");
      lcd.setCursor(5,1);
      lcd.print("RIGHT");
      Serial.println("Right");
      digitalWrite(motorPin3, HIGH);
   digitalWrite(motorPin4, LOW);
   //delay(100);
   digitalWrite(motorPin1, LOW);
   digitalWrite(motorPin2, HIGH);
//      left;
      i=0;
    }

     else if(str[i-1]=='B')
    {
      lcd.clear();
      lcd.setCursor(5,0);
      lcd.print("MANUAL");
      lcd.setCursor(4,1);
      lcd.print("BACKWARD");
      Serial.println("Backward");
       digitalWrite(motorPin3, HIGH);
   digitalWrite(motorPin4, LOW);
   digitalWrite(motorPin1, HIGH);
   digitalWrite(motorPin2, LOW);
//      backward;
      i=0;
    }

    else if(str[i-1]=='U' || str[i-1]=='u')
    {
      lcd.clear();
      lcd.setCursor(5,0);
      lcd.print("MANUAL");
      lcd.setCursor(6,1);
      lcd.print("STOP");
      Serial.println("top");
      digitalWrite(motorPin3, LOW);
   digitalWrite(motorPin4, LOW);
   digitalWrite(motorPin1, LOW);
   digitalWrite(motorPin2, LOW);
//      top;
      i=0;
    }
 }
    }
//}
//}
