char data = 0;
void setup() {
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
}

void loop() {
  data = Serial.read();
  //   Serial.print(data);
  // Serial.print("\n");
  //   digitalWrite(9, HIGH);
  // digitalWrite(6,LOW);
  // digitalWrite(3, HIGH);
  // digitalWrite(5,LOW);
  if (data == '1')
    digitalWrite(3, HIGH);
  else
    digitalWrite(3, LOW);
  if (data == '2')
    digitalWrite(5, HIGH);
  else(digitalWrite(5, LOW));
  if (data == '3')
    digitalWrite(6, HIGH);
  else(digitalWrite(6, LOW));
  if (data == '4')
    digitalWrite(9, HIGH);
  else(digitalWrite(9, LOW));


}
