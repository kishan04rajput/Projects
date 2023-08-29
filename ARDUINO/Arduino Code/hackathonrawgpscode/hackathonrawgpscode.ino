#include<LiquidCrystal.h>
LiquidCrystal lcd(7,6,5,4,3,2);

#include <SoftwareSerial.h>
SoftwareSerial gps(10,11); // RX, TX

String gpsString="";

char *test="$GPGGA";

String latitude="";
String longitude="";


int temp=0,i;
boolean gps_status=0;

void setup(){
  Serial.begin(9600);
  lcd.print("GPS INITIALIZING");
  lcd.setCursor(0,1);
  lcd.print("  NO GPS RANGE   ");
  get_gps();
  delay(2000);
  lcd.clear();
  lcd.print("GPS RANGE FOUND");
  delay(2000);
  lcd.clear();
  lcd.print("SYSTEM READY");
  temp=0;  
}

void loop(){
  if(temp)
  {
    get_gps();
    //tracking();
  }
}

void get_gps(){
  gps_status=0;
  int x=0;
  while(gps_status==0){
    gpsEvent();
    int str_length=i;
    latitude="";
    longitude="";
    int comma=0;
    while(x<str_length){
      if(gpsString[x]==',')
      comma++;
      if(comma==2)
      latitude+=gpsString[x+1];
      else if(comma==4)
      longitude+=gpsString[x+1];
      x++;
    }
    int l1=latitude.length();
    latitude[l1-1]=' ';
    l1=longitude.length();
    longitude[l1-1]=' ';
    lcd.clear();
    lcd.print("Lat:");
    lcd.print(latitude);
    lcd.setCursor(0,1);
    lcd.print("Long:");
    lcd.print(longitude);
    i=0;x=0;
    str_length=0;
    delay(2000);
  }
}

void gpsEvent()
{
  gpsString="";
  while(1)
  {
   while (gps.available()>0)            //checking serial data from GPS
   {
    char inChar = (char)gps.read();
     gpsString+= inChar;                    //store data from GPS into gpsString
     i++;
     if (i < 7)                      
     {
      if(gpsString[i-1] != test[i-1])         //checking for $GPGGA sentence
      {
        i=0;
        gpsString="";
      }
     }
    if(inChar=='\r')
    {
     if(i>65)
     {
       gps_status=1;
       break;
     }
     else
     {
       i=0;
     }
    }
  }
   if(gps_status)
    break;
  }
}

