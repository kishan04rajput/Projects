//UPDATE
//conditioned changed from if to else if.
//speed controlled pins are reduced from EN to MOTOR PINS.
//precise direction control.
int in0 = A0, in1 = A1, in2 = A2, in0v, in1v, in2v, ml1 = 8, ml2 = 9, mr1 = 10, mr2 = 11;
char s;
void setup() {
  // put your setup code here, to run once:
  //INPUT FROM RECEIVER
  pinMode(in0, INPUT);
  pinMode(in1, INPUT);
  pinMode(in2, INPUT);
  //MOTOR
  pinMode(ml1, OUTPUT);
  pinMode(ml2, OUTPUT);  // motor speed
  pinMode(mr1, OUTPUT);
  pinMode(mr2, OUTPUT);  // motor speed
  //LED
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  //SERIAL COMMUNICATION STARTS
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  in0v = map(pulseIn(in0, HIGH), 1100, 1800, 0, 255);  //left,right
  in1v = map(pulseIn(in1, HIGH), 1100, 1800, 0, 255);  //backward,forward
  in2v = map(pulseIn(in2, HIGH), 1100, 1800, 0, 255);  //speed
  /*Serial.print("LR=");
    Serial.println(in0v);
    Serial.print("FB=");
    Serial.println(in1v);*/
  if (in2v <= 20) //throttle thershold value 20
  {
    in2v = 0;
  }
  if (in1v > 140 && in0v < 110 && in0v > -30)
  {
    digitalWrite(ml1, 1);
    analogWrite(ml2, in2v / 2);
    digitalWrite(mr1, 1);
    analogWrite(mr2, in2v);
  }
  else if (in1v > 140 && in0v > 200)
  {
    digitalWrite(ml1, 1);
    analogWrite(ml2, in2v);
    digitalWrite(mr1, 1);
    analogWrite(mr2, in2v / 2);
  }
  else if (in1v < 110 && in1v > -30 && in0v < 110 && in0v > -30)
  {
    digitalWrite(ml1, 0);
    analogWrite(ml2, in2v / 2);
    digitalWrite(mr1, 0);
    analogWrite(mr2, in2v);
  }
  else if (in1v < 110 && in1v > -30 && in0v > 200)
  {
    digitalWrite(ml1, 0);
    analogWrite(ml2, in2v);
    digitalWrite(mr1, 0);
    analogWrite(mr2, in2v / 2);
  }
  else if (in0v < 110 && in0v > -30)
  {
    digitalWrite(ml1, 1);
    analogWrite(ml2, in2v);
    digitalWrite(mr1, 0);
    analogWrite(mr2, in2v);
  }
  else if (in0v > 200)
  {
    digitalWrite(ml1, 0);
    analogWrite(ml2, in2v);
    digitalWrite(mr1, 1);
    analogWrite(mr2, in2v);
  }
  else if (in1v < 110 && in1v > -30) //  if -> else if
  {
    digitalWrite(ml1, 0);
    analogWrite(ml2, in2v);
    digitalWrite(mr1, 0);
    analogWrite(mr2, in2v);
  }
  else if (in1v > 140)
  {
    digitalWrite(ml1, 1);
    analogWrite(ml2, in2v);
    digitalWrite(mr1, 1);
    analogWrite(mr2, in2v);
  }
  else
  {
    digitalWrite(ml1, 0);
    digitalWrite(ml2, 0);
    digitalWrite(mr1, 0);
    digitalWrite(mr2, 0);
  }
  delay(10);
}
