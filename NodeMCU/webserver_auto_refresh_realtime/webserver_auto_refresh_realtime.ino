#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// Replace with your network credentials
const char* ssid = "SSID"; //Enter Wi-Fi SSID
const char* password =  "WatchWord"; //Enter Wi-Fi Password

ESP8266WebServer server(80);   //instantiate server at port 80 (http port)

String page = "";
String text = "";
double data;
void setup(void) {
  pinMode(D1, INPUT);
  pinMode(D0, OUTPUT);
  delay(1000);
  Serial.begin(115200);
  WiFi.begin(ssid, password); //begin WiFi connection
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.on("/data.txt", []() {
    text = (String)data;
    server.send(200, "text/html", text);
  });
  server.on("/", []() {
    page = "<h1>BUTTON STATE:&nbsp;<span id=\"data\">""</span></h1>\r\n";
    page += "<script>\r\n";
    page += "var x = setInterval(function() {loadData(\"data.txt\",updateData)}, 1000);\r\n";
    page += "function loadData(url, callback){\r\n";
    page += "var xhttp = new XMLHttpRequest();\r\n";
    page += "xhttp.onreadystatechange = function(){\r\n";
    page += " if(this.readyState == 4 && this.status == 200){\r\n";
    page += " callback.apply(xhttp);\r\n";
    page += " }\r\n";
    page += "};\r\n";
    page += "xhttp.open(\"GET\", url, true);\r\n";
    page += "xhttp.send();\r\n";
    page += "}\r\n";
    page += "function updateData(){\r\n";
    page += "document.getElementById(\"data\").innerHTML = ((this.responseText==1)?\"ON\":\"OFF\");\r\n";
    page += "}\r\n";
    page += "</script>\r\n";
    server.send(200, "text/html", page);
  });

  server.begin();
  Serial.println("Web server started!");
}

void loop(void) {
  int data1 = digitalRead(D1);
  data = data1;
  if (data1 == HIGH)
    digitalWrite(D0, HIGH);
  else
    digitalWrite(D0, LOW);
  delay(121);
  Serial.println(data);
  server.handleClient();
}
