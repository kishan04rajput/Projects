#include<Servo.h>
Servo servo;
int button = 2, red_led = 3, green_led = 4, pos, buttons;
void setup() {
  // put your setup code here, to run once:
  pinMode(button, INPUT);
  pinMode(red_led, OUTPUT);
  pinMode(green_led, OUTPUT);
  servo.attach(9);
  servo.write(0);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttons = digitalRead(button);
  if (buttons == HIGH)
  {
    digitalWrite(green_led, 1);
    digitalWrite(red_led, 0);
    for (pos = 0; pos < 90; pos++)
    {
      servo.write(pos);
      delay(15);
    }
    delay(5000);
  }
  digitalWrite(green_led, 0);
  digitalWrite(red_led, 1);
  for (pos; pos > 0; pos--)
  {
    servo.write(pos);
    delay(15);
  }
}
