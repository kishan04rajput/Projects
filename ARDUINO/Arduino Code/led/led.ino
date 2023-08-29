int led=13;
void setup() {
  pinMode(led,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(4,OUTPUT);
  // put your setup code here, to run once:

}

void loop() {
  digitalWrite(led,HIGH);
  delay(1000);
  digitalWrite(led,LOW);
  delay(1000);
  digitalWrite(2,HIGH);
  digitalWrite(4,LOW);
  // put your main code here, to run repeatedly:

}
