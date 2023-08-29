
/*
  Node MCU ESP8266 1.0(12E)

  PROJECT TITLE - LED MATRIX USING NODEMCU BY SPI INTERFACE
  PROJECT CODENAMED - BEETRIX

  This sketch is Modified BY AKSHAY SANKLE(ZUKROS).

  Parts required:

  - LED
  - 74HC595 SHIFT REGISTER
  - CD4017 DECADE COUNTER
  - 100 kilohm resistor
  - 2N3904 Transistor

  Created by - Nematic!
  Modified 12 Nov 2019
  by Akshay Sankle.

  http://www.arduino.cc/starterKit

  This code will work for 24x6 LED MATRIX

  Source :- https://www.instructables.com/id/Make-Your-Own-LED-Matrix-/
*/
#include <SPI.h>
#define A {B01110000, B10001000, B10001000, B11111000, B10001000, B10001000}
#define B {B11110000,B10001000,B10001000,B11110000,B10001000,B11111000}
#define C {B11111000,B10000000,B10000000,B10000000,B10000000,B11111000}
#define D {B11110000,B10001000,B10001000,B10001000,B10001000,B11110000}
#define E {B11111000,B10000000,B10000000,B11110000,B10000000,B11111000}
#define F {B11111000,B10000000,B10000000,B11110000,B10000000,B10000000}
#define G {B01110000,B10001000,B10000000,B10011000,B10001000,B01110000}
#define H {B10001000,B10001000,B11111000,B10001000,B10001000,B10001000}
#define I {B11111000,B00100000,B00100000,B00100000,B00100000,B11111000}
#define J {B00111000,B00010000,B00010000,B00010000,B10010000,B01100000}
#define M {B10001000,B11011000,B10101000,B10101000,B10001000,B10001000}
#define N {B10001000,B11001000,B10101000,B10101000,B10011000,B10001000}
#define L {B10000000,B10000000,B10000000,B10000000,B10000000,B11111000}
#define O {B01110000,B10001000,B10001000,B10001000,B10001000,B01110000}
#define P {B11110000,B10001000,B10001000,B11110000,B10000000,B10000000}
#define Q {B01110000,B10001000,B10101000,B10011000,B01111000,B00001000}
#define R {B11110000,B10001000,B10001000,B11110000,B10001000,B10001000}
#define S {B01110000,B10001000,B01100000,B00010000,B10001000,B01110000}
#define K {B10001000,B10010000,B11100000,B11100000,B10010000,B10001000}
#define T {B11111000,B00100000,B00100000,B00100000,B00100000,B00100000}
#define U {B10001000,B10001000,B10001000,B10001000,B10001000,B01110000}
#define V {B10001000,B10001000,B10001000,B10001000,B01010000,B00100000}
#define W {B10001000,B10001000,B10101000,B10101000,B10101000,B01010000}
#define X {B10001000,B01010000,B00100000,B00100000,B01010000,B10001000}
#define Y {B10001000,B01010000,B00100000,B00100000,B00100000,B00100000}
#define Z {B11111000,B00001000,B00110000,B01100000,B10000000,B11111000}
#define EX {B0,B0,B0,B0,B0,B0,}
#define MARK{B00100000,B01110000,B01110000,B00100000,B00000000,B00100000}
#define APLUS {B01110000,B10001000,B10001000,B10111110,B10001000,B10001000}
#define EXL {B00100000,B00100000,B00100000,B00100000,B00100000,B00111110}
#define HEART {B01110111,B00110110,B00010100,B00001000}
#define ALLON  {B11111111,B11111111,B11111111,B11111111,B11111111,B11111111}
#define SLS {B10000000,B01000000,B00100000,B00010000,B00001000,B00000100}

const int latchPin = D8;        // Pin no.12 on 74HC595 Shift Register
const int clockePin = D5;       // Pin no.11 on 74HC595 Shift Register
const int dataPin = D7;         // Pin no.14 on 74HC595 Shift Register
const int clocke = D1;          // Pin no.14 on 4017 Decade Counter
const int Reset = D2;           // Pin no.15 on 4017 Decade Counter
int i = 0;
long scrolling_word[6];
int array_turn = 0;
byte your_text[30][6] = {S, APLUS, EXL, EX, E, D, U, C, A, T, I, O, N, EX, E, C, SLS, I, C, EX, D, E, P, A, R, T, M, E, N, T,};
// your_text[x][y],     Edit [x] according to the number of letters.

void setup()

{
  Serial.begin(9600);     //intialize OUTPUTS
  pinMode(dataPin, OUTPUT);
  pinMode(clockePin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clocke, OUTPUT);
  pinMode(Reset, OUTPUT);
  digitalWrite(Reset, HIGH);
  digitalWrite(Reset, LOW);
  SPI.begin();
}

void display_word(int loops, byte word_print[][6], int num_patterns, int delay_langth) { // this function displays your symbols
  i = 0;// resets the counter fot the 4017
  for (int g = 0; g < 6; g++) //resets the the long int where your word goes
    scrolling_word[g] = 0;
  for (int x = 0; x < num_patterns; x++) { //main loop, goes over your symbols
    // you will need to find a better way to make the symbols scroll my way is limited for 24 columns

    for (int r = 0; r < 6; r++) //puts the buildes the first symbol
      scrolling_word[r] |= word_print[x][r];
    for (int z = 0; z < 6; z++) { //the sctolling action
      for (int p = 0; p < 6; p++)
        scrolling_word[p] = scrolling_word[p] << 1;
      // end of the scrolling funcion
      for (int t = 0; t < delay_langth; t++) { // delay function, it just loops over the same display
        for (int y = 0; y < 6; y++) { // scaning the display
          if (i == 6) { // counting up to 6 with the 4017
            digitalWrite(Reset, HIGH);
            digitalWrite(Reset, LOW);
            i = 0;
          }
          latchOff();
          SPI.transfer(make_word(0x01000000, y)); // sending the data
          SPI.transfer(make_word(0x00010000, y));
          SPI.transfer(make_word(0x00000100, y));
          latchOn();
          delayMicroseconds(800);//waiting a bit
          latchOff();
          SPI.transfer(0);// clearing the data
          SPI.transfer(0);
          SPI.transfer(0);
          latchOn();
          digitalWrite(clocke, HIGH); //counting up with the 4017
          digitalWrite(clocke, LOW);
          i++;
          delay(0); //This small delay fixes the entire loop for Node Mcu esp8266
        }
      }
    }
  }
  finish_scroll(delay_langth);
}

void finish_scroll(int delay_scroll) { // this function is the same as the funcion above, it just finishing scrolling
  for (int n = 0; n < 24; n++) {
    for (int h = 0; h < 6; h++)
      scrolling_word[h] = scrolling_word[h] << 1;
    for (int w = 0; w < delay_scroll; w++) {
      for (int k = 0; k < 6; k++) {
        if (i == 6) {
          digitalWrite(Reset, HIGH);
          digitalWrite(Reset, LOW);
          i = 0;
        }
        latchOff();
        SPI.transfer(make_word(0x01000000, k));
        SPI.transfer(make_word(0x00010000, k));
        SPI.transfer(make_word(0x00000100, k));
        latchOn();
        delayMicroseconds(800);
        latchOff();
        SPI.transfer(0);
        SPI.transfer(0);
        SPI.transfer(0);
        latchOn();
        digitalWrite(clocke, HIGH);
        digitalWrite(clocke, LOW);
        i++;
        delay(0);//This small delay fixes the entire loop for Node Mcu esp8266
      }
    }
  }
}

byte make_word (long posistion, byte turn) {
  byte dummy_word = 0;
  for (int q = 0; q < 24; q++) {
    if (scrolling_word[turn] & (posistion << q))
      dummy_word |= 0x01 << q;
  }
  return dummy_word;
}

void loop() {
  display_word(1, your_text, 30 , 15);
}

void latchOn()
{
  digitalWrite(latchPin, HIGH);
}

void latchOff()
{
  digitalWrite(latchPin, LOW);
}
