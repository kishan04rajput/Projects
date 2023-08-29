int outputPin = 8;//pin 8 will generate output
char k;
void setup() {
  // put your setup code here, to run once:
  pinMode(outputPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available())
  {
    k = Serial.read();
    if (k == 'N')//when N is received the output will be active
      digitalWrite(outputPin, 1);
    else if (k == 'F')//when F is received the output will be passive
      digitalWrite(outputPin, 0);
  }

}
