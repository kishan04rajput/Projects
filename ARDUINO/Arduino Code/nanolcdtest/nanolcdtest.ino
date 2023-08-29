#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);//rs, en, d4, d5, d6, d7
void setup() {
  lcd.begin(16,2);
  lcd.print("HELLO WORLD");

}

void loop() {
  // put your main code here, to run repeatedly:

}
