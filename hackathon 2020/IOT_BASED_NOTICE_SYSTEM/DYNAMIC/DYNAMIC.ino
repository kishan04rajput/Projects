#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <FS.h>

#include "./LoginPage.h"
#include "./BackEndProcess.h"
#include "./HomePage.h"
// #include "./api.h"

#ifndef STASSID
#define STASSID "SSID"
#define STAPSK "WatchWord"
#endif

#define USERNAME "admin"
#define PWORD "password"

const char *ssid = STASSID;
const char *password = STAPSK;

ESP8266WebServer server(80);

const int led = 13;
String userName = "";
String watchWord = "";

const char *successMsg PROGMEM = R"=====(
    <body>
        File Uploaded Sucessfully.....
        <script>
            setTimeout(()=>{
                  window.location.replace(window.location.origin+"/backend");
            }, 2000);
        </script>
    </body>
)=====";

void handleLogin() // Handle Login request
{
    server.send_P(200, "text/html", login_page);
}

void handleBackend()
{
    String tmpUserName = server.arg("txtUserName");
    String tmpPWord = server.arg("pwWatchword");
    if (tmpUserName == USERNAME && tmpPWord == PWORD)
    {
        userName = USERNAME;
        watchWord = PWORD;
        server.send_P(200, "text/html", success);
    }
    else
    {
        server.send_P(200, "text/html", err);
    }
}
void authenticate()
{
    if (userName != USERNAME && watchWord != PWORD)
    {
        server.send(401, "text/plain", "Error: Access Denied");
    }
}
File fsUploadFile;

void handleFileUpload()
{ // upload a new file to the SPIFFS
    HTTPUpload &upload = server.upload();
    if (upload.status == UPLOAD_FILE_START)
    {
        String filename = upload.filename;
        if (!filename.startsWith("/"))
            filename = "/" + filename;
        Serial.print(F("handleFileUpload Name: "));
        Serial.println(filename);
        fsUploadFile = SPIFFS.open(filename, "w"); // Open the file for writing in SPIFFS (create if it doesn't exist)
        filename = String();
    }
    else if (upload.status == UPLOAD_FILE_WRITE)
    {
        if (fsUploadFile)
            fsUploadFile.write(upload.buf, upload.currentSize); // Write the received bytes to the file
    }
    else if (upload.status == UPLOAD_FILE_END)
    {
        if (fsUploadFile)
        {                         // If the file was successfully created
            fsUploadFile.close(); // Close the file again
            Serial.print(F("handleFileUpload Size: "));
            Serial.println(upload.totalSize);
            server.sendHeader("Location", "/success"); // Redirect the client to the success page
            server.send(303);
        }
        else
        {
            server.send(500, "text/plain", F("500: couldn't create file"));
        }
    }
}

void handleSuccess()
{
    // authenticate();
    server.send_P(200, "text/html", successMsg);
}

void handleRoot()
{
    digitalWrite(led, 1);
    server.send(200, "text/plain", "hello from esp8266!");
    digitalWrite(led, 0);
}

void sendFileJsonData()
{
    Dir dir = SPIFFS.openDir("");
    String data = "[\n";
    String filename;
    int i = 1;
    while (dir.next())
    {
        data += "{\n";
        data += "id: " + (i++);
        data += "filename: " + dir.fileName();
        data += "},\n";
    }
    data += "]";
    server.send(200, "text/json", data);
}

void handleNotFound()
{
    //   String message = "File Not Found\n\n";
    //   message += "URI: ";
    //   message += server.uri();
    //   message += "\nMethod: ";
    //   message += (server.method() == HTTP_GET) ? "GET" : "POST";
    //   message += "\nArguments: ";
    //   message += server.args();
    //   message += "\n";
    //   for (uint8_t i = 0; i < server.args(); i++) {
    //     message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    //   }
    server.send(404, "text/plain", F("File Not Found\n\n"));
    digitalWrite(led, 0);
}

void setup(void)
{
    pinMode(led, OUTPUT);
    digitalWrite(led, 0);
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.println("");

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println(F(""));
    Serial.print(F("Connected to "));
    Serial.println(ssid);
    Serial.print(F("IP address: "));
    Serial.println(WiFi.localIP());

    if (MDNS.begin("esp8266"))
    {
        Serial.println("MDNS responder started");
    }

    server.on("/", handleRoot);

    server.on("/login", handleLogin);

    server.on("/backend", handleBackend);

    server.on("/success", handleSuccess);

    server.on(
        "/datahandling", HTTP_POST,
        []() { server.send(200); },
        handleFileUpload);

    server.on("/fileData", sendFileJsonData);

    server.onNotFound(handleNotFound);

    server.begin();
    Serial.println("HTTP server started");
}

void loop(void)
{
    server.handleClient();
    MDNS.update();
}
