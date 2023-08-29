#include <Arduino.h>
#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#else
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>

//LED
int ledPin = LED_BUILTIN; // GPIO13---D7 of NodeMCU

//beetrix
const int latchPin = D8;        // Pin no.12 on 74HC595 Shift Register
const int clockePin = D5;       // Pin no.11 on 74HC595 Shift Register
const int dataPin = D7;         // Pin no.14 on 74HC595 Shift Register
const int clocke = D1;          // Pin no.14 on 4017 Decade Counter
const int Reset = D2;           // Pin no.15 on 4017 Decade Counter
int i = 0;
long scrolling_word[6];
int array_turn = 0;
String inputMessage;

//RESET
int rst = A0;

//SERVER INTIALIZATION
AsyncWebServer server(80);

//NETWORK CREDENTIALS
const char* ssid = "SSID";
const char* password = "WatchWord";
const char* PARAM_INPUT_1 = "input1";

//HTML WEBPAGE
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html>
  <head>
    <title>ESP Input Form</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <script>
    function validateForm() {
      var x = document.forms["myForm"]["input1"].value;
      if (x == "") {
          alert("Textbox cannot be empty");
          return false;
      }
    }
    </script>
    <style>
    </style>
  </head>
  <body>
  <form action="/get" name="myForm" onSubmit="return validateForm()">
    <label for="input1">Notification:</label> <input type="text" name="input1" autofocus id="input1">
    <input type="submit" value="Send">
  </form><br>  
</body></html>)rawliteral";

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void setup() {
  pinMode(rst, OUTPUT);
  digitalWrite(rst, HIGH);

  //beetrix
  pinMode(dataPin, OUTPUT);
  pinMode(clockePin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clocke, OUTPUT);
  pinMode(Reset, OUTPUT);
  digitalWrite(Reset, HIGH);
  digitalWrite(Reset, LOW);
  SPI.begin();

  //LED
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);

  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Failed!");
    return;
  }
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Send web page with input fields to client
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", index_html);
  });

  // Send a GET request to <ESP_IP>/get?input1=<inputMessage>
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest * request) {
    //   String inputMessage;
    String inputParam;
    // GET input1 value on <ESP_IP>/get?input1=<inputMessage>
    if (request->hasParam(PARAM_INPUT_1)) {
      inputMessage = request->getParam(PARAM_INPUT_1)->value();
      inputParam = PARAM_INPUT_1;
    }
    
    int count = 0;
    while (inputMessage[count] != '\0')
      Serial.println(inputMessage[count++]);

    request->send(200, "text/html", R"rawliteral(
<!DOCTYPE HTML>
<html>
<body bgcolor="skyblue">
 <script>
    function alertNotification(){
      alert("Message has been sent.");
    }
    </script>
    <H1><FONT COLOR="DARKCYAN"><CENTER>COLLEGE TIME TABLE</FONT></H1>
<table border="2" cellspacing="3" align="center">
<tr>
 <td align="center">
 <td>8:30-9:30
 <td>9:30-10:30
 <td>10:3-11:30
 <td>11:30-12:30
 <td>12:30-2:00
 <td>2:00-3:00
 <td>3:00-4:00
 <td>4:00-5:00
</tr>
<tr>
 <td align="center">MONDAY
 <td align="center">---<td align="center"><font color="blue">SUB1<br>
 <td align="center"><font color="pink">SUB2<br>
 <td align="center"><font color="red">SUB3<br>
 <td rowspan="6"align="center">L<br>U<br>N<br>C<br>H
 <td align="center"><font color="maroon">SUB4<br>
 <td align="center"><font color="brown">SUB5<br>
 <td align="center">counselling class
</tr>
<tr>
 <td align="center">TUESDAY
 <td align="center"><font color="blue">SUB1<br>
 <td align="center"><font color="red">SUB2<br>
 <td align="center"><font color="pink">SUB3<br>
 <td align="center">---
 <td align="center"><font color="orange">SUB4<BR>
 <td align="center"><font color="maroon">SUB5<br>
 <td align="center">library
</tr>
<tr>
 <td align="center">WEDNESDAY
 <td align="center"><font color="pink">SUB1<br>
 <td align="center"><font color="orange">SUB2<BR>
 <td align="center"><font color="brown">SWA<br>
 <td align="center">---
 <td colspan="3" align="center"><font color="green"> lab
</tr>
<tr>
 <td align="center">THURSDAY
 <td align="center">SUB1<br>
 <td align="center"><font color="brown">SUB2<br>
 <td align="center"><font color="orange">SUB3<BR>
 <td align="center">---
 <td align="center"><font color="blue">SUB4<br>
 <td align="center"><font color="red">SUB5<br>
 <td align="center">library
</tr>
<tr>
 <td align="center">FRIDAY
 <td align="center"><font color="orange">SUB1<BR>
 <td align="center"><font color="maroon">SUB2<br>
 <td align="center"><font color="blue">SUB3<br>
 <td align="center">---
 <td align="center"><font color="pink">SUB4<br>
 <td align="center"><font color="brown">SUB5<br>
 <td align="center">library
</tr>
<tr>
 <td align="center">SATURDAY
 <td align="center"><font color="red">SUB1<br>
 <td colspan="3" align="center">seminar
 <td align="center"><font color="pink">SUB4<br>
 <td align="center"><font color="brown">SUB5<br>
 <td align="center">library
</tr>
<tr>
 <td align="center" colspan="9"> TO CHANGE NOTIFICATION CLICK ON:<a href="/"><button autofocus>UPDATE </button></a>
</tr>
<body onload="alertNotification()">
</body></html>)rawliteral");
  });
  server.onNotFound(notFound);
  server.begin();
}
