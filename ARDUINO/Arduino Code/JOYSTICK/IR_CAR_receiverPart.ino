//RX CAR SIDE
#include <IRremote.h>
int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  // put your setup code here, to run once:
pinMode(10,OUTPUT);
pinMode(9,OUTPUT);
pinMode(12,OUTPUT);
pinMode(13,OUTPUT);
Serial.begin(9600);

 irrecv.enableIRIn();
}

void loop() {
  // put your main code here, to run repeatedly:
   if (irrecv.decode(&results)) {
    unsigned long x=results.value;
    irrecv.resume(); // Receive the next value
    Serial.println(x);
    if(x==2160022444)//forward      2160022444 is just the decimal value of the hex number 80BF53AC
       {
      digitalWrite(10,HIGH);
      digitalWrite(9,LOW );
      digitalWrite(12,LOW );
      digitalWrite(13,HIGH );
       }
      else if(x==2160020404)//backward
      {
      digitalWrite(10,LOW);
      digitalWrite(9,HIGH );
      digitalWrite(12,HIGH );
      digitalWrite(13,LOW );}
  
      else if(x==2160034684)//right
      {
       digitalWrite(10,LOW );
      digitalWrite(9,LOW);
      digitalWrite(12,LOW );
      digitalWrite(13,HIGH);       
      }
      else if(x==2160040294)//left
      {
       digitalWrite(10,HIGH );
      digitalWrite(9,LOW);
      digitalWrite(12,LOW );
      digitalWrite(13,LOW);
      }
        else //stop      at any other joy position the car will stop
      {
      digitalWrite(10,LOW );
      digitalWrite(9,LOW);
      digitalWrite(12,LOW );
      digitalWrite(13,LOW);
      }
      }
       }
