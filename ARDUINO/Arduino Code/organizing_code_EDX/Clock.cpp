/* file clock.cpp */
#include "Arduino.h"
#include "Clock.h"

char getTime() {
   Serial.println("getTime");
   return 0;
}

char getMinute() {
   Serial.println("getTime");
   return 0;
}

char getSecond() {
   Serial.println("getTime");
   return 0;
}

char getDay() {
   Serial.println("getTime");
   return 0;
}

char getMonth() {
   Serial.println("getTime");
   return 0;
}

char getAnnee() {
   Serial.println("getTime");
   return 0;
}


void setHour(char val) {
   Serial.print("setHour : ");
   Serial.println(val, DEC);
}

void setMinute(char val) {
   Serial.print("setMinute : ");
   Serial.println(val, DEC);
}

void setSecond(char val) {
   Serial.print("setSecond : ");
   Serial.println(val, DEC);
}

void setDay(char val) {
   Serial.print("setDay : ");
   Serial.println(val, DEC);
}

void setMonth(char val) {
   Serial.print("setMonth : ");
   Serial.println(val, DEC);
}

void setYear(char val) {
   Serial.print("setYear : ");
   Serial.println(val, DEC);
}


void printDate() {
   Serial.println("printDate");
}

void printTime() {
   Serial.println("printTime");
}

void printDateTime() {
   Serial.println("printDateTime");
}
