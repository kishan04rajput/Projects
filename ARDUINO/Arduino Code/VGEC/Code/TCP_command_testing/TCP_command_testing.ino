
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "RTClib.h"
int produc=0;
 const int trigPin = D7;
const int echoPin = D8;

long duration, inches, cm;



LiquidCrystal_I2C lcd(0x27, 16, 2);
RTC_DS1307 RTC;


const char *ssid = "IOT";
const char *password = "123456789";

String Essid = "";                    //EEPROM Network SSID
String Epass = "";                    //EEPROM Network Password

ESP8266WebServer server(80);


const char* host = "103.232.124.170";
const int port = 15054;


String deviceId = "";

String voltage = "12";


int long tyme = 1549705181;
int long ctyme = 0;
int long dis_tyme = 0;
int long rtyme = 0;

WiFiClient client;


unsigned long d_tim = 0;
unsigned long h_tim = 0;
unsigned long s_time = 0;


boolean c_flag = true;

long c_index = 0;
long p_index = 0;



boolean flag = true;






void setup()
{
 
  Wire. begin (4, 5); // 4,5 I2C of ESP8266 D1 SCL D2 SDA
  RTC. begin ();  // RTC switch
  
 digitalWrite(D3, 0);
 digitalWrite(D4, 0);
 digitalWrite(D5, 0);
 digitalWrite(D6, 0);
 
  lcd.begin();
  lcd.backlight();
  


  EEPROM.begin(512);
  Serial.begin(115200);

  


  WiFi.mode(WIFI_AP_STA);
  delay(1000);
  WiFi.softAP(ssid, password);
  delay(1000);

  Serial.println ("start");
  Serial.println();
  Serial.print("Configuring access point...");
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);


  String macadd = WiFi.macAddress();
  deviceId += macadd.substring(1, 2);
  deviceId += macadd.substring(3, 5);
  deviceId += macadd.substring(6, 8);
  deviceId += macadd.substring(9, 11);
  deviceId += macadd.substring(12, 14);
  deviceId += macadd.substring(15, 17);

  Serial.println(deviceId);

  //deviceId = "AAAAAAAAAAA";

  server.on("/", wlanPageHandler);

  server.begin();

  Serial.println("HTTP server started");








  for (int i = 0; i < 32; ++i)                               //Reading SSID
  {
    Essid += char(EEPROM.read(i));
  }


  for (int i = 32; i < 96; ++i)                            //Reading Password
  {
    Epass += char(EEPROM.read(i));
  }



  Essid = "VARDHAN";                  //your hotspot id and password
  Epass = "nopassword";

  if ( Essid.length() > 1 )
  {
    Serial.println(Essid);                             //Print SSID
    Serial.println(Epass);

    WiFi.begin(Essid.c_str(), Epass.c_str());   //c_str()
  }
  c_flag = true;
 // pinMode(D5, INPUT);
//  attachInterrupt(D5, isr1, FALLING);      //product
  //pinMode(D6, INPUT_PULLUP);
//  attachInterrupt(D6, isr2, FALLING);   //rpm



//  myservo.attach(2); //D4 nodemcu

  pinMode(D0, OUTPUT);

}


void loop()
{
  server.handleClient();
// if(Serial.available()>0)
{
   // data=Serial.readString();
  // c_flag=true; 
}
pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
inches = microsecondsToInches(duration);
Serial.print(inches);
  Serial.print("in, ");
   delay(1000);
  
if (inches<6)
{   
  Serial.print("lesser distance");
  digitalWrite(D3,0);
  digitalWrite(D4,1);
  delay(1000);
  digitalWrite(D4,0);
  }

//  if (!digitalRead(D5) && flag)
//  {
//    produc++;
//   
//
//    // flag = false;
//    // delay(100);
//  }
//  if (digitalRead(D5))
//  {
//    flag = true;
//  }
//


  unsigned long tym = millis();
  while ((client.available() > 0) || ((millis() - tym) < 300))
  {
    if (client.available() > 0)
    {

      String a = client.readStringUntil(')');
      Serial.println(a);
      decodecmd(a);
      client.flush();
    }
  }



  if (WiFi.status() == WL_CONNECTED)
  {
    dis_tyme = 0;
    if (c_flag)
    {
      Serial.println("WiFi connected");
      //  Serial.print("IP address: ");
      //Serial.println(WiFi.localIP());
      

      if (!client.connect(host, port))
      {
        Serial.println("connection failed");
        return;
      }
      Serial.println("connected");
      // String data = ("(" + deviceId + "DH" + ")");
      String data = ("(" + deviceId + "DR" + "V01)");
 Serial.println(data);
    client.print(data);


      c_flag = false;
      d_tim = millis();
    }



    if ((millis() - d_tim) > 5000)
    {



      disp();
      d_tim = millis();
      
      Serial.println("(" + deviceId + "DSP" + String(produc) + "R" + String(100) + "C" + String(35 ) + "V" + voltage + "A" + String(0.5 ) + "I" + c_index + "T" + String(getnewtime()) + ")");
      client.print("(" + deviceId + "DSP" + String(produc) + "R" + String(100) + "C" + String(35) + "V" + voltage + "A" + String(0.5 ) + "I" + c_index + "T" + String(getnewtime()) + ")");



    }

    if ((millis() - h_tim) > 60000)
    {
      Serial.println("(" + deviceId + "DA)");
      client.print("(" + deviceId + "DA)");
      h_tim = millis();
    }



  }

  else
  {
    c_flag = true;
    if ((millis() - dis_tyme) > 10000)
    {
      Serial.println("WiFi not-connected");
      WiFi.begin(Essid.c_str(), Epass.c_str());   //c_str()
      dis_tyme = millis();
    }
    if ((millis() - d_tim) > 5000)
    {
      disp();
      d_tim = millis();


    }

  }



}

long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}



void wlanPageHandler()
{
  // Check if there are any GET parameters




  if (server.hasArg("ssid"))
  {
    if (server.hasArg("password"))
    {
      // WiFi.begin(server.arg("ssid").c_str(), server.arg("password").c_str());



      ClearEeprom();//First Clear Eeprom

      Essid = server.arg("ssid");
      Epass = server.arg("password");

      WiFi.begin(Essid.c_str(), Epass.c_str());   //c_str()

      // Serial.print("wifi begin status=");
      // Serial.println(WiFi.begin(Essid.c_str(), Epass.c_str()));   //c_str()


      for (int i = 0; i < Essid.length(); ++i)
      {
        EEPROM.write(i, Essid[i]);
      }

      for (int i = 0; i < Epass.length(); ++i)
      {
        EEPROM.write(32 + i, Epass[i]);
      }
      EEPROM.commit();

    }
    else
    {
      WiFi.begin(server.arg("ssid").c_str());
    }





  }

  String response_message = "";
  response_message += "<html>";
  response_message += "<head><title>ACDC Home Automation Webserver</title></head>";
  response_message += "<body style=\"background-color:MediumSeaGreen\"><h1><center>WLAN Settings</center></h1>";

  if (WiFi.status() == WL_CONNECTED)
  {
    response_message += "Status: Connected<br>";

  }
  else
  {
    response_message += "Status: Disconnected<br>";

  }


  response_message += "<p>To connect to a WiFi network, please select a network...</p>";

  // Get number of visible access points
  int ap_count = WiFi.scanNetworks();

  if (ap_count == 0)
  {
    response_message += "No access points found.<br>";
  }
  else
  {
    response_message += "<form method=\"get\">";

    // Show access points
    for (uint8_t ap_idx = 0; ap_idx < ap_count; ap_idx++)
    {
      response_message += "<input type=\"radio\" name=\"ssid\" value=\"" + String(WiFi.SSID(ap_idx)) + "\">";
      response_message += String(WiFi.SSID(ap_idx)) + " (RSSI: " + WiFi.RSSI(ap_idx) + ")";
      (WiFi.encryptionType(ap_idx) == ENC_TYPE_NONE) ? response_message += " " : response_message += "*";
      response_message += "<br><br>";
    }

    response_message += "WiFi password (if required):<br>";
    response_message += "<input type=\"text\" name=\"password\"><br>";
    response_message += "<input type=\"submit\" value=\"Connect\">";
    response_message += "</form>";
  }

  response_message += "</body></html>";

  server.send(200, "text/html", response_message);


}

void ClearEeprom()
{
  Serial.println("Clearing Eeprom");
  for (int i = 0; i < 96; ++i) {
    EEPROM.write(i, 0);
  }
}
//void isr1()
//{
//  product++;
//}


void isr2()
{

}


void disp()
{
  lcd.clear();
  lcd.setCursor(0, 0);
}
