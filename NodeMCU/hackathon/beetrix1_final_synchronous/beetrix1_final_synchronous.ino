#include <SPI.h>
#include "MHBS.h"
#include "CHARACTERS.h"
//int counter = 0;
//byte your_text[400][6] = {};
void display_word(int loops, byte word_print[][6], int num_patterns, int delay_langth) { // this function displays your symbols
  i = 0;// resets the counter fot the 4017
  for (int g = 0; g < 6; g++) //resets the the long int where your word goes
    scrolling_word[g] = 0;
  for (int x = 0; x < num_patterns; x++) { //main loop, goes over your symbols
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
  character();
  display_word(1, your_text, counter , 15);
  if (WL_CONNECTED)
    digitalWrite(ledPin, LOW);
  else
    digitalWrite(ledPin, LOW);
      server.handleClient();
      MDNS.update();
}

void latchOn()
{
  digitalWrite(latchPin, HIGH);
}

void latchOff()
{
  digitalWrite(latchPin, LOW);
}
