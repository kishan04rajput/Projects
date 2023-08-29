const int m11=11 ;   // rear motor
const int m12=12;
const int m21=10 ;   // front motor
const int m22=9;
char str[2],i;
int forward;
int backward;
int left;
int right;
int top;

void setup() 
{
  Serial.begin(9600);
  pinMode(m11, OUTPUT);
  pinMode(m12, OUTPUT);
  pinMode(m21, OUTPUT);
  pinMode(m22, OUTPUT);
}

void loop() 
{
  while(Serial.available())
  {

    char ch=Serial.read();
   str[i++]=ch;
    
    if(str[i-1]=='F')
    {
     Serial.println("Forward");
   digitalWrite(m11, HIGH);
   digitalWrite(m12, LOW);
   //delay(100);
   digitalWrite(m21, HIGH);
   digitalWrite(m22, LOW);
     forward;
     i=0;
    }

    else if(str[i-1]=='L')
    {
     Serial.println("Left");
     digitalWrite(m11, HIGH);
   digitalWrite(m12, LOW);
   //delay(100);
   digitalWrite(m21, LOW);
   digitalWrite(m22, HIGH);
     right;
     i=0;
    }

    else if(str[i-1]=='R')
    {
      Serial.println("Right");
      digitalWrite(m11, LOW);
   digitalWrite(m12, HIGH);
   //delay(100);
   digitalWrite(m21, HIGH);
   digitalWrite(m22, LOW);
      left;
      i=0;
    }





/*void forward()
{
   digitalWrite(m11, LOW);
   digitalWrite(m12, LOW);
   digitalWrite(m21, HIGH);
   digitalWrite(m22, LOW);
}*/

/*void backward()
{
   digitalWrite(m11, LOW);
   digitalWrite(m12, LOW);
   digitalWrite(m21, LOW);
   digitalWrite(m22, HIGH); 
}*/

/*void left()
{
   digitalWrite(m11, HIGH);
   digitalWrite(m12, LOW);
   delay(100);
   digitalWrite(m21, HIGH);
   digitalWrite(m22, LOW);
}*/

/*void right()
{
   digitalWrite(m11, LOW);
   digitalWrite(m12, HIGH);
   delay(100);
   digitalWrite(m21, HIGH);
   digitalWrite(m22, LOW);
}*/

/*void top()
{
   digitalWrite(m11, LOW);
   digitalWrite(m12, LOW);
   digitalWrite(m21, LOW);
   digitalWrite(m22, LOW);
}*/




    /*char ch=Serial.read();
    str[i++]=ch;
    
    if(str[i-1]=='1')
    {
     Serial.println("Forward");
     forward;
     i=0;
    }

    else if(str[i-1]=='2')
    {
     Serial.println("Left");
     right;
     i=0;
    }

    else if(str[i-1]=='3')
    {
      Serial.println("Right");
      left;
      i=0;
    }*/
    
    else if(str[i-1]=='B')
    {
      Serial.println("Backward");
       digitalWrite(m11, LOW);
   digitalWrite(m12, HIGH);
   digitalWrite(m21, LOW);
   digitalWrite(m22, HIGH);
      backward;
      i=0;
    }

    else if(str[i-1]=='S')
    {
      Serial.println("top");
      digitalWrite(m11, LOW);
   digitalWrite(m12, LOW);
   digitalWrite(m21, LOW);
   digitalWrite(m22, LOW);
      top;
      i=0;
    }
    delay(100);
  }
}

