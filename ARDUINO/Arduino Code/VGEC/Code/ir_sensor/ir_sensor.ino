//int cnt=0;
//int flag;
//int laststate=1;
void setup() {
  // put your setup code here, to run once:
  pinMode(A0,INPUT);
  Serial.begin(9600);
/*  flag = 0;*/
}


void loop() {
  // put your main code here, to run repeatedly:
  int x = analogRead(A0);
  Serial.println(x);
  float c = (x*3.3*100)/(1024);
  Serial.println(c);
  /*
  if(x==1 && !flag)
    {
      flag = 1;  
    }else if(x==0 && flag)
  {
      cnt= cnt+1;
      Serial.println(cnt);
      flag = 0;
    }
   */
    delay(1000);
    
}
