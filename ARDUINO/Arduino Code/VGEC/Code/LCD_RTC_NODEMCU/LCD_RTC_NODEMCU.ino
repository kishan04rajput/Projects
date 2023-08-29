#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "RTClib.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);
RTC_DS1307 RTC;
void setup()
{
  Serial.begin(115200);
  Wire. begin ( 4 , 5 ); // 4.5 I2C of ESP8266
  lcd.begin();
  lcd.backlight();
  RTC. begin ();      // RTC switch
  delay ( 500 );
  RTC. adjust ( DateTime (__DATE__, __TIME__));
  delay ( 1000 );

  // RTC.adjust(DateTime(2018, 9, 28, 14, 53, 0)); //year,month,date,time;


}

void loop()
{
  DateTime now = RTC. now (); // Time = time current RTC
  // Print time
  Serial. print (now. year (), DEC ); // Year
  Serial. print ( '/' );
  Serial. print (now. month (), DEC); // Month
  Serial. print ( '/' );
  Serial. print (now. day (), DEC); // Day
  Serial. print ( ' ' );
  Serial. print (now. hour (), DEC); // Time
  Serial. print ( ':' );
  Serial. print (now. minute (), DEC); // Minutes
  Serial. print ( ':' );
  Serial. print (now. second (), DEC); // Second
  Serial. println ();

  Serial.print(" unixtime = ");
  Serial.print(now.unixtime());
  Serial. println ();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("GTU");

}
