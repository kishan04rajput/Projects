int cnt=0;
int state;
int laststate=1;
void setup() {
  // put your setup code here, to run once:
  pinMode(D0,INPUT);
  Serial.begin(9600);
  state = 0;
}


void loop() {
  // put your main code here, to run repeatedly:
  int x = digitalRead(D0);
  if(x==1 && !state)
    {
      state = 1;  
    }else if(x==0 && state)
  {
      cnt= cnt+1;
      Serial.println(cnt);
      state = 0;
    }
    delay(100);
    
}
