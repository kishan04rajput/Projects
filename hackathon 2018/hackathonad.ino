#include <TimerOne.h>
#include<LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);   //RS,EN,4,5,6,7

#include <SoftwareSerial.h>
SoftwareSerial gps(10, 11); // RX, TX

char str[70];
String gpsString = "";

char *test = "$GPGGA";

String latitude = "";
String longitude = "";

int temp = 0, i;
boolean gps_status = 0;

unsigned int counter = 0;

int b1a = 6;  // L9110 B-1A
int b1b = 9;  // L9110 B-1B

void setup()
{
  lcd.begin(16, 2);
  Serial.begin(9600);
  gps.begin(9600);

  lcd.print("Vehicle Tracking");
  lcd.setCursor(6, 1);
  lcd.print("System");
  delay(2000);
  gsm_init();
  lcd.clear();
  Serial.println("AT+CNMI=2,2,0,0,0");
  lcd.print("GPS Initializing");
  lcd.setCursor(0, 1);
  lcd.print("  No GPS Range  ");
  get_gps();
  delay(2000);
  lcd.clear();
  lcd.print("GPS Range Found");
  lcd.setCursor(0, 1);
  lcd.print("GPS is Ready");
  delay(2000);
  lcd.clear();
  lcd.print("System Ready");
  temp = 0;

  pinMode(b1a, OUTPUT);
  pinMode(b1b, OUTPUT);

  Timer1.initialize(1000000); // set timer for 1sec
  attachInterrupt(0, docount, RISING);  // increase counter when speed sensor pin goes High
  Timer1.attachInterrupt( timerIsr ); // enable the timer
}

void loop()
{
  serialEvent();
  if (temp)
  {
    get_gps();
    tracking();
  }
}

void serialEvent()
{
  while (Serial.available())
  {
    if (Serial.find("Track Vehicle"))
    {
      temp = 1;
      break;
    }
    else
      temp = 0;
  }
}

void gpsEvent()
{
  gpsString = "";
  while (1)
  {
    while (gps.available() > 0)          //checking serial data from GPS
    {
      char inChar = (char)gps.read();
      gpsString += inChar;                   //store data from GPS into gpsString
      i++;
      if (i < 7)
      {
        if (gpsString[i - 1] != test[i - 1])    //checking for $GPGGA sentence
        {
          i = 0;
          gpsString = "";
        }
      }
      if (inChar == '\r')
      {
        if (i > 65)
        {
          gps_status = 1;
          break;
        }
        else
        {
          i = 0;
        }
      }
    }
    if (gps_status)
      break;
  }
}

void gsm_init()
{
  lcd.clear();
  lcd.print("Finding Module..");
  boolean at_flag = 1;
  while (at_flag)
  {
    Serial.println("AT");
    while (Serial.available() > 0)
    {
      if (Serial.find("OK"))
        at_flag = 0;
    }

    delay(1000);
  }

  lcd.clear();
  lcd.print("Module Connected..");
  delay(1000);
  lcd.clear();
  lcd.print("Disabling ECHO");
  boolean echo_flag = 1;
  while (echo_flag)
  {
    Serial.println("ATE0");
    while (Serial.available() > 0)
    {
      if (Serial.find("OK"))
        echo_flag = 0;
    }
    delay(1000);
  }

  lcd.clear();
  lcd.print("Echo OFF");
  delay(1000);
  lcd.clear();
  lcd.print("Finding Network...");
  boolean net_flag = 1;
  while (net_flag)
  {
    Serial.println("AT+CPIN?");
    while (Serial.available() > 0)
    {
      if (Serial.find("+CPIN: READY"))
        net_flag = 0;
    }
    delay(1000);
  }
  lcd.clear();
  lcd.print("Network Found...");
  delay(1000);
  lcd.clear();
}

void get_gps()
{
  gps_status = 0;
  int x = 0;
  while (gps_status == 0)
  {
    gpsEvent();
    int str_lenth = i;
    latitude = "";
    longitude = "";
    int comma = 0;
    while (x < str_lenth)
    {
      if (gpsString[x] == ',')
        comma++;
      if (comma == 2)     //extract latitude from string
        latitude += gpsString[x + 1];
      else if (comma == 4)     //extract longitude from string
        longitude += gpsString[x + 1];
      x++;
    }
    int l1 = latitude.length();
    latitude[l1 - 1] = ' ';
    l1 = longitude.length();
    longitude[l1 - 1] = ' ';
    lcd.clear();
    lcd.print("Lat:");
    lcd.print(latitude);
    lcd.setCursor(0, 1);
    lcd.print("Long:");
    lcd.print(longitude);
    i = 0; x = 0;
    str_lenth = 0;
    delay(2000);
  }
}

void init_sms()
{
  Serial.println("AT+CMGF=1");
  delay(400);
  Serial.println("AT+CMGS=\"+919723327896\"");   //your 10 digit cell no. here
  delay(400);
}

void send_data(String message)
{
  Serial.println(message);
  delay(200);
}

void send_sms()
{
  Serial.write(26);
}

void lcd_status()
{
  lcd.clear();
  lcd.print("Message Sent");
  delay(2000);
  lcd.clear();
  lcd.print("System Ready");
  return;
}

void tracking()
{
  coordinate2dec();
  init_sms();
  send_data("Vehicle Tracking Alert:");
  send_data("Your Vehicle Current Location is:");
  Serial.print("Latitude:");
  send_data(latitude);
  Serial.print("Longitude:");
  send_data(longitude);
  send_data("CAMERA: USERNAME:xxxxx\n PASSWORD:xxxxx");
  //send_data("https://www.google.co.in/maps/@'longitude','latitude',14z");
  send_data("ssprintf();");
  send_data("timerIsr();");
  send_sms();
  delay(2000);
  lcd_status();
}

void coordinate2dec()
{

  //j=0;
  String lat_degree = "";
  for (i = 18; i < 20; i++)   //extract latitude from string
    lat_degree += gpsString[i];

  String lat_minut = "";
  for (i = 20; i < 28; i++)
    lat_minut += gpsString[i];

  String long_degree = "";
  for (i = 30; i < 33; i++)   //extract longitude from string
    long_degree += gpsString[i];

  String long_minut = "";
  for (i = 33; i < 41; i++)
    long_minut += gpsString[i];

  float minut = lat_minut.toFloat();
  minut = minut / 60;
  float degree = lat_degree.toFloat();
  latitude = degree + minut;

  minut = long_minut.toFloat();
  minut = minut / 60;
  degree = long_degree.toFloat();
  longitude = degree + minut;
}

void ssprintf() {
  float lo = longitude.toFloat();
  float la = latitude.toFloat();
  printf("https://www.google.co.in/maps/@%f,%f,14z", lo, la);
}

void docount()  // counts from the speed sensor
{
  counter++;  // increase +1 the counter value
}

void timerIsr()
{
  Timer1.detachInterrupt();  //stop the timer
  Serial.print("BUS Speed: ");
  int rotation = (counter / 20);  // divide by number of holes in Disc
  Serial.print(rotation, DEC);
  //Serial.println(" Rotation per seconds");
  counter = 0; //  reset counter to zero
  Timer1.attachInterrupt( timerIsr );  //enable the timer
}
