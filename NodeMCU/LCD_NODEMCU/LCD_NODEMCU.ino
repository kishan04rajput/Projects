#include <LiquidCrystal.h>
const int RS = D2, EN = D3, d4 = D4, d5 = D5, d6 = D6, d7 = D7;   
LiquidCrystal lcd(RS, EN, d4, d5, d6, d7);

void setup() {
  pinMode(D8,OUTPUT);
                         // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
                      // Print a message to the LCD.
  lcd.print("hello, world!");
  analogWrite(D8,0);
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis() / 1000);
}
