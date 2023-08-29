int trigPin1 = 9;
int trigPin2 = 10;
int echoPin1 = 11;
int echoPin2 = 12;
int revright = 4;      //REVerse motion of Right motor
int fwdright = 5;       //ForWarD motion of Right motor
int redled = 7;      
int blueled = 8;       
int rx = 0;
int tx = 1;
const int enablem1Pin3 = 6;
//const int enablem2Pin3 = 3;

void setup() {
  //Serial.begin(9600); 
   pinMode(5, OUTPUT);
   pinMode(6, OUTPUT);
   pinMode(4, OUTPUT);
   pinMode(7, OUTPUT);
   pinMode(trigPin1, OUTPUT);
   pinMode(trigPin2, OUTPUT);
   pinMode(echoPin1, INPUT);
   pinMode(echoPin2, INPUT);
   pinMode(2,INPUT);
   pinMode(1,OUTPUT);
   pinMode(enablem1Pin3, OUTPUT);
   //pinMode(enablem2Pin3, OUTPUT);
  // put your setup code here, to run once:
   
  //Set Exact Baud rate of the GSM/GPRS Module.
  Serial.begin(9600);  
  Serial.print("\r");
  //delay(10);                  
  Serial.print("AT+CMGF=1\r");    
  //delay(10);
  /*Replace XXXXXXXXXX to 10 digit mobile number &  ZZ to 2 digit country code*/
  Serial.print("AT+CMGS=\"+919773287994\"\r");    
  //delay(10);
  //The text of the message to be sent.
  Serial.print("HD");   
  //delay(10);
  Serial.write(0x1A);
  //delay(10); 

}

void loop() 
{
  long duration, distance;                              //ultrasonic sensor 1
  digitalWrite(trigPin1,HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin1, LOW);
  duration=pulseIn(echoPin1, HIGH);
  distance =(duration/2)/29.1;
  //Serial.print(distance);
  //Serial.println("CM");
  delay(10);
 
  
  if((distance>20))
 {
  digitalWrite(5,HIGH);                               //       If you dont get proper movements of your robot,
   digitalWrite(4,LOW);                               //        then alter the pin numbers
   digitalWrite(enablem1Pin3, HIGH);
   //digitalWrite(6,LOW);                               //
   //digitalWrite(7,HIGH);                              //
 }
 
  else if(distance<20)  
 {
   digitalWrite(5,HIGH);
   digitalWrite(4,LOW);
   digitalWrite(enablem1Pin3, LOW);
   //digitalWrite(6,HIGH);                                  //HIGH
   //digitalWrite(7,LOW);
                                            
 }
  long duration1, distance1;                            //ultrasonic sensor 2
  digitalWrite(trigPin2,HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin2, LOW);
  duration1=pulseIn(echoPin2, HIGH);
  distance1 =(duration/2)/29.1;
  //Serial.print(distance);
  //Serial.println("CM");
  delay(10);
 
  if((distance>5))
 {
  digitalWrite(8,HIGH);
  digitalWrite(7,LOW);                             
  digitalWrite(1,LOW);      
  digitalWrite(0,HIGH); 
 }
 
  else if(distance<5)  
 {
  digitalWrite(7,HIGH);
  digitalWrite(8,LOW);                             
  digitalWrite(0,LOW);      
  digitalWrite(1,HIGH);                                          
 }

}
