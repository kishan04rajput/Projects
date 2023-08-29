void setup() {
  // put your setup code here, to run once:
  DDRD = 00111100;//2,3,4,5:OUTPUT
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    switch (Serial.read())
    {
      case 'F':
        PORTD |= 00010100;//2,4,HIGH
        break;
      case 'B':
        PORTD |= 00101000;//3,5,HIGH
        break;
      case 'L':
        PORTD |= 00011000;//3,4,HIGH
        break;
      case 'R':
        PORTD |= 00100100;//2,5,HIGH
        break;
      default:
        PORTD &= 00000000;//2,3,4,5,LOW
    }
  }
}
