int pwm = 3, i;
void setup() {
  // put your setup code here, to run once:
  pinMode(pwm, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (i = 0; i <= 255; i++)
  {
    analogWrite(pwm, i);
    delay(10);
    if (i == 255)
    {
      for (i; i >= 0; i--)
      {
        analogWrite(pwm, i);
        delay(10);
      }
    }
  }
}
