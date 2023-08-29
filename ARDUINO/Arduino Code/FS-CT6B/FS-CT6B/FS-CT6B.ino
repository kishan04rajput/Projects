int in0 = A0, in1 = A1, in2 = A2, in0v, in1v, in2v, ml1 = 2, ml2 = 3, mr1 = 4, mr2 = 5, mls = 10, mrs = 11;
char s;
void setup() {
  // put your setup code here, to run once:
  //input from receiver
  pinMode(in0, INPUT);
  pinMode(in1, INPUT);
  pinMode(in2, INPUT);
  //motor
  pinMode(ml1, OUTPUT);
  pinMode(ml2, OUTPUT);
  pinMode(mr1, OUTPUT);
  pinMode(mr2, OUTPUT);
  //motor speed
  pinMode(mls, OUTPUT);
  pinMode(mrs, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  in0v = map(pulseIn(in0, HIGH), 1100, 1800, 0, 255);
  in1v = map(pulseIn(in1, HIGH), 1100, 1800, 0, 255);
  in2v = map(pulseIn(in2, HIGH), 1100, 1800, 0, 255);
  if (in2v <= 20)
    in2v = 0;
  analogWrite(mls, in2v);
  analogWrite(mrs, in2v);
  if (in0v < 110)
  {
    s = 'l';
  }
  else if (in0v > 200)
  {
    s = 'r';
  }
  if (in1v < 110)
  {
    s = 'b';
  }
  else if (in1v > 140)
  {
    s = 'f';
  }
  switch (s)
  {
    case 'f':
      digitalWrite(ml1, 1);
      digitalWrite(ml2, 0);
      digitalWrite(mr1, 1);
      digitalWrite(mr2, 0);
      break;
    case 'b':
      digitalWrite(ml1, 0);
      digitalWrite(ml2, 1);
      digitalWrite(mr1, 0);
      digitalWrite(mr2, 1);
      break;
    case 'l':
      digitalWrite(ml1, 1);
      digitalWrite(ml2, 0);
      digitalWrite(mr1, 0);
      digitalWrite(mr2, 1);
      break;
    case 'r':
      digitalWrite(ml1, 0);
      digitalWrite(ml2, 1);
      digitalWrite(mr1, 1);
      digitalWrite(mr2, 0);
      break;
    default:
      digitalWrite(ml1, 0);
      digitalWrite(ml2, 0);
      digitalWrite(mr1, 0);
      digitalWrite(mr2, 0);
      break;
  }
  Serial.println(s);
  delay(10);
  s = 0;
}
