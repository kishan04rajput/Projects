#include<LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);//RS, EN, D4, D5, D6, D7
byte c[8] = {
  B00000,
  B00000,
  B00100,
  B00000,
  B01110,
  B01110,
  B01110,
  B01110,
};
byte c0[8] = {
  B00000,
  B00000,
  B01000,
  B00000,
  B01110,
  B01110,
  B01110,
  B01110,
};
byte c1[8] = {
  B00000,
  B00000,
  B00010,
  B00000,
  B01110,
  B01110,
  B01110,
  B01110,
};
byte c2[8]={
  B00000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B00000,
};
byte c3[8]={
  B00000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B11000,
  B00000,
};
byte c4[8]={
  B00000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10100,
  B11000,
  B00000,
};
byte c5[8]={
  B00000,
  B10000,
  B10000,
  B10000,
  B10010,
  B10100,
  B11000,
  B00000,
};
byte c6[8]={
  B00000,
  B10000,
  B10000,
  B10010,
  B10010,
  B10100,
  B11000,
  B00000,
};
byte c7[8]={
  B00000,
  B10000,
  B10100,
  B10010,
  B10010,
  B10100,
  B11000,
  B00000,
};
byte c8[8]={
  B00000,
  B11000,
  B10100,
  B10010,
  B10010,
  B10100,
  B11000,
  B00000,
};
void setup(){
  lcd.begin(16,2);
  lcd.createChar(0, c);
  lcd.createChar(1, c0);
  lcd.createChar(2, c1);
  lcd.createChar(3, c2);
  lcd.createChar(4, c3);
  lcd.createChar(5, c4);
  lcd.createChar(6, c5);
  lcd.createChar(7, c6);
  //lcd.createChar(8, c7);
  //lcd.createChar(9, c8);
  }

void loop(){
  lcd.clear();
  cake();
  ca1();
  lcd.setCursor(5,0);
  lcd.print("H");
  ca1();
  d();
  lcd.setCursor(6,0);
  lcd.print("A");
  ca1();
  d();
  lcd.setCursor(7,0);
  lcd.print("P");
  ca1();
  d();
  lcd.setCursor(8,0);
  lcd.print("P");
  ca1();
  d();
  lcd.setCursor(9,0);
  lcd.print("Y");
  ca1();
  d();
  lcd.setCursor(4,1);
  lcd.print("B");
  ca1();
  d();
  lcd.setCursor(5,1);
  lcd.print("I");
  ca1();
  d();
  lcd.setCursor(6,1);
  lcd.print("R");
  ca1();
  d();
  lcd.setCursor(7,1);
  lcd.print("T");
  ca1();
  d();
  lcd.setCursor(8,1);
  lcd.print("H");
  ca1();
  d();
  lcd.setCursor(9,1);
  lcd.print("D");
  ca1();
  d();
  lcd.setCursor(10,1);
  lcd.print("A");
  ca1();
  d();
  lcd.setCursor(11,1);
  lcd.print("Y");
  ca1();
  d();
  lcd.clear();
  cake();
  ca1();
  lcd.setCursor(5,0);
  lcd.print("D");
  /*lcd.write(char(3));
  delay(100);
  lcd.setCursor(5,0);
  lcd.write(char(4));
  delay(100);
  lcd.setCursor(5,0);
  lcd.write(char(5));
  delay(100);
  lcd.setCursor(5,0);
  lcd.write(char(6));
  delay(100);
  lcd.setCursor(5,0);
  lcd.write(char(7));
  delay(100);
  lcd.setCursor(5,0);
  lcd.write(char(8));
  delay(100);
  lcd.setCursor(5,0);
  lcd.write(char(9));*/
  ca1();
  d();
  lcd.setCursor(6,0);
  lcd.print("I");
  ca1();
  d();
  lcd.setCursor(7,0);
  lcd.print("N");
  ca1();
  d();
  lcd.setCursor(8,0);
  lcd.print("E");
  ca1();
  d();
  lcd.setCursor(9,0);
  lcd.print("S");
  ca1();
  d();
  lcd.setCursor(10,0);
  lcd.print("H");
  ca1();
  d();
  lcd.setCursor(4,1);
  lcd.print("B");
  ca1();
  d();
  lcd.setCursor(5,1);
  lcd.print("H");
  ca1();
  d();
  lcd.setCursor(6,1);
  lcd.print("A");
  ca1();
  d();
  lcd.setCursor(7,1);
  lcd.print("D");
  ca1();
  d();
  lcd.setCursor(8,1);
  lcd.print("A");
  ca1();
  d();
  lcd.setCursor(9,1);
  lcd.print("N");
  ca1();
  d();
  lcd.setCursor(10,1);
  lcd.print("E");
  ca1();
  d();
}

void d(){
  delay(300);
}
void cake(){
  lcd.clear();
  delay(200);
  lcd.setCursor(0,1);
  lcd.print(char(255));
  lcd.print(char(255));
  lcd.print(char(255));
  lcd.setCursor(13,1);
  lcd.print(char(255));
  lcd.print(char(255));
  lcd.print(char(255));
  delay(500);
  lcd.setCursor(1,0);
  lcd.write(byte(0));
  lcd.setCursor(14,0);
  lcd.write(byte(0));
  delay(500);
}
void ca1(){
 lcd.setCursor(1,0);
  lcd.write(byte(1));
  de();
  lcd.setCursor(14,0);
  lcd.write(byte(1));
  de();
  lcd.setCursor(1,0);
  lcd.write(byte(0));
  lcd.setCursor(14,0);
  lcd.write(byte(0));
  de();
  lcd.setCursor(1,0);
  lcd.write(byte(2));
  de();
  lcd.setCursor(14,0);
  lcd.write(byte(2));
  de(); 
  lcd.setCursor(1,0);
  lcd.write(byte(0));
  lcd.setCursor(14,0);
  lcd.write(byte(0));
}
void de(){
  delay(100);
}
  
