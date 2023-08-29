/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-esp8266-input-data-html-form/

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*********/

#include <Arduino.h>
#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#else
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>
#include <SPI.h>
AsyncWebServer server1(80);




const int latchPin = D8;        // Pin no.12 on 74HC595 Shift Register
const int clockePin = D5;       // Pin no.11 on 74HC595 Shift Register
const int dataPin = D7;         // Pin no.14 on 74HC595 Shift Register
const int clocke = D1;          // Pin no.14 on 4017 Decade Counter
const int Reset = D2;           // Pin no.15 on 4017 Decade Counter
int i = 0;
long scrolling_word[6];
int array_turn = 0;



// REPLACE WITH YOUR NETWORK CREDENTIALS
const char* ssid = "SSID";
const char* password = "WatchWord";

const char* PARAM_INPUT_1 = "input1";
/*
   const char* PARAM_INPUT_2 = "input2";
  const char* PARAM_INPUT_3 = "input3";
*/

// HTML web page to handle 3 input fields (input1, input2, input3)
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
    Notification: <input type="text" name="input1">
    <input type="submit" value="Send">
  </form><br>
  
</body></html>)rawliteral";

void dataFunction(String);

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
//  WiFi.begin(ssid, password);
 // if (WiFi.waitForConnectResult() != WL_CONNECTED) {
  //  Serial.println("WiFi Failed!");
  //  return;
 // }
 // Serial.println();
  //Serial.print("IP Address: ");
  //Serial.println(WiFi.localIP());

  // Send web page with input fields to client
  server1.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", index_html);
  });

  // Send a GET request to <ESP_IP>/get?input1=<inputMessage>
  server1.on("/get", HTTP_GET, [] (AsyncWebServerRequest * request) {
    String inputMessage;
    String inputParam;
    // GET input1 value on <ESP_IP>/get?input1=<inputMessage>
    if (request->hasParam(PARAM_INPUT_1)) {
      inputMessage = request->getParam(PARAM_INPUT_1)->value();
      inputParam = PARAM_INPUT_1;
    }
    // GET input2 value on <ESP_IP>/get?input2=<inputMessage>
    //else if (request->hasParam(PARAM_INPUT_2)) {
    //inputMessage = request->getParam(PARAM_INPUT_2)->value();
    //inputParam = PARAM_INPUT_2;
    //}
    // GET input3 value on <ESP_IP>/get?input3=<inputMessage>
    //else if (request->hasParam(PARAM_INPUT_3)) {
    //inputMessage = request->getParam(PARAM_INPUT_3)->value();
    //inputParam = PARAM_INPUT_3;
    //}
    /*
       else {
      inputMessage = "No message sent";
      inputParam = "none";
      }
    */
    dataFunction(inputMessage);
    Serial.println(inputMessage);
    request->send(200, "text/html", R"rawliteral(
<!DOCTYPE HTML>
<html>
  <head>
    <title>ESP Input Form</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <script>
    function alertNotification(){
      alert("Message has been sent.");
    }
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
  <body onload="alertNotification()">
  <form action="/get" name="myForm" onSubmit="return validateForm()">
    Notification: <input type="text" name="input1">
    <input type="submit" value="Send">
  </form><br>
  
</body></html>)rawliteral");
  });
  server1.onNotFound(notFound);
  server1.begin();




  
  //Serial.begin(9600);     //intialize OUTPUTS
  Serial.begin(115200);
  pinMode(dataPin, OUTPUT);
  pinMode(clockePin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clocke, OUTPUT);
  pinMode(Reset, OUTPUT);
  digitalWrite(Reset, HIGH);
  digitalWrite(Reset, LOW);
  SPI.begin();

  //WIFI

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server1.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

//void loop() {

//}
/*
   HTML form
  <form action="/get">
    input2: <input type="text" name="input2">
    <input type="submit" value="Submit">
  </form><br>
  <form action="/get">
    input3: <input type="text" name="input3">
    <input type="submit" value="Submit">
  </form>
*/
