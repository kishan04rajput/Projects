//Static wala

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <FS.h>
#include "WEBPAGE1.h"
#include "WEBPAGE2.h"
#include "WEBPAGE3.h"

#ifndef STASSID
#define STASSID "SSID"    //wifi se connect hoga uska name
#define STAPSK  "WatchWord"    //wifi se connect hoga uska password
#define LOGIN_USERNAME "Admin"   //Login_page_username
#define LOGIN_PASSWORD "ADMIN"    //Login_page_password

#endif

const char* ssid = STASSID;
const char* password = STAPSK;

File fsUploadFile; //Uploaded file ka pointer

ESP8266WebServer server(80);

const int led = 13;

String FileName;


//file uploaded successfully
char msg1[] PROGMEM = R"=====(
File Uploaded Successfully....
redirecting to Upload Page
<script>
  setTimeout(function(){window.location.replace(window.location.origin+"/successKuchKoHiMiltiHai");}, 2000);
</script>
)=====";

//File upload hone ke baad phir se second page pe upload karta hai.
void successKuchKoHiMiltiHai(){
  server.send_P(200, "text/html", success);
}

void listAllFiles(){

  File root = SPIFFS.open("/", "w");

  File file = root.openNextFile();

  while(file){

      FileName = file.name();
      Serial.print("FILE: ");
      Serial.println(FileName);
      file = root.openNextFile();
      
  }
}

//Send first page.
void handleHtml(){
//  listAllFiles();
  server.send(200,"text/html",msg);
}

//Send login page.
void handleLogin(){
  server.send_P(200, "text/html", login_page);
}

//Send backend.
void handleBackend(){
  String userName = server.arg("txtUserName");
  String watchWord = server.arg("pwWatchword");
//  char *temp = userName+watchWord;
//  char *backend_page PROGMEM= temp;
//  server.send_P(200, "text/html", backend_page);
  if(userName == LOGIN_USERNAME && watchWord == LOGIN_PASSWORD){
    successKuchKoHiMiltiHai();
  }
  else{
    server.send_P(200, "text/html", err);
    }
}

//Handle file upload server.
void handleFileUpload(){ // upload a new file to the SPIFFS
  HTTPUpload& upload = server.upload();
  if(upload.status == UPLOAD_FILE_START){
    String filename = upload.filename;
    if(!filename.startsWith("/")) 
      filename = "/"+filename;
    Serial.print(F("handleFileUpload Name: ")); 
    Serial.println(filename);
    fsUploadFile = SPIFFS.open(filename, "w");            // Open the file for writing in SPIFFS (create if it doesn't exist)
    filename = String();
  } else if(upload.status == UPLOAD_FILE_WRITE){
    if(fsUploadFile)
      fsUploadFile.write(upload.buf, upload.currentSize); // Write the received bytes to the file
  } else if(upload.status == UPLOAD_FILE_END){
    if(fsUploadFile) {                                    // If the file was successfully created
      fsUploadFile.close();                               // Close the file again
      Serial.print(F("handleFileUpload Size: ")); 
      Serial.println(upload.totalSize);
      server.sendHeader("Location","/success");      // Redirect the client to the success page
      server.send(303);
    } else {
      server.send(500, "text/plain", F("500: couldn't create file"));
    }
  }
}

//File not found ka message.
char message[] PROGMEM = R"=====(
ERROR 404: File Not Found
)=====";

//File not found ka server handle.
void handleNotFound() {
  digitalWrite(led, 1);
  server.send_P(404, "text/plain", message);
  digitalWrite(led, 0);
}

void handleDelete(){
  SPIFFS.remove("/helloworld.txt");
  server.send(200,"text/html",success);
}

void setup(void) {
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
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

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }
  SPIFFS.begin(); // Start the SPI Flash Files System

  server.on("/", handleHtml);

  server.on("/login", handleLogin);

  server.on("/backend", handleBackend);

  server.on("/successKuchKoHiMiltiHai", successKuchKoHiMiltiHai);
  server.on("/Deleted", handleDelete);
  server.on("/helloworld.txt", []() {

    //File download hogi yahan se.
    File download = SPIFFS.open("/helloworld.txt", "r");
    if (download) {
      server.sendHeader("Content-Type", "text/text");
      server.sendHeader("Content-Disposition", "attachment; filename=helloworld.txt");
      server.sendHeader("Connection", "close");
      server.streamFile(download, "application/octet-stream");
      download.close();
      server.sendHeader("Location", "/");     // Redirect the client to the success page
      server.send(303);
    }
    else {
      Serial.println("Error: Reading File...");
    }
  });

  //Send to handle file upload.
  server.on("/datahandling", HTTP_POST,                       // if the client posts to the upload page
  []() {
    server.send(200);
  },                          // Send status 200 (OK) to tell the client we are ready to receive
  handleFileUpload                                    // Receive and save the file
           );


  server.on("/success", []() {       //Success message display karwane ke kaam aata hai!!!!

    server.send_P(200, "text/html", msg1);
  });
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println(F("HTTP server started"));

}

void loop(void) {

  server.handleClient();
  MDNS.update();
}
