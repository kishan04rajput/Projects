void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT); //Gear up button
  //pinMode(A1, INPUT); //Gear down button
  //pinMode(2, OUTPUT); //Gear up indication
  //pinMode(3, OUTPUT); //Gear down indication
  pinMode(4, OUTPUT); //Both button indication
  //digitalWrite(2, HIGH);
  //digitalWrite(3, HIGH);
  //digitalWrite(4, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(A0) == HIGH)
  {
    digitalWrite(4, HIGH);
   // digitalWrite(3, LOW);
    //digitalWrite(2, LOW);
  }
  if(digitalRead(A0) == LOW);
  {
    digitalWrite(4, LOW);
  }
  /*else if (digitalRead(A1) == HIGH)
  {
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
  }
  else if (digitalRead(A0) == HIGH && digitalRead(A1) == HIGH)
  {
    digitalWrite(4, LOW);
    digitalWrite(3, LOW);
    digitalWrite(2, HIGH);
  }
  else
  {
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  }*/
}
