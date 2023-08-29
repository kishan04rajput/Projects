void setup() {
  // put your setup code here, to run once:
DDRB = 100000;
}

void loop() {
  // put your main code here, to run repeatedly:
PORTB |= 100000;
delay(20);
PORTB &= 000000;
delay(20);
}
