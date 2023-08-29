// defines pins numbers
const int trigPin0 = 52;
const int echoPin0 = 50;

const int trigPin1 = 48;
const int echoPin1 = 46;

const int trigPin2 = 44;
const int echoPin2 = 42;

const int trigPin3 = 40;
const int echoPin3 = 38;

const int led=13;

// defines variables
long duration0;
int distance0;

long duration1;
int distance1;

long duration2;
int distance2;

long duration3;
int distance3;

void setup() {
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

pinMode(led, OUTPUT);
digitalWrite(led, LOW);
Serial.begin(9600); // Starts the serial communication
}

void loop() {
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
distance0= duration0*0.034/2;

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
distance1= duration1*0.034/2;

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
distance2= duration2*0.034/2;

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
distance3= duration3*0.034/2;

// Prints the distance on the Serial Monitor
Serial.print("Distance0: ");
Serial.println(distance0);

Serial.print("Distance1: ");
Serial.println(distance1);

Serial.print("Distance2: ");
Serial.println(distance2);

Serial.print("Distance3: ");
Serial.println(distance3);
if(distance0<30)
digitalWrite(led, HIGH);
if(distance0>30)
digitalWrite(led, LOW);
}
