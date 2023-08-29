#include <LiquidCrystal.h>
LiquidCrystal lcd(A5, A4, A3, A2, A1, 12); //(rs, en, d4, d5, d6, d7)
int flame = 2, buzzer = 3, motor1 = 4, motor2 = 5, led = 13, lm35 = A0;
int flamev;
int temp;
void setup() {
  // put your setup code here, to run once:
  pinMode(flame, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(lm35, OUTPUT);
  digitalWrite(buzzer, 0);
  digitalWrite(motor1, 0);
  digitalWrite(motor2, 0);
  digitalWrite(led, 0);
  lcd.begin(16, 2);
  lcd.print("WELCOME");
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.clear();
  temp = analogRead(lm35);
  temp = map(temp, 0, 308, 0, 150);
  //  temp = (temp/1024)*500 ;
  flamev = digitalRead(flame);
  if (flamev == HIGH || temp >= 85) {
    digitalWrite(buzzer, 1);
    digitalWrite(motor1, 1);
    digitalWrite(motor2, 0);
    lcd.print("Fire Detected");
    lcd.setCursor(0, 1);
    lcd.print("Temp:");
    lcd.setCursor(5, 1);
    lcd.print(temp);
    digitalWrite(led, 1);
  }
  else {
    digitalWrite(buzzer, 0);
    digitalWrite(motor1, 0);
    digitalWrite(motor2, 0);
    lcd.print("All Good");
    lcd.setCursor(0, 1);
    lcd.print("Temp:");
    lcd.setCursor(5, 1);
    lcd.print(temp);
    digitalWrite(led, 0);
  }
  delay(400);
}
