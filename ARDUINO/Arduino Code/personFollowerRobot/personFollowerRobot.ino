int pir = 2, irl = 3, irr = 4, in1 = 8, in2 = 7, in3 = 6, in4 = 5, led = 13;
void setup() {
  pinMode(pir,INPUT);
  pinMode(irl,INPUT);
  pinMode(irr,INPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
}

void loop() {
  int IRL = digitalRead(irl);
  int IRR = digitalRead(irr);
  while (IRL == LOW && IRR ==LOW){
    forward();
    stop();
    int PIR = digitalRead(pir);
    delay(100);
    if (PIR == HIGH){
      digitalWrite(led,HIGH);
    }
    IRL = digitalRead(irl);
    IRR = digitalRead(irr);
    if (IRL == HIGH || IRR == HIGH)
    break;
    right();
    forward();
    stop();
    PIR = digitalRead(pir);
    delay(100);
    if (PIR == HIGH){
      digitalWrite(led,HIGH);
    }
    IRL = digitalRead(irl);
    IRR = digitalRead(irr);
    if (IRL == HIGH || IRR == HIGH)
    break;   
  }
  if (IRL == HIGH && IRR == LOW){
    right();
    IRR = digitalRead(irr);
    if (IRR == HIGH)
    backward();
  }
  if (IRL == LOW && IRR == HIGH){
    left();
    IRL = digitalRead(irl);
    if (IRL == HIGH)
    backward();
  }
  if (IRL == HIGH && IRR == HIGH){
    backward();
  }
}
void forward(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(1000);
}

void left(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);  
  delay(1000);
}

void right(){
  
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(1000);
}

void backward(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);  
  delay(1000);
}

void stop(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW); 
  delay(5); 
}

