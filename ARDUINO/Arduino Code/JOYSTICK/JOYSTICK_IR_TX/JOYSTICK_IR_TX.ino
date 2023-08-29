//TX REMOTE SIDE
#include<IRremote.h>  
IRsend irsend;
void setup() {
  // put your setup code here, to run once:
pinMode(A0,INPUT);
pinMode(A1,INPUT);
//pinMode(A2,INPUT);
//Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
int x= map(analogRead(A0),0,1023,0,10);
int y= map(analogRead(A1),0,1023,0,10);
//int z= map(analogRead(A2),0,1023,0,10);
//Serial.print(String(x)+"  "+String(y)+"  "+String(z)+"\n");
if(x==0 && y==5)
{
   irsend.sendNEC(0x80BF53AC,32);//up    the 80BF53AC is just a HEX code
}
else if(x==10 && y==5)
{
    irsend.sendNEC(0x80BF4BB4,32);//dwn
}
else if(x==5 && y==0)
{
   irsend.sendNEC(0x80BF9966,32);
}
else if(x==5 && y==10)
{
  irsend.sendNEC(0x80BF837C,32);
}
else
{
  irsend.sendNEC(0x70CA9977,32);
}
delay(500);
}
