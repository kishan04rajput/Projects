#include<Servo.h>
Servo servo;
const int trigPin = 4;//underwala
const int echoPin = 5;
const int trigPin1 = 6;//baharwala
const int echoPin1 = 7;
//const int m11 = 8, m12 = 9;
long duration;
int distance;
long duration1;
int distance1, c = 1, k;
void setup()
{
  //Set Exact Baud rate of the GSM/GPRS Module.
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);
  pinMode(trigPin1, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin1, INPUT);
//  pinMode(m11, OUTPUT);
 // pinMode(m12, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A0, OUTPUT);
  servo.attach(8);
}
void loop()
{
  digitalWrite(A0, 1);
  digitalWrite(A1, 0);
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
  Serial.print("Distance: ");
  Serial.println(distance);
  //UNDERWALA
  if (distance <= 40 && c == 1)
  {
    Serial.print("\r");
    delay(1000);
    Serial.print("AT+CMGF=1\r");
    delay(1000);
    /*Replace XXXXXXXXXX to 10 digit mobile number &  ZZ to 2 digit country code*/
    Serial.print("AT+CMGS=\"+919773287994\"\r");
    delay(1000);
    //The text of the message to be sent.
    Serial.print("AB ME  BHAR CHUKI HU!!!!");
    delay(1000);
    Serial.write(0x1A);
    delay(1000);
    c = 0;
  }
  if (distance <= 40)
    digitalWrite(10, 1); //red LED//uner wala jab full hojayega tab
  else
    digitalWrite(10, 0);
  if (distance >= 40)
    digitalWrite(11, 1); //blue led
  else
    digitalWrite(11, 0);
  //if (distance >= 40)
  //c = 0;

  //bahar wala
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
  Serial.print("Distance baharwala: ");
  Serial.println(distance1);
  if (distance1 <= 40 && k==0)
  {
  //  digitalWrite(m11, 1);
    //digitalWrite(m12, 0);
    //delay(1000);//man marzi ke hisab se set karna hai door open ke liye
    servo.write(180);
    k = 1;
  }
  if (distance1 >= 40 && k == 1)
  {
//    digitalWrite(m11, 0);
  //  digitalWrite(m12, 1);
  servo.write(0);
    delay(1000);//darvaja band hoga to kitne time ke liye band hoga
    k = 0;
    c = 1;
  }
}
