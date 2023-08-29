int buzzer = 8, ldr = A0, ldrs;
void setup() {
  // put your setup code here, to run once:
  pinMode(buzzer, OUTPUT);
  pinMode(ldr, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  ldrs = analogRead(ldr);
  ldrs = map(ldrs, 0, 1023, 50, 20000);
  tone(buzzer, ldrs);
}
