#include <LiquidCrystal.h>

const int rs = 3, en = 4, d4 = 5, d5 = 6, d6 = 7, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int input = 2, s, l;
void setup() {
  //Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(input,INPUT);
  lcd.print("DOOR SENSOR");
  delay(1000);
  s = digitalRead(input);
  delay(1);
}

void loop() {
  while (s == LOW) {
    s = digitalRead(input);
    delay(1);
    if (s == HIGH)
      break;
  }
  while (s == HIGH) {
    if (l == 1);{
    lcd.clear();
    }
    s = digitalRead(input);
    delay(1);
    lcd.print("KOI NAHI BAKKA");
    lcd.setCursor(4, 1);
    lcd.print("SHANTI!!!");
    delay(500);
    l = 0;
    if (s == LOW) {
      lcd.clear();
      lcd.print("KOI APDA DOOR");
      lcd.setCursor(0, 1);
      lcd.print("AGAD UBHO CHE!!!");
      l = 1;
      break;
    }
  }
}
